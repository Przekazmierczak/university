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

    int treeSize;
    bool treeHeightUpdated = true;
    int treeHeight = -1;

    BST() { root = nullptr; }
    ~BST() {
        // clear();
    }

    int size() const { return treeSize; }

    int add(T value, int (*cmp)(const T&, const T&)) {
        Node* newNode = createNewNode(value);
        if (newNode == nullptr) return FAIL;

        if (root == nullptr) {
            root = newNode;
        } else {
            Node* leaf = findLeaf(value, cmp);

            if (cmp(value, leaf->val) > 0) {
                leaf->right = newNode;
            } else {
                leaf->left = newNode;
            }
        }
        return SUCCESS;
    };

    std::string toString(std::string (*toStringObj)(const T&)) {
        // Every level of tree double the size + 1: 2^(treeHeight + 1) - 1
        int rows = (1 << (treeHeight + 1)) - 1;
        int cols = treeHeight + 2;

        std::vector<std::vector<std::string>> treeGraph(cols, std::vector<std::string>(rows, "      "));

        for (int i = 0; i < rows; i++) {
            treeGraph[cols - 1][i] = "\n";
        }
        addToGraph(root, 0, rows / 2, rows / 2, red("Root--"), treeGraph, toStringObj);

        std::string result;
        std::string row;
        bool ifNode;

        for (int i = 0; i < rows; i++) {
            row = "";
            ifNode = false;
            for (int j = 0; j < cols; j++) {
                if (treeGraph[j][i].size() > 15) ifNode = true;
                row += treeGraph[j][i];
            }
            if (ifNode) result += row;
        }

        return result;
    }

    void addToGraph(Node* curr, int col, int row, int size, std::string prefix, std::vector<std::vector<std::string>> &treeGraph, std::string (*toStringObj)(const T&)) {
        int newSize = size / 2;

        treeGraph[col][row] = prefix + green("(" + toStringObj(curr->val) + ")");

        if (curr->right) {
            for (int i = 1; i < newSize + 1; i++) {
                treeGraph[col + 1][row - i] = yellow("|     ");
            }
            addToGraph(curr->right, col + 1, row - (newSize + 1), newSize, yellow("R-----"), treeGraph, toStringObj);
        };

        if (curr->left) {
            for (int i = 1; i < newSize + 1; i++) {
                treeGraph[col + 1][row + i] = blue("|     ");
            }
            addToGraph(curr->left, col + 1, row + (newSize + 1), newSize, blue("L-----"), treeGraph, toStringObj);
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

private:    

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

        if (treeHeightUpdated && treeHeight < depth) treeHeight = depth; 
        return prev;
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
    BST <SomeObject>* da = new BST <SomeObject>();

    SomeObject s0 = { 0, 'a' };
    SomeObject s1 = { 1, 'b' };
    SomeObject s2 = { 2, 'c' };
    SomeObject s3 = { 3, 'd' };
    SomeObject s4 = { 4, 'e' };
    SomeObject s5 = { 5, 'f' };
    SomeObject s6 = { 6, 'g' };

    std::vector<SomeObject> tests = {s0, s1, s2, s3, s4, s5, s6};
    
    for (int i = 0; i < 1000; i++) {
        da->add(createRandom(), compare);
    }


    // std::cout << da->root->val.field_1 << std::endl;
    // std::cout << da->root->right->val.field_1 << std::endl;
    // std::cout << da->root->right->left->val.field_1 << std::endl;
    // std::cout << da->treeHeight << std::endl;
    std::cout << da->toString(toStringObj) << std::endl;

    // // Small correctness check
    // assertTests(da);

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

    delete da;
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

template <typename Func>
std::string measureMethod(Func func, BST <SomeObject>* da, int elements, bool requiresFill, int width, bool multiRun) {
    if (requiresFill) fillVector(elements, dv);

    clock_t t1 = clock();
    if (multiRun) {
        for (int i = 0; i < elements; i++) {
            func();
        }
    } else {
        func();
    }
    clock_t t2 = clock();

    da->clear();

    double currTime = (t2 - t1) / (double)CLOCKS_PER_SEC;
    std:: string strTime = std::to_string(currTime);
    strTime.erase(strTime.size() - 3);
    return getColumn(strTime + 's', width, ' ', '|');
}

// void assertTests(Dynamic_array <SomeObject>* da) {
//     SomeObject s0 = { 0, 'a' };
//     SomeObject s1 = { 1, 'b' };
//     SomeObject s2 = { 2, 'c' };
//     SomeObject s3 = { 3, 'd' };
//     SomeObject s4 = { 4, 'e' };

//     auto outOfRangeTest = [&da](int index) {
//         bool outOfRange = false;
//         try {
//             (*da)[index];
//         } catch (std::out_of_range&) {
//             outOfRange = true;
//         }
//         assert(outOfRange == true);
//     };

//     // ---- Test add() methods ----
//     da->add(s0);
//     // Expected: [0]
//     assert((*da)[0].field_1 == 0);
//     assert(da->size() == 1);
//     assert(da->checkMaxSize() == 1);
//     outOfRangeTest(1);

//     da->add(s2);
//     // Expected: [0, 2]
//     assert((*da)[0].field_1 == 0);
//     assert((*da)[1].field_1 == 2);
//     assert(da->size() == 2);
//     assert(da->checkMaxSize() == 2);
//     outOfRangeTest(2);

//     da->add(s1);
//     // Expected: [0, 2, 1]
//     assert((*da)[0].field_1 == 0);
//     assert((*da)[1].field_1 == 2);
//     assert((*da)[2].field_1 == 1);
//     assert(da->size() == 3);
//     assert(da->checkMaxSize() == 4);
//     outOfRangeTest(3);

//     da->add(s4);
//     // Expected: [0, 2, 1, 4]
//     assert((*da)[0].field_1 == 0);
//     assert((*da)[1].field_1 == 2);
//     assert((*da)[2].field_1 == 1);
//     assert((*da)[3].field_1 == 4);
//     assert(da->size() == 4);
//     assert(da->checkMaxSize() == 4);
//     outOfRangeTest(4);

//     da->add(s3);
//     // Expected: [0, 2, 1, 4, 3]
//     assert((*da)[0].field_1 == 0);
//     assert((*da)[1].field_1 == 2);
//     assert((*da)[2].field_1 == 1);
//     assert((*da)[3].field_1 == 4);
//     assert((*da)[4].field_1 == 3);
//     assert(da->size() == 5);
//     assert(da->checkMaxSize() == 8);
//     outOfRangeTest(5);

//     // ---- Test set() methods ----
//     da->set(1, s3);
//     // Expected: [0, 3, 1, 4, 3]
//     assert((*da)[0].field_1 == 0);
//     assert((*da)[1].field_1 == 3);
//     assert((*da)[2].field_1 == 1);
//     assert((*da)[3].field_1 == 4);
//     assert((*da)[4].field_1 == 3);
//     assert(da->size() == 5);
//     assert(da->checkMaxSize() == 8);
//     outOfRangeTest(5);

//     da->set(4, s2);
//     // Expected: [0, 3, 1, 4, 2]
//     assert((*da)[0].field_1 == 0);
//     assert((*da)[1].field_1 == 3);
//     assert((*da)[2].field_1 == 1);
//     assert((*da)[3].field_1 == 4);
//     assert((*da)[4].field_1 == 2);
//     assert(da->size() == 5);
//     assert(da->checkMaxSize() == 8);
//     outOfRangeTest(5);

//     // ---- Test sort() methods ----
//     da->sort(compare);
//     // Expected: [0, 1, 2, 3, 4]
//     assert((*da)[0].field_1 == 0);
//     assert((*da)[1].field_1 == 1);
//     assert((*da)[2].field_1 == 2);
//     assert((*da)[3].field_1 == 3);
//     assert((*da)[4].field_1 == 4);
//     assert(da->size() == 5);
//     assert(da->checkMaxSize() == 8);
//     outOfRangeTest(5);

//     // ---- Test toString() method ----
//     assert(da->toString(toStringObj) == "[(0, a);(1, b);(2, c);(3, d);(4, e)]");

//     // ---- Test clear() methods ----
//     da->clear();
//     assert(da->size() == 0);
//     assert(da->checkMaxSize() == 1);
//     outOfRangeTest(0);
//     outOfRangeTest(-1);
// }