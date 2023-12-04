#include "pcUtilities.h"

pcUtilities::pcUtilities() {

}

void pcUtilities::readInjsonlCPU(string filename) {
    ifstream input_file(filename);

    string json_line;
    Json::Value root;

    while(getline(input_file, json_line)) {
        Json::Reader reader;
        if (reader.parse(json_line, root)) {
            string name = root["name"].asString();
            double price = root["price"].asDouble();
            int core_count = root["core_count"].asInt();
            double core_clock = root["core_clock"].asDouble();
            int tdp = root["tdp"].asInt();
            string socket = root["socket"].asString();
            if(price == 0 || price == NULL){
                //do nothing
            }
            else{
                CPUList.push_back(CPU(name, price, core_count, core_clock, tdp, socket));
            }
        }
    }
}


void pcUtilities::readInjsonlGPU(string filename) {
    ifstream input_file(filename);

    string json_line;
    Json::Value root;

    while(getline(input_file, json_line)) {
        Json::Reader reader;
        if (reader.parse(json_line, root)) {
            string name = root["name"].asString();
            double price = root["price"].asDouble();
            int memory = root["memory"].asInt();
            double core_clock = root["core_clock"].asDouble();
            string chipset = root["chipset"].asString();
            int tdp = root["tdp"].asInt();
            if(price == 0 || price == NULL){
                // do nothing
            }
            else{
                GPUList.push_back(GPU(name, price, memory, core_clock, tdp, chipset));
            }
        }
    }
}

void pcUtilities::readInjsonlPSU(string filename) {
    ifstream input_file(filename);

    string json_line;
    Json::Value root;

    while (getline(input_file, json_line)) {
        Json::Reader reader;
        if (reader.parse(json_line, root)) {
            string name = root["name"].asString();
            double price = root["price"].asDouble();
            string type = root["type"].asString();
            string efficiency = root["efficiency"].asString();
            int wattage = root["wattage"].asInt();

            if(price == 0 || price == NULL){
                // do nothing
            }
            else{
                PSUList.push_back(PSU(name, price, type, efficiency, wattage));
            }
        }
    }
}

void pcUtilities::readInjsonlRAM(string filename) {
    ifstream input_file(filename);

    string json_line;
    Json::Value root;
    pair<int, int> temp;
    int count = 0;
    while (getline(input_file, json_line)) {
        Json::Reader reader;
        if (reader.parse(json_line, root)) {
            string name = root["name"].asString();
            double price = root["price"].asDouble();

            Json::Value speeds = root["speed"];
            int truespeed;
            for(const Json::Value& speed : speeds){
                if(count == 0){
                    count++;
                }
                if(count == 1){
                    truespeed = speed.asInt();
                    count = 0;
                }
            }

            Json::Value modules = root["modules"];
            for(const Json::Value mod : modules){
                if(count == 0){
                    temp.first = mod.asInt();
                    count++;
                }
                else if(count == 1){
                    temp.second = mod.asInt();
                    count = 0;
                }
            }
            RAMList.push_back(RAM(name, price, truespeed, temp));
        }
    }
}


void pcUtilities::readInjsonlMB(string filename) {
    ifstream input_file(filename);

    string json_line;
    Json::Value root;

    while (getline(input_file, json_line)) {
        Json::Reader reader;
        if (reader.parse(json_line, root)) {
            string name = root["name"].asString();
            double price = root["price"].asDouble();
            string socket = root["socket"].asString();
            if(socket.substr(0, 3) == "LGA") socket = socket.substr(3);
            string form_factor = root["form_factor"].asString();
            int memory_slots = root["memory_slots"].asInt();
            int max_memory = root["max_memory"].asInt();
            if(price == 0 || price == NULL){
                // do nothing
            }
            else{
                MBList.push_back(Motherboard(name, price, socket, form_factor, memory_slots, max_memory));
            }
        }
    }
}


void pcUtilities::readInjsonlStr(string filename) {
    ifstream input_file(filename);

    string json_line;
    Json::Value root;

    while (getline(input_file, json_line)) {
        Json::Reader reader;
        if (reader.parse(json_line, root)) {
            string name = root["name"].asString();
            double price = root["price"].asDouble();
            int capacity = root["capacity"].asInt();
            string type = root["type"].asString();
            string interface = root["interace"].asString();
            if(price == 0 || price == NULL){
                // do nothing
            }
            else{
                STRList.push_back(Storage(name, price, capacity, type, interface));
            }
        }
    }
}

void pcUtilities::hashMotherboards() {
    for(Motherboard& mobo : MBList){
        motherboardsBySocket[mobo.socket].push_back(&mobo);
    }
}
void pcUtilities::hashRam() {
    for(RAM& ram : RAMList){
        ramByGeneration[ram.generation].push_back(&ram);
    }
}

void pcUtilities::conglomerate() {
    int size = 10000000; //Max size of pc list, 10 million, if goes over stop, if under, return
    hashMotherboards();
    hashRam();
    sortedList.resize(size);

    int count = 0;
    //Creates large number of possible compatible combination of PC parts
    for(int a = 0; a < CPUList.size()/4; a++){
        CPU& cpu = CPUList[a];
        cout << cpu.name << endl;
        for(int b = 0; b < GPUList.size()/6; b++){
            GPU& gpu = GPUList[b];
            for(int c = 0; c < motherboardsBySocket[cpu.socket].size()/2; c++){
                Motherboard& mobo = *motherboardsBySocket[cpu.socket][c];
                for(int d = 0; d < min((int)ramByGeneration[mobo.ram_generation].size(), 2); d++) {
                    RAM& ram = *ramByGeneration[mobo.ram_generation][d];
                    for(int e = 16; e < 17; e += 500) {
                        if(count == size){
                            cout << a << endl;
                            return;
                        }
                        Storage& str = STRList[e];
                        sortedList[count] = pcCombo(cpu, gpu, PSUList[0], ram, mobo, str);
                        count++;
                    }
                }
            }
        }
    }
    sortedList.resize(count); //If under max size, return
}

