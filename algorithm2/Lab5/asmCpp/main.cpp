#include <iostream>
#include <string>
#include <cstdlib>

#include <cassert>
#include <ctime>
#include <cmath>
#include <time.h>
#include <functional>

#include "DynamicArray.h"

struct SomeObject {
    int field_1;
    char field_2;

    bool operator==(const SomeObject& other) const {
        return field_1 == other.field_1 && field_2 == other.field_2;
    }
};

extern "C" {
    int maxHeapAdd(struct MaxHeap *heap, SomeObject val, int (*cmp)(const SomeObject*, const SomeObject*));
    SomeObject maxHeapPop(struct MaxHeap *heap, int (*cmp)(const SomeObject*, const SomeObject*));
    int DynamicArray_add(DynamicArray<SomeObject> *arr, SomeObject val, int (*cmp)(const SomeObject*, const SomeObject*)) { return arr->add(val); };
    void DynamicArray_swap(DynamicArray<SomeObject> *arr, int index1, int index2) { arr->swap(index1, index2); };
    int DynamicArray_size(DynamicArray<SomeObject> *arr) { return arr->size(); };
    int DynamicArray_remove(DynamicArray<SomeObject> *arr) { return arr->remove(); };
}

struct MaxHeap {
    DynamicArray<SomeObject> array;

    void add(SomeObject val, int (*cmp)(const SomeObject*, const SomeObject*)) {
        maxHeapAdd(this, val, cmp);
    };

    SomeObject pop(int (*cmp)(const SomeObject*, const SomeObject*)) {
        if (array.size() == 0) throw std::out_of_range("Index out of range");
        return maxHeapPop(this, cmp);
    };

    void clear() { array.clear(); };

    std::string toString(std::string (*toStringObj)(const SomeObject&)) { return array.toString(toStringObj); };
};

SomeObject createRandom();

int compare(const SomeObject* new_obj, const SomeObject* list_obj);
std::string toStringObj(const SomeObject& obj);

std::string getColumn(std::string value, int width, char filling, char last);
void printSeparator(int numOfMethods,int width);

template <typename Func>
std::string measureMethod(Func func, MaxHeap* maxHeap, int elements, bool requiresFill, int width, bool multiRun);

void assertTests(MaxHeap* maxHeap);

int main() {
    srand(time(0));
    MaxHeap *maxHeap = new MaxHeap();

    // Small correctness check
    assertTests(maxHeap);

    // Maximum order: 9 (int overflow)
    int maxOrder = 8;
    int columnWidth = 11;

    struct TestArguments {
        bool enabled;
        std::string name;
        std::function<void()> body;
        bool requiresFill;
        bool multiRun;
    };

    // Change first value (enabled) to reduce number of tests
    TestArguments testMethods[] = {
        {true, "add()", [maxHeap]() { maxHeap->add(createRandom(), compare); }, false, true},
        {true, "pop()", [maxHeap]() { maxHeap->pop(compare); }, true, true},
        {true, "clear()", [maxHeap]() { maxHeap->clear(); }, true, false}
    };

    int countMethodsToPrint = 0;
    for (const TestArguments& testMethod : testMethods) {
        if (testMethod.enabled) countMethodsToPrint++;
    }

    printSeparator(countMethodsToPrint, columnWidth);
    std::cout << "|" << getColumn("elements", columnWidth, ' ', '|');
    for (const TestArguments& testMethod : testMethods) {
        if (testMethod.enabled) std::cout << getColumn(testMethod.name, columnWidth, ' ', '|');
    }
    std::cout << std::endl;
    printSeparator(countMethodsToPrint, columnWidth);

    // performance tests
    for (int o = 1; o <= maxOrder; o++) {
        int elements = pow(10, o);
        std::cout << "|" << getColumn(std::to_string(elements), columnWidth, ' ', '|');
        for (const TestArguments& testMethod : testMethods) {
            if (testMethod.enabled) {
                std::cout <<
                measureMethod(testMethod.body, maxHeap, elements,
                              testMethod.requiresFill, columnWidth,
                              testMethod.multiRun)
                << std::flush;
            }
        }
        std::cout << std::endl;
    }
    printSeparator(countMethodsToPrint, columnWidth);

    delete maxHeap;
}

