//
// Created by Maksym Marek on 12/3/2023.
//
#include "PCUtilities.h"
#ifndef PROJECT_FINAL_MERGESORT_H

//The merging step of merge sort
template <typename T>
void merge(vector<T>& vec, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<T> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = vec[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = vec[mid + 1 + j];

    int i = 0, j = 0, k = left;
    //Use indexes to track which part of the merge sort
    while (i < n1 && j < n2) {
        if (L[i].price <= R[j].price) { // compare based on price
            vec[k] = L[i];
            i++;
        } else {
            vec[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        vec[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        vec[k] = R[j];
        j++;
        k++;
    }
}

template <typename T>
void mergeSorts(vector<T>& vec, int left, int right) {
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    mergeSorts(vec, left, mid); //recursively call merge sort
    mergeSorts(vec, mid + 1, right);
    merge(vec, left, mid, right);
}

#define PROJECT_FINAL_MERGESORT_H

#endif //PROJECT_FINAL_MERGESORT_H
