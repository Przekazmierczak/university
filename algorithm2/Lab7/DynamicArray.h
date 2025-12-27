#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include <iostream>
#include <string>

template <typename T>
struct DynamicArray {
    T* array;

    DynamicArray() : ratio(2), currSize(0), maxSize(1) { array = new T[maxSize]; }
    DynamicArray(int sizeInput) : ratio(2), currSize(sizeInput), maxSize(sizeInput) { array = new T[sizeInput]; }
    DynamicArray(int currSizeInput, int maxSizeInput) : ratio(2), currSize(currSizeInput), maxSize(maxSizeInput) { array = new T[maxSizeInput]; }
    ~DynamicArray() { delete[] array; }

    int size() const { return currSize; }
    int checkMaxSize() const { return maxSize; }

    int add(T value);
    int remove();
    T& at(int index) const;
    T& operator[](int index) const { return at(index); }
    int set(int index, T newValue);
    int clear() { return resize(1, true); }
    std::string toString(std::string (*toStringObj)(const T&)) const;
    void sort(int (*cmp)(const T&, const T&));
    void swap(int index1, int index2);

private:    
    int ratio;
    int currSize;
    int maxSize;
    enum Status { SUCCESS = 0, FAIL = 1 };

    int resize(int newSize, bool resetCurrSize);
    void checkOutOfRange(int index) const;
    int getMemory(T* &array, int elements);
};

template <typename T>
int DynamicArray<T>::add(T value) {
    if (currSize == maxSize) {
        if (resize(maxSize * ratio, false) == FAIL) return FAIL;
    }
    array[currSize] = value;
    currSize++;
    return SUCCESS;
}

template <typename T>
int DynamicArray<T>::remove() {
    if (currSize == 0) return FAIL;
    currSize--;
    return SUCCESS;
}

template <typename T>
T& DynamicArray<T>::at(int index) const {
    checkOutOfRange(index);
    return array[index];
}

template <typename T>
int DynamicArray<T>::set(int index, T newValue) {
    checkOutOfRange(index);
    array[index] = newValue;
    return SUCCESS;
}

template <typename T>
std::string DynamicArray<T>::toString(std::string (*toStringObj)(const T&)) const {
    std::string str = "[";
    for (int i = 0; i < currSize; i++) {
        if (i != 0) str+= ";";
        str += toStringObj(array[i]);
    }
    str+= "]";

    return str;
}

template <typename T>
void DynamicArray<T>::sort(int (*cmp)(const T&, const T&)) {
    if (currSize == 0 || currSize == 1) return;

    bool ifSwapped = true;
    while (ifSwapped) {
        ifSwapped = false;
        for (int i = 0; i < currSize - 1; i++) {
            if (cmp(array[i], array[i + 1]) > 0) {
                swap(i, i + 1);
                ifSwapped = true;
            }
        }
    }
}

template <typename T>
int DynamicArray<T>::resize(int newSize, bool resetCurrSize) {
    T* newArray;
    if (getMemory(newArray, newSize) == FAIL) return FAIL;

    currSize = (resetCurrSize) ? 0 : currSize;
    maxSize = newSize;

    for (int i = 0; i < currSize; i++) {
        newArray[i] = array[i];
    }
    delete[] array;
    array = newArray;

    return SUCCESS;
}

template <typename T>
void DynamicArray<T>::checkOutOfRange(int index) const {
    if (index >= currSize || index < 0) {
        throw std::out_of_range("Index out of range");
    }
}

template <typename T>
int DynamicArray<T>::getMemory(T* &array, int elements) {
    try {
        array = new T[elements];
    } catch (const std::bad_alloc&) {
        return FAIL;
    }
    return SUCCESS;
}

template <typename T>
void DynamicArray<T>::swap(int index1, int index2) {
    T temp = array[index1];
    array[index1] = array[index2];
    array[index2] = temp;
}

#endif