//
// Created by Maksym M on 12/2/2023.
//
#include "PCCombo.h"
#include <iostream>
#include <vector>
#include <fstream>
#include "dist/json/json.h"

using namespace std;
#ifndef PROJECT_3__PCUTILITIES_H
#define PROJECT_3__PCUTILITIES_H
class PCUtilities{
public:
    vector<CPU> CPUList;
    vector<GPU> GPUList;
    vector<PSU> PSUList;
    vector<RAM> RAMList;
    vector<Motherboard> MBList;
    vector<Storage> STRList;
    vector<pcCombo> sortedList;
    vector<pcCombo> compList;



    vector<CPU> CPUList2;
    vector<GPU> GPUList2;
    vector<PSU> PSUList2;
    vector<RAM> RAMList2;
    vector<Motherboard> MBList2;
    vector<Storage> STRList2;
    vector<pcCombo> sortedList2;



    void compareParts();

    void dupeVect();

    void readInjsonlCPU(string filename); //read in each file dependent on the jsonl files
    void readInjsonlGPU(string filename);
    void readInjsonlPSU(string filename);
    void readInjsonlRAM(string filename);
    void readInjsonlMB(string filename);
    void readInjsonlStr(string filename);

    unordered_map<string, vector<Motherboard*>> motherboardsBySocket;
    unordered_map<int, vector<RAM*>> ramByGeneration;
    void hashMotherboards();
    void hashRam();
    void conglomerate();
};

#endif //PROJECT_3__PCUTILITIES_H
