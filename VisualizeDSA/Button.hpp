#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <functional>
#include <iostream>
#include "MouseDetection.hpp"


class Button : public MouseDetection, public sf::Drawable {
public:
	Button() {};
	Button(sf::Vector2f _pos, sf::Vector2f _size);

	void create(sf::Vector2f _pos, sf::Vector2f _size);
	void handleEvent(sf::RenderWindow &window, sf::Event event);
	void update();
public:
	void setText(std::string s, sf::Font *font);
	void setRadius(float _radius);
	void addHandle(std::function<void(const Button*)> handle);
	void addState(sf::RoundedRectangleShape newState);
	std::function<int(const Button*)> getStateId;

private:
	sf::Text *text = nullptr;
	std::vector<sf::RoundedRectangleShape> states;
	std::vector<std::function<void(const Button*)>> handles;

public:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	
public:
	~Button() {
		delete text;
	}
};

#endif // !BUTTON_HPP