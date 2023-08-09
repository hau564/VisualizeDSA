#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <functional>
#include <iostream>
#include "MouseDetection.hpp"

class ButtonState {
public:
	sf::Color fillColor, outlineColor;
	float outlineThickness;
};

class Button : public MouseDetection, public sf::Drawable {
public:
	Button() {};
	Button(sf::Vector2f _pos, sf::Vector2f _size);

	void create(sf::Vector2f _pos, sf::Vector2f _size);
	void handleEvent(sf::RenderWindow &window, sf::Event event);
	void update();
public:
	void setText(std::string s, std::shared_ptr<sf::Font> font);
	void setText(const sf::Uint32 s[], std::shared_ptr<sf::Font> font);
	void setRadius(float _radius);
	void setState(ButtonState state, int id);
	void setStates(std::vector<ButtonState> _states);
	void setFontSize(int size);
	void setTransparency(int alpha);
	
	void addHandle(std::function<void(const Button*)> handle);
	
	void addState(sf::RoundedRectangleShape newState);
	void addCircleState(sf::CircleShape newState);
	
	void addGetStateId(std::function<int(const Button*)> getId);
	void addGetCircleStateId(std::function<int(const Button*)> getId);
	
	void removeGetStateId(int i);

	std::string getLabel();

	std::function<int(const Button*)> getStateId;
	std::vector< std::function<int(const Button*)>> getStateIds;
	std::vector< std::function<int(const Button*)>> getCircleStateIds;

	std::shared_ptr<sf::Text> text = std::make_shared<sf::Text>();
private:
	bool specialText = 0;
	std::vector<sf::RoundedRectangleShape> states;
	std::vector<sf::CircleShape> circleStates;
	std::vector<std::function<void(const Button*)>> handles;
	sf::Font font;
	sf::Vector2f lastPos = { 0, 0 };
public:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	
public:
	~Button() {
		//delete text;
	}
};

#endif // !BUTTON_HPP