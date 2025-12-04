#include <iostream>
#include <string>
#include <cstdlib>

#include <cassert>
#include <ctime>
#include <cmath>
#include <time.h>
#include <functional>

#include "DynamicArray.h"
#include "LinkedList.h"

template <typename T>
struct HashTable {
    struct Pair {
        std::string key;
        T val;
        Pair() {};
        Pair(std::string keyInput, T valInput) {
            key = keyInput;
            val = valInput;
        }
    };
    
    std::string toStringPair(const Pair& obj) {
        return std::to_string(obj.key) + ", " + obj.val;
    }

    DynamicArray<LinkedList<Pair>> *array = new DynamicArray<LinkedList<Pair>>();

    int add(std::string key, T val) {
        Pair *pair = new Pair(key, val);
        int index = hash(pair->key);
        LinkedList<Pair> list = array->at(index);
        if (list.size == 0) {
            list.addFront(*pair);
        }
        return 0;
    }

    int hash(std::string key) {
        long res = 0;
        int size = key.size();
        for (int i = 0; i < size; i++) {
            res += (long)(key[i]) * pow(31, size - 1 - i);
        }
        return res % array->checkMaxSize();
    }

    void toString() {
        for (int i = 0; i < array->checkMaxSize(); i++) {
            std::cout << i << ":" << std::endl;
        }
    }

private:

};

template <typename T>
struct SomeObject {
    std::string key;
    T val;

    bool operator==(const SomeObject& other) const {
        return key == other.key && val == other.val;
    }
};

// SomeObject createRandom();

// int compare(const SomeObject& new_obj, const SomeObject& list_obj);
// std::string toStringObj(const SomeObject& obj);

// std::string getColumn(std::string value, int width, char filling, char last);
// void printSeparator(int numOfMethods,int width);

// void fillBST(int elements, BST <SomeObject>* bst);

// template <typename Func>
// std::string measureMethod(Func func, BST <SomeObject>* bst, int elements, bool requiresFill, int width, bool multiRun);

void assertTests(HashTable <int>* hashTable);

int main() {
    srand(time(0));
    HashTable <int>* hashTable = new HashTable <int>();

    // Small correctness check
    assertTests(hashTable);

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
    //     {true, "add()", [bst]() { bst->add(createRandom(), compare); }, false, true},
    //     {true, "find()", [bst]() { bst->find(createRandom(), compare); }, true, true},
    //     {true, "remove()", [bst]() { bst->remove(createRandom(), compare); }, true, true},
    //     {true, "preorder()", [bst]() { bst->preorder(); }, true, false},
    //     {true, "inorder()", [bst]() { bst->inorder(); }, true, false},
    //     {true, "clear()", [bst]() { bst->clear(); }, true, false}
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
    //             measureMethod(testMethod.body, bst, elements,
    //                           testMethod.requiresFill, columnWidth,
    //                           testMethod.multiRun)
    //             << std::flush;
    //         }
    //     }
    //     std::cout << std::endl;
    // }
    // printSeparator(countMethodsToPrint, columnWidth);

    // delete bst;
}

// SomeObject createRandom() {
//     return { rand() % 1000000, (char)('a' + rand() % 26) };
// };

// int compare(const SomeObject& new_obj, const SomeObject& list_obj) {
//     if (new_obj.field_1 > list_obj.field_1) return 1;
//     if (new_obj.field_1 < list_obj.field_1) return -1;
//     if (new_obj.field_2 > list_obj.field_2) return 1;
//     if (new_obj.field_2 < list_obj.field_2) return -1;
//     return 0;
// }

// std::string toStringObj(const SomeObject& obj) {
//     return std::to_string(obj.field_1) + ", " + obj.field_2;
// }

// std::string getColumn(std::string value, int width, char filling, char last) {
//     if (value.size() < width) {
//         return std::string(width - value.size(), filling) + value + last;
//     }
//     return value;
// }

// void printSeparator(int numOfMethods,int width) {
//     std::cout << "+";
//     for (int i = 0; i <= numOfMethods; i++) {
//         std::cout << getColumn("", width, '-', '+');
//     }
//     std::cout << std::endl;
// }

// void fillBST(int elements, BST <SomeObject>* bst) {
//     for (int i = 0; i < elements; i++) {
//         bst->add(createRandom(), compare);
//     }
// }

// template <typename Func>
// std::string measureMethod(Func func, BST <SomeObject>* bst, int elements, bool requiresFill, int width, bool multiRun) {
//     if (requiresFill) fillBST(elements, bst);

//     clock_t t1 = clock();
//     if (multiRun) {
//         for (int i = 0; i < elements; i++) {
//             func();
//         }
//     } else {
//         func();
//     }
//     clock_t t2 = clock();

//     bst->clear();

//     double currTime = (t2 - t1) / (double)CLOCKS_PER_SEC;
//     std:: string strTime = std::to_string(currTime);
//     strTime.erase(strTime.size() - 3);
//     return getColumn(strTime + 's', width, ' ', '|');
// }

void assertTests(HashTable <int>* hashTable) {
    SomeObject<int> s0 = { "zero", 0 };
    SomeObject<int> s1 = { "one", 1 };
    SomeObject<int> s2 = { "two", 2 };
    SomeObject<int> s3 = { "three", 3 };
    SomeObject<int> s4 = { "four", 4 };
    SomeObject<int> s5 = { "five", 5 };
    SomeObject<int> s6 = { "six", 6 };
    SomeObject<int> s7 = { "seven", 7 };
    SomeObject<int> s8 = { "eight", 8 };
    SomeObject<int> s9 = { "nine", 9 };
    SomeObject<int> s10 = { "ten", 10 };
    SomeObject<int> s11 = { "eleven", 11 };

    hashTable->add(s0.key, s0.val);

    hashTable->toString();
}