//
// Created by Maksym M on 12/2/2023.
//
#include "PCCombo.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <set>
#include "dist/json/json.h"
#include <unordered_map>
#include <list>
#include <algorithm>

using namespace std;
#ifndef PROJECT_3__PCUTILITIES_H
#define PROJECT_3__PCUTILITIES_H
class PCUtilities{
public:
    vector<CPU> CPUList; //declaring all vectors for PC components and the whole PC itself
    vector<GPU> GPUList;
    vector<PSU> PSUList;
    vector<RAM> RAMList;
    vector<Motherboard> MBList;
    vector<Storage> STRList;
    vector<PCCombo> sortedList;
    vector<PCCombo> sortedList2;


    PCUtilities();

    void dupeVect(); //duplicate a vector for both sorts

    void readInjsonlCPU(string filename); //read in each file dependent on the jsonl files
    void readInjsonlGPU(string filename);
    void readInjsonlPSU(string filename);
    void readInjsonlRAM(string filename);
    void readInjsonlMB(string filename);
    void readInjsonlStr(string filename);

    unordered_map<string, vector<Motherboard*>> motherboardsBySocket; //used to generate combinations
    unordered_map<int, vector<RAM*>> ramByGeneration; //used to generate combinations
    void hashMotherboards();
    void hashRam();
    void conglomerate(); //produce combinations of pc parts
};

#endif //PROJECT_3__PCUTILITIES_H
