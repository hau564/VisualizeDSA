#include "StructureRunner.hpp"

void StructureRunner::create(std::string _structName)
{
	structName = _structName;
	display.setup();
	control.setup();
	control.setTimeList({1,1,1,1,1,1,1,1,1,1,1,1,1,1,1});
	control.startAnimation();
}

void StructureRunner::handleEvent(sf::RenderWindow& window, sf::Event event)
{
	control.handleEvent(window, event);	
}

void StructureRunner::update()
{
	control.update();
}

void StructureRunner::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(display);
	target.draw(control);
}
