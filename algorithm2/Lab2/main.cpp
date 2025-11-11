#include <iostream>
#include <string>
#include <cstdlib>

#include <cassert>
#include <ctime>
#include <cmath>
#include <time.h>
#include <functional>

template <typename T>
struct Dynamic_array {
    T** array;

    Dynamic_array() : ratio(2), currSize(0), maxSize(1) {
        array = new T*[maxSize];
    };

    ~Dynamic_array() {
        delete[] array;
    };

    int ratio;
    int currSize;
    int maxSize;

    int add(T &value) {
        if (currSize == maxSize) {
            if (resize() == FAIL) return FAIL;
        }
        array[currSize] = &value;
        currSize++;
        return SUCCESS;
    }

    T* at(int index) {
        checkOutOfRange(index);
        return array[index];
    }

    T* operator[](int index) {
        return at(index);
    }

    int set(int index, T &newValue) {
        checkOutOfRange(index);
        array[index] = &newValue;
        return SUCCESS;
    }

    int clear() {
        delete[] array;
        if (getMemory(array, 1) == FAIL) return FAIL;
        currSize = 0;
        maxSize = 1;
        return SUCCESS;
    }

    std::string toString(std::string (*toStringObj)(const T&)) const {
        std::string str = "[";
        for (int i = 0; i < currSize; i++) {
            if (i != 0) str+= ";";
            str += toStringObj(*array[i]);
        }
        str+= "]";

        return str;
    }

private:
    enum Status { SUCCESS = 0, FAIL = 1 };

    int resize() {
        maxSize *= ratio;
        T** newArray;
        if (getMemory(newArray, maxSize) == FAIL) return FAIL;

        for (int i = 0; i < currSize; i++) {
            newArray[i] = array[i];
        }
        delete[] array;
        array = newArray;

        return SUCCESS;
    }

    void checkOutOfRange(int index) {
        if (index >= currSize || index < 0) {
            throw std::out_of_range("Index out of range");
        }
    }

    int getMemory(T** &array, int elements) {
        try {
            array = new T*[elements];
        } catch (const std::bad_alloc&) {
            return FAIL;
        }
        return SUCCESS;
    }
};

struct SomeObject {
    int field_1;
    char field_2;
};

SomeObject createRandom();

std::string toStringObj(const SomeObject& obj);

std::string printColumn(std::string value, int width);
void fillList(int elements, Dynamic_array <SomeObject>* ll);

template <typename Func>
std::string measureMethod(Func func, Dynamic_array <SomeObject>* ll, int elements, bool requiresFill, int width, bool multiRun);

void assertTests(Dynamic_array <SomeObject>* ll);

