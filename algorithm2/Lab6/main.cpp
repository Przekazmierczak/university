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

        static std::string toString(const Pair& pair) {
            return pair.key + " -> " + std::to_string(pair.val);
        }

        static int compare(const std::string& key, const Pair& pair) {
            return !(key == pair.key);
        }
    }; 

    DynamicArray<LinkedList<Pair>> *array = new DynamicArray<LinkedList<Pair>>(5, 5);

    ~HashTable() {
        clear();
        delete array;
    }
    
    int size() { return currSize; }
    int maxSize() { return array->size(); }

    int add(std::string key, T val) {
        int res = addHelper(key, val, array);
        if ((float)currSize / array->size() > 0.75) resizeRehash();
        return res;
    }

    Pair* find(std::string key) {
        int index = hash(key, array->size());
        return array->at(index).find(key, Pair::compare);
    }

    int remove(std::string key) {
        int index = hash(key, array->size());
        if (array->at(index).findRemove(key, Pair::compare) == 0) {
            currSize--;
            return SUCCESS;
        };
        return FAIL;
    }

    void clear() {
        for (int i = 0; i < array->size(); i++) {
            array->at(i).clear();
        }
        currSize = 0;
    }

    std::string toString() {
        int listMaxSize = 0;
        int occupiedList = 0;

        std::string str;

        str += "Hash Table:\n";
        str += "  Current size: " + std::to_string(currSize) + "\n";
        str += "  Max size: " + std::to_string(array->size()) + "\n";
        str += "  Table:\n";
        for (int i = 0; i < array->size(); i++) {
            if (array->at(i).size() > 0) {
                if (occupiedList < 8) {
                    str += "      " + std::to_string(i) + ":" + array->at(i).toString(Pair::toString) + "\n";
                } else if (occupiedList == 8) {
                    str += "      ...\n";
                }
                if (listMaxSize < array->at(i).size()) listMaxSize = array->at(i).size();
                occupiedList++;
            }
        }
        str += "  Stats:\n";
        str += "      List max size: " + std::to_string(listMaxSize) + "\n";
        str += "      Occupied list count: " + std::to_string(occupiedList) + "\n";
        if (occupiedList > 0) str += "      List avg size: " + std::to_string((float)currSize / occupiedList) + "\n";

        return str;
    }

private:
    int currSize = 0;
    enum Status { SUCCESS = 0, FAIL = 1 };

    int addHelper(std::string key, T val, DynamicArray<LinkedList<Pair>> *currArray) {
        int index = hash(key, currArray->size());

        Pair* currPair = currArray->at(index).find(key, Pair::compare);
        if (currPair != nullptr) {
            currPair->val = val;
            return SUCCESS;
        }

        if (currArray == array) currSize++;
        
        Pair pair(key, val);
        return currArray->at(index).addFront(pair);
    }

    int hash(std::string key, int arraySize) {
        long long res = 0;
        for (unsigned char c : key) {
            res = (res * 31 + c) % arraySize;
        }
        return (int)res;
    }

    int resizeRehash() {
        DynamicArray<LinkedList<Pair>> *newArray;
        try {
            newArray = new DynamicArray<LinkedList<Pair>>(array->size() * 2, array->size() * 2);
        } catch (const std::bad_alloc&) {
            return FAIL;
        }

        for (int i = 0; i < array->size(); i++) {
            for (int j = 0; j < array->at(i).size(); j++) {
                addHelper(array->at(i).at(j).key, array->at(i).at(j).val, newArray);
            }
        }

        delete array;
        array = newArray;
        return SUCCESS;
    }
};

std::string generateRandomKey();
int generateRandomVal();

std::string getColumn(std::string value, int width, char filling, char last);
void printSeparator(int numOfMethods,int width);

void fillHashTable(int elements, HashTable<int>* hashTable);

template <typename Func>
std::string measureMethod(Func func, HashTable<int>* hashTable, int elements, bool requiresFill, int width, bool multiRun);

void assertTests(HashTable <int>* hashTable);

int main() {
    srand(time(0));
    HashTable <int>* hashTable = new HashTable <int>();

    // Small correctness check
    assertTests(hashTable);

    // Maximum order: 9 (int overflow)
    int maxOrder = 7;
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
        {true, "add()", [hashTable]() { hashTable->add(generateRandomKey(), generateRandomVal()); }, false, true},
        {true, "find()", [hashTable]() { hashTable->find(generateRandomKey()); }, true, true},
        {true, "remove()", [hashTable]() { hashTable->remove(generateRandomKey()); }, true, true}
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
                measureMethod(testMethod.body, hashTable, elements,
                              testMethod.requiresFill, columnWidth,
                              testMethod.multiRun)
                << std::flush;
            }
        }
        std::cout << std::endl;
    }
    printSeparator(countMethodsToPrint, columnWidth);

    delete hashTable;
}

std::string generateRandomKey() {
    std::string key;
    for (int i = 0; i < 6; i++) {
        key += (char)('a' + rand() % 26);
    }
    return key;
};

int generateRandomVal() {
    return rand() % 1000000;
};

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

void fillHashTable(int elements, HashTable<int>* hashTable) {
    for (int i = 0; i < elements; i++) {
        hashTable->add(generateRandomKey(), generateRandomVal());
    }
}

template <typename Func>
std::string measureMethod(Func func, HashTable<int>* hashTable, int elements, bool requiresFill, int width, bool multiRun) {
    if (requiresFill) fillHashTable(elements, hashTable);

    clock_t t1 = clock();
    if (multiRun) {
        for (int i = 0; i < elements; i++) {
            func();
        }
    } else {
        func();
    }
    clock_t t2 = clock();

    hashTable->clear();

    double currTime = (t2 - t1) / (double)CLOCKS_PER_SEC;
    std:: string strTime = std::to_string(currTime);
    strTime.erase(strTime.size() - 3);
    return getColumn(strTime + 's', width, ' ', '|');
}

