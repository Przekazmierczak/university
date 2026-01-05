#include <iostream>
#include <string>
#include <cstdlib>

#include <cassert>
#include <ctime>
#include <cmath>
#include <time.h>
#include <functional>

#include <vector>

template <typename T>
struct BRT {
private:
    enum Color { BLACK = 0, RED = 1 };

public:
    struct Node {
        Node* parent;
        Node* left;
        Node* right;
        T val;
        Color color;

        Node(T newVal) {
            parent = nullptr;
            left = nullptr;
            right = nullptr;
            val = newVal;
            color = RED;
        }
    };

    Node* root;

    BRT() { root = nullptr; }
    ~BRT() { clear(); }

    int size() const { return treeSize; }
    int height();

    int add(T value, int (*cmp)(const T&, const T&));
    Node* find(T value, int (*cmp)(const T&, const T&));

    std::vector<T> preorder();
    std::vector<T> inorder();

    void clear();

    std::string toString(std::string (*toStringObj)(const T&), bool ifColor, bool ifParent);

private:
    int treeSize = 0;
    bool ifHeightUpdated = true;
    int treeHeight = -1;

    const int printWidth = 6;
    enum Status { SUCCESS = 0, FAIL = 1 };

    int updateHeight(Node* curr);
    Node* createNewNode(T newNodeVal);
    Node* findLeaf(T value, int (*cmp)(const T&, const T&));
    Node* findHelper(Node* curr, T value, int (*cmp)(const T&, const T&));
    
    void fixTree(Node* curr);
    Node* findUncle(Node* curr);

    void rightRotation(Node* node);
    void leftRotation(Node* node);
    void rotate(Node* node);

    void preorderHelper(Node* node, std::vector<T> &pre);
    void inorderHelper(Node* node, std::vector<T> &in);

    void clearHelper(Node* node);

    void addToGraph(
        Node* curr, int col, int row, int size,
        std::string prefix,
        std::vector<std::vector<std::string>> &treeGraph,
        std::string (*toStringObj)(const T&),
        bool ifColor, bool ifParent
        );

    std::string yellow(std::string text) {
        return "\033[33m" + text + "\033[0m";
    }

    std::string green(std::string text) {
        return "\033[32m" + text + "\033[0m";
    }

    std::string blue(std::string text) {
        return "\033[34m" + text + "\033[0m";
    }
    std::string red(std::string text) {
        return "\033[31m" + text + "\033[0m";
    }
    // white
    std::string black(std::string text) {
        return "\033[90m" + text + "\033[0m";
    }

};

struct SomeObject {
    int field_1;
    char field_2;

    bool operator==(const SomeObject& other) const {
        return field_1 == other.field_1 && field_2 == other.field_2;
    }
};

SomeObject createRandom();

int compare(const SomeObject& new_obj, const SomeObject& list_obj);
std::string toStringObj(const SomeObject& obj);

std::string getColumn(std::string value, int width, char filling, char last);
void printSeparator(int numOfMethods,int width);

void fillBRT(int elements, BRT <SomeObject>* brt);

template <typename Func>
std::string measureMethod(Func func, BRT <SomeObject>* brt, int elements, bool requiresFill, int width, bool multiRun);

void assertTests(BRT <SomeObject>* da);

int main() {
    srand(time(0));
    BRT <SomeObject>* brt = new BRT <SomeObject>();

    // Small correctness check
    assertTests(brt);

    // Maximum order: 9 (int overflow)
    int maxOrder = 6;
    int columnWidth = 11;

    struct TestArguments {
        bool enabled;
        std::string name;
        std::function<void()> body;
        bool requiresFill;
        bool multiRun;
    };

    // Change first value (enabled) to reduce number of tests
    TestArguments testMethods[] = {
        {true, "add()", [brt]() { brt->add(createRandom(), compare); }, false, true},
        {true, "find()", [brt]() { brt->find(createRandom(), compare); }, true, true},
        {true, "preorder()", [brt]() { brt->preorder(); }, true, false},
        {true, "inorder()", [brt]() { brt->inorder(); }, true, false},
        {true, "clear()", [brt]() { brt->clear(); }, true, false}
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
                measureMethod(testMethod.body, brt, elements,
                              testMethod.requiresFill, columnWidth,
                              testMethod.multiRun)
                << std::flush;
            }
        }
        std::cout << std::endl;
    }
    printSeparator(countMethodsToPrint, columnWidth);

    delete brt;
}

