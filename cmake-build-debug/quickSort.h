//
// Created by Maksym Marek on 12/3/2023.
//
#include "pcUtilities.h"
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


/*template <typename T>
int partition(vector<T>& arr, int low, int high){
    int pivot = arr[high].price;
    int i = low - 1;

    for(int j = low; j < high; ++j) {
        if(arr[j].price < pivot){
            i++;
            swap(arr[i], arr[j]);

        }
    }

    swap(arr[i + 1], arr[high]);
    return i + 1;
}


template <typename T>
void quicksort(vector<T>& arr, int low, int high){
    if(low < high) {
        int pivotIndex = partition(arr, low, high);
        quicksort(arr, low, pivotIndex -1);
        quicksort(arr, pivotIndex + 1, high);
    }
}*/

#endif //PROJECT_FINAL_QUICKSORT_H