void assertTests(HashTable <int>* hashTable) {
    // Test add, overwrite, remove, add: "zero" -> 0
    hashTable->add("zero", 0);
    assert(hashTable->size() == 1);
    assert(hashTable->maxSize() == 5);
    assert(hashTable->find("zero")->val == 0);

    hashTable->add("zero", 1);
    assert(hashTable->size() == 1);
    assert(hashTable->maxSize() == 5);
    assert(hashTable->find("zero")->val == 1);

    hashTable->remove("zero");
    assert(hashTable->size() == 0);
    assert(hashTable->maxSize() == 5);
    assert(hashTable->find("zero") == nullptr);

    hashTable->add("zero", 0);
    assert(hashTable->size() == 1);
    assert(hashTable->find("zero")->val == 0);

    // Test add, overwrite, remove, add: "one" -> 1
    hashTable->add("one", 1);
    assert(hashTable->size() == 2);
    assert(hashTable->maxSize() == 5);
    assert(hashTable->find("one")->val == 1);

    hashTable->add("one", 2);
    assert(hashTable->size() == 2);
    assert(hashTable->maxSize() == 5);
    assert(hashTable->find("one")->val == 2);

    hashTable->remove("one");
    assert(hashTable->size() == 1);
    assert(hashTable->maxSize() == 5);
    assert(hashTable->find("one") == nullptr);

    hashTable->add("one", 1);
    assert(hashTable->size() == 2);
    assert(hashTable->find("one")->val == 1);

    // Test add, overwrite, remove, add: "two" -> 2
    hashTable->add("two", 2);
    assert(hashTable->size() == 3);
    assert(hashTable->maxSize() == 5);
    assert(hashTable->find("two")->val == 2);

    hashTable->add("two", 3);
    assert(hashTable->size() == 3);
    assert(hashTable->maxSize() == 5);
    assert(hashTable->find("two")->val == 3);

    hashTable->remove("two");
    assert(hashTable->size() == 2);
    assert(hashTable->maxSize() == 5);
    assert(hashTable->find("two") == nullptr);

    hashTable->add("two", 2);
    assert(hashTable->size() == 3);
    assert(hashTable->find("two")->val == 2);

    // Test add, overwrite, remove, add: "three" -> 3
    hashTable->add("three", 3);
    assert(hashTable->size() == 4);
    assert(hashTable->maxSize() == 10);
    assert(hashTable->find("three")->val == 3);

    hashTable->add("three", 4);
    assert(hashTable->size() == 4);
    assert(hashTable->maxSize() == 10);
    assert(hashTable->find("three")->val == 4);

    hashTable->remove("three");
    assert(hashTable->size() == 3);
    assert(hashTable->maxSize() == 10);
    assert(hashTable->find("three") == nullptr);

    hashTable->add("three", 3);
    assert(hashTable->size() == 4);
    assert(hashTable->find("three")->val == 3);

    // Test resizeRehash
    hashTable->add("four", 4);
    assert(hashTable->size() == 5);
    assert(hashTable->maxSize() == 10);

    hashTable->add("five", 5);
    assert(hashTable->size() == 6);
    assert(hashTable->maxSize() == 10);

    hashTable->add("six", 6);
    assert(hashTable->size() == 7);
    assert(hashTable->maxSize() == 10);

    hashTable->add("seven", 7);
    assert(hashTable->size() == 8);
    assert(hashTable->maxSize() == 20);

    hashTable->add("eight", 8);
    assert(hashTable->size() == 9);
    assert(hashTable->maxSize() == 20);

    hashTable->add("nine", 9);
    assert(hashTable->size() == 10);
    assert(hashTable->maxSize() == 20);

    hashTable->add("ten", 10);
    assert(hashTable->size() == 11);
    assert(hashTable->maxSize() == 20);
    
    // Test long key
    hashTable->add("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", 11);
    assert(hashTable->size() == 12);
    assert(hashTable->maxSize() == 20);
    hashTable->remove("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
    assert(hashTable->size() == 11);
    assert(hashTable->maxSize() == 20);

    // Test find
    assert(hashTable->find("zero")->val == 0);
    assert(hashTable->find("one")->val == 1);
    assert(hashTable->find("two")->val == 2);
    assert(hashTable->find("three")->val == 3);
    assert(hashTable->find("four")->val == 4);
    assert(hashTable->find("five")->val == 5);
    assert(hashTable->find("six")->val == 6);
    assert(hashTable->find("seven")->val == 7);
    assert(hashTable->find("eight")->val == 8);
    assert(hashTable->find("nine")->val == 9);
    assert(hashTable->find("ten")->val == 10);
    assert(hashTable->find("eleven") == nullptr);
    
    // Test clear
    hashTable->clear();
    assert(hashTable->size() == 0);

    assert(hashTable->find("zero") == nullptr);
    assert(hashTable->find("one") == nullptr);
    assert(hashTable->find("two") == nullptr);
    assert(hashTable->find("three") == nullptr);
    assert(hashTable->find("four") == nullptr);
    assert(hashTable->find("five") == nullptr);
    assert(hashTable->find("six") == nullptr);
    assert(hashTable->find("seven") == nullptr);
    assert(hashTable->find("eight") == nullptr);
    assert(hashTable->find("nine") == nullptr);
    assert(hashTable->find("ten") == nullptr);
    assert(hashTable->find("eleven") == nullptr);
    
    // Print for 1000000 elements
    for (int i = 0; i < 1000000; i++) {
        hashTable->add(generateRandomKey(), generateRandomVal());
    }

    std::cout << hashTable->toString() << std::endl;
}