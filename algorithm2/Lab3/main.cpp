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
    struct Node {
        Node* parent;
        Node* left;
        Node* right;
        T val;

        Node(T newVal) {
            parent = nullptr;
            left = nullptr;
            right = nullptr;
            val = newVal;
        }
    };
    Node* root;

    BST() { root = nullptr; }
    ~BST() {
        clear();
    }

    int size() const { return treeSize; }

    int add(T value, int (*cmp)(const T&, const T&)) {
        Node* newNode = createNewNode(value);
        if (newNode == nullptr) return FAIL;

        if (root == nullptr) {
            root = newNode;
            treeHeight++;
        } else {
            Node* leaf = findLeaf(value, cmp);

            if (cmp(value, leaf->val) > 0) {
                leaf->right = newNode;
            } else {
                leaf->left = newNode;
            }

            newNode->parent = leaf;
        }
        treeSize++;
        return SUCCESS;
    };

    Node* find(T value, int (*cmp)(const T&, const T&)) {
        return findHelper(root, value, cmp);
    }

    int remove(T value, int (*cmp)(const T&, const T&)) {
        Node* node = find(value, cmp);
        if (node == nullptr) return FAIL;
        
        removeNode(node);

        treeSize--;
        ifHeightUpdated = false;

        return SUCCESS;
    }

    std::vector<T> preorder() {
        std::vector<T> pre;
        preorderHelper(root, pre);
        return pre;
    }

    void preorderHelper(Node* node, std::vector<T> &pre) {
        if (!node) return;
        pre.push_back(node->val);
        preorderHelper(node->left, pre);
        preorderHelper(node->right, pre);
    }

    std::vector<T> inorder() {
        std::vector<T> in;
        inorderHelper(root, in);
        return in;
    }

    void inorderHelper(Node* node, std::vector<T> &in) {
        if (!node) return;
        inorderHelper(node->left, in);
        in.push_back(node->val);
        inorderHelper(node->right, in);
    }

    void clear() {
        clearHelper(root);
        root = nullptr;
        treeSize = 0;
        treeHeight = -1;
        ifHeightUpdated = true;
    }

    void clearHelper(Node* node) {
        if (!node) return;
        clearHelper(node->left);
        clearHelper(node->right);
        delete node;
    }

    int height() {
        if (!ifHeightUpdated) {
            treeHeight = updateHeight(root);
            ifHeightUpdated = true;
        }
        return treeHeight;
    }

    std::string toString(std::string (*toStringObj)(const T&)) {
        if (!ifHeightUpdated) {
            treeHeight = updateHeight(root);
            ifHeightUpdated = true;
        }

        // Every level of tree double the size + 1: 2^(treeHeight + 1) - 1
        int rows = (1 << (treeHeight + 1)) - 1;
        int cols = treeHeight + 2;

        std::vector<std::vector<std::string>> treeGraph(cols, std::vector<std::string>(rows, std::string(printWidth, ' ')));

        addToGraph(root, 0, rows / 2, rows / 2,
                   red("Root" + std::string(printWidth - 4, '-')),
                   treeGraph,
                   toStringObj);

        std::string result;
        std::string row;
        
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

private:
    int treeSize = 0;
    bool ifHeightUpdated = true;
    int treeHeight = -1;

    const int printWidth = 6;
    enum Status { SUCCESS = 0, FAIL = 1 };

    Node* createNewNode(T newNodeVal) {
        try {
            return new Node(newNodeVal);
        }
        catch (const std::bad_alloc&) {
            return nullptr;
        }
    }

    Node* findLeaf(T value, int (*cmp)(const T&, const T&)) {
        Node* curr = root;
        Node* prev;
        int depth = 0;

        while (curr) {
            prev = curr;
            if (cmp(value, curr->val) > 0) {
                curr = curr->right;
            } else {
                curr = curr->left;
            }
            depth++;
        }

        if (ifHeightUpdated && treeHeight < depth) treeHeight = depth; 
        return prev;
    }

    Node* findHelper(Node* curr, T value, int (*cmp)(const T&, const T&)) {
        if (curr == nullptr) return nullptr;
        int compare = cmp(curr->val, value);
        if (compare == 0) return curr;
        if (compare > 0) return findHelper(curr->left, value, cmp);
        return findHelper(curr->right, value, cmp);
    }

    void removeNode(Node* node) {
        if (node->left == nullptr && node->right == nullptr) {
            removeWithNoChildren(node);
        } else if (node->right == nullptr) {
            removeWithOneChild(node, node->left);
        } else if (node->left == nullptr) {
            removeWithOneChild(node, node->right);
        } else {
            removeWithTwoChildren(node);
        }
    }

    void removeWithNoChildren(Node* node) {
        if (node->parent == nullptr) {
            root = nullptr;
        } else if (node->parent->left == node) {
            node->parent->left = nullptr;
        } else {
            node->parent->right = nullptr;
        }
        delete node;
    }

    void removeWithOneChild(Node* node, Node* child) {
        if (node->parent == nullptr) {
            root = child;
            child->parent = nullptr;
        } else if (node->parent->left == node) {
            node->parent->left = child;
            child->parent = node->parent;
        } else {
            node->parent->right = child;
            child->parent = node->parent;
        }
        delete node;
    }

    void removeWithTwoChildren(Node* node) {
        Node* neighbor = findNeighbor(node->left);

        Node* child = neighbor->left;

        if (neighbor->parent->right == neighbor) {
            neighbor->parent->right = child;
        } else if (neighbor->parent->left == neighbor) {
            neighbor->parent->left = child;
        }
        if (child) child->parent = neighbor->parent;

        neighbor->parent = node->parent;
        neighbor->left = node->left;
        neighbor->right = node->right;

        if (node->left) node->left->parent = neighbor;
        if (node->right) node->right->parent = neighbor;

        if (node->parent == nullptr) {
            root = neighbor;
        } else if (node->parent->left == node) {
            node->parent->left = neighbor;
        } else {
            node->parent->right = neighbor;
        }

        delete node;
    }

    Node* findNeighbor(Node* node) {
        while (node->right != nullptr) node = node->right;
        return node;
    }

    // void swap(Node* node, Node* neighbor) {
    //     Node* child = neighbor->left;

    //     if (neighbor->parent->right == neighbor) {
    //         neighbor->parent->right = child;
    //     } else if (neighbor->parent->left == neighbor) {
    //         neighbor->parent->left = child;
    //     }
    //     if (child) child->parent = neighbor->parent;

    //     neighbor->parent = node->parent;
    //     neighbor->left = node->left;
    //     neighbor->right = node->right;

    //     if (node->left) node->left->parent = neighbor;
    //     if (node->right) node->right->parent = neighbor;

    //     if (node->parent == nullptr) {
    //         root = neighbor;
    //     } else if (node->parent->left == node) {
    //         node->parent->left = neighbor;
    //     } else {
    //         node->parent->right = neighbor;
    //     }

    //     delete node;
    // }

    int updateHeight(Node* curr) {
        if (!curr) return -1;
        return std::max(updateHeight(curr->left) + 1, updateHeight(curr->right) + 1);
    }

    void addToGraph(
        Node* curr, int col, int row, int size,
        std::string prefix,
        std::vector<std::vector<std::string>> &treeGraph,
        std::string (*toStringObj)(const T&)
        ) {
        int newSize = size / 2;
        std::string parent = red("P:(Null)");
        if (curr->parent) parent = red("P:(" + toStringObj(curr->parent->val) + ")");
        treeGraph[col][row] = prefix + green("N:(" + toStringObj(curr->val) + ")") + parent;
        treeGraph[col + 1][row] = "\n";

        if (curr->right) {
            for (int i = 1; i < newSize + 1; i++) {
                treeGraph[col + 1][row - i] = yellow("|") + std::string(printWidth - 1, ' ');
            }
            addToGraph(curr->right, col + 1, row - (newSize + 1), newSize,
                       yellow("R" + std::string(printWidth - 1, '-')),
                       treeGraph,
                       toStringObj);
        };

        if (curr->left) {
            for (int i = 1; i < newSize + 1; i++) {
                treeGraph[col + 1][row + i] = blue("|") + std::string(printWidth - 1, ' ');
            }
            addToGraph(curr->left, col + 1, row + (newSize + 1), newSize,
                       blue("L" + std::string(printWidth - 1, '-')),
                       treeGraph,
                       toStringObj);
        };
    }

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
};

