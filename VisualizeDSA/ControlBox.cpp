#include "ControlBox.hpp"
#include "Layout.hpp"
#include "Resources.hpp"
#include "Tools.hpp"

void ControlBox::setupButtons()
{

	sf::Vector2f pos = Layout::ControlBox::pos, size = Layout::ControlBox::size;
	sf::Vector2f center = pos + sf::Vector2f(size.x / 2, size.y / 2);
	sf::Vector2f buttonSize = Layout::ControlBox::buttonSize;
	//std::cout << std::endl;


	//const sf::Uint32 text[] = { 9658,9658,108,9668, 0 }; 
	// play button
	bplay.create(center - sf::Vector2f(buttonSize.x / 2, buttonSize.y / 2), buttonSize);
	bplay.setRadius(bplay.getSize().y / 2);
	sf::Uint32 play[] = { 9658, 0 };
	bplay.setText(play, Resources::Font::arial);
	bplay.text->setPosition(bplay.text->getPosition() + sf::Vector2f(2, 0));
	
	// stop button
	bstop.create(center - sf::Vector2f(buttonSize.x / 2, buttonSize.y / 2), buttonSize);
	bstop.setRadius(bstop.getSize().y / 2);
	
	sf::Uint32 stop[] = { 9612, 9612, 0 };
	bstop.setText(stop, Resources::Font::arial);

	// forw button
	sf::Vector2f playPos = bplay.getPosition();
	bforw.create(playPos + sf::Vector2f(+Layout::ControlBox::buttonSpacing + buttonSize.x, 0), buttonSize);
	bforw.setRadius(bforw.getSize().y / 2);

	sf::Uint32 forw[] = { 9658,108, 0 };
	bforw.setText(forw, Resources::Font::arial);
	
	// end button
	sf::Vector2f forwPos = bforw.getPosition();
	bend.create(forwPos + sf::Vector2f(+Layout::ControlBox::buttonSpacing + buttonSize.x, 0), buttonSize);
	bend.setRadius(bend.getSize().y / 2);

	sf::Uint32 end[] = { 9658,9658,108, 0 };
	bend.setText(end, Resources::Font::arial);

	// back button
	bback.create(playPos + sf::Vector2f(-Layout::ControlBox::buttonSpacing - buttonSize.x, 0), buttonSize);
	bback.setRadius(bback.getSize().y / 2);

	sf::Uint32 back[] = { 108,9668, 0 };
	bback.setText(back, Resources::Font::arial);

	// start button
	sf::Vector2f backPos = bback.getPosition();
	bstart.create(backPos + sf::Vector2f(-Layout::ControlBox::buttonSpacing - buttonSize.x, 0), buttonSize);
	bstart.setRadius(bstart.getSize().y / 2);

	sf::Uint32 start[] = { 108,9668,9668, 0 };
	bstart.setText(start, Resources::Font::arial);

	// speed buttons
	sf::Vector2f speedSize(35, 20);
	incSpeed.create(Layout::ControlBox::pos + sf::Vector2f(112, Layout::ControlBox::size.y / 2 - speedSize.y - 1), speedSize);
	incSpeed.setText("+", Resources::Font::courier);
	incSpeed.setFontSize(30);
	incSpeed.setRadius(3);

	decSpeed.create(Layout::ControlBox::pos + sf::Vector2f(112, Layout::ControlBox::size.y / 2 + 1), speedSize);
	decSpeed.setText("-", Resources::Font::courier);
	decSpeed.setFontSize(30);
	decSpeed.setRadius(3);

	speedText.setFont(*Resources::Font::courier);
	speedText.setString("x1");
	speedText.setCharacterSize(50);
	speedText.setPosition(Layout::ControlBox::pos + sf::Vector2f(50, 0));
	speedText.setFillColor(sf::Color::Black);
	speedText.setOutlineColor(sf::Color::White);
	speedText.setOutlineThickness(0.5);
}

void ControlBox::setup()
{
	bound.setSize(Layout::ControlBox::size);
	bound.setPosition(Layout::ControlBox::pos);
	bound.setFillColor(Layout::ControlBox::fillColor);
	bound.setOutlineColor(Layout::ControlBox::outlineColor);
	bound.setOutlineThickness(Layout::ControlBox::outlineThickness);
	bound.setCornerPointCount(Layout::cornerPointCount);
	bound.setCornersRadius(Layout::ControlBox::cornerRadius);

	setupButtons();

	playing = 0;
	current = -1;
}

void ControlBox::handleEvent(sf::RenderWindow& window, sf::Event event)
{
	bplay.handleEvent(window, event);
	bstop.handleEvent(window, event);
	bforw.handleEvent(window, event);
	bend.handleEvent(window, event);
	bback.handleEvent(window, event);
	bstart.handleEvent(window, event);
	incSpeed.handleEvent(window, event);
	decSpeed.handleEvent(window, event);

	if (incSpeed.justReleasedInside()) speed = std::min(speed + 1, 9);
	if (decSpeed.justReleasedInside()) speed = std::max(speed - 1, 1);

	if (current < 0) return;

	if (playing) {
		if (bstop.justReleasedInside()) playing = 0;
	}
	else {
		if (bplay.justReleasedInside()) playing = 1;
	}

	if (bstart.justReleasedInside()) {
		current = 0;
		timeSinceLast = 0;
	}
	if (bend.justReleasedInside()) {
		current = (int)timeList.size() - 1;
		timeSinceLast = timeList[current];
	}
	if (bforw.justReleasedInside()) {
		if (current < (int)timeList.size() - 30) {
			current += 30;
			timeSinceLast = 0;
		}
		else {
			timeSinceLast = timeList[current];
		}
	}
	if (bback.justReleasedInside()) {
		current = std::max(0, current - 30);
		timeSinceLast = 0;
	}
}

void ControlBox::update()
{
	bplay.update();
	bstop.update();
	bforw.update();
	bend.update();
	bback.update();
	bstart.update();
	incSpeed.update();
	decSpeed.update();

	speedText.setString("x" + Tools::String::toString(speed));

	if (playing) {
		timeSinceLast += clock.restart().asSeconds() * (float)speed;
		while (current < (int)timeList.size() - 1 && timeSinceLast >= timeList[current]) {
			timeSinceLast -= timeList[current];
			current++;
		}
	}
	else {
		clock.restart();
	}
	if (playing) if (current == (int)timeList.size() - 1 && timeSinceLast >= timeList[current])
	{
		playing = 0;
	}

	//std::cout << speed << ": " << current << std::endl;
}

void ControlBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//target.draw(bound);
	if (playing) target.draw(bstop);
	else target.draw(bplay);
	target.draw(bforw);
	target.draw(bend);
	target.draw(bback);
	target.draw(bstart);
	target.draw(incSpeed);
	target.draw(decSpeed);
	target.draw(speedText);
}

void ControlBox::setTimeList(std::vector<float> _timeList)
{
	timeList = _timeList;
}

void ControlBox::addTime(float _time)
{
	timeList.push_back(_time);
}

void ControlBox::start()
{
	if (timeList.size() == 0) return;
	playing = 1;
	current = 0;
	clock.restart();
}

void ControlBox::clear()
{
	timeList.clear();
	playing = 0;
	current = -1;
	timeSinceLast = 0;
}

int ControlBox::getCurrent() const
{
	return current;
}
