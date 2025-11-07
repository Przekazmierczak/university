#include <iostream>
#include <string>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <time.h>
#include <map>

template <typename T>
struct Linked_list {
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

    Node* dummy;
    int size = 0;

    Linked_list() {
        dummy = new Node(T());
        dummy->next = dummy;
        dummy->prev = dummy;
    }

    ~Linked_list() {
        clear();
        delete dummy;
    }

    enum Status {
        SUCCESS = 0,
        FAIL = 1
    };

    int addFront(T newNodeVal) {
        Node* newNode = createNewNode(newNodeVal);
        if (newNode == nullptr) return FAIL;
        addNodeFront(newNode, dummy);
        return SUCCESS;
    }

    int addBack(T newNodeVal) {
        Node* newNode = createNewNode(newNodeVal);
        if (newNode == nullptr) return FAIL;
        addNodeBack(newNode, dummy);
        return SUCCESS;
    }

    int removeFront() {
        return removeNode(dummy->next);
    }

    int removeBack() {
        return removeNode(dummy->prev);
    }

    T& at(int index) const {
        if (index >= size || index < 0) {
            throw std::out_of_range("Index out of range");
        }

        if (index < size / 2) {
            return getFromIndexFront(index);
        }
        return getFromIndexBack(size - index - 1);
    }

    void set(int index, T newValue) {
        at(index) = newValue;
    }

    T& operator[](int index) {
        return at(index);
    }

    template <typename A>
    T* find(A searched, int (*cmp)(const A&, const T&)) const {
        Node* find = findNode(searched, cmp);
        
        if (find != nullptr) return &(find->val);

        return nullptr;
    }

    template <typename A>
    int findRemove(A searched, int (*cmp)(const A&, const T&)) {
        Node* node = findNode(searched, cmp);

        if (node != nullptr) {
            removeNode(node);
            return SUCCESS;
        }

        return FAIL;
    }

    int insertOrdered(T newNodeVal, int (*cmp)(const T&, const T&)) {
        Node* newNode = createNewNode(newNodeVal);
        if (newNode == nullptr) return FAIL;

        Node* curr = dummy->next;
        while (curr != dummy && cmp(newNode->val, curr->val) > 0) {
            curr = curr->next;
        }
        addNodeBack(newNode, curr);
        return SUCCESS;
    };

    void clear() {
        while (dummy->next != dummy) {
            removeNode(dummy->next);
        }
    }

    std::string toString(std::string (*toStringObj)(const T&)) const {
        Node* curr = dummy->next;
        bool first = true;

        std::string str = "[";
        while (curr != dummy) {
            if (curr != dummy->next) str+= ";";
            str += toStringObj(curr->val);
            curr = curr->next;
        }

        str+= "]";

        return str;
    }

    private:
    Node* createNewNode(T newNodeVal) {
        try {
            return new Node(newNodeVal);
        }
        catch (const std::bad_alloc&) {
            return nullptr;
        }
    }

    void addNodeFront(Node* newNode, Node* node) {
        newNode->next = node->next;
        newNode->prev = node;
        newNode->next->prev = newNode;
        node->next = newNode;
        size++;
    }

    void addNodeBack(Node* newNode, Node* node) {
        newNode->prev = node->prev;
        newNode->next = node;
        newNode->prev->next = newNode;
        node->prev = newNode;
        size++;
    }

    int removeNode(Node* node) {
        if (node != dummy) {
            node->prev->next = node->next;
            node->next->prev = node->prev;
            delete node;
            size--;
            return SUCCESS;
        }
        return FAIL;
    }

    T& getFromIndexFront(int index) const {
        Node* curr = dummy->next;
        for (int i = 0; i < index; i++) {
            curr = curr->next;
        }
        return curr->val;
    }

    T& getFromIndexBack(int index) const {
        Node* curr = dummy->prev;
        for (int i = 0; i < index; i++) {
            curr = curr->prev;
        }

        return curr->val;
    }

    template <typename A>
    Node* findNode(A search, int (*cmp)(const A&, const T&)) const {
        Node* curr = dummy->next;

        while (curr != dummy) {
            if (cmp(search, curr->val) == 0) {
                return curr;
            }
            curr = curr->next;
        }

        return nullptr;
    }
};

struct SomeObject {
    int field_1;
    char field_2;
};

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

void fillList(int elements, Linked_list <SomeObject>* ll) {
    for (int i = 0; i < elements; i++) {
        ll->addFront(createRandom());
    }
}