SomeObject createRandom() {
    return { rand() % 1000000, (char)('a' + rand() % 26) };
};

int compare(const SomeObject* new_obj, const SomeObject* list_obj) {
    if (new_obj->field_1 > list_obj->field_1) return 1;
    if (new_obj->field_1 < list_obj->field_1) return -1;
    if (new_obj->field_2 > list_obj->field_2) return 1;
    if (new_obj->field_2 < list_obj->field_2) return -1;
    return 0;
}

std::string toStringObj(const SomeObject& obj) {
    return std::to_string(obj.field_1) + ", " + obj.field_2;
}

std::string getColumn(std::string value, int width, char filling, char last) {
    if (value.size() < width) {
        return std::string(width - value.size(), filling) + value + last;
    }
    return value;
}

void printSeparator(int numOfMethods,int width) {
    std::cout << "+";
    for (int i = 0; i <= numOfMethods; i++) {
        std::cout << getColumn("", width, '-', '+');
    }
    std::cout << std::endl;
}

void fillHeap(int elements, MaxHeap *maxHeap) {
    for (int i = 0; i < elements; i++) {
        maxHeap->add(createRandom(), compare);
    }
}

template <typename Func>
std::string measureMethod(Func func, MaxHeap *maxHeap, int elements, bool requiresFill, int width, bool multiRun) {
    if (requiresFill) fillHeap(elements, maxHeap);

    clock_t t1 = clock();
    if (multiRun) {
        for (int i = 0; i < elements; i++) {
            func();
        }
    } else {
        func();
    }
    clock_t t2 = clock();

    maxHeap->clear();

    double currTime = (t2 - t1) / (double)CLOCKS_PER_SEC;
    std:: string strTime = std::to_string(currTime);
    strTime.erase(strTime.size() - 3);
    return getColumn(strTime + 's', width, ' ', '|');
}

void assertTests(MaxHeap* maxHeap) {
    SomeObject s0 = { 0, 'a' };
    SomeObject s1 = { 1, 'b' };
    SomeObject s2 = { 2, 'c' };
    SomeObject s3 = { 3, 'd' };
    SomeObject s4 = { 4, 'e' };
    SomeObject s5 = { 5, 'f' };
    SomeObject s6 = { 6, 'g' };
    SomeObject s7 = { 7, 'h' };
    SomeObject s8 = { 8, 'i' };
    SomeObject s9 = { 9, 'j' };
    SomeObject s10 = { 10, 'k' };
    SomeObject s11 = { 11, 'i' };

    MaxHeap *maxHeap2 = new MaxHeap();

    maxHeap->add(s0, compare);
    maxHeap->add(s3, compare);
    maxHeap->add(s4, compare);
    maxHeap->add(s11, compare);
    maxHeap->add(s5, compare);
    maxHeap->add(s1, compare);
    maxHeap->add(s2, compare);
    maxHeap->add(s6, compare);
    maxHeap->add(s10, compare);
    maxHeap->add(s7, compare);
    maxHeap->add(s9, compare);
    maxHeap->add(s8, compare);

    assert(maxHeap->pop(compare) == s11);
    assert(maxHeap->pop(compare) == s10);
    assert(maxHeap->pop(compare) == s9);
    assert(maxHeap->pop(compare) == s8);
    assert(maxHeap->pop(compare) == s7);
    assert(maxHeap->pop(compare) == s6);
    assert(maxHeap->pop(compare) == s5);
    assert(maxHeap->pop(compare) == s4);
    assert(maxHeap->pop(compare) == s3);
    assert(maxHeap->pop(compare) == s2);
    assert(maxHeap->pop(compare) == s1);
    assert(maxHeap->pop(compare) == s0);

    maxHeap->add(s11, compare);
    maxHeap->add(s10, compare);

    maxHeap->clear();

    maxHeap->add(s1, compare);

    assert(maxHeap->pop(compare) == s1);
}