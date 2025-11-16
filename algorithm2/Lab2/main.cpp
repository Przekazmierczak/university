#include <iostream>
#include <string>
#include <cstdlib>

#include <cassert>
#include <ctime>
#include <cmath>
#include <time.h>
#include <functional>

#include <vector>
#include <algorithm>

template <typename T>
struct Dynamic_array {
    T* array;

    Dynamic_array() : ratio(2), currSize(0), maxSize(1) { array = new T[maxSize]; }
    ~Dynamic_array() { delete[] array; }

    int size() const { return currSize; }
    int checkMaxSize() const { return maxSize; }

    int add(T value);
    T& at(int index) const;
    T& operator[](int index) const { return at(index); }
    int set(int index, T newValue);
    int clear() { return resize(1, true); }
    std::string toString(std::string (*toStringObj)(const T&)) const;
    void sort(int (*cmp)(const T&, const T&));

private:    
    int ratio;
    int currSize;
    int maxSize;
    enum Status { SUCCESS = 0, FAIL = 1 };

    int resize(int newSize, bool resetCurrSize);
    void checkOutOfRange(int index) const;
    int getMemory(T* &array, int elements);
    void swap(int index1, int index2);
};

struct SomeObject {
    int field_1;
    char field_2;
};

SomeObject createRandom();

int compare(const SomeObject& new_obj, const SomeObject& list_obj);
std::string toStringObj(const SomeObject& obj);

std::string getColumn(std::string value, int width, char filling, char last);
void printSeparator(int numOfMethods,int width);

void fillArray(int elements, Dynamic_array <SomeObject>* da);
void fillVector(int elements, std::vector <SomeObject>* dv);

template <typename Func>
std::string measureMethod(Func func, Dynamic_array <SomeObject>* da, std::vector<SomeObject>*dv, int elements, bool requiresFill, int width, bool multiRun, bool ifVector);

void assertTests(Dynamic_array <SomeObject>* da);

int main() {
    srand(time(0));
    Dynamic_array <SomeObject>* da = new Dynamic_array <SomeObject>();
    std::vector<SomeObject>* dv = new std::vector<SomeObject>();

    auto compareV = [](const SomeObject &a, const SomeObject &b) {
        return a.field_1 < b.field_1;
    };

    SomeObject s0 = { 0, 'a' };
    SomeObject s1 = { 1, 'b' };
    SomeObject s2 = { 2, 'c' };
    SomeObject s3 = { 3, 'd' };
    SomeObject s4 = { 4, 'e' };

    // Small correctness check
    assertTests(da);

    // Maximum order: 9 (int overflow)
    int maxOrder = 5;
    int columnWidth = 11;

    struct TestArguments {
        bool enabled;
        std::string name;
        std::function<void()> body;
        bool requiresFill;
        bool multiRun;
        bool ifVector;
    };

    // Change first value (enabled) to reduce number of tests
    TestArguments testMethods[] = {
        {true, "add()", [da]() { da->add(createRandom()); }, false, true, false},
        {true, "vadd()", [dv]() { dv->push_back(createRandom()); },false, true, true},
        {true, "at()",  [da]() { da->at(rand() % da->size()); }, true, true, false},
        {true, "vat()", [dv]() { (void)dv->at(rand() % dv->size()); }, true, true, true},
        {true, "set()", [da]() { da->set(rand() % da->size(), createRandom()); }, true, true, false},
        {true, "vset()", [dv]() { (*dv)[(rand() % dv->size())] = createRandom(); },true, true, true},
        {true, "clear()", [da]() { da->clear(); }, true, false, false},
        {true, "vclear()", [dv]() { dv->clear(); }, true, false, true},
        {true, "toStr()", [da]() { da->toString(toStringObj); }, true, false, false},
        {true, "sort()", [da]() { da->sort(compare); }, true, false, false},
        {true, "vsort()", [dv, compareV]() { std::sort(dv->begin(), dv->end(), compareV); }, true, false, true},
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
                measureMethod(testMethod.body, da, dv, elements,
                              testMethod.requiresFill, columnWidth,
                              testMethod.multiRun, testMethod.ifVector)
                << std::flush;
            }
        }
        std::cout << std::endl;
    }
    printSeparator(countMethodsToPrint, columnWidth);

    delete da;
}

template <typename T>
int Dynamic_array<T>::add(T value) {
    if (currSize == maxSize) {
        if (resize(maxSize * ratio, false) == FAIL) return FAIL;
    }
    array[currSize] = value;
    currSize++;
    return SUCCESS;
}

template <typename T>
T& Dynamic_array<T>::at(int index) const {
    checkOutOfRange(index);
    return array[index];
}

template <typename T>
int Dynamic_array<T>::set(int index, T newValue) {
    checkOutOfRange(index);
    array[index] = newValue;
    return SUCCESS;
}

template <typename T>
std::string Dynamic_array<T>::toString(std::string (*toStringObj)(const T&)) const {
    std::string str = "[";
    for (int i = 0; i < currSize; i++) {
        if (i != 0) str+= ";";
        str += toStringObj(array[i]);
    }
    str+= "]";

    return str;
}

