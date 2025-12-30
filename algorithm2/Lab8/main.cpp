#include <iostream>
#include <string>
#include <fstream>
// #include <cassert>
#include <chrono>
#include <iomanip>

#include "DynamicArray.h"

struct Point {
    double x, y;

    Point() {}
    Point(double inputX, double inputY) : x(inputX), y(inputY) {}
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

    DynamicArray<Point> shell;
    double sortTime, mainLoopTime;

// private:
    Point startPoint;
    const double EPS = 1e-9;
    
public:
    GrahamScan(DynamicArray<Point> inputPoints)
        : points(inputPoints)
    {
        startPoint = findStartPoint();
        sort();
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

    double cross(Point A, Point B, Point C) {
        return ((B.x - A.x) * (C.y - A.y) - (B.y - A.y) * (C.x - A.x));
    }

    double distance(Point A, Point B) {
        double x = B.x - A.x;
        double y = B.y - A.y;
        return x * x + y * y;
    }

    bool compare(Point A, Point B) {
        double currCross = cross(startPoint, A, B);
        if (fabs(currCross) > EPS) return currCross > 0;
        return distance(A, startPoint) < distance(B, startPoint);
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
            while (currLeft <= currRight && compare(points[currLeft], points[right])) {
                currLeft++;
            }
            while (currLeft <= currRight && !compare(points[currRight], points[right])) {
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

        if (!compare(points[left], points[right])) {
            small = right;
            big = left;
        } else {
            small = left;
            big = right;
        }

        if (!compare(points[mid], points[big])) {
            return big;
        } else if (!compare(points[mid], points[small])) {
            return small;
        }

        return mid;
    }

    void pointsSwap(long left, long right) {
        Point temp = points[right];
        points[right] = points[left];
        points[left] = temp;
    }
};


int main() {
    std::string fileName = "points1.txt";
    DynamicArray<Point> points;
    if (getPoints(points, fileName)) return 1;

    // for (size_t i = 0; i < points.size(); i++) {
    //     std::cout << std::setprecision(9) << "x: " << points[i].x << ", y: " << points[i].y << std::endl;
    // }

    GrahamScan grahamScan = GrahamScan(points);

    for (size_t i = 0; i < grahamScan.points.size(); i++) {
        std::cout << std::setprecision(9) << "x: " << grahamScan.points[i].x << ", y: " << grahamScan.points[i].y << std::endl;
    }

    std::cout << "x = " << grahamScan.startPoint.x << ", y = " << grahamScan.startPoint.y << std::endl;

    Point point1 = Point(0.450785905, 0.057055898);
    Point point2 = Point(0.988508463, 0.119079731);
    Point point3 = Point(0.450785905, 0.057055898);

    std::cout << grahamScan.cross(point1, point2, point3) << std::endl;

    return 0;
}
