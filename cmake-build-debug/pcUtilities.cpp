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

void pcUtilities::alterCPU(pcCombo orgPC) {
    int index;
    for(int i = 0; i < CPUList.size(); i++){
        if(CPUList[i].name == orgPC.cpu.name){
            index = i;
        }
    }
    if(index < 50){
        int remaining = 100 - index;
        for(int i = index; i >= 0; --i) {
            sortedList.push_back(pcCombo(CPUList[i], orgPC.gpu, orgPC.psu, orgPC.ram, orgPC.mb, orgPC.str));
        }
        for(int i = 1; i < remaining + 1; i++){
            sortedList.push_back(pcCombo(CPUList[i + index], orgPC.gpu, orgPC.psu, orgPC.ram, orgPC.mb, orgPC.str));
        }
    }
    else if(index > CPUList.size() - 50){
        int remaining = 100 - (CPUList.size() - index);
        for(int i = 0; i < CPUList.size() - index; i++){
            sortedList.push_back(pcCombo(CPUList[index + i], orgPC.gpu, orgPC.psu, orgPC.ram, orgPC.mb, orgPC.str));
        }
        for(int i = remaining; i >= 0; --i){
            sortedList.push_back(pcCombo(CPUList[index - i], orgPC.gpu, orgPC.psu, orgPC.ram, orgPC.mb, orgPC.str));
        }
    }
    else{
        for(int i = 1; i < 51; i++){
            sortedList.push_back(pcCombo(CPUList[index + i], orgPC.gpu, orgPC.psu, orgPC.ram, orgPC.mb, orgPC.str));
            sortedList.push_back(pcCombo(CPUList[index - i], orgPC.gpu, orgPC.psu, orgPC.ram, orgPC.mb, orgPC.str));
        }
    }
}

void pcUtilities::alterGPU(pcCombo orgPC) {
    int index;
    for(int i = 0; i < GPUList.size(); i++){
        if(GPUList[i].name == orgPC.gpu.name){
            index = i;
        }
    }
    if(index < 50){
        int remaining = 100 - index;
        for(int i = index; i >= 0; --i) {
            sortedList.push_back(pcCombo(orgPC.cpu, GPUList[i], orgPC.psu, orgPC.ram, orgPC.mb, orgPC.str));
        }
        for(int i = 1; i < remaining + 1; i++){
            sortedList.push_back(pcCombo(orgPC.cpu, GPUList[i + index], orgPC.psu, orgPC.ram, orgPC.mb, orgPC.str));
        }
    }
    else if(index > GPUList.size() - 50){
        int remaining = 100 - (GPUList.size() - index);
        for(int i = 0; i < GPUList.size() - index; i++){
            sortedList.push_back(pcCombo(orgPC.cpu, GPUList[index + i], orgPC.psu, orgPC.ram, orgPC.mb, orgPC.str));
        }
        for(int i = remaining; i >= 0; --i){
            sortedList.push_back(pcCombo(orgPC.cpu, GPUList[index - i], orgPC.psu, orgPC.ram, orgPC.mb, orgPC.str));
        }
    }
    else{
        for(int i = 1; i < 101; i++){
            sortedList.push_back(pcCombo(orgPC.cpu, GPUList[index + i], orgPC.psu, orgPC.ram, orgPC.mb, orgPC.str));
            sortedList.push_back(pcCombo(orgPC.cpu, GPUList[index - i], orgPC.psu, orgPC.ram, orgPC.mb, orgPC.str));
        }
    }
}


void pcUtilities::alterPSU(pcCombo orgPC) {
    int index;
    for(int i = 0; i < PSUList.size(); i++){
        if(PSUList[i].name == orgPC.psu.name){
            index = i;
        }
    }
    if(index < 50){
        int remaining = 100 - index;
        for(int i = index; i >= 0; --i) {
            sortedList.push_back(pcCombo(orgPC.cpu, orgPC.gpu, PSUList[i], orgPC.ram, orgPC.mb, orgPC.str));
        }
        for(int i = 1; i < remaining + 1; i++){
            sortedList.push_back(pcCombo(orgPC.cpu, orgPC.gpu, PSUList[i + index], orgPC.ram, orgPC.mb, orgPC.str));
        }
    }
    else if(index > PSUList.size() - 50){
        int remaining = 100 - (PSUList.size() - index);
        for(int i = 0; i < PSUList.size() - index; i++){
            sortedList.push_back(pcCombo(orgPC.cpu, orgPC.gpu, PSUList[index + i], orgPC.ram, orgPC.mb, orgPC.str));
        }
        for(int i = remaining; i >= 0; --i){
            sortedList.push_back(pcCombo(orgPC.cpu, orgPC.gpu, PSUList[index - i], orgPC.ram, orgPC.mb, orgPC.str));
        }
    }
    else{
        for(int i = 1; i < 101; i++){
            sortedList.push_back(pcCombo(orgPC.cpu, orgPC.gpu, PSUList[index + i], orgPC.ram, orgPC.mb, orgPC.str));
            sortedList.push_back(pcCombo(orgPC.cpu, orgPC.gpu, PSUList[index - i], orgPC.ram, orgPC.mb, orgPC.str));
        }
    }
}

