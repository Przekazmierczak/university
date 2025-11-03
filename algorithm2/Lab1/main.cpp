#include <iostream>

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

    T dummyVal;
    Node* dummy;
    int size = 0;

    Linked_list() {
        dummy = new Node(dummyVal);
        dummy->next = dummy;
        dummy->prev = dummy;
    }

    int addFront(T newNodeVal) {
        Node* newNode = createNewNode(newNodeVal);
        if (newNode == nullptr) return 1;
        addNodeFront(newNode, dummy);
        return 0;
    }

    int addBack(T newNodeVal) {
        Node* newNode = createNewNode(newNodeVal);
        if (newNode == nullptr) return 1;
        addNodeBack(newNode, dummy);
        return 0;
    }

    int removeFront() {
        return removeNodeFront(dummy);
    }

    int removeBack() {
        return removeNodeBack(dummy);
    }

    T& getFromIndex(int index) {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }

        if (index < size / 2) {
            return getFromIndexFront(index);
        }
        return getFromIndexBack(size - index - 1);
    }

    void setToIndex(int index, T newValue) {
        getFromIndex(index) = newValue;
    }

    T& operator[](int index) {
        return getFromIndex(index);
    }

    template <typename A, typename O>
    T* find(A searched, int (*cmp)(A, O)) {
        Node* find = findNode(searched, cmp);
        
        if (find != nullptr) return &(find->val);

        return nullptr;
    }

    template <typename A>
    int remove(A searched, int (*cmp)(A, T)) {
        Node* toRemove = findNode(searched, cmp);

        if (toRemove != nullptr) {
            toRemove->prev->next = toRemove->next;
            toRemove->next->prev = toRemove->prev;
            delete toRemove;
            size--;
            return 0;
        }

        return 1;
    }

    int addInOrder(T newNodeVal, int (*cmp)(T, T)) {
        Node* newNode = createNewNode(newNodeVal);
        if (newNode == nullptr) return 1;

        Node* curr = dummy->next;
        while (curr != dummy && cmp(newNode->val, curr->val) > 0) {
            curr = curr->next;
        }
        addNodeBack(newNode, curr);
        return 0;
    };

    void printList() {
        Node* curr = dummy->next;

        std::cout << "[";
        while (curr != dummy) {
            std::cout << curr->val.field_1 << ",";
            curr = curr->next;
        }
        std::cout << "]" << " size: " << size << std::endl;
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

    int removeNodeFront(Node* node) {
        if (node->next != dummy) {
            Node* toRemove = node->next;
            node->next = node->next->next;
            node->next->prev = node;
            delete toRemove;
            size--;
            return 0;
        }
        return 1;
    }

    int removeNodeBack(Node* node) {
        if (node->prev != dummy) {
            Node* toRemove = node->prev;
            node->prev = node->prev->prev;
            node->prev->next = node;
            delete toRemove;
            size--;
            return 0;
        }
        return 1;
    }

    T& getFromIndexFront(int index) {
        Node* curr = dummy->next;
        for (int i = 0; i < index; i++) {
            curr = curr->next;
        }
        return curr->val;
    }

    T& getFromIndexBack(int index) {
        Node* curr = dummy->prev;
        for (int i = 0; i < index; i++) {
            curr = curr->prev;
        }

        return curr->val;
    }

    template <typename A>
    Node* findNode(A searched, int (*cmp)(A, T)) {
        Node* curr = dummy->next;

        while (curr != dummy) {
            if (cmp(searched, curr->val) == 0) {
                return curr;
            }
            curr = curr->next;
        }

        return nullptr;
    }
};

struct Some_object {
    int field_1;
    char field_2;
};

int compare1(int value, Some_object obj) {
    if (value == obj.field_1) {
        return 0;
    }
    return 1;
}

int compare2(Some_object new_obj, Some_object list_obj) {
    if (new_obj.field_1 > list_obj.field_1) return 1;
    if (new_obj.field_1 < list_obj.field_1) return -1;
    return 0;
}

int main () {
    Linked_list <Some_object>* ll = new Linked_list <Some_object>();

    Some_object s0;
    s0.field_1 = 0;
    s0.field_2 = 'a';
    ll->addBack(s0);

    Some_object s1;
    s1.field_1 = 1;
    s1.field_2 = 'a';
    ll->addBack(s1);

    Some_object s2;
    s2.field_1 = 2;
    s2.field_2 = 'a';
    ll->addBack(s2);

    Some_object s3;
    s3.field_1 = 3;
    s3.field_2 = 'a';
    ll->addBack(s3);

    Some_object s4;
    s4.field_1 = 4;
    s4.field_2 = 'a';

    ll->printList();
    std::cout<<ll->removeFront()<<std::endl;
    ll->printList();
    std::cout<<ll->removeFront()<<std::endl;
    ll->printList();
    std::cout<<ll->removeFront()<<std::endl;
    ll->printList();
    std::cout<<ll->removeFront()<<std::endl;
    ll->printList();
    std::cout<<ll->removeFront()<<std::endl;
    ll->printList();
    
    ll->addBack(s0);
    ll->printList();
    ll->addBack(s1);
    ll->printList();
    ll->addFront(s3);
    ll->printList();
    
    std::cout<<ll->removeBack()<<std::endl;
    ll->printList();
    std::cout<<ll->removeBack()<<std::endl;
    ll->printList();
    std::cout<<ll->removeBack()<<std::endl;
    ll->printList();
    std::cout<<ll->removeBack()<<std::endl;
    ll->printList();
    std::cout<<ll->removeBack()<<std::endl;
    ll->printList();

    ll->addFront(s0);
    ll->printList();
    ll->addFront(s1);
    ll->printList();
    ll->addBack(s3);
    ll->printList();
    ll->addFront(s2);
    ll->printList();

    (*ll)[1] = s4;
    ll->printList();

    std::cout << (*ll)[0].field_1 << std::endl;
    std::cout << ll->getFromIndex(1).field_1 << std::endl;
    std::cout << (*ll)[2].field_1 << std::endl;
    std::cout << ll->getFromIndex(3).field_1 << std::endl;

    std::cout << ll->find(4, compare1)->field_1 << std::endl;
    std::cout << ll->find(2, compare1)->field_1 << std::endl;

    ll->printList();
    ll->remove(4, compare1);
    ll->printList();
    ll->remove(2, compare1);
    ll->printList();
    ll->remove(3, compare1);
    ll->printList();
    ll->remove(0, compare1);
    ll->printList();

    ll->addInOrder(s2, compare2);
    ll->addInOrder(s0, compare2);
    ll->addInOrder(s4, compare2);
    ll->addInOrder(s3, compare2);
    ll->addInOrder(s1, compare2);
    //ll->addInOrder(s0, compare2);
    ll->printList();

    delete ll;
}