struct SomeObject {
    int field_1;
    char field_2;
};

SomeObject createRandom();

int compare(const SomeObject& new_obj, const SomeObject& list_obj);
std::string toStringObj(const SomeObject& obj);

std::string getColumn(std::string value, int width, char filling, char last);
void printSeparator(int numOfMethods,int width);

void fillArray(int elements, BST <SomeObject>* da);

template <typename Func>
std::string measureMethod(Func func, BST <SomeObject>* da, int elements, bool requiresFill, int width, bool multiRun);

void assertTests(BST <SomeObject>* da);

int main() {
    srand(time(0));
    BST <SomeObject>* bst = new BST <SomeObject>();

    
    
    // Small correctness check
    assertTests(bst);

    // // Maximum order: 9 (int overflow)
    // int maxOrder = 5;
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
    //     {true, "add()", [da]() { da->add(createRandom(), compare); }, false, true},
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
    //             measureMethod(testMethod.body, da, elements,
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

SomeObject createRandom() {
    return { rand() % 1000000, (char)('a' + rand() % 26) };
};

int compare(const SomeObject& new_obj, const SomeObject& list_obj) {
    if (new_obj.field_1 > list_obj.field_1) return 1;
    if (new_obj.field_1 < list_obj.field_1) return -1;
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

// template <typename Func>
// std::string measureMethod(Func func, BST <SomeObject>* da, int elements, bool requiresFill, int width, bool multiRun) {
//     if (requiresFill) fillVector(elements, dv);

//     clock_t t1 = clock();
//     if (multiRun) {
//         for (int i = 0; i < elements; i++) {
//             func();
//         }
//     } else {
//         func();
//     }
//     clock_t t2 = clock();

//     da->clear();

//     double currTime = (t2 - t1) / (double)CLOCKS_PER_SEC;
//     std:: string strTime = std::to_string(currTime);
//     strTime.erase(strTime.size() - 3);
//     return getColumn(strTime + 's', width, ' ', '|');
// }

void assertTests(BST <SomeObject>* bst) {
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
    
    // for (int i = 0; i < 20; i++) {
    //     bst->add(createRandom(), compare);
    // }

    // std::cout << bst->toString(toStringObj) << std::endl;

    // ---- Test add() methods ----
    assert(bst->root == nullptr);
    assert(bst->size() == 0);
    assert(bst->height() == -1);

    bst->add(s5, compare);
    assert(bst->root->val.field_1 == 5);
    assert(bst->size() == 1);
    assert(bst->height() == 0);

    bst->add(s3, compare);
    assert(bst->root->val.field_1 == 5);
    assert(bst->root->left->val.field_1 == 3);
    assert(bst->size() == 2);
    assert(bst->height() == 1);

    bst->add(s7, compare);
    assert(bst->root->val.field_1 == 5);
    assert(bst->root->left->val.field_1 == 3);
    assert(bst->root->right->val.field_1 == 7);
    assert(bst->size() == 3);
    assert(bst->height() == 1);
    
    bst->add(s1, compare);
    assert(bst->root->val.field_1 == 5);
    assert(bst->root->left->val.field_1 == 3);
    assert(bst->root->right->val.field_1 == 7);
    assert(bst->root->left->left->val.field_1 == 1);
    assert(bst->size() == 4);
    assert(bst->height() == 2);

    bst->add(s4, compare);
    assert(bst->root->val.field_1 == 5);
    assert(bst->root->left->val.field_1 == 3);
    assert(bst->root->right->val.field_1 == 7);
    assert(bst->root->left->left->val.field_1 == 1);
    assert(bst->root->left->right->val.field_1 == 4);
    assert(bst->size() == 5);
    assert(bst->height() == 2);

    bst->add(s6, compare);
    assert(bst->root->right->left->val.field_1 == 6);
    assert(bst->size() == 6);
    assert(bst->height() == 2);

    bst->add(s9, compare);
    assert(bst->root->right->right->val.field_1 == 9);
    assert(bst->size() == 7);
    assert(bst->height() == 2);

    bst->add(s0, compare);
    assert(bst->root->left->left->left->val.field_1 == 0);
    assert(bst->size() == 8);
    assert(bst->height() == 3);

    bst->add(s2, compare);
    assert(bst->root->left->left->right->val.field_1 == 2);
    assert(bst->size() == 9);
    assert(bst->height() == 3);

    bst->add(s8, compare);
    assert(bst->root->right->right->left->val.field_1 == 8);
    assert(bst->size() == 10);
    assert(bst->height() == 3);

    bst->add(s10, compare);
    assert(bst->root->right->right->right->val.field_1 == 10);
    assert(bst->size() == 11);
    assert(bst->height() == 3);

    // ---- Test find() methods ----
    assert((bst->find(s1, compare))->val.field_1 == 1);
    assert((bst->find(s3, compare))->val.field_1 == 3);
    assert((bst->find(s5, compare))->val.field_1 == 5);
    assert((bst->find(s7, compare))->val.field_1 == 7);
    assert((bst->find(s9, compare))->val.field_1 == 9);
    assert((bst->find(s11, compare)) == nullptr);

    std::cout << bst->toString(toStringObj) << std::endl;
}