int main() {
    srand(time(0));
    Dynamic_array <SomeObject>* da = new Dynamic_array <SomeObject>();

    SomeObject s0 = { 0, 'a' };
    SomeObject s1 = { 1, 'b' };
    SomeObject s2 = { 2, 'c' };
    SomeObject s3 = { 3, 'd' };
    SomeObject s4 = { 4, 'e' };

    std::cout << da->currSize << "/" << da->maxSize << std::endl;
    da->add(s0);
    std::cout << da->currSize << "/" << da->maxSize << std::endl;
    da->add(s1);
    std::cout << da->currSize << "/" << da->maxSize << std::endl;
    da->add(s2);
    std::cout << da->currSize << "/" << da->maxSize << std::endl;
    da->add(s3);
    std::cout << da->currSize << "/" << da->maxSize << std::endl;
    da->add(s4);
    std::cout << da->currSize << "/" << da->maxSize << std::endl;

    std::cout << (*da)[0]->field_1 << std::endl;
    std::cout << (*da)[1]->field_1 << std::endl;
    std::cout << (*da)[2]->field_1 << std::endl;
    std::cout << da->toString(toStringObj) << std::endl;
    
    da->set(0, s4);
    
    std::cout << (*da)[0]->field_1 << std::endl;
    std::cout << da->toString(toStringObj) << std::endl;
    
    da->clear();
    std::cout << da->currSize << "/" << da->maxSize << std::endl;
    std::cout << da->toString(toStringObj) << std::endl;

    std::cout << da->currSize << "/" << da->maxSize << std::endl;
    da->add(s0);
    std::cout << da->currSize << "/" << da->maxSize << std::endl;
    da->add(s1);
    std::cout << da->currSize << "/" << da->maxSize << std::endl;
    da->add(s2);
    std::cout << da->currSize << "/" << da->maxSize << std::endl;
    da->add(s3);
    std::cout << da->currSize << "/" << da->maxSize << std::endl;
    da->add(s4);
    std::cout << da->currSize << "/" << da->maxSize << std::endl;
    da->add(s0);
    std::cout << da->currSize << "/" << da->maxSize << std::endl;
    da->add(s1);
    std::cout << da->currSize << "/" << da->maxSize << std::endl;
    da->add(s2);
    std::cout << da->currSize << "/" << da->maxSize << std::endl;
    da->add(s3);
    std::cout << da->currSize << "/" << da->maxSize << std::endl;
    da->add(s4);
    std::cout << da->currSize << "/" << da->maxSize << std::endl;
    da->add(s0);
    std::cout << da->currSize << "/" << da->maxSize << std::endl;
    da->add(s1);
    std::cout << da->currSize << "/" << da->maxSize << std::endl;
    da->add(s2);
    std::cout << da->currSize << "/" << da->maxSize << std::endl;
    da->add(s3);
    std::cout << da->currSize << "/" << da->maxSize << std::endl;
    da->add(s4);
    std::cout << da->currSize << "/" << da->maxSize << std::endl;
    da->add(s0);
    std::cout << da->currSize << "/" << da->maxSize << std::endl;
    da->add(s1);
    std::cout << da->currSize << "/" << da->maxSize << std::endl;
    da->add(s2);
    std::cout << da->currSize << "/" << da->maxSize << std::endl;
    da->add(s3);
    std::cout << da->currSize << "/" << da->maxSize << std::endl;
    da->add(s4);
    std::cout << da->currSize << "/" << da->maxSize << std::endl;

    std::cout << da->toString(toStringObj) << std::endl;


    // Small correctness check
    // assertTests(da);

    int maxOrder = 6;
    // Minimum width: 12
    int columnWidth = 12;

    struct TestArguments {
        bool enabled;
        std::string name;
        std::function<void()> body;
        bool requiresFill;
        bool multiRun;
    };



    // Change first value (enabled) to reduce number of tests
    // TestArguments testMethods[11] = {
    //     {true, "addFront", [ll]() { ll->addFront(createRandom()); }, false, true},
    //     {true, "addBack",  [ll]() { ll->addBack(createRandom()); }, false, true},
    //     {true, "removeFront", [ll]() { ll->removeFront(); }, true, true},
    //     {true, "removeBack", [ll]() { ll->removeBack(); }, false, true},
    //     {true, "at", [ll]() { ll->at(rand() % ll->size); }, true, true},
    //     {true, "set", [ll]() { ll->set(rand() % ll->size, createRandom()); }, true, true},
    //     {true, "find", [ll]() { ll->find(rand() % 1000000, compare1); }, true, true},
    //     {true, "findRemove", [ll]() { ll->findRemove(rand() % 1000000, compare1); }, true, true},
    //     {true, "insertOrd.", [ll]() { ll->insertOrdered(createRandom(), compare2); }, true, true},
    //     {true, "toString", [ll]() { ll->toString(toStringObj); }, true, false},
    //     {true, "clear", [ll]() { ll->clear(); }, true, false}
    // };

    // std::cout << "|" << printColumn("elements", columnWidth);
    // for (const TestArguments& testMethod : testMethods) {
    //     if (testMethod.enabled) std::cout << printColumn(testMethod.name, columnWidth);
    // }
    // std::cout << std::endl;

    // // performance tests
    // for (int o = 1; o <= maxOrder; o++) {
    //     int elements = pow(10, o);
    //     std::cout << "|" << printColumn(std::to_string(elements), columnWidth);
    //     for (const TestArguments& testMethod : testMethods) {
    //         if (testMethod.enabled) {
    //             std::cout <<
    //             measureMethod(testMethod.body, ll, elements,
    //                           testMethod.requiresFill, columnWidth,
    //                           testMethod.multiRun)
    //             << std::flush;
    //         }
    //     }
    //     std::cout << std::endl;
    // }

    delete da;
}

SomeObject createRandom() {
    return { rand() % 1000000, (char)('a' + rand() % 26) };
};

int compare1(const int& value, const SomeObject& obj) {
    if (value == obj.field_1) {
        return 0;
    }
    return 1;
}

int compare2(const SomeObject& new_obj, const SomeObject& list_obj) {
    if (new_obj.field_1 > list_obj.field_1) return 1;
    if (new_obj.field_1 < list_obj.field_1) return -1;
    return 0;
}

std::string toStringObj(const SomeObject& obj) {
    return "(" + std::to_string(obj.field_1) + ", " + obj.field_2 + ")";
}

std::string printColumn(std::string value, int width) {
    if (value.size() < width) {
        return std::string(width - value.size(), ' ') + value + "|";
    }
    return value;
}

void fillList(int elements, Dynamic_array <SomeObject>* ll) {
}

template <typename Func>
std::string measureMethod(Func func, Dynamic_array <SomeObject>* ll, int elements, bool requiresFill, int width, bool multiRun) {
    if (requiresFill) fillList(elements, ll);
    clock_t t1 = clock();
    if (multiRun) {
        for (int i = 0; i < elements; i++) {
            func();
        }
    } else {
        func();
    }
    clock_t t2 = clock();
    ll->clear();
    double currTime = (t2 - t1) / (double)CLOCKS_PER_SEC;
    std:: string strTime = std::to_string(currTime);
    strTime.erase(strTime.size() - 3);
    return printColumn(strTime, width);
}

void assertTests(Dynamic_array <SomeObject>* ll) {
    SomeObject s0 = { 0, 'a' };
    SomeObject s1 = { 1, 'b' };
    SomeObject s2 = { 2, 'c' };
    SomeObject s3 = { 3, 'd' };
    SomeObject s4 = { 4, 'e' };
}