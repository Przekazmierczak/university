#include <iostream>
#include <string>
#include <cstdlib>

#include <cassert>
#include <ctime>
#include <cmath>
#include <time.h>
#include <functional>

template <typename T>
struct LinkedList {
    struct Node {
        Node* next;
        Node* prev;
        T val;

        Node(T newVal) {
            next = nullptr;
            prev = nullptr;
            val = newVal;
        }
    };

    int size = 0;

    LinkedList();
    ~LinkedList();

    int addFront(T newNodeVal);
    int addBack(T newNodeVal);
    int removeFront();
    int removeBack();

    T& at(int index) const;
    void set(int index, T newValue);
    T& operator[](int index);

    template <typename A>
    T* find(A searched, int (*cmp)(const A&, const T&)) const;

    template <typename A>
    int findRemove(A searched, int (*cmp)(const A&, const T&));

    int insertOrdered(T newNodeVal, int (*cmp)(const T&, const T&));
    void clear();
    std::string toString(std::string (*toStringObj)(const T&)) const;

private:
    Node* dummy;
    enum Status { SUCCESS = 0, FAIL = 1 };

    Node* createNewNode(T newNodeVal);
    void addNodeFront(Node* newNode, Node* node);
    void addNodeBack(Node* newNode, Node* node);
    int removeNode(Node* node);
    T& getFromIndexFront(int index) const;
    T& getFromIndexBack(int index) const;

    template <typename A>
    Node* findNode(A search, int (*cmp)(const A&, const T&)) const;
};

struct SomeObject {
    int field_1;
    char field_2;
};

SomeObject createRandom();

int compare1(const int& value, const SomeObject& obj);
int compare2(const SomeObject& new_obj, const SomeObject& list_obj);
std::string toStringObj(const SomeObject& obj);

std::string printColumn(std::string value, int width);
void fillList(int elements, LinkedList <SomeObject>* ll);

template <typename Func>
std::string measureMethod(Func func, LinkedList <SomeObject>* ll, int elements, bool requiresFill, int width, bool multiRun);

void assertTests(LinkedList <SomeObject>* ll);

int main() {
    srand(time(0));
    LinkedList <SomeObject>* ll = new LinkedList <SomeObject>();

    // Small correctness check
    assertTests(ll);

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
    TestArguments testMethods[11] = {
        {true, "addFront", [ll]() { ll->addFront(createRandom()); }, false, true},
        {true, "addBack",  [ll]() { ll->addBack(createRandom()); }, false, true},
        {true, "removeFront", [ll]() { ll->removeFront(); }, true, true},
        {true, "removeBack", [ll]() { ll->removeBack(); }, false, true},
        {true, "at", [ll]() { ll->at(rand() % ll->size); }, true, true},
        {true, "set", [ll]() { ll->set(rand() % ll->size, createRandom()); }, true, true},
        {true, "find", [ll]() { ll->find(rand() % 1000000, compare1); }, true, true},
        {true, "findRemove", [ll]() { ll->findRemove(rand() % 1000000, compare1); }, true, true},
        {true, "insertOrd.", [ll]() { ll->insertOrdered(createRandom(), compare2); }, true, true},
        {true, "toString", [ll]() { ll->toString(toStringObj); }, true, false},
        {true, "clear", [ll]() { ll->clear(); }, true, false}
    };

    std::cout << "|" << printColumn("elements", columnWidth);
    for (const TestArguments& testMethod : testMethods) {
        if (testMethod.enabled) std::cout << printColumn(testMethod.name, columnWidth);
    }
    std::cout << std::endl;

    // performance tests
    for (int o = 1; o <= maxOrder; o++) {
        int elements = pow(10, o);
        std::cout << "|" << printColumn(std::to_string(elements), columnWidth);
        for (const TestArguments& testMethod : testMethods) {
            if (testMethod.enabled) {
                std::cout <<
                measureMethod(testMethod.body, ll, elements,
                              testMethod.requiresFill, columnWidth,
                              testMethod.multiRun)
                << std::flush;
            }
        }
        std::cout << std::endl;
    }

    delete ll;
}

template <typename T>
LinkedList<T>::LinkedList() {
    dummy = new Node(T());
    dummy->next = dummy;
    dummy->prev = dummy;
}

template <typename T>
LinkedList<T>::~LinkedList() {
    clear();
    delete dummy;
}

template <typename T>
int LinkedList<T>::addFront(T newNodeVal) {
    Node* newNode = createNewNode(newNodeVal);
    if (newNode == nullptr) return FAIL;
    addNodeFront(newNode, dummy);
    return SUCCESS;
}

template <typename T>
int LinkedList<T>::addBack(T newNodeVal) {
    Node* newNode = createNewNode(newNodeVal);
    if (newNode == nullptr) return FAIL;
    addNodeBack(newNode, dummy);
    return SUCCESS;
}

template <typename T>
int LinkedList<T>::removeFront() {
    return removeNode(dummy->next);
}

