#ifndef LINKLIST_H
#define LINKLIST_H

#include <iostream>
#include <string>

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

    LinkedList();
    ~LinkedList();

    int size() { return currSize; }

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
    int currSize = 0;
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
    if (index >= currSize || index < 0) {
        throw std::out_of_range("Index out of range");
    }

    if (index < currSize / 2) {
        return getFromIndexFront(index);
    }
    return getFromIndexBack(currSize - index - 1);
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
        if (curr != dummy->next) str+= "; ";
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
    currSize++;
}

template <typename T>
void LinkedList<T>::addNodeBack(LinkedList<T>::Node* newNode, LinkedList<T>::Node* node) {
    newNode->prev = node->prev;
    newNode->next = node;
    newNode->prev->next = newNode;
    node->prev = newNode;
    currSize++;
}

template <typename T>
int LinkedList<T>::removeNode(LinkedList<T>::Node* node) {
    if (node != dummy) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
        delete node;
        currSize--;
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

#endif