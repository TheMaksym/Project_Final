#include <iostream>
#include "pcUtilities.h"
#include "pcCombo.h"
using namespace std;

int main() {
    pcUtilities* pc = new pcUtilities;
    pc->readInjsonlCPU("JSONL/cpu.jsonl"); //works
    pc->readInjsonlGPU("JSONL/gpu.jsonl"); //works

    pc->readInjsonlPSU("JSONL/power-supply.jsonl");
    pc->readInjsonlRAM("JSONL/memory.jsonl");
    pc->readInjsonlMB("JSONL/motherboard.jsonl");
    pc->readInjsonlStr("JSONL/internal-hard-drive.jsonl");

    return 0;
}

