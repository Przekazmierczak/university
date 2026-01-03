#include <iostream>
#include <string>
#include <fstream>
#include <cassert>
#include <chrono>
#include <iomanip>

#include "DynamicArray.h"

const double EPS = 1e-9;

struct Point {
    double x, y;

public:
    Point() {}
    Point(double inputX, double inputY) : x(inputX), y(inputY) {}
};

struct GrahamScan {
    struct InnerPoint {
        double x, y;
        size_t index = 0;

    public:
        InnerPoint() {}
        InnerPoint(double inputX, double inputY, size_t inputIndex) : x(inputX), y(inputY),  index(inputIndex){}
        bool operator==(const Point& other) const {
            return fabs(x - other.x) < EPS && fabs(y - other.y) < EPS;
        }
    };

    DynamicArray<InnerPoint> points;
    DynamicArray<InnerPoint> hull;
    double sortTime = 0;
    double mainLoopTime = 0;

// private:
    InnerPoint startPoint;
    
public:
    GrahamScan(DynamicArray<Point> inputPoints) {
        for (size_t i = 0; i < inputPoints.size(); i++) {
            points.add(InnerPoint(inputPoints[i].x, inputPoints[i].y, i));
        }

        if (points.size() > 0) {
            startPoint = findStartPoint();
            
            auto t1 = std::chrono::high_resolution_clock::now();
            sort();
            auto t2 = std::chrono::high_resolution_clock::now();
            sortTime = std::chrono::duration<double>(t2 - t1).count();

            auto t3 = std::chrono::high_resolution_clock::now();
            findConvexHull();
            auto t4 = std::chrono::high_resolution_clock::now();
            mainLoopTime = std::chrono::duration<double>(t4 - t3).count();
        }
    }

    InnerPoint findStartPoint() {
        InnerPoint currSmallest = points[0];
        for (size_t i = 1; i < points.size(); i++) {
            if (points[i].y < currSmallest.y - EPS || (fabs(points[i].y - currSmallest.y) < EPS && points[i].x < currSmallest.x)) {
                currSmallest = points[i];
            }
        }
        return currSmallest;
    }

    double cross(InnerPoint A, InnerPoint B, InnerPoint C) {
        return ((B.x - A.x) * (C.y - A.y) - (B.y - A.y) * (C.x - A.x));
    }

    double distance(InnerPoint A, InnerPoint B) {
        double x = B.x - A.x;
        double y = B.y - A.y;
        return x * x + y * y;
    }

    bool compareSort(InnerPoint A, InnerPoint B) {
        double currCross = cross(startPoint, A, B);
        if (fabs(currCross) > EPS) return currCross > 0;
        return distance(A, startPoint) < distance(B, startPoint);
    }
    
    bool compareScan(InnerPoint A, InnerPoint B, InnerPoint C) {
        double currCross = cross(A, B, C);
        if (fabs(currCross) > EPS) return currCross > 0;
        return distance(B, A) > distance(C, A);
    }

    void sort() {
        if (points.size() > 1) {
            quickSort(0, points.size() - 1);
        }
    }

    void quickSort(long left, long right) {
        if (left >= right) {
            return;
        }

        long mid = left + (right - left) / 2;
        long newPivot = pickPivot(left, right, mid);

        pointsSwap(newPivot, right);

        long currLeft = left;
        long currRight = right - 1;

        double currCross;
        while (currLeft <= currRight) {
            while (currLeft <= currRight && compareSort(points[currLeft], points[right])) {
                currLeft++;
            }
            while (currLeft <= currRight && !compareSort(points[currRight], points[right])) {
                currRight--;
            }
            if (currLeft <= currRight) {
                pointsSwap(currLeft, currRight);
                currLeft++;
                currRight--;
            }
        }

        pointsSwap(currLeft, right);

        quickSort(left, currLeft - 1);
        quickSort(currLeft + 1, right);
    }

    long pickPivot(long left, long right, long mid) {
        long small;
        long big;

        if (!compareSort(points[left], points[right])) {
            small = right;
            big = left;
        } else {
            small = left;
            big = right;
        }

        if (!compareSort(points[mid], points[big])) {
            return big;
        } else if (!compareSort(points[mid], points[small])) {
            return small;
        }

        return mid;
    }

    void pointsSwap(long left, long right) {
        InnerPoint temp = points[right];
        points[right] = points[left];
        points[left] = temp;
    }

    void findConvexHull() {
        for(size_t i = 0; i < points.size(); i++) {
            while (hull.size() > 1 && !compareScan(hull[hull.size() - 2], hull[hull.size() - 1], points[i])) {
                hull.remove();
            }
            hull.add(points[i]);
        }

        if (hull.size() == 2 && fabs(distance(hull[0], hull[1])) < EPS) {
            hull.remove();
        }
    }

