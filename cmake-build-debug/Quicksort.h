//
// Created by Maksym Marek on 12/3/2023.
//
#include "PCUtilities.h"
#ifndef PROJECT_FINAL_QUICKSORT_H
#define PROJECT_FINAL_QUICKSORT_H

template <typename T>
int partition(vector<T>& vec, int start, int end) { //partition function based on pivot
    int pivot = vec[start].price; //declare pivot as the lower index
    int i = start + 1;
    int j = end;

    while(true) { //swap based on values
        while(i <= j && vec[i].price <= pivot) { //Increase lower Index
            i++;
        }
        while(i <= j && vec[j].price > pivot) { //Decrease upper Index
            j--;
        }
        if(i >= j) break; //When indexes meet swap
        swap(vec[i], vec[j]);
    }
    //Swap pivot and upper
    swap(vec[start], vec[j]);
    return j;
}

template <typename T>
void quickSorts(vector<T>& vec, int start, int end) { //function call
    if(start >= end) return;
    int p = partition(vec, start, end); //call partition
    quickSorts(vec, start, p - 1); //recursively call quicksort
    quickSorts(vec, p + 1, end);
}




#endif //PROJECT_FINAL_QUICKSORT_H
