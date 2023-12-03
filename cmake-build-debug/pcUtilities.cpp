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


            CPUList.push_back(CPU(name, price, core_count, core_clock, tdp));
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


            GPUList.push_back(GPU(name, price, memory, core_clock, tdp, chipset));
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

            PSUList.push_back(PSU(name, price, type, efficiency, wattage));

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
            string form_factor = root["form_factor"].asString();
            int memory_slots = root["memory_slots"].asInt();
            int max_memory = root["max_memory"].asInt();

            MBList.push_back(Motherboard(name, price, socket, form_factor, memory_slots, max_memory));

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

            STRList.push_back(Storage(name, price, capacity, type, interface));

        }
    }
}