template <typename T>
int LinkedList<T>::removeBack() {
    return removeNode(dummy->prev);
}

template <typename T>
T& LinkedList<T>::at(int index) const {
    if (index >= size || index < 0) {
        throw std::out_of_range("Index out of range");
    }

    if (index < size / 2) {
        return getFromIndexFront(index);
    }
    return getFromIndexBack(size - index - 1);
}

template <typename T>
void LinkedList<T>::set(int index, T newValue) {
    at(index) = newValue;
}

template <typename T>
T& LinkedList<T>::operator[](int index) {
    return at(index);
}

template <typename T>
template <typename A>
T* LinkedList<T>::find(A searched, int (*cmp)(const A&, const T&)) const {
    Node* find = findNode(searched, cmp);
    
    if (find != nullptr) return &(find->val);

    return nullptr;
}

template <typename T>
template <typename A>
int LinkedList<T>::findRemove(A searched, int (*cmp)(const A&, const T&)) {
    Node* node = findNode(searched, cmp);

    if (node != nullptr) {
        removeNode(node);
        return SUCCESS;
    }

    return FAIL;
}

template <typename T>
int LinkedList<T>::insertOrdered(T newNodeVal, int (*cmp)(const T&, const T&)) {
    Node* newNode = createNewNode(newNodeVal);
    if (newNode == nullptr) return FAIL;

    Node* curr = dummy->next;
    while (curr != dummy && cmp(newNode->val, curr->val) > 0) {
        curr = curr->next;
    }
    addNodeBack(newNode, curr);
    return SUCCESS;
}

template <typename T>
void LinkedList<T>::clear() {
    while (dummy->next != dummy) {
        removeNode(dummy->next);
    }
}

template <typename T>
std::string LinkedList<T>::toString(std::string (*toStringObj)(const T&)) const {
    Node* curr = dummy->next;

    std::string str = "[";
    while (curr != dummy) {
        if (curr != dummy->next) str+= ";";
        str += toStringObj(curr->val);
        curr = curr->next;
    }

    str+= "]";

    return str;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::createNewNode(T newNodeVal) {
    try {
        return new Node(newNodeVal);
    }
    catch (const std::bad_alloc&) {
        return nullptr;
    }
}

template <typename T>
void LinkedList<T>::addNodeFront(LinkedList<T>::Node* newNode, LinkedList<T>::Node* node) {
    newNode->next = node->next;
    newNode->prev = node;
    newNode->next->prev = newNode;
    node->next = newNode;
    size++;
}

template <typename T>
void LinkedList<T>::addNodeBack(LinkedList<T>::Node* newNode, LinkedList<T>::Node* node) {
    newNode->prev = node->prev;
    newNode->next = node;
    newNode->prev->next = newNode;
    node->prev = newNode;
    size++;
}

template <typename T>
int LinkedList<T>::removeNode(LinkedList<T>::Node* node) {
    if (node != dummy) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
        delete node;
        size--;
        return SUCCESS;
    }
    return FAIL;
}

template <typename T>
T& LinkedList<T>::getFromIndexFront(int index) const {
    Node* curr = dummy->next;
    for (int i = 0; i < index; i++) {
        curr = curr->next;
    }
    return curr->val;
}

template <typename T>
T& LinkedList<T>::getFromIndexBack(int index) const {
    Node* curr = dummy->prev;
    for (int i = 0; i < index; i++) {
        curr = curr->prev;
    }

    return curr->val;
}

