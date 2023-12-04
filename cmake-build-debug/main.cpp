#include <iostream>
#include "pcUtilities.h"
#include "pcCombo.h"
#include "mergeSort.h"
#include "quickSort.h"
#include <chrono>
#include <algorithm>
using namespace std;

int main() {
    pcUtilities* pc = new pcUtilities;
    pcCombo* combo = new pcCombo;

    pc->readInjsonlCPU("JSONL/cpu.jsonl");
    pc->readInjsonlGPU("JSONL/gpu.jsonl");

    pc->readInjsonlPSU("JSONL/power-supply.jsonl");
    pc->readInjsonlRAM("JSONL/memory.jsonl");
    pc->readInjsonlMB("JSONL/motherboard.jsonl");
    pc->readInjsonlStr("JSONL/internal-hard-drive.jsonl");

    pc->dupeVect();
    auto start = chrono::high_resolution_clock::now();
    quickSort(pc->GPUList, 0, pc->GPUList.size() - 1);
    quickSort(pc->CPUList, 0, pc->CPUList.size() - 1);
    quickSort(pc->PSUList, 0, pc->PSUList.size() - 1);
    quickSort(pc->RAMList, 0, pc->RAMList.size() - 1);
    quickSort(pc->MBList, 0, pc->MBList.size() - 1);
    quickSort(pc->STRList, 0, pc->STRList.size() - 1);
    auto stop = chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    cout << "Time taken by quickSort: " << duration.count() << " milliseconds" << std::endl;

    start = chrono::high_resolution_clock::now();
    mergeSort(pc->GPUList2, 0, pc->GPUList2.size() - 1);
    mergeSort(pc->CPUList2, 0, pc->CPUList2.size() - 1);
    mergeSort(pc->PSUList2, 0, pc->PSUList2.size() - 1);
    mergeSort(pc->RAMList2, 0, pc->RAMList2.size() - 1);
    mergeSort(pc->MBList2, 0, pc->MBList2.size() - 1);
    mergeSort(pc->STRList2, 0, pc->STRList2.size() - 1);
    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    cout << "Time taken by mergeSort: " << duration.count() << " milliseconds" << std::endl;
    cout << pc->CPUList2.size()<< " cpu" << endl;
    cout << pc->GPUList2.size()<< " gpu" << endl;
    cout << pc->PSUList2.size()<< " psu" << endl;
    cout << pc->RAMList2.size()<< " ram" << endl;
    cout << pc->MBList2.size()<< " mb" << endl;
    cout << pc->STRList2.size()<< " str" << endl;
    reverse(pc->CPUList.begin(), pc->CPUList.end());
    reverse(pc->GPUList.begin(), pc->GPUList.end());
    reverse(pc->PSUList.begin(), pc->PSUList.end());
    reverse(pc->RAMList.begin(), pc->RAMList.end());
    reverse(pc->MBList.begin(), pc->MBList.end());
    reverse(pc->STRList.begin(), pc->STRList.end());


//    cout << pc->sortedList.size()<< "sorted list" << endl;
    float priceCPU, priceGPU, pricePSU, priceRAM, priceMB, priceSTR, pricePC;
    cout << "Enter your budget for PC: ";
    cin >> pricePC;
    priceCPU = pricePC * .25;
    priceGPU = pricePC * .35;
    priceMB = pricePC * .15;
    priceRAM = pricePC * .1;
    pricePSU = pricePC * .1;
    priceSTR = pricePC * .05;
    cout << priceCPU << " " << priceGPU << " " << pricePSU << " " << priceRAM << " " << priceMB << " " << priceSTR << endl;

    int cpuCount= 0;
    for (int i = 0; i < pc->CPUList.size(); ++i) {
        if(pc->CPUList[i].price > priceCPU){
            cpuCount++;
        }
    }
    int gpuCount= 0;
    for (int i = 0; i < pc->GPUList.size(); ++i) {
        if(pc->GPUList[i].price > priceGPU){
            gpuCount++;
        }
    }
    int psuCount= 0;
    for (int i = 0; i < pc->PSUList.size(); ++i) {
        if(pc->PSUList[i].price > pricePSU){
            psuCount++;
        }
    }
    int ramCount= 0;
    for (int i = 0; i < pc->RAMList.size(); ++i) {
        if(pc->RAMList[i].price > priceRAM){
            ramCount++;
        }
    }
    int mbCount= 0;
    for (int i = 0; i < pc->MBList.size(); ++i) {
        if(pc->MBList[i].price > priceMB){
            mbCount++;
        }
    }
    int strCount= 0;
    for (int i = 0; i < pc->STRList.size(); ++i) {
        if(pc->STRList[i].price > priceSTR){
            strCount++;
        }
    }
    cout << cpuCount << " " << gpuCount << " " << psuCount << " " << ramCount << " " << mbCount << " " << strCount << endl;
    cout << endl;



//    if(cpuCount < 100){
//        int remaining = 200 - cpuCount;
//        for(int i = cpuCount; i >= 0; --i) {
//            pcCombo nasa =  pcCombo(pc->CPUList[i], pc->GPUList[gpuCount], pc->PSUList[psuCount],
//                                                  pc->RAMList[ramCount], pc->MBList[mbCount], pc->STRList[strCount]);
//            pc->alterGPU(nasa);
//            pc->alterPSU(nasa);
//            pc->alterRAM(nasa);
//            pc->alterMB(nasa);
//            pc->alterSTR(nasa);
//        }
//        for(int i = 1; i < remaining + 1; i++){
//            pcCombo nasa =  pcCombo(pc->CPUList[i + cpuCount], pc->GPUList[gpuCount], pc->PSUList[psuCount],
//                                    pc->RAMList[ramCount], pc->MBList[mbCount], pc->STRList[strCount]);
//            pc->alterGPU(nasa);
//            pc->alterPSU(nasa);
//            pc->alterRAM(nasa);
//            pc->alterMB(nasa);
//            pc->alterSTR(nasa);
//        }
//    }
//    else if(cpuCount > pc->CPUList.size() - 100){
//        int remaining = 200 - (pc->CPUList.size() - cpuCount);
//        for(int i = 0; i < pc->CPUList.size() - cpuCount; i++){
//            pcCombo nasa =  pcCombo(pc->CPUList[i + cpuCount], pc->GPUList[gpuCount], pc->PSUList[psuCount],
//                                    pc->RAMList[ramCount], pc->MBList[mbCount], pc->STRList[strCount]);
//            pc->alterGPU(nasa);
//            pc->alterPSU(nasa);
//            pc->alterRAM(nasa);
//            pc->alterMB(nasa);
//            pc->alterSTR(nasa);
//
//        }
//        for(int i = remaining; i >= 0; --i){
//            pcCombo nasa =  pcCombo(pc->CPUList[cpuCount - i], pc->GPUList[gpuCount], pc->PSUList[psuCount],
//                                    pc->RAMList[ramCount], pc->MBList[mbCount], pc->STRList[strCount]);
//            pc->alterGPU(nasa);
//            pc->alterPSU(nasa);
//            pc->alterRAM(nasa);
//            pc->alterMB(nasa);
//            pc->alterSTR(nasa);
//        }
//    }
//    else{
//        for(int i = 1; i < 101; i++){
//            pcCombo nasa =  pcCombo(pc->CPUList[cpuCount + i], pc->GPUList[gpuCount], pc->PSUList[psuCount],
//                                    pc->RAMList[ramCount], pc->MBList[mbCount], pc->STRList[strCount]);
//            pc->alterGPU(nasa);
//            pc->alterPSU(nasa);
//            pc->alterRAM(nasa);
//            pc->alterMB(nasa);
//            pc->alterSTR(nasa);
//
//            pcCombo nasa2 =  pcCombo(pc->CPUList[cpuCount - i], pc->GPUList[gpuCount], pc->PSUList[psuCount],
//                                    pc->RAMList[ramCount], pc->MBList[mbCount], pc->STRList[strCount]);
//            pc->alterGPU(nasa2);
//            pc->alterPSU(nasa2);
//            pc->alterRAM(nasa2);
//            pc->alterMB(nasa2);
//            pc->alterSTR(nasa2);
//        }
//    }


//    pcCombo nasa = pcCombo(pc->CPUList[cpuCount], pc->GPUList[gpuCount], pc->PSUList[psuCount],
//                           pc->RAMList[ramCount], pc->MBList[mbCount], pc->STRList[strCount]);
//    pc->alterCPU(nasa);
//    pc->alterGPU(nasa);
//    pc->alterPSU(nasa);
//    pc->alterRAM(nasa);
//    pc->alterMB(nasa);
//    pc->alterSTR(nasa);

//    for(int i = 0; i < pc->CPUList.size(); i++){
//        pcCombo nasa = pcCombo(pc->CPUList[i], pc->GPUList[gpuCount], pc->PSUList[psuCount],
//                               pc->RAMList[ramCount], pc->MBList[mbCount], pc->STRList[strCount]);
//        pc->alterGPU(nasa);
//        pc->alterPSU(nasa);
//        pc->alterRAM(nasa);
//        pc->alterMB(nasa);
//        pc->alterSTR(nasa);
//    }

//    string temp = "";
//    set<string> lol;
//    for (auto &i: pc->sortedList){
//        temp = i.cpu.name + i.gpu.name + i.ram.name + i.psu.name + i.str.name + i.mb.name;
//        lol.insert(temp);
//    }
//
//
//
//    cout << lol.size()<< " sorted list" << endl;

    for(int i = 0; i < pc->CPUList.size(); i++){
        pcCombo nasa = pcCombo(pc->CPUList[i], pc->GPUList[gpuCount], pc->PSUList[psuCount], pc->RAMList[ramCount], pc->MBList[mbCount], pc->STRList[strCount]);
        pc->alterGPU(nasa);
        pc->alterPSU(nasa);
        pc->alterRAM(nasa);
        pc->alterMB(nasa);
        pc->alterSTR(nasa);
    }

    for(int i = 0; i < pc->GPUList.size(); i++){
        pcCombo nasa = pcCombo(pc->CPUList[cpuCount], pc->GPUList[i], pc->PSUList[psuCount], pc->RAMList[ramCount], pc->MBList[mbCount], pc->STRList[strCount]);
        pc->alterCPU(nasa);
        pc->alterPSU(nasa);
        pc->alterRAM(nasa);
        pc->alterMB(nasa);
        pc->alterSTR(nasa);
    }

    for(int i = 0; i < pc->PSUList.size(); i++){
        pcCombo nasa = pcCombo(pc->CPUList[cpuCount], pc->GPUList[gpuCount], pc->PSUList[i], pc->RAMList[ramCount], pc->MBList[mbCount], pc->STRList[strCount]);
        pc->alterCPU(nasa);
        pc->alterGPU(nasa);
        pc->alterRAM(nasa);
        pc->alterMB(nasa);
        pc->alterSTR(nasa);
    }
    for(int i = 0; i < pc->RAMList.size(); i++){
        pcCombo nasa = pcCombo(pc->CPUList[cpuCount], pc->GPUList[gpuCount], pc->PSUList[psuCount], pc->RAMList[i], pc->MBList[mbCount], pc->STRList[strCount]);
        pc->alterCPU(nasa);
        pc->alterGPU(nasa);
        pc->alterPSU(nasa);
        pc->alterMB(nasa);
        pc->alterSTR(nasa);
    }
    for(int i = 0; i < pc->MBList.size(); i++){
        pcCombo nasa = pcCombo(pc->CPUList[cpuCount], pc->GPUList[gpuCount], pc->PSUList[psuCount], pc->RAMList[ramCount], pc->MBList[i], pc->STRList[strCount]);
        pc->alterCPU(nasa);
        pc->alterGPU(nasa);
        pc->alterPSU(nasa);
        pc->alterRAM(nasa);
        pc->alterSTR(nasa);
    }
    for(int i = 0; i < pc->STRList.size(); i++){
        pcCombo nasa = pcCombo(pc->CPUList[cpuCount], pc->GPUList[gpuCount], pc->PSUList[psuCount], pc->RAMList[ramCount], pc->MBList[mbCount], pc->STRList[i]);
        pc->alterCPU(nasa);
        pc->alterGPU(nasa);
        pc->alterPSU(nasa);
        pc->alterRAM(nasa);
        pc->alterMB(nasa);
    }
    cout << pc->sortedList.size() << " sorted list orginial" <<endl;
    pc->compareParts();
    cout << pc->compList.size() << " comp list" <<endl;
    string temp = "";
    set<string> lol;
    for (auto &i: pc->compList){
        temp = i.cpu.name + i.gpu.name + i.ram.name + i.psu.name + i.str.name + i.mb.name;
        lol.insert(temp);
    }
    cout << lol.size()<< " set + compList" << endl;


    //pc->comboMaker(*combo);
//    pc->comboMaker();
    return 0;
}

