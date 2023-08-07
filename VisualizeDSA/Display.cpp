#include "Display.hpp"
#include "Layout.hpp"
#include "Tools.hpp"
#include "Animation.hpp"

void Display::setup()
{
	screenShape.setSize(Layout::DisplayScreen::size);
	screenShape.setPosition(Layout::DisplayScreen::pos);
	screenShape.setFillColor(Layout::DisplayScreen::fillColor);
	screenShape.setOutlineColor(Layout::DisplayScreen::outlineColor);
	screenShape.setOutlineThickness(Layout::DisplayScreen::outlineThickness);
	screenShape.setCornerPointCount(Layout::cornerPointCount);
	screenShape.setCornersRadius(Layout::DisplayScreen::cornerRadius);

	mouseDetection.setSize(Layout::DisplayScreen::size);
	mouseDetection.setPosition(Layout::DisplayScreen::pos);

	view.setViewport(sf::FloatRect(screenShape.getPosition().x / Layout::Window::width, screenShape.getPosition().y / Layout::Window::height, screenShape.getSize().x / Layout::Window::width, screenShape.getSize().y / Layout::Window::height));
	
	viewTarget = sf::FloatRect(0, Layout::Window::height + 5, screenShape.getSize().x, screenShape.getSize().y);
	view.reset(viewTarget);
	
	control.setup();
	
	started = 0;
}

void Display::move(sf::FloatRect& rect, sf::Vector2f delta) {
	rect.left = std::min(std::max(rect.left + delta.x, baseView.left), baseView.left + baseView.width - viewTarget.width);
	rect.top = std::min(std::max(rect.top + delta.y, baseView.top), baseView.top + baseView.height - viewTarget.height);
}

void Display::zoom(sf::FloatRect& rect, sf::Vector2f mousePosition, float ratio)
{
	mousePosition -= screenShape.getPosition();
	float rx = (mousePosition.x) / screenShape.getSize().x;
	float ry = (mousePosition.y) / screenShape.getSize().y;

	float px = viewTarget.left + viewTarget.width * rx;
	float py = viewTarget.top + viewTarget.height * ry;
	
	rect.width = std::max(std::min(rect.width * ratio, baseView.width), baseView.width / 8);
	rect.height = std::max(std::min(rect.height * ratio, baseView.height), baseView.height / 8);

	rect.left = std::min(std::max(px - rect.width * rx, baseView.left), baseView.left + baseView.width - viewTarget.width);
	rect.top = std::min(std::max(py - rect.height * ry, baseView.top), baseView.top + baseView.height - viewTarget.height);
}

void Display::handleEvent(sf::RenderWindow& window, sf::Event event)
{
	control.handleEvent(window, event);
	mouseDetection.handleEvent(window, event);

	if (mouseDetection.isHolding()) {
		sf::Vector2f mousePosition = Tools::Mouse::getPosition(window);
		if (holdingPosition.x >= 0) {
			move(viewTarget, holdingPosition - mousePosition);
		}
		holdingPosition = mousePosition;
	}
	else {
		holdingPosition = sf::Vector2f(-1, -1);
	}

	if (mouseDetection.isFocusing()) {
		if (event.type == sf::Event::MouseWheelScrolled) {
			if (event.mouseWheelScroll.delta < 0) {
				zoom(viewTarget, Tools::Mouse::getPosition(window), zoomRatio);
			}
			else {
				zoom(viewTarget, Tools::Mouse::getPosition(window), 1.0000 / zoomRatio);
			}
		}
	}
}

void Display::update()
{
	control.update();
	mouseDetection.update();
	view.reset(viewTarget);

	if (started) {
		int id = control.getCurrent();
		if (prev && prev != corSource[id]) {
			prev->setOutlineColor(sf::Color::White);
		}
		prev = corSource[id];
		if (prev)
			prev->setOutlineColor(sf::Color::Green);
	}
}

void Display::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(screenShape);
	target.draw(control);
	if (started) {		
		target.setView(view);
		int id = control.getCurrent();
		if (idLeft[id] == id) {
			target.draw(layers[control.getCurrent()]);
		}
		else {
			target.draw(Animation::getLayer(layers[idLeft[id]], layers[idRight[id]], 1.f * (id - idLeft[id]) / (idRight[id] - idLeft[id])));
		}
		target.setView(target.getDefaultView());
	}
	for (auto& text : textMap) {
		target.draw(*text.second);
	}
}


void Display::addVirtualLayer(float time, std::string s)
{
	layers.push_back(Layer());
	if (textMap.find(s) == textMap.end()) 
		corSource.push_back(nullptr);
	else 
		corSource.push_back(textMap[s]);
	
	control.addTime(time);
	if (!idLeft.size()) idLeft.push_back(0);
	else idLeft.push_back(idLeft.back());
}

void Display::addLayer(Layer layer, float time, std::string s)
{
	layers.push_back(layer);
	if (textMap.find(s) == textMap.end())
		corSource.push_back(nullptr);
	else
		corSource.push_back(textMap[s]);
	control.addTime(time);
	idLeft.push_back(idLeft.size());
}

void Display::setSource(std::vector<std::string> source)
{
	textMap.clear();
	float height = 0, width = 0;
	for (std::string s : source) {
		textMap.emplace(s, nullptr);
		sf::Text* &text = textMap.find(s)->second;
		text = new sf::Text();
		text->setFont(*Resources::Font::courier);
		text->setCharacterSize(30);
		text->setFillColor(Layout::workplaceOutline);
		text->setOutlineColor(sf::Color::White);
		text->setOutlineThickness(1);
		text->setString(s);
		height += text->getLocalBounds().height;
		width = std::max(width, text->getLocalBounds().width);
	}

	sf::Vector2f pos = Layout::DisplayScreen::pos + Layout::DisplayScreen::size - sf::Vector2f(width + 20, height + 20 + 7 * (source.size()));
	for (std::string s : source) {
		sf::Text* &text = textMap.find(s)->second;
		text->setPosition(pos);
		pos.y += text->getLocalBounds().height + 7;
	}
}

void Display::start()
{
	if (layers.size() == 0) return;
	started = 1;
	idRight.resize(idLeft.size());
	int id = (int)idLeft.size() - 1;
	for (int i = id; i >= 0; --i) {
		if (idLeft[i] == i) id = i;
		idRight[i] = id;
	}
	control.start();

	sf::Vector2f maxCoord(0, 0);
	for (Layer layer : layers) {
		sf::Vector2f coord = layer.getMaxCoord();
		if (coord.x > maxCoord.x) maxCoord.x = coord.x;
		if (coord.y > maxCoord.y) maxCoord.y = coord.y;
	}

	float t = std::max((maxCoord.x + 100) / screenShape.getSize().x, (maxCoord.y + 100 - Layout::Window::height - 5) / screenShape.getSize().y);
	
	viewTarget = sf::FloatRect(0, Layout::Window::height + 5, screenShape.getSize().x, screenShape.getSize().y);
	viewTarget.width = t * screenShape.getSize().x;
	viewTarget.height = t * screenShape.getSize().y;

	view.reset(viewTarget);
	baseView = viewTarget;
}

void Display::clear()
{
	layers.clear();
	control.clear();
	idLeft.clear();
	idRight.clear();
	corSource.clear();
	started = 0;
}

bool Display::isPlaying() const
{
	return started;
}
