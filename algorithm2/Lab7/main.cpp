#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

// #include <cassert>
// #include <ctime>
// #include <cmath>
// #include <time.h>
// #include <functional>

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
    Edge(size_t inputNode1, size_t inputNode2, float inputWeight) : node1(inputNode1), node2(inputNode2), weight(inputWeight) {}
};

struct Graf {
    size_t size;
    size_t edgesSize;

    DynamicArray<Node> nodes;
    DynamicArray<Edge> edges;

    void sort() { quickSort(0, edgesSize - 1); }

    private:
    void quickSort(long left, long right);
    long pickPivot(long left, long right, long mid);
    void edgesSwap(long left, long right);
};

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
        if (getSize_t(line.substr(position + 1, position2), node2)) return 1;
        float weight;
        if (getFloat(line.substr(position2 + 1), weight)) return 1;

        Edge newEdge = Edge(node1, node2, weight);

        graf.edges.add(newEdge);
    }

    file.close();

    return 0;
}

int main() {
    std::string fileName = "g1.txt";
    Graf graf;

    if (createGraf(graf, fileName)) return 1;

    graf.sort();

    for (size_t i = 0; i < graf.size; i++) {
        std::cout << "x: " << graf.nodes[i].x << ", y: " << graf.nodes[i].y << std::endl;
    }

    for (size_t i = 0; i < graf.edgesSize; i++) {
        std::cout << "node1: " << graf.edges[i].node1 << ", node2: " << graf.edges[i].node2 << ", weight: "<< graf.edges[i].weight << std::endl;
    }

    return 0;
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