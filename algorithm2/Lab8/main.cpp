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
    size_t index = 0;

public:
    Point() {}
    Point(double inputX, double inputY) : x(inputX), y(inputY) {}
    Point(double inputX, double inputY, size_t inputIndex) : x(inputX), y(inputY),  index(inputIndex){}
    bool operator==(const Point& other) const {
        return fabs(x - other.x) < EPS && fabs(y - other.y) < EPS;
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

struct GrahamScan {
    DynamicArray<Point> points;

    DynamicArray<Point> hull;
    double sortTime = 0;
    double mainLoopTime = 0;

// private:
    Point startPoint;
    
public:
    GrahamScan(DynamicArray<Point> inputPoints)
        : points(inputPoints)
    {
        if (points.size() > 0) {
            startPoint = findStartPoint();
            saveIndexes();
            sort();
            findConvexHull();
        }
    }

    Point findStartPoint() {
        Point currSmallest = points[0];
        for (size_t i = 1; i < points.size(); i++) {
            if (points[i].y < currSmallest.y - EPS || (fabs(points[i].y - currSmallest.y) < EPS && points[i].x < currSmallest.x)) {
                currSmallest = points[i];
            }
        }
        return currSmallest;
    }

    void saveIndexes() {
        for (size_t i = 0; i < points.size(); i ++) {
            points[i].index = i;
        }
    }

    double cross(Point A, Point B, Point C) {
        return ((B.x - A.x) * (C.y - A.y) - (B.y - A.y) * (C.x - A.x));
    }

    double distance(Point A, Point B) {
        double x = B.x - A.x;
        double y = B.y - A.y;
        return x * x + y * y;
    }

    bool compareSort(Point A, Point B) {
        double currCross = cross(startPoint, A, B);
        if (fabs(currCross) > EPS) return currCross > 0;
        return distance(A, startPoint) < distance(B, startPoint);
    }
    
    bool compareScan(Point A, Point B, Point C) {
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
        Point temp = points[right];
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
};

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

    std::string fileName = "points1.txt";
    DynamicArray<Point> points;
    if (getPoints(points, fileName)) return 1;

    // // for (size_t i = 0; i < points.size(); i++) {
    // //     std::cout << std::setprecision(9) << "x: " << points[i].x << ", y: " << points[i].y << std::endl;
    // // }

    // GrahamScan grahamScan = GrahamScan(points);

    // for (size_t i = 0; i < grahamScan.points.size(); i++) {
    //     std::cout << std::setprecision(9) << "x: " << grahamScan.points[i].x << ", y: " << grahamScan.points[i].y << std::endl;
    // }

    // // std::cout << "x = " << grahamScan.startPoint.x << ", y = " << grahamScan.startPoint.y << std::endl;

    // // Point point1 = Point(0.450785905, 0.057055898);
    // // Point point2 = Point(0.988508463, 0.119079731);
    // // Point point3 = Point(0.450785905, 0.057055898);

    // // std::cout << grahamScan.cross(point1, point2, point3) << std::endl;

    // for (size_t i = 0; i < grahamScan.hull.size(); i++) {
    //     std::cout << i + 1 << "- x :" << grahamScan.hull[i].x << ", y: " << grahamScan.hull[i].y << std::endl;
    // }

    DynamicArray<Point> points2;
    points2.add(Point(0, 2));
    // points2.add(Point(0, 2));
    // points2.add(Point(0, 3));
    // points2.add(Point(0, 2));
    // points2.add(Point(2, 0));
    // points2.add(Point(2, 2));
    // points2.add(Point(3, 3));
    // points2.add(Point(3, 3));
    // points2.add(Point(3, 0));
    // points2.add(Point(0, 0));

    
    GrahamScan grahamScan2 = GrahamScan(points2);
    for (size_t i = 0; i < points2.size(); i++) {
        std::cout << std::setprecision(9) << "x: " << points2[i].x << ", y: " << points2[i].y << std::endl;
    }
    for (size_t i = 0; i < grahamScan2.points.size(); i++) {
        std::cout << std::setprecision(9) << "x: " << grahamScan2.points[i].x << ", y: " << grahamScan2.points[i].y << std::endl;
    }

    std::cout << "start - x:  " << grahamScan2.startPoint.x << ", y: " << grahamScan2.startPoint.y << std::endl;
    for (size_t i = 0; i < grahamScan2.hull.size(); i++) {
        std::cout << i + 1 << "- x :" << grahamScan2.hull[i].x << ", y: " << grahamScan2.hull[i].y << std::endl;
    }

    return 0;
}
