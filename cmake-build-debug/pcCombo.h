#include <string>
#include <utility>
#include <vector>
#include <set>
#include <algorithm>
#include <iostream>
#include <set>
using namespace std;
#ifndef PROJECT_3__PCCOMBO_H
#define PROJECT_3__PCCOMBO_H

//Contains sets useful for comparing whether parts are compatible with each other
struct CompatInfo{
    //Which sockets are compatible with which cpus
    set<string> DDR5_sockets = {"AM5", "LGA1700"};;
    set<string> DDR4_sockets = {"LGA1150", "LGA1151", "LGA1200", "LGA2066", "LGA2011-3", "AM4", "TR4", "sTRX4"};
    //Which cpus are compatible with which sockets


};

class pcPart{
public:
    string name;
    double price;
    pcPart(string name, int price){
        this->name = name;
        this->price = price;
    }
    pcPart() {};
};

class CPU : public pcPart{
public:
    int core_count;
    double core_clock; //Base Clock of CPU
    int tdp; //Thermal Design Power, measured in watts
    string socket;
    CPU(string name, double price, int core_count, double core_clock, int tdp, string socket)
    : pcPart(name, price) {
        this->core_count = core_count;
        this->core_clock = core_clock;
        this->tdp = tdp;
        this->socket = socket;
    }
    //Default Constructor, if values need to be initialized later
    CPU() {};
};

class GPU : public pcPart{
public:
    double core_clock;
    int memory;
    int tdp; // Thermal Design Power in watts
    string chipset;
    GPU(string name, double price, int memory, double core_clock, int tdp, string chipset)
    : pcPart(name, price) {
        this->memory = memory;
        this->core_clock = core_clock;
        this->tdp = tdp;
        this->chipset = chipset;
    }
    //Default Constructor, if values need to be initialized later
    GPU() {};
};

class PSU : public pcPart{
public:
    string type;
    string efficiency;
    int wattage;


    PSU(string name, double price, string type, string efficiency, int wattage)
    : pcPart(name, price){
        this->type = type;
        this->efficiency = efficiency;
        this->wattage = wattage;
    }
    //Default Constructor, if values need to be initialized later
    PSU() {};
};

class RAM : public pcPart{
public:
    int speed;
    pair<int, int> modules; // true for full modular, false otherwise
    int generation; //5 for ddr5, 4 for ddr4, 3 for ddr3, necessary for mobo compatibility

    RAM(string name, double price, int speed, pair<int, int> modules)
    : pcPart(name, price){
        this->speed = speed;
        this->modules.first = modules.first;
        this->modules.second = modules.second;
        //DDR generation to DDR speeds roughly follow this trend
        generation = 5;
        if(speed < 4200) generation = 4;
        if(speed <= 2200) generation = 3;
    }
    //Default Constructor, if values need to be initialized later
    RAM() {};
};

class Motherboard : public pcPart{
public:
    string socket;
    string form_factor;
    int memory_slots;
    int max_memory_per_slot;
    int ram_generation; //Which RAM gen this mobo is compatible with, dependent on socket

    Motherboard(string name, double price, string socket, string form_factor, int memory_slots, int max_memory)
    : pcPart(name, price){
        this->socket = socket;
        this->form_factor = form_factor;
        this->memory_slots = memory_slots;
        this->max_memory_per_slot = max_memory/memory_slots;
        CompatInfo compat_info;
        if(compat_info.DDR5_sockets.count(socket) != 0){
            ram_generation = 5;
        }
        else if(compat_info.DDR4_sockets.count(socket) != 0){
            ram_generation = 4;
        }
        else{
            ram_generation = 3;
        }
    }
    //Default Constructor, if values need to be initialized later
    Motherboard() {};
};

class Storage : public pcPart{
public:
    int capacity;
    string type;
    string interface;

    Storage(string name, double price, int capacity, string type, string interface)
    : pcPart(name, price){
        this->capacity = capacity;
        this->type = type;
        this->interface = interface;
    }
    //Default Constructor, if values need to be initialized later
    Storage() {};
};

class pcCombo {

};


#endif //PROJECT_3__PCCOMBO_H
