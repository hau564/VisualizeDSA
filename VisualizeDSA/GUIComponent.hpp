#ifndef GUICOMPONENT_HPP
#define GUICOMPONENT_HPP

#include <SFML/Graphics.hpp>
#include "MouseDetection.hpp"

namespace GUIComponent {
	class GUIComponent : public MouseDetection, public sf::Drawable {
	};
}

#endif // !GUICOMPONENT_HPP