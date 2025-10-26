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

    void addFront(T newNodeT) {
        Node* newNode = new Node(newNodeT);

        newNode->next = dummy->next;
        newNode->prev = dummy;
        newNode->next->prev = newNode;
        dummy->next = newNode;
    };

    void addBack(T newNodeT) {
        Node* newNode = new Node(newNodeT);

        newNode->prev = dummy->prev;
        newNode->next = dummy;
        newNode->prev->next = newNode;
        dummy->prev = newNode;
    };

    int removeFront() {
        if (dummy->next != dummy) {
            Node* toRemove = dummy->next;
            dummy->next = dummy->next->next;
            dummy->next->prev = dummy;
            delete toRemove;
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
            return 0;
        }
        return 1;
    }

    void printList() {
        Node* curr = dummy->next;

        std::cout << "[";
        while (curr != dummy) {
            std::cout << curr->val.field_1 << ",";
            curr = curr->next;
        }
        std::cout << "]" << std::endl;
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

    delete ll;
}