template <typename Func>
std::string measureMethodMulti(Func func, Linked_list <SomeObject>* ll, int elements, bool needFill, int width) {
    if (needFill) fillList(elements, ll);
    clock_t t1 = clock();
    for (int i = 0; i < elements; i++) {
        func();
    }
    clock_t t2 = clock();
    ll->clear();
    double currTime = (t2 - t1) / (double)CLOCKS_PER_SEC;
    std:: string strTime = std::to_string(currTime);
    strTime.erase(strTime.size() - 3);
    return printColumn(strTime, width);
}

template <typename Func>
std::string measureMethodOnce(Func func, Linked_list <SomeObject>* ll, int elements, bool needFill, int width) {
    if (needFill) fillList(elements, ll);
    clock_t t1 = clock();
    func();
    clock_t t2 = clock();
    ll->clear();
    double currTime = (t2 - t1) / (double)CLOCKS_PER_SEC;
    std:: string strTime = std::to_string(currTime);
    strTime.erase(strTime.size() - 3);
    return printColumn(strTime, width);
}



int main() {
    srand(time(0));
    Linked_list <SomeObject>* ll = new Linked_list <SomeObject>();

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

    const int MAXORDER = 9;
   
    std::map<std::string, bool> methods = {
        {"addFront", false},
        {"removeFront", false},
        {"addBack", false},
        {"at", false},
        {"set", false},
        {"find", false},
        {"findRemove", false},
        {"removeBack", false},
        {"insertOrd.", false},
        {"toString", false},
        {"clear", true},
    };

    int width = 12;
    int namesSize = 1;

    std::cout << "|" << printColumn("elements", width);
    for (const auto& [method, condition] : methods) {
        if (condition) std::cout << printColumn(method, width);
    }
    std::cout << std::endl;

    for (int o = 1; o <= MAXORDER; o++) {
        int elements = pow(10, o);
        std::cout << "|";

        std::cout << printColumn(std::to_string(elements), width);
        // ---- Measuring execution time of addFront() method ----
        if (methods["addFront"]) {
            std::cout << measureMethodMulti([&]() { ll->addFront(createRandom()); }, ll, elements, false, width);
        }
        // ---- Measuring execution time of removeFront() method ----
        if (methods["removeFront"]) {
            std::cout << measureMethodMulti([&]() { ll->removeFront(); }, ll, elements, true, width);
        }
        // ---- Measuring execution time of addBack() method ----
        if (methods["addBack"]) {
            std::cout << measureMethodMulti([&]() { ll->addBack(createRandom()); }, ll, elements, false, width);
        }
        // ---- Measuring execution time of at() method ----
        if (methods["at"]) {
            std::cout << measureMethodMulti([&]() { ll->at(rand() % ll->size); }, ll, elements, true, width);
        }
        // ---- Measuring execution time of set() method ----
        if (methods["set"]) {
            std::cout << measureMethodMulti([&]() { ll->set(rand() % ll->size, createRandom()); }, ll, elements, true, width);
        }
        // ---- Measuring execution time of find() method ----
        if (methods["find"]) {
            std::cout << measureMethodMulti([&]() { ll->find(rand() % 1000000, compare1); }, ll, elements, true, width);
        }
        // ---- Measuring execution time of findRemove() method ----
        if (methods["findRemove"]) {
            std::cout << measureMethodMulti([&]() { ll->findRemove(rand() % 1000000, compare1); }, ll, elements, true, width);
        }
        // ---- Measuring execution time of removeBack() method ----
        if (methods["removeBack"]) {
            std::cout << measureMethodMulti([&]() { ll->removeBack(); }, ll, elements, true, width);
        }
        // ---- Measuring execution time of insertOrdered() method ----
        if (methods["insertOrd."]) {
            std::cout << measureMethodMulti([&]() { ll->insertOrdered(createRandom(), compare2); }, ll, elements, false, width);
        }
        // ---- Measuring execution time of toString() method ----
        if (methods["toString"]) {
            std::cout << measureMethodOnce([&]() { ll->toString(toStringObj); }, ll, elements, true, width);
        }
        // ---- Measuring execution time of clear() method ----
        if (methods["clear"]) {
            std::cout << measureMethodOnce([&]() { ll->clear(); }, ll, elements, true, width);
        }

        std::cout << std::endl;
    }

    delete ll;
}