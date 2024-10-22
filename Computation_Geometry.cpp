#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <float.h>
#include <fstream>
#include <ctime>

using namespace std;

struct Point {
    int id;
    float x, y;
};

// 计算两点之间的距离
double distance(const Point& p1, const Point& p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

pair<Point, Point> solve_brute(vector<Point>& points) {//暴力搜索，用于时间复杂度比较
    pair<Point, Point> bestPair;
    double minDist = DBL_MAX;
    for (size_t i = 0; i < points.size(); ++i) {
        for (size_t j = i + 1; j < points.size(); ++j) {
            double d = distance(points[i], points[j]);
            if (d < minDist) {
                minDist = d;
                bestPair = {points[i], points[j]};
            }
        }
    }
    return bestPair;
}

// 暴力法寻找最近点对
double BruteForce(vector<Point>& points, int left, int right, pair<Point, Point>& bestPair) {
    double minDist = DBL_MAX;
    for (int i = left; i < right; ++i) {
        for (int j = i + 1; j < right; ++j) {
            double d = distance(points[i], points[j]);
            if (d < minDist) {
                minDist = d;
                bestPair = {points[i], points[j]};
            }
        }
    }
    return minDist;
}

bool compareX(const Point& p1, const Point& p2) {//sort调用以下函数对point数组排序
    return p1.x < p2.x;
}

bool compareY(const Point& p1, const Point& p2) {
    return p1.y < p2.y;
}

// 在跨越分割线的区域中寻找最近点对
double Split(vector<Point>& points, int left, int right, int mid, double delta, pair<Point, Point>& bestPair) {
    vector<Point> strip;
    Point midpoint = points[mid];
    for (int i = left; i < right; ++i) {
        if (abs(points[i].x - midpoint.x) < delta) {
            strip.push_back(points[i]);
        }
    }

    sort(strip.begin(), strip.end(), compareY);

    double minDist = delta;
    for (size_t i = 0; i < strip.size(); ++i) {
        for (size_t j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) < minDist; ++j) {
            double d = distance(strip[i], strip[j]);
            if (d < minDist) {
                minDist = d;
                bestPair = {strip[i], strip[j]};
            }
        }
    }
    return minDist;
}

// 分治法寻找最近点对
double PairtoRec(vector<Point>& points, int left, int right, pair<Point, Point>& bestPair) {
    if (right - left <= 3) {
        return BruteForce(points, left, right, bestPair);//当点数量小于三的时候，采取暴力寻找
    }
    //开始分治
    int mid = left + (right - left) / 2;
    pair<Point, Point> leftPair, rightPair;
    double leftDistance = PairtoRec(points, left, mid, leftPair);
    double rightDistance = PairtoRec(points, mid, right, rightPair);//左右的最小距离

    double delta = (leftDistance < rightDistance)? leftDistance : rightDistance;//找到德尔塔
    bestPair = (leftDistance < rightDistance) ? leftPair : rightPair;

    pair<Point, Point> splitPair;
    double splitDistance = Split(points, left, right, mid, delta, splitPair);

    if (splitDistance < delta) {
        bestPair = splitPair;
        return splitDistance;
    }
    return delta;
}

// 主函数，调用分治法寻找最近点对
pair<Point, Point> closestPair(vector<Point>& points) {
    sort(points.begin(), points.end(), compareX);
    pair<Point, Point> NearestPair;
    PairtoRec(points, 0, points.size(), NearestPair);
    return NearestPair;
}

int main() {
    system("chcp 65001");
    ifstream file("");
    if (!file.is_open()) {
        cerr << "Can't open the file." << endl;
        system("pause");
        return 1;
    }

    int pointSize = 10000;
    vector<Point> points(pointSize);
    vector<Point> points1(pointSize);
    for (int i = 0; i < pointSize; ++i) {
        file >> points[i].id >> points[i].x >> points[i].y;
    }
    points1 = points;
    auto start1 = clock();
    pair<Point, Point> result = closestPair(points);
    auto end1 = clock();
    cout << "Duration: " << end1 - start1 << " seconds" << endl;
    cout << "最近点对: " << result.first.id << "(" << result.first.x << ", " << result.first.y << ") 和 " << result.second.id << "("
         << result.second.x << ", " << result.second.y << ")" << endl;
    cout << "距离: " << distance(result.first, result.second) << endl;

    auto start2 = clock();
    pair<Point, Point> result1 = solve_brute(points1);
    auto end2 = clock();
    cout << "Duration: " << end2 - start2 << " seconds" << endl;
    cout << "最近点对: " << result1.first.id << "(" << result1.first.x << ", " << result1.first.y << ") 和 " << result1.second.id << "("
         << result1.second.x << ", " << result1.second.y << ")" << endl;
    cout << "距离: " << distance(result1.first, result1.second) << endl;
    system("pause");
    return 0;
}