template <typename T>
void Dynamic_array<T>::sort(int (*cmp)(const T&, const T&)) {
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
int Dynamic_array<T>::resize(int newSize, bool resetCurrSize) {
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
void Dynamic_array<T>::checkOutOfRange(int index) const {
    if (index >= currSize || index < 0) {
        throw std::out_of_range("Index out of range");
    }
}

template <typename T>
int Dynamic_array<T>::getMemory(T* &array, int elements) {
    try {
        array = new T[elements];
    } catch (const std::bad_alloc&) {
        return FAIL;
    }
    return SUCCESS;
}

template <typename T>
void Dynamic_array<T>::swap(int index1, int index2) {
    T temp = array[index1];
    array[index1] = array[index2];
    array[index2] = temp;
}

SomeObject createRandom() {
    return { rand() % 1000000, (char)('a' + rand() % 26) };
};

int compare(const SomeObject& new_obj, const SomeObject& list_obj) {
    if (new_obj.field_1 > list_obj.field_1) return 1;
    if (new_obj.field_1 < list_obj.field_1) return -1;
    return 0;
}

std::string toStringObj(const SomeObject& obj) {
    return "(" + std::to_string(obj.field_1) + ", " + obj.field_2 + ")";
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

void fillArray(int elements, Dynamic_array <SomeObject>* da) {
    for (int i = 0; i < elements; i++) {
        da->add(createRandom());
    }
}

void fillVector(int elements, std::vector <SomeObject>* dv) {
    for (int i = 0; i < elements; i++) {
        dv->push_back(createRandom());
    }
}

template <typename Func>
std::string measureMethod(Func func, Dynamic_array <SomeObject>* da, std::vector<SomeObject>*dv, int elements, bool requiresFill, int width, bool multiRun, bool ifVector) {
    if (!ifVector) {
        if (requiresFill) fillArray(elements, da);
    } else {
        if (requiresFill) fillVector(elements, dv);
    }
    
    clock_t t1 = clock();
    if (multiRun) {
        for (int i = 0; i < elements; i++) {
            func();
        }
    } else {
        func();
    }
    clock_t t2 = clock();

    da->clear();
    dv->clear();

    double currTime = (t2 - t1) / (double)CLOCKS_PER_SEC;
    std:: string strTime = std::to_string(currTime);
    strTime.erase(strTime.size() - 3);
    return getColumn(strTime + 's', width, ' ', '|');
}

void assertTests(Dynamic_array <SomeObject>* da) {
    SomeObject s0 = { 0, 'a' };
    SomeObject s1 = { 1, 'b' };
    SomeObject s2 = { 2, 'c' };
    SomeObject s3 = { 3, 'd' };
    SomeObject s4 = { 4, 'e' };

    auto outOfRangeTest = [&da](int index) {
        bool outOfRange = false;
        try {
            (*da)[index];
        } catch (std::out_of_range&) {
            outOfRange = true;
        }
        assert(outOfRange == true);
    };

    // ---- Test add() methods ----
    da->add(s0);
    // Expected: [0]
    assert((*da)[0].field_1 == 0);
    assert(da->size() == 1);
    assert(da->checkMaxSize() == 1);
    outOfRangeTest(1);

    da->add(s2);
    // Expected: [0, 2]
    assert((*da)[0].field_1 == 0);
    assert((*da)[1].field_1 == 2);
    assert(da->size() == 2);
    assert(da->checkMaxSize() == 2);
    outOfRangeTest(2);

    da->add(s1);
    // Expected: [0, 2, 1]
    assert((*da)[0].field_1 == 0);
    assert((*da)[1].field_1 == 2);
    assert((*da)[2].field_1 == 1);
    assert(da->size() == 3);
    assert(da->checkMaxSize() == 4);
    outOfRangeTest(3);

    da->add(s4);
    // Expected: [0, 2, 1, 4]
    assert((*da)[0].field_1 == 0);
    assert((*da)[1].field_1 == 2);
    assert((*da)[2].field_1 == 1);
    assert((*da)[3].field_1 == 4);
    assert(da->size() == 4);
    assert(da->checkMaxSize() == 4);
    outOfRangeTest(4);

    da->add(s3);
    // Expected: [0, 2, 1, 4, 3]
    assert((*da)[0].field_1 == 0);
    assert((*da)[1].field_1 == 2);
    assert((*da)[2].field_1 == 1);
    assert((*da)[3].field_1 == 4);
    assert((*da)[4].field_1 == 3);
    assert(da->size() == 5);
    assert(da->checkMaxSize() == 8);
    outOfRangeTest(5);

    // ---- Test set() methods ----
    da->set(1, s3);
    // Expected: [0, 3, 1, 4, 3]
    assert((*da)[0].field_1 == 0);
    assert((*da)[1].field_1 == 3);
    assert((*da)[2].field_1 == 1);
    assert((*da)[3].field_1 == 4);
    assert((*da)[4].field_1 == 3);
    assert(da->size() == 5);
    assert(da->checkMaxSize() == 8);
    outOfRangeTest(5);

    da->set(4, s2);
    // Expected: [0, 3, 1, 4, 2]
    assert((*da)[0].field_1 == 0);
    assert((*da)[1].field_1 == 3);
    assert((*da)[2].field_1 == 1);
    assert((*da)[3].field_1 == 4);
    assert((*da)[4].field_1 == 2);
    assert(da->size() == 5);
    assert(da->checkMaxSize() == 8);
    outOfRangeTest(5);

    // ---- Test sort() methods ----
    da->sort(compare);
    // Expected: [0, 1, 2, 3, 4]
    assert((*da)[0].field_1 == 0);
    assert((*da)[1].field_1 == 1);
    assert((*da)[2].field_1 == 2);
    assert((*da)[3].field_1 == 3);
    assert((*da)[4].field_1 == 4);
    assert(da->size() == 5);
    assert(da->checkMaxSize() == 8);
    outOfRangeTest(5);

    // ---- Test toString() method ----
    assert(da->toString(toStringObj) == "[(0, a);(1, b);(2, c);(3, d);(4, e)]");

    // ---- Test clear() methods ----
    da->clear();
    assert(da->size() == 0);
    assert(da->checkMaxSize() == 1);
    outOfRangeTest(0);
    outOfRangeTest(-1);
}