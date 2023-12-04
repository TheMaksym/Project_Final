#include <iostream>
#include "pcUtilities.h"
#include "pcCombo.h"
#include "mergeSort.h"
#include "quickSort.h"
#include <chrono>
#include <algorithm>
//SFML stuff
#include <SFML/Graphics.hpp>
#include <windows.h>
#include <unistd.h>
using namespace std;

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
    void handleEvent(sf::RenderWindow& window, sf::Event& event) {
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
                cout << percent << endl;
            }
        }
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
int main() {
    int height = 900;
    int width = 800;
    //Load Fonts
    sf::Font bladeFont;
    sf::Font tallFont;
    if (!bladeFont.loadFromFile("files/BLADRMF_.TTF")) return EXIT_FAILURE;
    if (!tallFont.loadFromFile("files/taller.ttf")) return EXIT_FAILURE;

    //Vectors of SFML objects represent which objects should be displayed at which state of the program
    vector<sf::Drawable*> state0; //State 0 will always be visible, contains title and bg
    vector<sf::Drawable*> state1;
    vector<sf::Drawable*> state2;
    vector<sf::Drawable*> state3;
    vector<sf::Drawable*> state4;

    // Load a sprite to display
    sf::Texture texture1;
    if (!texture1.loadFromFile("files/PC Picture 2.png"))
        return EXIT_FAILURE;
    sf::Sprite background(texture1);
    background.setScale(0.5, 0.5);
    state0.push_back(&background);
    // Create a graphical text to display
    sf::Text title("pc part suggester", bladeFont, 60);
    title.setPosition(10, height/4 - title.getLocalBounds().height);
    state0.push_back(&title);
    // Create a quicksort button
    TextButton quickSort(100, 100, 0, height*1/2, tallFont, "QuickSort");
    state1.push_back(quickSort.getRectangle());
    state2.push_back(quickSort.getText());
    // Create a mergesort button
    TextButton mergeSort(100, 100, width-100, height*1/2, tallFont, "MergeSort");
    state2.push_back(mergeSort.getRectangle());
    state2.push_back(mergeSort.getText());
    // Create a rectangle range object
    RectangleRange range(800, 40, 0, height*3/4);
    state2.push_back(range.getRectangle());
    //All window objects created

    //Create window
    sf::RenderWindow window(sf::VideoMode(width, height), "My window");

    while (window.isOpen())
    {
        //Draw all objects, then display to window
        window.clear();
        for(sf::Drawable* toDraw : state0){
            window.draw(*toDraw);
        }
        for(sf::Drawable* toDraw : state1){
            window.draw(*toDraw);
        }
        for(sf::Drawable* toDraw : state2){
            window.draw(*toDraw);
        }
        window.display();

        //Event handling logic below
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();
            range.handleEvent(window, event);
            cout << quickSort.handleEvent(window, event) << endl;
        }
    }

    pcUtilities* pc = new pcUtilities;

    pc->readInjsonlCPU("JSONL/cpu.jsonl");
    pc->readInjsonlGPU("JSONL/gpu.jsonl");

    pc->readInjsonlPSU("JSONL/power-supply.jsonl");
    pc->readInjsonlRAM("JSONL/memory.jsonl");
    pc->readInjsonlMB("JSONL/motherboard.jsonl");
    pc->readInjsonlStr("JSONL/internal-hard-drive.jsonl");

    pc->conglomerate();
    cout << pc->sortedList.size() << " sorted list will" << endl;
    cout << " done" << endl;

    pc->dupeVect();
    auto start = chrono::high_resolution_clock::now();
    quickSorts(pc->sortedList, 0, pc->sortedList.size() - 1);
    auto stop = chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    cout << "Time taken by quickSorts: " << duration.count() << " milliseconds" << std::endl;

//    start = chrono::high_resolution_clock::now();
//    mergeSorts(pc->sortedList2, 0, pc->sortedList2.size() - 1);
//    stop = chrono::high_resolution_clock::now();
//    duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
//    cout << "Time taken by mergeSorts: " << duration.count() << " milliseconds" << std::endl;

    double listTotal = pc->sortedList.size();
    double percentile;
    while(true){
        cout << "Enter a percentile (0-1): ";
        cin >> percentile;

        if (percentile < 0 || percentile > 1) {
            cout << "Invalid percentile. Please enter a value between 0 and 100." << endl;
        } else {
            int index = static_cast<int>((percentile) * listTotal);

            if (index > 0) index--;

            auto& item = pc->sortedList[index];
            cout << index << endl;
            cout << item.cpu.name << " " << item.gpu.name << " "<< item.ram.name << " "<< item.mb.name<< " " << item.psu.name << " "<< item.str.name<< " price:" <<item.price <<endl;
        }
    }



    return 0;
}