    void printResults() {
        std::cout << "Number of points: " << points.size() << std::endl;
        std::cout << "Number of points in convex hull: " << hull.size() << std::endl;
        std::cout << "Indexes: [";
        for (size_t i = 0; i < hull.size(); i++) {
            std::cout << hull[i].index;
            if (i < hull.size() - 1) std::cout<< ", ";
        }
        std::cout << "]" << std::endl;
        std::cout << "Sort time: " << std::to_string(sortTime) << std::endl;
        std::cout << "Main loop time: " << std::to_string(mainLoopTime) << std::endl;
    }
};

int getSize_t(std::string s, size_t& val) {
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

int getDouble(std::string s, double& val) {
    try {
        val = std::stod(s);
        return 0;
    }
    catch (const std::invalid_argument& e) {
        std::cout << "Invalid number: " << e.what() << std::endl;
    }
    return 1;
}

int getPoints(DynamicArray<Point>& points, std::string fileName) {
    std::ifstream file(fileName);

    if (!file.is_open()) {
        std::cerr << "Error opening file\n";
        return 1;
    }

    std::string line;

    std::getline(file, line);

    size_t size;
    if (getSize_t(line, size)) return 1;

    for (size_t i = 0; i < size; i++) {
        std::getline(file, line);

        size_t position = line.find(' ');

        double x;
        if (getDouble(line.substr(0, position), x)) return 1;
        double y;
        if (getDouble(line.substr(position + 1), y)) return 1;

        Point newNode = Point(x, y);

        points.add(newNode);
    }

    file.close();

    return 0;
}



void assertTests() {
    DynamicArray<Point> points;

    // points = {}
    // graham.points = {}
    // hull = {}
    GrahamScan graham0 = GrahamScan(points);
    assert(graham0.hull.size() == 0);
    
    points.add(Point(0, 0));
    GrahamScan graham1 = GrahamScan(points);
    // points = {[0, 0]}
    // graham.points = {[0, 0]}
    // hull = {[0, 0]}
    assert(graham1.points.size() == 1);
    assert(graham1.points[0] == Point(0, 0));
    assert(graham1.hull.size() == 1);
    assert(graham1.hull[0] == Point(0, 0));

    points.add(Point(0, 0));
    GrahamScan graham2 = GrahamScan(points);
    // points = {[0, 0], [0, 0]}
    // graham.points = {[0, 0], [0, 0]}
    // hull = {[0, 0]}
    assert(graham2.points.size() == 2);
    assert(graham2.points[0] == Point(0, 0));
    assert(graham2.points[1] == Point(0, 0));
    assert(graham2.hull.size() == 1);
    assert(graham2.hull[0] == Point(0, 0));

    points.add(Point(0, 2));
    GrahamScan graham3 = GrahamScan(points);
    // points = {[0, 0], [0, 0], [0, 2]}
    // graham.points = {[0, 0], [0, 0], [0, 2]}
    // hull = {[0, 0], [0, 2]}
    assert(graham3.points.size() == 3);
    assert(graham3.points[0] == Point(0, 0));
    assert(graham3.points[1] == Point(0, 0));
    assert(graham3.points[2] == Point(0, 2));
    assert(graham3.hull.size() == 2);
    assert(graham3.hull[0] == Point(0, 0));
    assert(graham3.hull[1] == Point(0, 2));

    points.add(Point(0, 3));
    GrahamScan graham4 = GrahamScan(points);
    // points = {[0, 0], [0, 0], [0, 2], [0, 3]}
    // graham.points = {[0, 0], [0, 0], [0, 2], [0, 3]}
    // hull = {[0, 0], [0, 3]}
    assert(graham4.points.size() == 4);
    assert(graham4.points[0] == Point(0, 0));
    assert(graham4.points[1] == Point(0, 0));
    assert(graham4.points[2] == Point(0, 2));
    assert(graham4.points[3] == Point(0, 3));
    assert(graham4.hull.size() == 2);
    assert(graham4.hull[0] == Point(0, 0));
    assert(graham4.hull[1] == Point(0, 3));

    points.add(Point(2, 0));
    GrahamScan graham5 = GrahamScan(points);
    // points = {[0, 0], [0, 0], [0, 2], [0, 3], [2, 0]}
    // graham.points = {[0, 0], [0, 0], [2, 0], [0, 2], [0, 3]}
    // hull = {[0, 0], [2, 0], [0, 3]}
    assert(graham5.points.size() == 5);
    assert(graham5.points[0] == Point(0, 0));
    assert(graham5.points[1] == Point(0, 0));
    assert(graham5.points[2] == Point(2, 0));
    assert(graham5.points[3] == Point(0, 2));
    assert(graham5.points[4] == Point(0, 3));
    assert(graham5.hull.size() == 3);
    assert(graham5.hull[0] == Point(0, 0));
    assert(graham5.hull[1] == Point(2, 0));
    assert(graham5.hull[2] == Point(0, 3));

    points.add(Point(2, 2));
    GrahamScan graham6 = GrahamScan(points);
    // points = {[0, 0], [0, 0], [0, 2], [0, 3], [2, 0], [2, 2]}
    // graham.points = {[0, 0], [0, 0], [2, 0], [2, 2], [0, 2], [0, 3]}
    // hull = {[0, 0], [2, 0], [2, 2], [0, 3]}
    assert(graham6.points.size() == 6);
    assert(graham6.points[0] == Point(0, 0));
    assert(graham6.points[1] == Point(0, 0));
    assert(graham6.points[2] == Point(2, 0));
    assert(graham6.points[3] == Point(2, 2));
    assert(graham6.points[4] == Point(0, 2));
    assert(graham6.points[5] == Point(0, 3));
    assert(graham6.hull.size() == 4);
    assert(graham6.hull[0] == Point(0, 0));
    assert(graham6.hull[1] == Point(2, 0));
    assert(graham6.hull[2] == Point(2, 2));
    assert(graham6.hull[3] == Point(0, 3));

    points.add(Point(3, 3));
    GrahamScan graham7 = GrahamScan(points);
    // points = {[0, 0], [0, 0], [0, 2], [0, 3], [2, 0], [2, 2], [3, 3]}
    // graham.points = {[0, 0], [0, 0], [2, 0], [2, 2], [3, 3], [0, 2], [0, 3]}
    // hull = {[0, 0], [2, 0], [3, 3], [0, 3]}
    assert(graham7.points.size() == 7);
    assert(graham7.points[0] == Point(0, 0));
    assert(graham7.points[1] == Point(0, 0));
    assert(graham7.points[2] == Point(2, 0));
    assert(graham7.points[3] == Point(2, 2));
    assert(graham7.points[4] == Point(3, 3));
    assert(graham7.points[5] == Point(0, 2));
    assert(graham7.points[6] == Point(0, 3));
    assert(graham7.hull.size() == 4);
    assert(graham7.hull[0] == Point(0, 0));
    assert(graham7.hull[1] == Point(2, 0));
    assert(graham7.hull[2] == Point(3, 3));
    assert(graham7.hull[3] == Point(0, 3));

    points.add(Point(1, 2));
    GrahamScan graham8 = GrahamScan(points);
    // points = {[0, 0], [0, 0], [0, 2], [0, 3], [2, 0], [2, 2], [3, 3], [1, 2]}
    // graham.points = {[0, 0], [0, 0], [2, 0], [2, 2], [3, 3], [1, 2], [0, 2], [0, 3]}
    // hull = {[0, 0], [2, 0], [3, 3], [0, 3]}
    assert(graham8.points.size() == 8);
    assert(graham8.points[0] == Point(0, 0));
    assert(graham8.points[1] == Point(0, 0));
    assert(graham8.points[2] == Point(2, 0));
    assert(graham8.points[3] == Point(2, 2));
    assert(graham8.points[4] == Point(3, 3));
    assert(graham8.points[5] == Point(1, 2));
    assert(graham8.points[6] == Point(0, 2));
    assert(graham8.points[7] == Point(0, 3));
    assert(graham8.hull.size() == 4);
    assert(graham8.hull[0] == Point(0, 0));
    assert(graham8.hull[1] == Point(2, 0));
    assert(graham8.hull[2] == Point(3, 3));
    assert(graham8.hull[3] == Point(0, 3));

    // Check for indexing
    assert(graham8.points[0].index == 0);
    assert(graham8.points[1].index == 1);
    assert(graham8.points[2].index == 4);
    assert(graham8.points[3].index == 5);
    assert(graham8.points[4].index == 6);
    assert(graham8.points[5].index == 7);
    assert(graham8.points[6].index == 2);
    assert(graham8.points[7].index == 3);

    assert(graham8.hull[0].index == 0);
    assert(graham8.hull[1].index == 4);
    assert(graham8.hull[2].index == 6);
    assert(graham8.hull[3].index == 3);
}


int main() {
    assertTests();

    std::string fileName[] = {"points1.txt", "points2.txt", "points3.txt", "points4.txt", "points5.txt"};
    for (size_t i = 0; i < 5; i++) {
        DynamicArray<Point> points;
        if (getPoints(points, fileName[i])) return 1;
        GrahamScan grahamScan = GrahamScan(points);
        grahamScan.printResults();
        std::cout << std::endl;
    }

    return 0;
}