template <typename T>
template <typename A>
typename LinkedList<T>::Node* LinkedList<T>::findNode(A search, int (*cmp)(const A&, const T&)) const {
    Node* curr = dummy->next;

    while (curr != dummy) {
        if (cmp(search, curr->val) == 0) {
            return curr;
        }
        curr = curr->next;
    }

    return nullptr;
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

void fillList(int elements, LinkedList <SomeObject>* ll) {
    for (int i = 0; i < elements; i++) {
        ll->addFront(createRandom());
    }
}

template <typename Func>
std::string measureMethod(Func func, LinkedList <SomeObject>* ll, int elements, bool requiresFill, int width, bool multiRun) {
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

void assertTests(LinkedList <SomeObject>* ll) {
    SomeObject s0 = { 0, 'a' };
    SomeObject s1 = { 1, 'b' };
    SomeObject s2 = { 2, 'c' };
    SomeObject s3 = { 3, 'd' };
    SomeObject s4 = { 4, 'e' };

    // ---- Test addFront() and addBack() methods ----
    ll->addFront(s0);
    // Expected: [0]
    assert((*ll)[0].field_1 == 0);
    assert(ll->size == 1);

    ll->addBack(s1);
    // Expected: [0, 1]
    assert((*ll)[0].field_1 == 0);
    assert((*ll)[1].field_1 == 1);
    assert(ll->size == 2);

    ll->addFront(s3);
    // Expected: [3, 0, 1]
    assert((*ll)[0].field_1 == 3);
    assert((*ll)[1].field_1 == 0);
    assert((*ll)[2].field_1 == 1);
    assert(ll->size == 3);

    ll->addBack(s4);
    // Expected: [3, 0, 1, 4]
    assert((*ll)[0].field_1 == 3);
    assert((*ll)[1].field_1 == 0);
    assert((*ll)[2].field_1 == 1);
    assert((*ll)[3].field_1 == 4);
    assert(ll->size == 4);

    // ---- Test removeFront() and removeBack() methods ----
    ll->removeFront();
    // Expected: [0, 1, 4]
    assert((*ll)[0].field_1 == 0);
    assert((*ll)[1].field_1 == 1);
    assert((*ll)[2].field_1 == 4);
    assert(ll->size == 3);

    ll->removeBack();
    // Expected: [0, 1]
    assert((*ll)[0].field_1 == 0);
    assert((*ll)[1].field_1 == 1);
    assert(ll->size == 2);

    ll->removeBack();
    // Expected: [0]
    assert((*ll)[0].field_1 == 0);
    assert(ll->size == 1);

    ll->removeFront();
    // Expected: empty list
    assert(ll->size == 0);

    // Removing from an empty list should return 1 (FAIL)
    assert(ll->removeFront() == 1);
    assert(ll->removeBack() == 1);

    // ---- Test set() method ----
    ll->addFront(s0);
    ll->addFront(s1);
    ll->addFront(s2);
    // Expected: [2, 1, 0]
    assert((*ll)[0].field_1 == 2);
    assert((*ll)[1].field_1 == 1);
    assert((*ll)[2].field_1 == 0);
    assert(ll->size == 3);

    ll->set(1, s4);
    // Expected: [2, 4, 0]
    assert((*ll)[0].field_1 == 2);
    assert((*ll)[1].field_1 == 4);
    assert((*ll)[2].field_1 == 0);
    assert(ll->size == 3);

    ll->set(2, s3);
    // Expected: [2, 4, 3]
    assert((*ll)[0].field_1 == 2);
    assert((*ll)[1].field_1 == 4);
    assert((*ll)[2].field_1 == 3);
    assert(ll->size == 3);

    // ---- Test find() method ----
    assert(ll->find(4, compare1)->field_1 == 4);
    assert(ll->find(2, compare1)->field_1 == 2);
    assert(ll->find(3, compare1)->field_1 == 3);
    assert(ll->find(0, compare1) == nullptr);
    assert(ll->find(s2, compare2)->field_1 == s2.field_1);

    // ---- Test findRemove() method ----
    ll->findRemove(4, compare1);
    // Expected: [2, 3]
    assert((*ll)[0].field_1 == 2);
    assert((*ll)[1].field_1 == 3);
    assert(ll->size == 2);

    ll->findRemove(2, compare1);
    // Expected: [3]
    assert((*ll)[0].field_1 == 3);
    assert(ll->size == 1);

    ll->findRemove(0, compare1);
    // Expected (unchanged): [3]
    assert((*ll)[0].field_1 == 3);
    assert(ll->size == 1);

    ll->findRemove(3, compare1);
    // Expected: empty list
    assert(ll->size == 0);

    // ---- Test insertOrdered() method ----
    ll->insertOrdered(s1, compare2);
    // Expected: [1]
    assert((*ll)[0].field_1 == 1);
    assert(ll->size == 1);

    ll->insertOrdered(s3, compare2);
    // Expected: [1, 3]
    assert((*ll)[0].field_1 == 1);
    assert((*ll)[1].field_1 == 3);
    assert(ll->size == 2);

    ll->insertOrdered(s4, compare2);
    // Expected: [1, 3, 4]
    assert((*ll)[0].field_1 == 1);
    assert((*ll)[1].field_1 == 3);
    assert((*ll)[2].field_1 == 4);
    assert(ll->size == 3);

    ll->insertOrdered(s2, compare2);
    // Expected: [1, 2, 3, 4]
    assert((*ll)[0].field_1 == 1);
    assert((*ll)[1].field_1 == 2);
    assert((*ll)[2].field_1 == 3);
    assert((*ll)[3].field_1 == 4);
    assert(ll->size == 4);

    ll->insertOrdered(s0, compare2);
    // Expected: [0, 1, 2, 3, 4]
    assert((*ll)[0].field_1 == 0);
    assert((*ll)[1].field_1 == 1);
    assert((*ll)[2].field_1 == 2);
    assert((*ll)[3].field_1 == 3);
    assert((*ll)[4].field_1 == 4);
    assert(ll->size == 5);

    // ---- Test toString() method ----
    assert(ll->toString(toStringObj) == "[(0, a);(1, b);(2, c);(3, d);(4, e)]");

    // ---- Test clear() method ----
    ll->clear();
    // Expected: empty list
    assert(ll->size == 0);
    assert(ll->toString(toStringObj) == "[]");
    assert(ll->removeFront() == 1);
    assert(ll->removeBack() == 1);
}