void pcUtilities::alterRAM(pcCombo orgPC) {
    int index;
    for(int i = 0; i < RAMList.size(); i++){
        if(RAMList[i].name == orgPC.ram.name){
            index = i;
        }
    }
    if(index < 50){
        int remaining = 100 - index;
        for(int i = index; i >= 0; --i) {
            sortedList.push_back(pcCombo(orgPC.cpu, orgPC.gpu, orgPC.psu, RAMList[i], orgPC.mb, orgPC.str));
        }
        for(int i = 1; i < remaining + 1; i++){
            sortedList.push_back(pcCombo(orgPC.cpu, orgPC.gpu, orgPC.psu, RAMList[i + index], orgPC.mb, orgPC.str));
        }
    }
    else if(index > RAMList.size() - 50){
        int remaining = 100 - (RAMList.size() - index);
        for(int i = 0; i < RAMList.size() - index; i++){
            sortedList.push_back(pcCombo(orgPC.cpu, orgPC.gpu, orgPC.psu, RAMList[index + i], orgPC.mb, orgPC.str));
        }
        for(int i = remaining; i >= 0; --i){
            sortedList.push_back(pcCombo(orgPC.cpu, orgPC.gpu, orgPC.psu, RAMList[index - i], orgPC.mb, orgPC.str));
        }
    }
    else{
        for(int i = 1; i < 101; i++){
            sortedList.push_back(pcCombo(orgPC.cpu, orgPC.gpu, orgPC.psu, RAMList[index + i], orgPC.mb, orgPC.str));
            sortedList.push_back(pcCombo(orgPC.cpu, orgPC.gpu, orgPC.psu, RAMList[index - i], orgPC.mb, orgPC.str));
        }
    }
}

void pcUtilities::alterMB(pcCombo orgPC) {
    int index;
    for(int i = 0; i < MBList.size(); i++){
        if(MBList[i].name == orgPC.mb.name){
            index = i;
        }
    }
    if(index < 50){
        int remaining = 100 - index;
        for(int i = index; i >= 0; --i) {
            sortedList.push_back(pcCombo(orgPC.cpu, orgPC.gpu, orgPC.psu, orgPC.ram, MBList[i], orgPC.str));
        }
        for(int i = 1; i < remaining + 1; i++){
            sortedList.push_back(pcCombo(orgPC.cpu, orgPC.gpu, orgPC.psu, orgPC.ram, MBList[i+ index], orgPC.str));
        }
    }
    else if(index > MBList.size() - 50){
        int remaining = 100 - (MBList.size() - index);
        for(int i = 0; i < MBList.size() - index; i++){
            sortedList.push_back(pcCombo(orgPC.cpu, orgPC.gpu, orgPC.psu, orgPC.ram, MBList[i+ index], orgPC.str));
        }
        for(int i = remaining; i >= 0; --i){
            sortedList.push_back(pcCombo(orgPC.cpu, orgPC.gpu, orgPC.psu, orgPC.ram, MBList[index - i], orgPC.str));
        }
    }
    else{
        for(int i = 1; i < 101; i++){
            sortedList.push_back(pcCombo(orgPC.cpu, orgPC.gpu, orgPC.psu, orgPC.ram, MBList[i+ index], orgPC.str));
            sortedList.push_back(pcCombo(orgPC.cpu, orgPC.gpu, orgPC.psu, orgPC.ram, MBList[index - i], orgPC.str));
        }
    }
}

void pcUtilities::alterSTR(pcCombo orgPC) {
    int index;
    for(int i = 0; i < STRList.size(); i++){
        if(STRList[i].name == orgPC.str.name){
            index = i;
        }
    }
    if(index < 50){
        int remaining = 100 - index;
        for(int i = index; i >= 0; --i) {
            sortedList.push_back(pcCombo(orgPC.cpu, orgPC.gpu, orgPC.psu, orgPC.ram, orgPC.mb, STRList[i]));
        }
        for(int i = 1; i < remaining + 1; i++){
            sortedList.push_back(pcCombo(orgPC.cpu, orgPC.gpu, orgPC.psu, orgPC.ram, orgPC.mb, STRList[i+ index]));
        }
    }
    else if(index > STRList.size() - 50){
        int remaining = 100 - (STRList.size() - index);
        for(int i = 0; i < STRList.size() - index; i++){
            sortedList.push_back(pcCombo(orgPC.cpu, orgPC.gpu, orgPC.psu, orgPC.ram, orgPC.mb, STRList[i+ index]));
        }
        for(int i = remaining; i >= 0; --i){
            sortedList.push_back(pcCombo(orgPC.cpu, orgPC.gpu, orgPC.psu, orgPC.ram, orgPC.mb, STRList[index - i]));
        }
    }
    else{
        for(int i = 1; i < 101; i++){
            sortedList.push_back(pcCombo(orgPC.cpu, orgPC.gpu, orgPC.psu, orgPC.ram, orgPC.mb, STRList[i+ index]));
            sortedList.push_back(pcCombo(orgPC.cpu, orgPC.gpu, orgPC.psu, orgPC.ram, orgPC.mb, STRList[index - i]));
        }
    }
}


void pcUtilities::compareParts() {
    for(auto& i : sortedList){
        if(i.cpu.socket == i.mb.socket){
            compList.push_back(i);
        }
    }
}



