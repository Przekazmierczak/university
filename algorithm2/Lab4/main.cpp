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
struct BST {
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

    BST() { root = nullptr; }
    ~BST() { clear(); }

    int size() const { return treeSize; }
    int height();

    int add(T value, int (*cmp)(const T&, const T&));
    Node* find(T value, int (*cmp)(const T&, const T&));
    // int remove(T value, int (*cmp)(const T&, const T&));

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

void fillBST(int elements, BST <SomeObject>* bst);

template <typename Func>
std::string measureMethod(Func func, BST <SomeObject>* bst, int elements, bool requiresFill, int width, bool multiRun);

void assertTests(BST <SomeObject>* da);

int main() {
    srand(time(0));
    BST <SomeObject>* bst = new BST <SomeObject>();

    // Small correctness check
    assertTests(bst);

    // // Maximum order: 9 (int overflow)
    // int maxOrder = 6;
    // int columnWidth = 11;

    // struct TestArguments {
    //     bool enabled;
    //     std::string name;
    //     std::function<void()> body;
    //     bool requiresFill;
    //     bool multiRun;
    // };

    // // Change first value (enabled) to reduce number of tests
    // TestArguments testMethods[] = {
    //     {true, "add()", [bst]() { bst->add(createRandom(), compare); }, false, true},
    //     {true, "find()", [bst]() { bst->find(createRandom(), compare); }, true, true},
    //     // {true, "remove()", [bst]() { bst->remove(createRandom(), compare); }, true, true},
    //     {true, "preorder()", [bst]() { bst->preorder(); }, true, false},
    //     {true, "inorder()", [bst]() { bst->inorder(); }, true, false},
    //     {true, "clear()", [bst]() { bst->clear(); }, true, false}
    // };

    // int countMethodsToPrint = 0;
    // for (const TestArguments& testMethod : testMethods) {
    //     if (testMethod.enabled) countMethodsToPrint++;
    // }

    // printSeparator(countMethodsToPrint, columnWidth);
    // std::cout << "|" << getColumn("elements", columnWidth, ' ', '|');
    // for (const TestArguments& testMethod : testMethods) {
    //     if (testMethod.enabled) std::cout << getColumn(testMethod.name, columnWidth, ' ', '|');
    // }
    // std::cout << std::endl;
    // printSeparator(countMethodsToPrint, columnWidth);

    // // performance tests
    // for (int o = 1; o <= maxOrder; o++) {
    //     int elements = pow(10, o);
    //     std::cout << "|" << getColumn(std::to_string(elements), columnWidth, ' ', '|');
    //     for (const TestArguments& testMethod : testMethods) {
    //         if (testMethod.enabled) {
    //             std::cout <<
    //             measureMethod(testMethod.body, bst, elements,
    //                           testMethod.requiresFill, columnWidth,
    //                           testMethod.multiRun)
    //             << std::flush;
    //         }
    //     }
    //     std::cout << std::endl;
    // }
    // printSeparator(countMethodsToPrint, columnWidth);

    delete bst;
}

template <typename T>
int BST<T>::height() {
    if (!ifHeightUpdated) {
        treeHeight = updateHeight(root);
        ifHeightUpdated = true;
    }
    return treeHeight;
}

template <typename T>
typename BST<T>::Node* BST<T>::findUncle(Node* nodeParent) {
    if (nodeParent == nodeParent->parent->left) {
        return nodeParent->parent->right;
    } else {
        return nodeParent->parent->left;
    }
}

template <typename T>
void BST<T>::rightRotation(Node* node) {
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
void BST<T>::leftRotation(Node* node) {
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
void BST<T>::rotate(Node* node) {
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
void BST<T>::fixTree(Node* node) {
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
int BST<T>::add(T value, int (*cmp)(const T&, const T&)) {
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
typename BST<T>::Node* BST<T>::find(T value, int (*cmp)(const T&, const T&)) {
    return findHelper(root, value, cmp);
}

// template <typename T>
// int BST<T>::remove(T value, int (*cmp)(const T&, const T&)) {
//     Node* node = find(value, cmp);
//     if (node == nullptr) return FAIL;
//     removeNode(node);
//     treeSize--;
//     ifHeightUpdated = false;
//     return SUCCESS;
// }

template <typename T>
std::vector<T> BST<T>::preorder() {
    std::vector<T> pre;
    preorderHelper(root, pre);
    return pre;
}


template <typename T>
std::vector<T> BST<T>::inorder() {
    std::vector<T> in;
    inorderHelper(root, in);
    return in;
}

template <typename T>
void BST<T>::clear() {
    clearHelper(root);
    root = nullptr;
    treeSize = 0;
    treeHeight = -1;
    ifHeightUpdated = true;
}

template <typename T>
std::string BST<T>::toString(std::string (*toStringObj)(const T&), bool ifColor, bool ifParent) {
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
int BST<T>::updateHeight(Node* curr) {
    if (!curr) return -1;
    return std::max(updateHeight(curr->left) + 1, updateHeight(curr->right) + 1);
}

template <typename T>
typename BST<T>::Node* BST<T>::createNewNode(T newNodeVal) {
    try {
        return new Node(newNodeVal);
    }
    catch (const std::bad_alloc&) {
        return nullptr;
    }
}

template <typename T>
typename BST<T>::Node* BST<T>::findLeaf(T value, int (*cmp)(const T&, const T&)) {
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
typename BST<T>::Node* BST<T>::findHelper(Node* curr, T value, int (*cmp)(const T&, const T&)) {
    if (curr == nullptr) return nullptr;
    int compare = cmp(curr->val, value);
    if (compare == 0) return curr;
    if (compare > 0) return findHelper(curr->left, value, cmp);
    return findHelper(curr->right, value, cmp);
}

template <typename T>
void BST<T>::preorderHelper(Node* node, std::vector<T> &pre) {
    if (!node) return;
    pre.push_back(node->val);
    preorderHelper(node->left, pre);
    preorderHelper(node->right, pre);
}

template <typename T>
void BST<T>::inorderHelper(Node* node, std::vector<T> &in) {
    if (!node) return;
    inorderHelper(node->left, in);
    in.push_back(node->val);
    inorderHelper(node->right, in);
}

template <typename T>
void BST<T>::clearHelper(Node* node) {
    if (!node) return;
    clearHelper(node->left);
    clearHelper(node->right);
    delete node;
}

template <typename T>
void BST<T>::addToGraph(
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

void fillBST(int elements, BST <SomeObject>* bst) {
    for (int i = 0; i < elements; i++) {
        bst->add(createRandom(), compare);
    }
}

template <typename Func>
std::string measureMethod(Func func, BST <SomeObject>* bst, int elements, bool requiresFill, int width, bool multiRun) {
    if (requiresFill) fillBST(elements, bst);

    clock_t t1 = clock();
    if (multiRun) {
        for (int i = 0; i < elements; i++) {
            func();
        }
    } else {
        func();
    }
    clock_t t2 = clock();

    bst->clear();

    double currTime = (t2 - t1) / (double)CLOCKS_PER_SEC;
    std:: string strTime = std::to_string(currTime);
    strTime.erase(strTime.size() - 3);
    return getColumn(strTime + 's', width, ' ', '|');
}

void assertTests(BST <SomeObject>* bst) {
    SomeObject s0 = { 0, 'a' };
    SomeObject s1 = { 10, 'b' };
    SomeObject s2 = { 20, 'c' };
    SomeObject s3 = { 30, 'd' };
    SomeObject s4 = { 40, 'e' };
    SomeObject s5 = { 50, 'f' };
    SomeObject s6 = { 60, 'g' };
    SomeObject s7 = { 70, 'h' };
    SomeObject s8 = { 80, 'i' };
    SomeObject s9 = { 90, 'j' };
    SomeObject s10 = { 4, 'k' };
    SomeObject s11 = { 8, 'i' };

    std::string print;
    
    // for (int i = 0; i < 20; i++) {
    //     bst->add(createRandom(), compare);
    // }

    bst->add(s1, compare);
    bst->add(s2, compare);
    bst->add(s3, compare);
    bst->add(s5, compare);
    bst->add(s4, compare);
    bst->add(s6, compare);
    bst->add(s7, compare);
    bst->add(s8, compare);
    bst->add(s10, compare);
    bst->add(s11, compare);

    std::cout << bst->toString(toStringObj, true, false) << std::endl;

    bst->clear();

//     // ---- Test add() methods ----
//     assert(bst->root == nullptr);
//     assert(bst->size() == 0);
//     assert(bst->height() == -1);

//     print =
//     "";
//     assert(bst->toString(toStringObj, false, true) == print);

//     bst->add(s5, compare);
//     assert(bst->root->val.field_1 == 5);
//     assert(bst->size() == 1);
//     assert(bst->height() == 0);

//     print =
//     "Root--N:(5, f)P:(Null)\n";
//     assert(bst->toString(toStringObj, false, true) == print);

//     bst->add(s3, compare);
//     assert(bst->root->val.field_1 == 5);
//     assert(bst->root->left->val.field_1 == 3);
//     assert(bst->size() == 2);
//     assert(bst->height() == 1);

//     print = 
//     "Root--N:(5, f)P:(Null)\n"
//     "      L-----N:(3, d)P:(5, f)\n";
//     assert(bst->toString(toStringObj, false, true) == print);

//     bst->add(s7, compare);
//     assert(bst->root->val.field_1 == 5);
//     assert(bst->root->left->val.field_1 == 3);
//     assert(bst->root->right->val.field_1 == 7);
//     assert(bst->size() == 3);
//     assert(bst->height() == 1);

//     print = 
//     "      R-----N:(7, h)P:(5, f)\n"
//     "Root--N:(5, f)P:(Null)\n"
//     "      L-----N:(3, d)P:(5, f)\n";
//     assert(bst->toString(toStringObj, false, true) == print);
    
//     bst->add(s1, compare);
//     assert(bst->root->val.field_1 == 5);
//     assert(bst->root->left->val.field_1 == 3);
//     assert(bst->root->right->val.field_1 == 7);
//     assert(bst->root->left->left->val.field_1 == 1);
//     assert(bst->size() == 4);
//     assert(bst->height() == 2);

//     print =
//     "      R-----N:(7, h)P:(5, f)\n"
//     "Root--N:(5, f)P:(Null)\n"
//     "      L-----N:(3, d)P:(5, f)\n"
//     "            L-----N:(1, b)P:(3, d)\n";
//     assert(bst->toString(toStringObj, false, true) == print);

//     bst->add(s4, compare);
//     assert(bst->root->val.field_1 == 5);
//     assert(bst->root->left->val.field_1 == 3);
//     assert(bst->root->right->val.field_1 == 7);
//     assert(bst->root->left->left->val.field_1 == 1);
//     assert(bst->root->left->right->val.field_1 == 4);
//     assert(bst->size() == 5);
//     assert(bst->height() == 2);

//     print =
//     "      R-----N:(7, h)P:(5, f)\n"
//     "Root--N:(5, f)P:(Null)\n"
//     "      |     R-----N:(4, e)P:(3, d)\n"
//     "      L-----N:(3, d)P:(5, f)\n"
//     "            L-----N:(1, b)P:(3, d)\n";
//     assert(bst->toString(toStringObj, false, true) == print);


//     bst->add(s6, compare);
//     assert(bst->root->right->left->val.field_1 == 6);
//     assert(bst->size() == 6);
//     assert(bst->height() == 2);

//     print =
//     "      R-----N:(7, h)P:(5, f)\n"
//     "      |     L-----N:(6, g)P:(7, h)\n"
//     "Root--N:(5, f)P:(Null)\n"
//     "      |     R-----N:(4, e)P:(3, d)\n"
//     "      L-----N:(3, d)P:(5, f)\n"
//     "            L-----N:(1, b)P:(3, d)\n";
//     assert(bst->toString(toStringObj, false, true) == print);

//     bst->add(s9, compare);
//     assert(bst->root->right->right->val.field_1 == 9);
//     assert(bst->size() == 7);
//     assert(bst->height() == 2);

//     print =
//     "            R-----N:(9, j)P:(7, h)\n"
//     "      R-----N:(7, h)P:(5, f)\n"
//     "      |     L-----N:(6, g)P:(7, h)\n"
//     "Root--N:(5, f)P:(Null)\n"
//     "      |     R-----N:(4, e)P:(3, d)\n"
//     "      L-----N:(3, d)P:(5, f)\n"
//     "            L-----N:(1, b)P:(3, d)\n";
//     assert(bst->toString(toStringObj, false, true) == print);

//     bst->add(s0, compare);
//     assert(bst->root->left->left->left->val.field_1 == 0);
//     assert(bst->size() == 8);
//     assert(bst->height() == 3);

//     print =
//     "            R-----N:(9, j)P:(7, h)\n"
//     "      R-----N:(7, h)P:(5, f)\n"
//     "      |     L-----N:(6, g)P:(7, h)\n"
//     "Root--N:(5, f)P:(Null)\n"
//     "      |     R-----N:(4, e)P:(3, d)\n"
//     "      L-----N:(3, d)P:(5, f)\n"
//     "            L-----N:(1, b)P:(3, d)\n"
//     "                  L-----N:(0, a)P:(1, b)\n";
//     assert(bst->toString(toStringObj, false, true) == print);

//     bst->add(s2, compare);
//     assert(bst->root->left->left->right->val.field_1 == 2);
//     assert(bst->size() == 9);
//     assert(bst->height() == 3);

//     print =
//     "            R-----N:(9, j)P:(7, h)\n"
//     "      R-----N:(7, h)P:(5, f)\n"
//     "      |     L-----N:(6, g)P:(7, h)\n"
//     "Root--N:(5, f)P:(Null)\n"
//     "      |     R-----N:(4, e)P:(3, d)\n"
//     "      L-----N:(3, d)P:(5, f)\n"
//     "            |     R-----N:(2, c)P:(1, b)\n"
//     "            L-----N:(1, b)P:(3, d)\n"
//     "                  L-----N:(0, a)P:(1, b)\n";
//     assert(bst->toString(toStringObj, false, true) == print);

//     bst->add(s8, compare);
//     assert(bst->root->right->right->left->val.field_1 == 8);
//     assert(bst->size() == 10);
//     assert(bst->height() == 3);

//     print =
//     "            R-----N:(9, j)P:(7, h)\n"
//     "            |     L-----N:(8, i)P:(9, j)\n"
//     "      R-----N:(7, h)P:(5, f)\n"
//     "      |     L-----N:(6, g)P:(7, h)\n"
//     "Root--N:(5, f)P:(Null)\n"
//     "      |     R-----N:(4, e)P:(3, d)\n"
//     "      L-----N:(3, d)P:(5, f)\n"
//     "            |     R-----N:(2, c)P:(1, b)\n"
//     "            L-----N:(1, b)P:(3, d)\n"
//     "                  L-----N:(0, a)P:(1, b)\n";
//     assert(bst->toString(toStringObj, false, true) == print);

//     bst->add(s10, compare);
//     assert(bst->root->right->right->right->val.field_1 == 10);
//     assert(bst->size() == 11);
//     assert(bst->height() == 3);

//     print =
//     "                  R-----N:(10, k)P:(9, j)\n"
//     "            R-----N:(9, j)P:(7, h)\n"
//     "            |     L-----N:(8, i)P:(9, j)\n"
//     "      R-----N:(7, h)P:(5, f)\n"
//     "      |     L-----N:(6, g)P:(7, h)\n"
//     "Root--N:(5, f)P:(Null)\n"
//     "      |     R-----N:(4, e)P:(3, d)\n"
//     "      L-----N:(3, d)P:(5, f)\n"
//     "            |     R-----N:(2, c)P:(1, b)\n"
//     "            L-----N:(1, b)P:(3, d)\n"
//     "                  L-----N:(0, a)P:(1, b)\n";
//     assert(bst->toString(toStringObj, false, true) == print);

//     // ---- Test find() methods ----
//     assert((bst->find(s1, compare))->val.field_1 == 1);
//     assert((bst->find(s3, compare))->val.field_1 == 3);
//     assert((bst->find(s5, compare))->val.field_1 == 5);
//     assert((bst->find(s7, compare))->val.field_1 == 7);
//     assert((bst->find(s9, compare))->val.field_1 == 9);
//     assert((bst->find(s11, compare)) == nullptr);

//     // ---- Test preorder(), inorder() methods ----
//     std::vector<SomeObject> pre = bst->preorder();
//     std::vector<SomeObject> preTest = { s5, s3, s1, s0, s2, s4, s7, s6, s9, s8, s10 };
//     assert(pre == preTest);
    
//     std::vector<SomeObject> in = bst->inorder();
//     std::vector<SomeObject> inTest = { s0, s1, s2, s3, s4, s5, s6, s7, s8, s9, s10 };
//     assert(in == inTest);

//     // ---- Test remove() methods ----
//     bst->remove(s10, compare);
//     assert(bst->size() == 10);
//     assert(bst->height() == 3);

//     print =
//     "            R-----N:(9, j)P:(7, h)\n"
//     "            |     L-----N:(8, i)P:(9, j)\n"
//     "      R-----N:(7, h)P:(5, f)\n"
//     "      |     L-----N:(6, g)P:(7, h)\n"
//     "Root--N:(5, f)P:(Null)\n"
//     "      |     R-----N:(4, e)P:(3, d)\n"
//     "      L-----N:(3, d)P:(5, f)\n"
//     "            |     R-----N:(2, c)P:(1, b)\n"
//     "            L-----N:(1, b)P:(3, d)\n"
//     "                  L-----N:(0, a)P:(1, b)\n";
//     assert(bst->toString(toStringObj, false, true) == print);

//     bst->remove(s9, compare);
//     assert(bst->size() == 9);
//     assert(bst->height() == 3);

//     print =
//     "            R-----N:(8, i)P:(7, h)\n"
//     "      R-----N:(7, h)P:(5, f)\n"
//     "      |     L-----N:(6, g)P:(7, h)\n"
//     "Root--N:(5, f)P:(Null)\n"
//     "      |     R-----N:(4, e)P:(3, d)\n"
//     "      L-----N:(3, d)P:(5, f)\n"
//     "            |     R-----N:(2, c)P:(1, b)\n"
//     "            L-----N:(1, b)P:(3, d)\n"
//     "                  L-----N:(0, a)P:(1, b)\n";
//     assert(bst->toString(toStringObj, false, true) == print);

//     bst->remove(s7, compare);
//     assert(bst->size() == 8);
//     assert(bst->height() == 3);

//     print =
//     "            R-----N:(8, i)P:(6, g)\n"
//     "      R-----N:(6, g)P:(5, f)\n"
//     "Root--N:(5, f)P:(Null)\n"
//     "      |     R-----N:(4, e)P:(3, d)\n"
//     "      L-----N:(3, d)P:(5, f)\n"
//     "            |     R-----N:(2, c)P:(1, b)\n"
//     "            L-----N:(1, b)P:(3, d)\n"
//     "                  L-----N:(0, a)P:(1, b)\n";
//     assert(bst->toString(toStringObj, false, true) == print);

//     bst->remove(s5, compare);
//     assert(bst->size() == 7);
//     assert(bst->height() == 3);

//     print =
//     "            R-----N:(8, i)P:(6, g)\n"
//     "      R-----N:(6, g)P:(4, e)\n"
//     "Root--N:(4, e)P:(Null)\n"
//     "      L-----N:(3, d)P:(4, e)\n"
//     "            |     R-----N:(2, c)P:(1, b)\n"
//     "            L-----N:(1, b)P:(3, d)\n"
//     "                  L-----N:(0, a)P:(1, b)\n";
//     assert(bst->toString(toStringObj, false, true) == print);

//     bst->remove(s1, compare);
//     assert(bst->size() == 6);
//     assert(bst->height() == 3);

//     print =
//     "            R-----N:(8, i)P:(6, g)\n"
//     "      R-----N:(6, g)P:(4, e)\n"
//     "Root--N:(4, e)P:(Null)\n"
//     "      L-----N:(3, d)P:(4, e)\n"
//     "            |     R-----N:(2, c)P:(0, a)\n"
//     "            L-----N:(0, a)P:(3, d)\n";
//     assert(bst->toString(toStringObj, false, true) == print);

//     bst->remove(s4, compare);
//     assert(bst->size() == 5);
//     assert(bst->height() == 2);

//     print =
//     "            R-----N:(8, i)P:(6, g)\n"
//     "      R-----N:(6, g)P:(3, d)\n"
//     "Root--N:(3, d)P:(Null)\n"
//     "      |     R-----N:(2, c)P:(0, a)\n"
//     "      L-----N:(0, a)P:(3, d)\n";
//     assert(bst->toString(toStringObj, false, true) == print);

//     // ---- Test clear() methods ----
//     bst->clear();
//     assert(bst->size() == 0);
//     assert(bst->height() == -1);
//     assert(bst->root == nullptr);
}