template <typename T>
int BRT<T>::height() {
    if (!ifHeightUpdated) {
        treeHeight = updateHeight(root);
        ifHeightUpdated = true;
    }
    return treeHeight;
}

template <typename T>
typename BRT<T>::Node* BRT<T>::findUncle(Node* nodeParent) {
    if (nodeParent == nodeParent->parent->left) {
        return nodeParent->parent->right;
    } else {
        return nodeParent->parent->left;
    }
}

template <typename T>
void BRT<T>::rightRotation(Node* node) {
    Node* parent = node->parent;

    if (parent == root) {
        root = node;
        node->parent = nullptr;
    } else {
        if (parent->parent->left == parent) {
            parent->parent->left = node;
        } else {
            parent->parent->right = node;
        }
        node->parent = parent->parent;
    }
    parent->left = node->right;
    if (node->right != nullptr) node->right->parent = parent;
    node->right = parent;
    parent->parent = node;
}

template <typename T>
void BRT<T>::leftRotation(Node* node) {
    Node* parent = node->parent;

    if (parent == root) {
        root = node;
        node->parent = nullptr;
    } else {
        if (parent->parent->left == parent) {
            parent->parent->left = node;
        } else {
            parent->parent->right = node;
        }
        node->parent = parent->parent;
    }
    parent->right = node->left;
    if (node->left != nullptr) node->left->parent = parent;
    node->left = parent;
    parent->parent = node;
}

template <typename T>
void BRT<T>::rotate(Node* node) {
    Node* parent = node->parent;
    Node* grandParent = parent->parent;

    if (parent->left == node) {
        if (grandParent->left == parent) {
            rightRotation(parent);
            parent->color = BLACK;
        } else {
            rightRotation(node);
            leftRotation(node);
            node->color = BLACK;
        }
    } else {
        if (grandParent->left == parent) {
            leftRotation(node);
            rightRotation(node);
            node->color = BLACK;
        } else {
            leftRotation(parent);
            parent->color = BLACK;
        }
    }
    grandParent->color = RED;
}

template <typename T>
void BRT<T>::fixTree(Node* node) {
    if (node == root) {
        node->color = BLACK;
        return;
    }

    if (node->parent->color == RED) {
        Node* uncle = findUncle(node->parent);
        if (uncle != nullptr && uncle->color == RED) {
            uncle->color = BLACK;
            node->parent->color = BLACK;
            node->parent->parent->color = RED;
            fixTree(node->parent->parent);
        } else {
            rotate(node);
        }
    }
}

template <typename T>
int BRT<T>::add(T value, int (*cmp)(const T&, const T&)) {
    Node* newNode = createNewNode(value);
    if (newNode == nullptr) return FAIL;

    if (root == nullptr) {
        root = newNode;
        newNode->color = BLACK;
        treeHeight++;
    } else {
        Node* leaf = findLeaf(value, cmp);

        if (cmp(value, leaf->val) > 0) {
            leaf->right = newNode;
            newNode->parent = leaf;
        } else {
            leaf->left = newNode;
            newNode->parent = leaf;
        }

        fixTree(newNode);
    }
    treeSize++;
    ifHeightUpdated = false;

    return SUCCESS;
};

template <typename T>
typename BRT<T>::Node* BRT<T>::find(T value, int (*cmp)(const T&, const T&)) {
    return findHelper(root, value, cmp);
}

template <typename T>
std::vector<T> BRT<T>::preorder() {
    std::vector<T> pre;
    preorderHelper(root, pre);
    return pre;
}


template <typename T>
std::vector<T> BRT<T>::inorder() {
    std::vector<T> in;
    inorderHelper(root, in);
    return in;
}

template <typename T>
void BRT<T>::clear() {
    clearHelper(root);
    root = nullptr;
    treeSize = 0;
    treeHeight = -1;
    ifHeightUpdated = true;
}

