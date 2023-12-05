#include <iostream>
#include <chrono>
#include <algorithm>
#include <windows.h>
#include <unistd.h>
#include "PCUtilities.h"
#include "PCCombo.h"
#include "Mergesort.h"
#include "Quicksort.h"
//SFML stuff
#include "SFMLtools.h"
#include <SFML/Graphics.hpp>
using namespace std;


int main() {
    //Height and width
    int height = 900;
    int width = 800;
    //Load Fonts
    sf::Font bladeFont;
    sf::Font tallFont;
    sf::Font tearsinrain;
    sf::Font Aquire;
    if (!bladeFont.loadFromFile("files/BLADRMF_.TTF")) return EXIT_FAILURE;
    if (!tallFont.loadFromFile("files/taller.ttf")) return EXIT_FAILURE;
    if (!tearsinrain.loadFromFile("files/TearsInRain-ALBK2.ttf")) return EXIT_FAILURE;
    if (!Aquire.loadFromFile("files/Aquire.otf")) return EXIT_FAILURE;

    //Vector of SFML objects represent which objects should be displayed at which state of the program
    vector<sf::Drawable*> state;

    //PC Image Background
    sf::Texture texture1;
    if (!texture1.loadFromFile("files/PC Picture 2.png"))
        return EXIT_FAILURE;
    sf::Sprite background(texture1);
    background.setScale(0.5, 0.5);
    state.push_back(&background);
    //PC Image Background
    sf::Texture texture2;
    if (!texture2.loadFromFile("files/badPc.png"))
        return EXIT_FAILURE;
    sf::Sprite badPC(texture2);
    badPC.setPosition(0, 725);
    state.push_back(&badPC);
    //PC Image Background
    sf::Texture texture3;
    if (!texture3.loadFromFile("files/goodPc.png"))
        return EXIT_FAILURE;
    sf::Sprite goodPC(texture3);
    goodPC.setPosition(650, 725);
    state.push_back(&goodPC);
    // Create a graphical text to display
    sf::Text title("pc part suggester", bladeFont, 60);
    title.setPosition(10, height/4 - title.getLocalBounds().height);
    state.push_back(&title);
    //Create PC text
    sf::Text cpuText("Nasa CPU", Aquire, 20);
    cpuText.setPosition(width / 2 - cpuText.getLocalBounds().width/2, height / 2);
    state.push_back(&cpuText);
    sf::Text gpuText("Nasa GPU", Aquire, 20);
    gpuText.setPosition(width / 2 - gpuText.getLocalBounds().width/2, (height / 2) + 30);
    state.push_back(&gpuText);
    sf::Text motherboardText("Nasa Motherboard", Aquire, 20);
    motherboardText.setPosition(width / 2 - motherboardText.getLocalBounds().width /2, (height / 2) + 60);
    state.push_back(&motherboardText);
    sf::Text ramText("Nasa Ram", Aquire, 20);
    ramText.setPosition(width / 2 - ramText.getLocalBounds().width /2, (height / 2) + 90);
    state.push_back(&ramText);
    sf::Text storageText("Nasa Storage", Aquire, 20);
    storageText.setPosition(width / 2 - storageText.getLocalBounds().width /2, (height / 2) + 120);
    state.push_back(&storageText);
    sf::Text psuText("Nasa PSU", Aquire, 20);
    psuText.setPosition(width / 2 - psuText.getLocalBounds().width /2, (height / 2) + 150);
    state.push_back(&psuText);
    sf::Text pcPrice("A lot of $", Aquire, 40);
    pcPrice.setPosition(width / 2 - pcPrice.getLocalBounds().width / 2, (height / 1.2));
    state.push_back(&pcPrice);
    // Create a quicksort button
    TextButton quickSort(100, 100, 0, height*1/2, tallFont, "QuickSort");
    state.push_back(quickSort.getRectangle());
    state.push_back(quickSort.getText());

    sf::Text quickSortime("Quicksort time: ", Aquire, 15);
    quickSortime.setPosition(10, (height*1/2) + 125);
    state.push_back(&quickSortime);
    // Create a mergesort button
    TextButton mergeSort(100, 100, width-120, height*1/2, tallFont, "MergeSort");
    state.push_back(mergeSort.getRectangle());
    state.push_back(mergeSort.getText());

    sf::Text mergeSortime("Mergesort time: ", Aquire, 15);
    mergeSortime.setPosition(width-150, (height*1/2) + 125);
    state.push_back(&mergeSortime);
    // Create a rectangle range object
    RectangleRange range(800, 40, 0, height*3/4);
    state.push_back(range.getRectangle());
    //All window objects created

    //Create window
    sf::RenderWindow window(sf::VideoMode(width, height), "My window");

    //Load in Data from Json files, and generate our random data set
    PCUtilities* pc = new PCUtilities; //Instance is responsible for backend logic
    pc->readInjsonlCPU("JSONL/cpu.jsonl");
    pc->readInjsonlGPU("JSONL/gpu.jsonl");
    pc->readInjsonlPSU("JSONL/power-supply.jsonl");
    pc->readInjsonlRAM("JSONL/memory.jsonl");
    pc->readInjsonlMB("JSONL/motherboard.jsonl");
    pc->readInjsonlStr("JSONL/internal-hard-drive.jsonl");
    pc->conglomerate();
    cout << pc->sortedList.size() << " listsize" << endl;
    cout << " done" << endl;
    pc->dupeVect();
    bool isSortedquick = false;

    while (window.isOpen())
    {
        //Draw all objects, then display to window
        window.clear();
        for(sf::Drawable* toDraw : state){
            window.draw(*toDraw);
        }
        window.display();

        //Event handling logic below
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();
            range.handleEvent(window, event);
            double listTotal = pc->sortedList.size();
            double percentile;
            if(quickSort.handleEvent(window, event)){
                //Measure Time it takes to quick sort with chrono
                auto start = chrono::high_resolution_clock::now();
                quickSorts(pc->sortedList, 0, pc->sortedList.size() - 1);
                auto stop = chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
                cout << "Time taken by quickSorts: " << duration.count() << " milliseconds" << std::endl;
                isSortedquick = true;
                //Modify quick sort text widget to reflect time
                quickSortime.setString("Quicksort time: \n" + to_string(duration.count() / 1000) + " seconds");
                quickSortime.setPosition(10, (height*1/2) + 125);
            }
            if(mergeSort.handleEvent(window, event)){
                auto start = chrono::high_resolution_clock::now();
                mergeSorts(pc->sortedList2, 0, pc->sortedList2.size() - 1);
                auto stop = chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
                cout << "Time taken by mergeSorts: " << duration.count() << " milliseconds" << std::endl;
                isSortedquick = false;
                //Modify merge sort text widget to reflect time
                mergeSortime.setString("Mergesort time: \n" + to_string(duration.count() / 1000) + " seconds");
                mergeSortime.setPosition(width-150, (height*1/2) + 125);
            }
            if(range.handleEvent(window, event) > -1){
                int index = static_cast<int>((range.handleEvent(window, event)) * listTotal);
                if (index > 0) index--;
                auto& item = pc->sortedList[index]; //uses either merge or quick sorted list depending on which is selected                
                if (isSortedquick) item = pc->sortedList[index];                
                else item = pc->sortedList2[index];
                //CPU Text
                string cpuFinal = item.cpu.name;
                cpuText.setString(cpuFinal);
                cpuText.setPosition(width / 2 - cpuText.getLocalBounds().width / 2, height / 2);
                //GPU Text
                string gpuFinal = item.gpu.name;
                gpuText.setString(gpuFinal);
                gpuText.setPosition(width / 2 - gpuText.getLocalBounds().width / 2, (height / 2) + 30);
                //Motherboard Text
                string motherboardFinal = item.mb.name;
                motherboardText.setString(motherboardFinal);
                motherboardText.setPosition(width / 2 - motherboardText.getLocalBounds().width / 2, (height / 2) + 60);
                //Ram Text
                string ramFinal = item.ram.name;
                ramText.setString(ramFinal);
                ramText.setPosition(width / 2 - ramText.getLocalBounds().width / 2, (height / 2) + 90);
                //Storage Text
                string storageFinal = item.str.name;
                storageText.setString(storageFinal);
                storageText.setPosition(width / 2 - storageText.getLocalBounds().width / 2, (height / 2) + 120);
                //PSU Text
                string psuFinal = item.psu.name;
                psuText.setString(psuFinal);
                psuText.setPosition(width / 2 - psuText.getLocalBounds().width / 2, (height / 2) + 150);
                //Price Text
                string priceFinal = "$" + to_string(int(item.price));
                pcPrice.setString(priceFinal);
                pcPrice.setPosition(width / 2 - pcPrice.getLocalBounds().width / 2, (height / 1.2));
            }
        }
    }
    //Because we stored it on the heap
    delete pc;
    return 0;
}

