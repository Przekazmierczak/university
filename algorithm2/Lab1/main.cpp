#include <iostream>
#include <string>

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

    template <typename A, typename O>
    T* find(A searched, int (*cmp)(const A&, const O&)) const {
        Node* find = findNode(searched, cmp);
        
        if (find != nullptr) return &(find->val);

        return nullptr;
    }

    template <typename A>
    int remove(A searched, int (*cmp)(const A&, const T&)) {
        Node* node = findNode(searched, cmp);

        if (node != nullptr) {
            removeNode(node);
            return 0;
        }

        return 1;
    }

    int insertOrdered(T newNodeVal, int (*cmp)(const T&, const T&)) {
        Node* newNode = createNewNode(newNodeVal);
        if (newNode == nullptr) return 1;

        Node* curr = dummy->next;
        while (curr != dummy && cmp(newNode->val, curr->val) > 0) {
            curr = curr->next;
        }
        addNodeBack(newNode, curr);
        return 0;
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
            return 0;
        }
        return 1;
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

struct Some_object {
    int field_1;
    char field_2;
};

int compare1(const int& value, const Some_object& obj) {
    if (value == obj.field_1) {
        return 0;
    }
    return 1;
}

int compare2(const Some_object& new_obj, const Some_object& list_obj) {
    if (new_obj.field_1 > list_obj.field_1) return 1;
    if (new_obj.field_1 < list_obj.field_1) return -1;
    return 0;
}

std::string toStringObj(const Some_object& obj) {
    return std::to_string(obj.field_1);
}

int main() {
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

    std::cout << ll->toString(toStringObj) << std::endl;
    std::cout<<ll->removeFront()<<std::endl;
    std::cout << ll->toString(toStringObj) << std::endl;
    std::cout<<ll->removeFront()<<std::endl;
    std::cout << ll->toString(toStringObj) << std::endl;
    std::cout<<ll->removeFront()<<std::endl;
    std::cout << ll->toString(toStringObj) << std::endl;
    std::cout<<ll->removeFront()<<std::endl;
    std::cout << ll->toString(toStringObj) << std::endl;
    std::cout<<ll->removeFront()<<std::endl;
    std::cout << ll->toString(toStringObj) << std::endl;
    
    ll->addBack(s0);
    std::cout << ll->toString(toStringObj) << std::endl;
    ll->addBack(s1);
    std::cout << ll->toString(toStringObj) << std::endl;
    ll->addFront(s3);
    std::cout << ll->toString(toStringObj) << std::endl;
    
    std::cout<<ll->removeBack()<<std::endl;
    std::cout << ll->toString(toStringObj) << std::endl;
    std::cout<<ll->removeBack()<<std::endl;
    std::cout << ll->toString(toStringObj) << std::endl;
    std::cout<<ll->removeBack()<<std::endl;
    std::cout << ll->toString(toStringObj) << std::endl;
    std::cout<<ll->removeBack()<<std::endl;
    std::cout << ll->toString(toStringObj) << std::endl;
    std::cout<<ll->removeBack()<<std::endl;
    std::cout << ll->toString(toStringObj) << std::endl;

    ll->addFront(s0);
    std::cout << ll->toString(toStringObj) << std::endl;
    ll->addFront(s1);
    std::cout << ll->toString(toStringObj) << std::endl;
    ll->addBack(s3);
    std::cout << ll->toString(toStringObj) << std::endl;
    ll->addFront(s2);
    std::cout << ll->toString(toStringObj) << std::endl;

    (*ll)[1] = s4;
    std::cout << ll->toString(toStringObj) << std::endl;

    std::cout << (*ll)[0].field_1 << std::endl;
    std::cout << ll->at(1).field_1 << std::endl;
    std::cout << (*ll)[2].field_1 << std::endl;
    std::cout << ll->at(3).field_1 << std::endl;

    std::cout << ll->find(4, compare1)->field_1 << std::endl;
    std::cout << ll->find(2, compare1)->field_1 << std::endl;

    std::cout << ll->toString(toStringObj) << std::endl;
    ll->remove(4, compare1);
    std::cout << ll->toString(toStringObj) << std::endl;
    ll->remove(2, compare1);
    std::cout << ll->toString(toStringObj) << std::endl;
    ll->remove(3, compare1);
    std::cout << ll->toString(toStringObj) << std::endl;
    ll->remove(0, compare1);
    std::cout << ll->toString(toStringObj) << std::endl;

    ll->insertOrdered(s2, compare2);
    ll->insertOrdered(s0, compare2);
    ll->insertOrdered(s4, compare2);
    ll->insertOrdered(s3, compare2);
    ll->insertOrdered(s1, compare2);
    //ll->insertOrdered(s0, compare2);
    std::cout << ll->toString(toStringObj) << std::endl;

    ll->clear();
    std::cout << ll->toString(toStringObj) << std::endl;

    delete ll;
}