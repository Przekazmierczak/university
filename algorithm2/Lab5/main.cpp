                    #include <iostream>
#include <string>
#include <cstdlib>

#include <cassert>
#include <ctime>
#include <cmath>
#include <time.h>
#include <functional>

#include "DynamicArray.h"

extern "C" int maxHeapAdd(struct MaxHeap2 *heap, int val, int (*cmp)(const int, const int));
extern "C" int DynamicArray_add(DynamicArray<int> *arr, int val, int (*cmp)(const int, const int)) {
    return arr->add(val);
}
extern "C" void DynamicArray_swap(DynamicArray<int> *arr, int index1, int index2) {
    arr->swap(index1, index2);
}
extern "C" int DynamicArray_size(DynamicArray<int> *arr) {
    return arr->size();
}

//extern "C" int maxHeapGetParent(int index);
//extern "C" int maxHeapBubbleUp(struct MaxHeap2 *heap, int child, int (*cmp)(const int, const int));

int elementCompare(int new_obj, int list_obj) {
    if (new_obj > list_obj) return 1;
    if (new_obj < list_obj) return -1;
    return 0;
};


template <typename T>
struct MaxHeap {
    DynamicArray<T> array;

    void add(T value, int (*cmp)(const T&, const T&)) {
        array.add(value);
        bubbleUp(array.size() - 1, cmp);
    }

    T pop(int (*cmp)(const T&, const T&)) {
        if (array.size() == 0) throw std::out_of_range("Index out of range");
        T res = array[0];
        array.swap(0, array.size() - 1);
        array.remove();
        bubbleDown(0, cmp);
        return res;
    }

    void clear() { array.clear(); };

    std::string toString(std::string (*toStringObj)(const T&)) { return array.toString(toStringObj); };

    // private:
    void bubbleUp(int child, int (*cmp)(const T&, const T&)) {
        if (child == 0) return;
        int parent = getParent(child);
        if (cmp(array[child], array[parent]) > 0) {
            array.swap(child, parent);
            bubbleUp(parent, cmp);
        }
    }

    void bubbleDown(int parent, int (*cmp)(const T&, const T&)) {
        int leftChild = getChild(parent);
        int rightChild = leftChild + 1;

        int greatest = parent;

        if (leftChild < array.size() && cmp(array[leftChild], array[parent]) > 0) {
            greatest = leftChild;
        }

        if (rightChild < array.size() && cmp(array[rightChild], array[greatest]) > 0) {
            greatest = rightChild;
        }

        if (greatest != parent) {
            array.swap(parent, greatest);
            bubbleDown(greatest, cmp);
        }
    }

    static int getParent(int index) {
        return (index - 1) / 2;
    }

    static int getChild(int index) {
        return index * 2 + 1;
    }
};

struct MaxHeap2 {
    DynamicArray<int> array;

    void add(int val, int (*cmp)(const int, const int)) {
        maxHeapAdd(this, val, cmp);
    };

    // static int getParent(int index) {
    //     return maxHeapGetParent(index);
    // }

    // void bubbleUp(int child, int (*cmp)(const int, const int)) {
    //     maxHeapBubbleUp(this, child, cmp);
    // }

    // void bubbleUp(int child, int (*cmp)(int, int)) {
    //     if (child == 0) return;
    //     int parent = getParent(child);
    //     if (cmp(array[child], array[parent]) > 0) {
    //         array.swap(child, parent);
    //         bubbleUp(parent, cmp);
    //     }
    // }
};

struct SomeObject {
    int field_1;
    char field_2;

    bool operator==(const SomeObject& other) const {
        return field_1 == other.field_1 && field_2 == other.field_2;
    }
};

SomeObject createRandom();

int compare(const SomeObject& new_obj, const SomeObject& list_obj);
std::string toStringObj(const SomeObject& obj);

std::string getColumn(std::string value, int width, char filling, char last);
void printSeparator(int numOfMethods,int width);

void fillBST(int elements, MaxHeap <SomeObject>* maxHeap);

template <typename Func>
std::string measureMethod(Func func, MaxHeap <SomeObject>* maxHeap, int elements, bool requiresFill, int width, bool multiRun);

void assertTests(MaxHeap <SomeObject>* da);

int main() {
    srand(time(0));
    MaxHeap<SomeObject> *maxHeap = new MaxHeap<SomeObject>();

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

int compare(const SomeObject& new_obj, const SomeObject& list_obj) {
    if (new_obj.field_1 > list_obj.field_1) return 1;
    if (new_obj.field_1 < list_obj.field_1) return -1;
    if (new_obj.field_2 > list_obj.field_2) return 1;
    if (new_obj.field_2 < list_obj.field_2) return -1;
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

void fillHeap(int elements, MaxHeap <SomeObject>* maxHeap) {
    for (int i = 0; i < elements; i++) {
        maxHeap->add(createRandom(), compare);
    }
}

template <typename Func>
std::string measureMethod(Func func, MaxHeap <SomeObject>* maxHeap, int elements, bool requiresFill, int width, bool multiRun) {
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

void assertTests(MaxHeap <SomeObject>* maxHeap) {
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

    std::cout << maxHeap->getParent(0) << std::endl;

    MaxHeap2 *maxHeap2 = new MaxHeap2();
    //std::cout << maxHeap2->getParent(10) << std::endl;
    maxHeap2->add(2, elementCompare);
    std::cout << maxHeap2->array[0] << std::endl;
    maxHeap2->add(1, elementCompare);
    std::cout << maxHeap2->array[0] << maxHeap2->array[1] << std::endl;
    maxHeap2->add(8, elementCompare);
    std::cout << maxHeap2->array[0] << maxHeap2->array[1] << maxHeap2->array[2] << std::endl;
    maxHeap2->add(3, elementCompare);
    std::cout << maxHeap2->array[0] << maxHeap2->array[1] << maxHeap2->array[2] << maxHeap2->array[3] << std::endl;
    maxHeap2->add(4, elementCompare);
    std::cout << maxHeap2->array[0] << maxHeap2->array[1] << maxHeap2->array[2] << maxHeap2->array[3] << maxHeap2->array[4] << std::endl;
    maxHeap2->add(9, elementCompare);
    std::cout << maxHeap2->array[0] << maxHeap2->array[1] << maxHeap2->array[2] << maxHeap2->array[3] << maxHeap2->array[4] << maxHeap2->array[5] << std::endl;

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