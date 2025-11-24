#include <iostream>
#include <string>
#include <cstdlib>

#include <cassert>
#include <ctime>
#include <cmath>
#include <time.h>
#include <functional>

#include "DynamicArray.h"

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

        if (rightChild < array.size()) {
            if (greatest == parent && cmp(array[rightChild], array[parent]) > 0 ||
                greatest == leftChild && cmp(array[rightChild], array[leftChild]) > 0) {
                greatest = rightChild;
            }
        }

        if (greatest != parent) {
            array.swap(parent, greatest);
            bubbleDown(greatest, cmp);
        }
    }

    int getParent(int index) {
        return (index - 1) / 2;
    }

    int getChild(int index) {
        return index * 2 + 1;
    }

    std::string toString(std::string (*toStringObj)(const T&)) { return array.toString(toStringObj); };
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

    DynamicArray<SomeObject> *dynamicArray = new DynamicArray<SomeObject>();

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

    maxHeap->add(s0, compare);
    maxHeap->add(s3, compare);
    maxHeap->add(s4, compare);
    maxHeap->add(s11, compare);
    maxHeap->add(s5, compare);
    maxHeap->add(s5, compare);


    std::cout << maxHeap->toString(toStringObj) << std::endl;
    std::cout << toStringObj(maxHeap->pop(compare)) << std::endl;
    std::cout << maxHeap->toString(toStringObj) << std::endl;
    std::cout << toStringObj(maxHeap->pop(compare)) << std::endl;
    std::cout << maxHeap->toString(toStringObj) << std::endl;
    std::cout << toStringObj(maxHeap->pop(compare)) << std::endl;
    std::cout << maxHeap->toString(toStringObj) << std::endl;
    std::cout << toStringObj(maxHeap->pop(compare)) << std::endl;
    std::cout << maxHeap->toString(toStringObj) << std::endl;
    std::cout << toStringObj(maxHeap->pop(compare)) << std::endl;
    std::cout << maxHeap->toString(toStringObj) << std::endl;
    std::cout << toStringObj(maxHeap->pop(compare)) << std::endl;
    std::cout << maxHeap->toString(toStringObj) << std::endl;

    // // Small correctness check
    // assertTests(maxHeap);

    // // Maximum order: 9 (int overflow)
    // int maxOrder = 7;
    // int columnWidth = 11;

    // struct TestArguments {
    //     bool enabled;
    //     std::string name;
    //     std::function<void()> body;
    //     bool requiresFill;
    //     bool multiRun;
    // };

    // // Change first value (enabled) to reduce number of tests
    // TestArguments testMethods[] = {
    //     {true, "add()", [maxHeap]() { maxHeap->add(createRandom(), compare); }, false, true},
    //     {true, "find()", [maxHeap]() { maxHeap->find(createRandom(), compare); }, true, true},
    //     {true, "remove()", [maxHeap]() { maxHeap->remove(createRandom(), compare); }, true, true},
    //     {true, "preorder()", [maxHeap]() { maxHeap->preorder(); }, true, false},
    //     {true, "inorder()", [maxHeap]() { maxHeap->inorder(); }, true, false},
    //     {true, "clear()", [maxHeap]() { maxHeap->clear(); }, true, false}
    // };

    // int countMethodsToPrint = 0;
    // for (const TestArguments& testMethod : testMethods) {
    //     if (testMethod.enabled) countMethodsToPrint++;
    // }

    // printSeparator(countMethodsToPrint, columnWidth);
    // std::cout << "|" << getColumn("elements", columnWidth, ' ', '|');
    // for (const TestArguments& testMethod : testMethods) {
    //     if (testMethod.enabled) std::cout << getColumn(testMethod.name, columnWidth, ' ', '|');
    // }
    // std::cout << std::endl;
    // printSeparator(countMethodsToPrint, columnWidth);

    // // performance tests
    // for (int o = 1; o <= maxOrder; o++) {
    //     int elements = pow(10, o);
    //     std::cout << "|" << getColumn(std::to_string(elements), columnWidth, ' ', '|');
    //     for (const TestArguments& testMethod : testMethods) {
    //         if (testMethod.enabled) {
    //             std::cout <<
    //             measureMethod(testMethod.body, maxHeap, elements,
    //                           testMethod.requiresFill, columnWidth,
    //                           testMethod.multiRun)
    //             << std::flush;
    //         }
    //     }
    //     std::cout << std::endl;
    // }
    // printSeparator(countMethodsToPrint, columnWidth);

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

// void fillBST(int elements, BST <SomeObject>* bst) {
//     for (int i = 0; i < elements; i++) {
//         bst->add(createRandom(), compare);
//     }
// }

template <typename Func>
std::string measureMethod(Func func, MaxHeap <SomeObject>* maxHeap, int elements, bool requiresFill, int width, bool multiRun) {
    if (requiresFill) fillBST(elements, maxHeap);

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

}