#include "ControlBox.hpp"
#include "Layout.hpp"
#include "Resources.hpp"
void ControlBox::setupButtons()
{

	sf::Vector2f pos = Layout::ControlBox::pos, size = Layout::ControlBox::size;
	sf::Vector2f center = pos + sf::Vector2f(size.x / 2, size.y / 2);
	sf::Vector2f buttonSize = Layout::ControlBox::buttonSize;
	std::cout << std::endl;


	// play button
	play.create(center - sf::Vector2f(buttonSize.x / 2, buttonSize.y / 2), buttonSize);
	stop.create(center - sf::Vector2f(buttonSize.x / 2, buttonSize.y / 2), buttonSize);
	stop.setState({ sf::Color::Red, sf::Color::Black, 1 }, 0);
	// forw button
	sf::Vector2f playPos = play.getPosition();
	forw.create(playPos + sf::Vector2f(+Layout::ControlBox::buttonSpacing + buttonSize.x, 0), buttonSize);
	
	// end button
	sf::Vector2f forwPos = forw.getPosition();
	end.create(forwPos + sf::Vector2f(+Layout::ControlBox::buttonSpacing + buttonSize.x, 0), buttonSize);

	// back button
	back.create(playPos + sf::Vector2f(-Layout::ControlBox::buttonSpacing - buttonSize.x, 0), buttonSize);

	// start button
	sf::Vector2f backPos = back.getPosition();
	start.create(backPos + sf::Vector2f(-Layout::ControlBox::buttonSpacing - buttonSize.x, 0), buttonSize);
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
	current = 0;
}

void ControlBox::handleEvent(sf::RenderWindow& window, sf::Event event)
{
	play.handleEvent(window, event);
	stop.handleEvent(window, event);
	forw.handleEvent(window, event);
	end.handleEvent(window, event);
	back.handleEvent(window, event);
	start.handleEvent(window, event);

	if (playing) {
		if (stop.justReleasedInside()) playing = 0;
	}
	else {
		if (play.justReleasedInside()) playing = 1;
	}

	if (start.justReleasedInside()) {
		current = 0;
		timeSinceLast = 0;
	}
	if (end.justReleasedInside()) {
		current = (int)timeList.size() - 1;
		timeSinceLast = timeList[current];
	}
	if (forw.justReleasedInside()) {
		if (current < (int)timeList.size() - 1) {
			current++;
			timeSinceLast = 0;
		}
		else {
			timeSinceLast = timeList[current];
		}
	}
	if (back.justReleasedInside()) {
		if (current > 0) {
			current--;
		}
		timeSinceLast = 0;
	}
}

void ControlBox::update()
{
	play.update();
	stop.update();
	forw.update();
	end.update();
	back.update();
	start.update();

	if (playing) {
		timeSinceLast += clock.restart().asSeconds();
		if (current < (int)timeList.size() - 1 && timeSinceLast >= timeList[current]) {
			timeSinceLast -= timeList[current];
			current++;
		}
	}
	else {
		clock.restart();
	}
	if (current == (int)timeList.size() - 1 && timeSinceLast >= timeList[current])
	{
		playing = 0;
	}

	std::cout << current << std::endl;
}

void ControlBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//target.draw(bound);
	if (playing) target.draw(stop);
	else target.draw(play);
	target.draw(forw);
	target.draw(end);
	target.draw(back);
	target.draw(start);
}

void ControlBox::setTimeList(std::vector<float> _timeList)
{
	timeList = _timeList;
}

void ControlBox::startAnimation()
{
	playing = 1;
	clock.restart();
}
