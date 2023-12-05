//
// Created by Maksym Marek on 12/3/2023.
//
#include "PCUtilities.h"
#ifndef PROJECT_FINAL_QUICKSORT_H
#define PROJECT_FINAL_QUICKSORT_H

template <typename T>
int partition(vector<T>& vec, int start, int end) {
    int pivot = vec[start].price;
    int i = start + 1;
    int j = end;

    while(true) {
        while(i <= j && vec[i].price <= pivot) {
            i++;
        }
        while(i <= j && vec[j].price > pivot) {
            j--;
        }
        if(i >= j) break;
        swap(vec[i], vec[j]);
    }

    swap(vec[start], vec[j]);
    return j;
}

template <typename T>
void quickSort(vector<T>& vec, int start, int end) {
    if(start >= end) return;
    int p = partition(vec, start, end);
    quickSort(vec, start, p - 1);
    quickSort(vec, p + 1, end);
}




#endif //PROJECT_FINAL_QUICKSORT_H
