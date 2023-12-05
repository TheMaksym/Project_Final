#include <SFML/Graphics.hpp>

#ifndef PROJECT_FINAL_SFMLTOOLS_H
#define PROJECT_FINAL_SFMLTOOLS_H
class RectangleRange {
    //Variables for size and position
    int length;
    int height;
    int x;
    int y;
    //SFML Data
    sf::RectangleShape rectangle;
    //What percent of the rectangle is to the left of the mouse
    float percent;
public:
    //Constructor takes in position and width and height
    RectangleRange(int length, int height, int x, int y) {
        this->length = length;
        this->height = height;
        this->x = x;
        this->y = y;
        sf::Vector2<float> size(length, height);
        rectangle.setSize(size);
        rectangle.setPosition(x, y);
        rectangle.setFillColor(sf::Color::Red);
    }
    //Gets mouse position to determine percent
    float handleEvent(sf::RenderWindow& window, sf::Event& event) {
        if(event.type == sf::Event::MouseMoved){
            sf::Vector2<int> mousePosition = sf::Mouse::getPosition(window);
            //Change mouse position to float so it works with bounds.contains method
            sf::Vector2<float> mousePositionF(mousePosition.x, mousePosition.y);
            sf::FloatRect bounds = rectangle.getGlobalBounds();
            if(bounds.contains(mousePositionF)){
                percent = mousePositionF.x/length;
            }
        }
        if(event.type == sf::Event::MouseButtonPressed){
            sf::Vector2<int> mousePosition = sf::Mouse::getPosition(window);
            //Change mouse position to float so it works with bounds.contains method
            sf::Vector2<float> mousePositionF(mousePosition.x, mousePosition.y);
            sf::FloatRect bounds = rectangle.getGlobalBounds();
            if(bounds.contains(mousePositionF)){
                return percent;
            }
        }
        return -1;
    }
    //Returns a pointer to the Rectangle shape
    sf::RectangleShape* getRectangle() {
        return &rectangle;
    }
};

//Class provides a button with a text overlay
class TextButton{
    //Variables for size and position
    int length;
    int height;
    int x;
    int y;
    //SFML Data
    sf::RectangleShape rectangle;
    sf::Text text;
public:
    //Constructor takes in position and width and height
    TextButton(int length, int height, int x, int y, sf::Font& font, string textData) {
        this->length = length;
        this->height = height;
        this->x = x;
        this->y = y;
        text = sf::Text(textData, font, height);
        text.setPosition(x, y);
        sf::Vector2<float> size(text.getLocalBounds().width, height);
        rectangle.setSize(size);
        rectangle.setPosition(x, y);
        rectangle.setFillColor(sf::Color::Blue);
    }
    //Checks if Button Clicked
    bool handleEvent(sf::RenderWindow& window, sf::Event& event) {
        sf::Vector2<int> mousePosition = sf::Mouse::getPosition(window);
        //Change mouse position to float so it works with bounds.contains method
        sf::Vector2<float> mousePositionF(mousePosition.x, mousePosition.y);
        sf::FloatRect bounds = rectangle.getGlobalBounds();
        if(bounds.contains(mousePositionF)){
            if(event.type == sf::Event::MouseButtonPressed){
                return true;
            };
        }
        return false;
    }
    //Returns a pointer to the Rectangle shape
    sf::RectangleShape* getRectangle() {
        return &rectangle;
    }
    //Returns a pointer to the Text shape
    sf::Text* getText() {
        return &text;
    }
};
#endif //PROJECT_FINAL_SFMLTOOLS_H
