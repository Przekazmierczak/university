#include <iostream>
#include <string>
#include <fstream>
// #include <cassert>
#include <chrono>
#include <iomanip>

#include "DynamicArray.h"

struct Node {
    float x;
    float y;

    Node() {}
    Node(float inputX, float inputY) : x(inputX), y(inputY) {}
};

struct Edge {
    size_t node1;
    size_t node2;
    float weight;

    Edge() {}
    Edge(size_t inputNode1, size_t inputNode2, float inputWeight)
        : node1(inputNode1), node2(inputNode2), weight(inputWeight) {}
};

struct Graf {
    size_t size;
    size_t edgesSize;

    DynamicArray<Node> nodes;
    DynamicArray<Edge> edges;

    Graf() = default;

    Graf(const Graf& other)
        : size(other.size),
          edgesSize(other.edgesSize),
          nodes(other.nodes),
          edges(other.edges) {}

    Graf& operator=(const Graf& other) {
        if (this != &other) {
            size = other.size;
            edgesSize = other.edgesSize;
            nodes = other.nodes;
            edges = other.edges;
        }
        return *this;
    }


    void sort();

    private:
    void quickSort(long left, long right);
    long pickPivot(long left, long right, long mid);
    void edgesSwap(long left, long right);
};

struct UnionFind {
    size_t size;
    long findCounter = 0;

    DynamicArray<size_t> parents;
    DynamicArray<size_t> ranks;

    UnionFind(size_t inputSize);

    void defaultUnion(size_t parent1, size_t parent2);
    void unionByRank(size_t parent1, size_t parent2);
    size_t find(size_t index);
    size_t findWithCompression(size_t index);
};

struct Kruskal {
    Graf graf;
    UnionFind unionFind;

    bool unionByRank;
    bool pathCompression;

    DynamicArray<Edge> MST;
    double MSTSum = 0;
    double sortTime;
    double mainLoopTime;

    Kruskal(Graf inputGraf, bool inputUnionByRank, bool inputPathCompression);
    void printHeadLine();
    void printStats();
    std::string getColumn(std::string value, int width, char filling, char last);
    void printSeparator(int elements,int width);
};

int getSize_t (std::string s, size_t& val);
int getFloat (std::string s, float& val);
int createGraf(Graf& graf, std::string fileName);

int main() {
    std::string fileName[3] = {"g1.txt", "g2.txt", "g3.txt"};
    bool flagCombinations[4][2] = {{false, false}, {true, false}, {false, true}, {true, true}};

    for (size_t i = 0; i < 3; i++) {
        Graf graf;
        if (createGraf(graf, fileName[i])) return 1;
        for (size_t j = 0; j < 4; j++) {
            Kruskal kruskalFF(graf, flagCombinations[j][0], flagCombinations[j][1]);
            if (j == 0) kruskalFF.printHeadLine();
            kruskalFF.printStats();
        }
        std::cout << std::endl;
    }
    
    return 0;
}

void Graf::sort() {
    if (edgesSize > 1) {
        quickSort(0, edgesSize - 1);
    }
}

void Graf::quickSort(long left, long right) {
    if (left >= right) {
        return;
    }

    long mid = left + (right - left) / 2;
    long newPivot = pickPivot(left, right, mid);

    if (newPivot != right) {
        edgesSwap(newPivot, right);
    }

    float pivotWeight = edges[right].weight;
    long currLeft = left;
    long currRight = right - 1;

    while (currLeft <= currRight) {
        if (edges[currLeft].weight < pivotWeight) {
            currLeft++;
            continue;
        }
        if (edges[currRight].weight > pivotWeight) {
            currRight--;
            continue;
        }
        edgesSwap(currLeft, currRight);
        currLeft++;
        currRight--;
    }

    edgesSwap(currLeft, right);

    quickSort(left, currLeft - 1);
    quickSort(currLeft + 1, right);
}

long Graf::pickPivot(long left, long right, long mid) {
    long small;
    long big;

    if (edges[left].weight > edges[right].weight) {
        small = right;
        big = left;
    } else {
        small = left;
        big = right;
    }

    if (edges[mid].weight > edges[big].weight) {
        return big;
    } else if (edges[mid].weight < edges[small].weight) {
        return small;
    }

    return mid;
}

void Graf::edgesSwap(long left, long right) {
    Edge temp = edges[right];
    edges[right] = edges[left];
    edges[left] = temp;
}

UnionFind::UnionFind(size_t inputSize)
    : size(inputSize), parents(inputSize), ranks(inputSize) {
        for (int i = 0; i < inputSize; i++) {
            parents[i] = i;
            ranks[i] = 0;
        }
    }

void UnionFind::defaultUnion(size_t parent1, size_t parent2) {
    parents[parent1] = parent2;
}

void UnionFind::unionByRank(size_t parent1, size_t parent2) {
    if (ranks[parent1] > ranks[parent2]) {
        parents[parent2] = parent1;
    } else if (ranks[parent1] < ranks[parent2]) {
        parents[parent1] = parent2;
    } else {
        parents[parent1] = parent2;
        ranks[parent2]++;
    }
}

size_t UnionFind::find(size_t index) {
    while (parents[index] != index) {
        index = parents[index];
        findCounter++;
    }

    findCounter++;

    return index;
}

size_t UnionFind::findWithCompression(size_t index) {
    size_t root = index;

    while (parents[root] != root) {
        root = parents[root];
        findCounter++;
    }

    while (parents[index] != index) {
        size_t prevIndex = index;
        index = parents[index];
        parents[prevIndex] = root;
    }

    findCounter++;

    return root;
}


