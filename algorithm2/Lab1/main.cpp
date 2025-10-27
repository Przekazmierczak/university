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

    int addFront(T newNodeT) {
        try {
            Node* newNode = new Node(newNodeT);
            newNode->next = dummy->next;
            newNode->prev = dummy;
            newNode->next->prev = newNode;
            dummy->next = newNode;
            size++;
            return 0;
        }
        catch (const std::bad_alloc&) {
            return 1;
        }
    };

    void addBack(T newNodeT) {
        Node* newNode = new Node(newNodeT);

        newNode->prev = dummy->prev;
        newNode->next = dummy;
        newNode->prev->next = newNode;
        dummy->prev = newNode;
        size++;
    };

    int removeFront() {
        if (dummy->next != dummy) {
            Node* toRemove = dummy->next;
            dummy->next = dummy->next->next;
            dummy->next->prev = dummy;
            delete toRemove;
            size--;
            return 0;
        }
        return 1;
    }

    int removeBack() {
        if (dummy->prev != dummy) {
            Node* toRemove = dummy->prev;
            dummy->prev = dummy->prev->prev;
            dummy->prev->next = dummy;
            delete toRemove;
            size--;
            return 0;
        }
        return 1;
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

    template <typename A, typename O>
    int remove(A searched, int (*cmp)(A, O)) {
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

    int addInOrder(T newNodeT, int (*cmp)(T, T)) {
        try {
            Node* newNode = new Node(newNodeT);
            
            return 0;
        }
        catch (const std::bad_alloc&) {
            return 1;
        }
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

    template <typename A, typename O>
    Node* findNode(A searched, int (*cmp)(A, O)) {
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


    delete ll;
}