template <typename T>
std::string BRT<T>::toString(std::string (*toStringObj)(const T&), bool ifColor, bool ifParent) {
    if (!root) return "";

    // Update height if needed
    if (!ifHeightUpdated) {
        treeHeight = updateHeight(root);
        ifHeightUpdated = true;
    }

    // Rows = every level double the size of rows
    int rows = (1 << (treeHeight + 1)) - 1; // pow(2, (treeHeight + 1)) - 1
    int cols = treeHeight + 2;

    std::vector<std::vector<std::string>> treeGraph(cols, std::vector<std::string>(rows, std::string(printWidth, ' ')));

    // Recursively fill treeGraph with node strings
    addToGraph(root, 0, rows / 2, rows / 2,
                ifColor ? green("Root" + std::string(printWidth - 4, '-'))
                        : "Root" + std::string(printWidth - 4, '-'),
                treeGraph,
                toStringObj,
                ifColor, ifParent);

    std::string result;
    std::string row;
    
    // Convert 2D graph to single string, skip lines without nodes (ended with "\n");
    for (int i = 0; i < rows; i++) {
        row = "";
        for (int j = 0; j < cols; j++) {
            row += treeGraph[j][i];
            if (treeGraph[j][i] == "\n") {
                result += row;
                break;
            }
        }
    }

    return result;
}

template <typename T>
int BRT<T>::updateHeight(Node* curr) {
    if (!curr) return -1;
    return std::max(updateHeight(curr->left) + 1, updateHeight(curr->right) + 1);
}

template <typename T>
typename BRT<T>::Node* BRT<T>::createNewNode(T newNodeVal) {
    try {
        return new Node(newNodeVal);
    }
    catch (const std::bad_alloc&) {
        return nullptr;
    }
}

template <typename T>
typename BRT<T>::Node* BRT<T>::findLeaf(T value, int (*cmp)(const T&, const T&)) {
    Node* curr = root;
    Node* prev;

    while (curr) {
        prev = curr;
        if (cmp(value, curr->val) > 0) {
            curr = curr->right;
        } else {
            curr = curr->left;
        }
    }

    return prev;
}

template <typename T>
typename BRT<T>::Node* BRT<T>::findHelper(Node* curr, T value, int (*cmp)(const T&, const T&)) {
    if (curr == nullptr) return nullptr;
    int compare = cmp(curr->val, value);
    if (compare == 0) return curr;
    if (compare > 0) return findHelper(curr->left, value, cmp);
    return findHelper(curr->right, value, cmp);
}

template <typename T>
void BRT<T>::preorderHelper(Node* node, std::vector<T> &pre) {
    if (!node) return;
    pre.push_back(node->val);
    preorderHelper(node->left, pre);
    preorderHelper(node->right, pre);
}

template <typename T>
void BRT<T>::inorderHelper(Node* node, std::vector<T> &in) {
    if (!node) return;
    inorderHelper(node->left, in);
    in.push_back(node->val);
    inorderHelper(node->right, in);
}

template <typename T>
void BRT<T>::clearHelper(Node* node) {
    if (!node) return;
    clearHelper(node->left);
    clearHelper(node->right);
    delete node;
}

template <typename T>
void BRT<T>::addToGraph(
    Node* curr, int col, int row, int size,
    std::string prefix,
    std::vector<std::vector<std::string>> &treeGraph,
    std::string (*toStringObj)(const T&),
    bool ifColor, bool ifParent
    ) {
    int newSize = size / 2;

    // Prepare parent string if needed
    std::string parent = "";
    if (ifParent) {
        parent = "P:(Null)";
        if (curr->parent) parent = "P:(" + toStringObj(curr->parent->val) + ")";
    }

    // Fill current node position
    treeGraph[col][row] = prefix + (ifColor ? (curr->color == BLACK ? black("N:(" + toStringObj(curr->val) + ")")
                                                                    : red("N:(" + toStringObj(curr->val) + ")"))
                                            : "N:(" + toStringObj(curr->val) + ")") + parent;

    // Add line break
    treeGraph[col + 1][row] = "\n";

    // Add right child if exists
    if (curr->right) {
        for (int i = 1; i < newSize + 1; i++) {
            treeGraph[col + 1][row - i] = (ifColor ? yellow("|") : ("|")) + std::string(printWidth - 1, ' ');
        }
        addToGraph(curr->right, col + 1, row - (newSize + 1), newSize,
                    ifColor ? yellow("R" + std::string(printWidth - 1, '-'))
                            : "R" + std::string(printWidth - 1, '-'),
                    treeGraph,
                    toStringObj,
                    ifColor, ifParent);
    };

    // Add left child if exists
    if (curr->left) {
        for (int i = 1; i < newSize + 1; i++) {
            treeGraph[col + 1][row + i] = (ifColor ? blue("|") : ("|")) + std::string(printWidth - 1, ' ');
        }
        addToGraph(curr->left, col + 1, row + (newSize + 1), newSize,
                    ifColor ? blue("L" + std::string(printWidth - 1, '-'))
                            : "L" + std::string(printWidth - 1, '-'),
                    treeGraph,
                    toStringObj,
                    ifColor, ifParent);
    };
}