Kruskal::Kruskal(Graf inputGraf, bool inputUnionByRank, bool inputPathCompression)
    : graf(inputGraf),
      unionFind(inputGraf.size),
      unionByRank(inputUnionByRank),
      pathCompression(inputPathCompression)
{
    auto t1 = std::chrono::high_resolution_clock::now();
    graf.sort();
    auto t2 = std::chrono::high_resolution_clock::now();

    sortTime = std::chrono::duration<double>(t2 - t1).count();

    auto t3 = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < graf.edgesSize; i++) {
        size_t parent1;
        size_t parent2;
        
        if (pathCompression) {
            parent1 = unionFind.findWithCompression(graf.edges[i].node1);
            parent2 = unionFind.findWithCompression(graf.edges[i].node2);
        } else {
            parent1 = unionFind.find(graf.edges[i].node1);
            parent2 = unionFind.find(graf.edges[i].node2);
        }
        
        if (parent1 != parent2) {
            MST.add(graf.edges[i]);
            MSTSum += graf.edges[i].weight;
            if (unionByRank) {
                unionFind.unionByRank(parent1, parent2);
            } else {
                unionFind.defaultUnion(parent1, parent2);
            }
        }

        if (MST.size() == graf.size - 1) break;
    }
    auto t4 = std::chrono::high_resolution_clock::now();

    mainLoopTime = std::chrono::duration<double>(t4 - t3).count();
}

void Kruskal::printHeadLine() {
    const int WIDTH = 17;
    const int ROWS = 8;

    printSeparator(ROWS, WIDTH);
    std::string rowsNames[ROWS] = {"Nodes", "Edges", "Union by Rank", "Path compression", "Sum of MST", "Number of find", "Sort Time", "Main loop time"};
    std::cout << "|";
    for (size_t i = 0; i < 8; i++) {
        std::cout << getColumn(rowsNames[i], WIDTH, ' ', '|') << std::flush;
    }; 
    std::cout << std::endl;
    printSeparator(ROWS, WIDTH);
}

void Kruskal::printStats() {
    const int WIDTH = 17;
    const int ROWS = 8;
    std::string unionByRankString = (unionByRank) ? "True" : "False";
    std::string pathCompressionString = (pathCompression) ? "True" : "False";

    std::cout << "|";
    std::cout << getColumn(std::to_string(graf.size), WIDTH, ' ', '|');
    std::cout << getColumn(std::to_string(graf.edgesSize), WIDTH, ' ', '|');
    std::cout << getColumn(unionByRankString, WIDTH, ' ', '|');
    std::cout << getColumn(pathCompressionString, WIDTH, ' ', '|');
    std::cout << getColumn(std::to_string(MSTSum), WIDTH, ' ', '|');
    std::cout << getColumn(std::to_string(unionFind.findCounter), WIDTH, ' ', '|');
    std::cout << getColumn(std::to_string(sortTime), WIDTH, ' ', '|');
    std::cout << getColumn(std::to_string(mainLoopTime), WIDTH, ' ', '|');
    std::cout << std::endl;
    printSeparator(ROWS, WIDTH);
}

std::string Kruskal::getColumn(std::string value, int width, char filling, char last) {
    if (value.size() < width) {
        return std::string(width - value.size(), filling) + value + last;
    }
    return value;
}

void Kruskal::printSeparator(int elements,int width) {
    std::cout << "+";
    for (int i = 0; i < elements; i++) {
        std::cout << getColumn("", width, '-', '+');
    }
    std::cout << std::endl;
}

int getSize_t (std::string s, size_t& val) {
    try {
        val = std::stoul(s);
        return 0;
    }
    catch (const std::invalid_argument& e) {
        std::cout << "Invalid number: " << e.what() << std::endl;
    }
    catch (const std::out_of_range& e) {
        std::cout << "Number out of range: " << e.what() << std::endl;
    }
    return 1;
}

int getFloat (std::string s, float& val) {
    try {
        val = std::stof(s);
        return 0;
    }
    catch (const std::invalid_argument& e) {
        std::cout << "Invalid number: " << e.what() << std::endl;
    }
    return 1;
}

int createGraf(Graf& graf, std::string fileName) {
    std::ifstream file(fileName);

    if (!file.is_open()) {
        std::cerr << "Error opening file\n";
        return 1;
    }

    std::string line;

    std::getline(file, line);

    size_t size;
    if (getSize_t(line, size)) return 1;

    graf.size = size;

    for (size_t i = 0; i < size; i++) {
        std::getline(file, line);

        size_t position = line.find(' ');

        float x;
        if (getFloat(line.substr(0, position), x)) return 1;
        float y;
        if (getFloat(line.substr(position + 1), y)) return 1;

        Node newNode = Node(x, y);

        graf.nodes.add(newNode);
    }

    std::getline(file, line);

    if (getSize_t(line, size)) return 1;

    graf.edgesSize = size;

    for (size_t i = 0; i < size; i++) {
        std::getline(file, line);

        size_t position = line.find(' ');
        size_t position2 = line.find(' ', position + 1);
        
        size_t node1;
        if (getSize_t(line.substr(0, position), node1)) return 1;
        size_t node2;
        if (getSize_t(line.substr(position + 1, position2 - position - 1), node2)) return 1;
        float weight;
        if (getFloat(line.substr(position2 + 1), weight)) return 1;

        Edge newEdge = Edge(node1, node2, weight);

        graf.edges.add(newEdge);
    }

    file.close();

    return 0;
}