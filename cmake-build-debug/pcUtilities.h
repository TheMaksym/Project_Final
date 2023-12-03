//
// Created by Maksym M on 12/2/2023.
//
#include "pcCombo.h"
#include <iostream>
#include <vector>
#include <fstream>
#include "dist/json/json.h"

using namespace std;
#ifndef PROJECT_3__PCUTILITIES_H
#define PROJECT_3__PCUTILITIES_H
class pcUtilities{
private:
    vector<CPU> CPUList;
    vector<GPU> GPUList;
    vector<PSU> PSUList;
    vector<RAM> RAMList;
    vector<Motherboard> MBList;
    vector<Storage> STRList;
    vector<pcCombo> sortedList;
public:
    void readInjsonlCPU(string filename);
    pcUtilities();

    void readInjsonlGPU(string filename);
    void readInjsonlPSU(string filename);
    void readInjsonlRAM(string filename);
    void readInjsonlMB(string filename);
    void readInjsonlStr(string filename);
    void mergeSort();

    void quickSort();

};

#endif //PROJECT_3__PCUTILITIES_H
