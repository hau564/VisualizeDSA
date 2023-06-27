#ifndef TEXTBOX_HPP
#define TEXTBOX_HPP

#include <SFML/Graphics.hpp>
#include <functional>
#include "Button.hpp"

class Textbox : public Button {
public:
	Textbox() {};
	Textbox(sf::Vector2f _pos, sf::Vector2f _size);
	void create(sf::Vector2f _pos, sf::Vector2f _size);
	void handleEvent(sf::RenderWindow &window, sf::Event event);
	void update();
	void addHandle(std::function<void(const Textbox*)> handle);

	bool isEntered() { return entered; }
	void setFontSize(int fontSize);

private:
	int active = 0, entered = 0, cursorState = 0;
	float timeCursor = 0;
	sf::Clock clock;
	std::string inputString;
	sf::Text text, cursor;
	std::vector<std::function<void(const Textbox*)>> handles;
public:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	
public:
	~Textbox() {};
};

#endif // !TEXTBOX_HPP