SomeObject createRandom() {
    return { rand() % 1000000, (char)('a' + rand() % 26) };
};

int compare(const SomeObject& new_obj, const SomeObject& list_obj) {
    if (new_obj.field_1 > list_obj.field_1) return 1;
    if (new_obj.field_1 < list_obj.field_1) return -1;
    if (new_obj.field_2 > list_obj.field_2) return 1;
    if (new_obj.field_2 < list_obj.field_2) return -1;
    return 0;
}

std::string toStringObj(const SomeObject& obj) {
    return std::to_string(obj.field_1) + ", " + obj.field_2;
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

void fillBRT(int elements, BRT <SomeObject>* brt) {
    for (int i = 0; i < elements; i++) {
        brt->add(createRandom(), compare);
    }
}

template <typename Func>
std::string measureMethod(Func func, BRT <SomeObject>* brt, int elements, bool requiresFill, int width, bool multiRun) {
    if (requiresFill) fillBRT(elements, brt);

    clock_t t1 = clock();
    if (multiRun) {
        for (int i = 0; i < elements; i++) {
            func();
        }
    } else {
        func();
    }
    clock_t t2 = clock();

    brt->clear();

    double currTime = (t2 - t1) / (double)CLOCKS_PER_SEC;
    std:: string strTime = std::to_string(currTime);
    strTime.erase(strTime.size() - 3);
    return getColumn(strTime + 's', width, ' ', '|');
}

void assertTests(BRT <SomeObject>* brt) {
    SomeObject s0 = { 0, 'a' };
    SomeObject s1 = { 1, 'b' };
    SomeObject s2 = { 2, 'c' };
    SomeObject s3 = { 3, 'd' };
    SomeObject s4 = { 4, 'e' };
    SomeObject s5 = { 5, 'f' };
    SomeObject s6 = { 6, 'g' };
    SomeObject s7 = { 7, 'h' };
    SomeObject s8 = { 8, 'i' };
    SomeObject s9 = { 9, 'j' };
    SomeObject s10 = { 10, 'k' };
    SomeObject s11 = { 11, 'i' };

    std::string print;
    
    for (int i = 0; i < 50; i++) {
        brt->add(createRandom(), compare);
    }

    std::cout << brt->toString(toStringObj, true, false) << std::endl;

    brt->clear();

    // ---- Test add() methods ----
    assert(brt->root == nullptr);
    assert(brt->size() == 0);
    assert(brt->height() == -1);


    brt->add(s0, compare);
    // Root--N:(0, a) BLACK
    assert(brt->root->val.field_1 == 0);
    assert(brt->root->color == 0);

    assert(brt->size() == 1);
    assert(brt->height() == 0);

    brt->add(s1, compare);
    //       R-----N:(1, b) RED
    // Root--N:(0, a) BLACK
    assert(brt->root->val.field_1 == 0);
    assert(brt->root->color == 0);

    assert(brt->root->right->val.field_1 == 1);
    assert(brt->root->right->color == 1);

    assert(brt->size() == 2);
    assert(brt->height() == 1);

    brt->add(s2, compare);
    //       R-----N:(2, c) RED
    // Root--N:(1, b) BLACK
    //       L-----N:(0, a) RED
    assert(brt->root->val.field_1 == 1);
    assert(brt->root->color == 0);

    assert(brt->root->right->val.field_1 == 2);
    assert(brt->root->right->color == 1);
    assert(brt->root->left->val.field_1 == 0);
    assert(brt->root->left->color == 1);

    assert(brt->size() == 3);
    assert(brt->height() == 1);


    brt->add(s5, compare);
    //             R-----N:(5, e) RED
    //       R-----N:(2, c) BLACK
    // Root--N:(1, b) BLACK
    //       L-----N:(0, a) BLACK
    assert(brt->root->val.field_1 == 1);
    assert(brt->root->color == 0);

    assert(brt->root->right->val.field_1 == 2);
    assert(brt->root->right->color == 0);
    assert(brt->root->left->val.field_1 == 0);
    assert(brt->root->left->color == 0);

    assert(brt->root->right->right->val.field_1 == 5);
    assert(brt->root->right->right->color == 1);

    assert(brt->size() == 4);
    assert(brt->height() == 2);

    brt->add(s3, compare);
    //             R-----N:(5, e) RED
    //       R-----N:(3, d) BLACK
    //       |     L-----N:(2, c) RED
    // Root--N:(1, b) BLACK
    //       L-----N:(0, a) BLACK
    assert(brt->root->val.field_1 == 1);
    assert(brt->root->color == 0);

    assert(brt->root->right->val.field_1 == 3);
    assert(brt->root->right->color == 0);
    assert(brt->root->left->val.field_1 == 0);
    assert(brt->root->left->color == 0);

    assert(brt->root->right->right->val.field_1 == 5);
    assert(brt->root->right->right->color == 1);
    assert(brt->root->right->left->val.field_1 == 2);
    assert(brt->root->right->left->color == 1);

    assert(brt->size() == 5);
    assert(brt->height() == 2);

    brt->add(s6, compare);
    //                   R-----N:(6, f) RED
    //             R-----N:(5, e) BLACK
    //       R-----N:(3, d) RED
    //       |     L-----N:(2, c) BLACK
    // Root--N:(1, b) BLACK
    //       L-----N:(0, a) BLACK

    assert(brt->root->val.field_1 == 1);
    assert(brt->root->color == 0);

    assert(brt->root->right->val.field_1 == 3);
    assert(brt->root->right->color == 1);
    assert(brt->root->left->val.field_1 == 0);
    assert(brt->root->left->color == 0);

    assert(brt->root->right->right->val.field_1 == 5);
    assert(brt->root->right->right->color == 0);
    assert(brt->root->right->left->val.field_1 == 2);
    assert(brt->root->right->left->color == 0);

    assert(brt->root->right->right->right->val.field_1 == 6);
    assert(brt->root->right->right->right->color == 1);

    assert(brt->size() == 6);
    assert(brt->height() == 3);

    brt->add(s7, compare);
    //                   R-----N:(7, g) RED
    //             R-----N:(6, f) BLACK
    //             |     L-----N:(5, e) RED
    //       R-----N:(3, d) RED
    //       |     L-----N:(2, c) BLACK
    // Root--N:(1, b) BLACK
    //       L-----N:(0, a) BLACK
    assert(brt->root->val.field_1 == 1);
    assert(brt->root->color == 0);

    assert(brt->root->right->val.field_1 == 3);
    assert(brt->root->right->color == 1);
    assert(brt->root->left->val.field_1 == 0);
    assert(brt->root->left->color == 0);

    assert(brt->root->right->right->val.field_1 == 6);
    assert(brt->root->right->right->color == 0);
    assert(brt->root->right->left->val.field_1 == 2);
    assert(brt->root->right->left->color == 0);

    assert(brt->root->right->right->right->val.field_1 == 7);
    assert(brt->root->right->right->right->color == 1);
    assert(brt->root->right->right->left->val.field_1 == 5);
    assert(brt->root->right->right->left->color == 1);

    assert(brt->size() == 7);
    assert(brt->height() == 3);

    brt->add(s4, compare);
    //             R-----N:(7, h) BLACK
    //       R-----N:(6, g) RED
    //       |     L-----N:(5, f) BLACK
    //       |           L-----N:(4, e) RED
    // Root--N:(3, d) BLACK
    //       |     R-----N:(2, c) BLACK
    //       L-----N:(1, b) RED
    //             L-----N:(0, a) BLACK
    assert(brt->root->val.field_1 == 3);
    assert(brt->root->color == 0);

    assert(brt->root->right->val.field_1 == 6);
    assert(brt->root->right->color == 1);
    assert(brt->root->left->val.field_1 == 1);
    assert(brt->root->left->color == 1);

    assert(brt->root->right->right->val.field_1 == 7);
    assert(brt->root->right->right->color == 0);
    assert(brt->root->right->left->val.field_1 == 5);
    assert(brt->root->right->left->color == 0);
    assert(brt->root->left->right->val.field_1 == 2);
    assert(brt->root->left->right->color == 0);
    assert(brt->root->left->left->val.field_1 == 0);
    assert(brt->root->left->left->color == 0);

    assert(brt->root->right->left->left->val.field_1 == 4);
    assert(brt->root->right->left->left->color == 1);

    assert(brt->size() == 8);
    assert(brt->height() == 3);

    // ---- Test clear() methods ----
    brt->clear();
    assert(brt->size() == 0);
    assert(brt->height() == -1);
    assert(brt->root == nullptr);
}