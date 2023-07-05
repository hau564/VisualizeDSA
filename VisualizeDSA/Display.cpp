#include "Display.hpp"
#include "Layout.hpp"

void Display::setup()
{
	screenShape.setSize(Layout::DisplayScreen::size);
	screenShape.setPosition(Layout::DisplayScreen::pos);
	screenShape.setFillColor(Layout::DisplayScreen::fillColor);
	screenShape.setOutlineColor(Layout::DisplayScreen::outlineColor);
	screenShape.setOutlineThickness(Layout::DisplayScreen::outlineThickness);
	screenShape.setCornerPointCount(Layout::cornerPointCount);
	screenShape.setCornersRadius(Layout::DisplayScreen::cornerRadius);
}

void Display::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(screenShape, states);
}
