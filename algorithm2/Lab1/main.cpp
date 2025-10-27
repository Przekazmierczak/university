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
            return 1;
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

    T atIndex(int index) {
        return nodeAtIndex(index)->val;
    }

    void changeAtIndex(int index, T newValue) {
        nodeAtIndex(index)->val = newValue;
    }

    T& operator[](int index) {
        return nodeAtIndex(index)->val;
    }

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
    Node* nodeAtIndex(int index) {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }

        if (index < size / 2) {
            return nodeAtIndexFront(index);
        }
        return nodeAtIndexBack(size - index - 1);
    }

    Node* nodeAtIndexFront(int index) {
        Node* curr = dummy->next;
        for (int i = 0; i < index; i++) {
            curr = curr->next;
        }
        return curr;
    }

    Node* nodeAtIndexBack(int index) {
        Node* curr = dummy->prev;
        for (int i = 0; i < index; i++) {
            curr = curr->prev;
        }

        return curr;
    }
};

struct Some_object {
    int field_1;
    char field_2;
};

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
    std::cout << ll->atIndex(1).field_1 << std::endl;
    std::cout << (*ll)[2].field_1 << std::endl;
    std::cout << ll->atIndex(3).field_1 << std::endl;
    delete ll;
}