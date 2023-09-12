#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
using namespace std;

// Class to represent a point
class Point {
public:
    double x, y;
    Point(double x, double y) : x(x), y(y) {}
};

// Class to read data from a text file
class DataReader {
private:
    vector<Point> points;
public:
    void readFromFile(const char* filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Error: Could not open file." << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            if (line == "PTS") {
                readPoints(file);
            } else if (line == "CON") {
               
            }
        }
        file.close();
    }

    void readPoints(ifstream& file) {
        points.clear();
        while (true) {
            double x, y;
            if (!(file >> x >> y)) break;
            points.push_back(Point(x, y));
        }
    }

    const vector<Point>& getPoints() const {
        return points;
    }
};

// Function to calculate the area of a shape
double calculateArea(const vector<Point>& shape) {
    int n = shape.size();
    if (n < 3) return 0.0; 

    double area = 0.0;
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        area += (shape[i].x * shape[j].y - shape[j].x * shape[i].y);
    }
    return abs(area) / 2.0;
}

// Function to find the point to remove for the largest area
int findPointToRemove(const vector<Point>& points) {
    int n = points.size();
    if (n < 3) return -1; // Cannot remove a point

    double maxArea = 0.0;
    int pointToRemove = -1;

    for (int i = 0; i < n; i++) {
        vector<Point> tempPoints = points;
        tempPoints.erase(tempPoints.begin() + i);
        double area = calculateArea(tempPoints);

        if (area > maxArea) {
            maxArea = area;
            pointToRemove = i;
        }
    }
    return pointToRemove;
}

// Function to find the center of a shape
Point findCenterOfShape(const vector<Point>& shape) {
    int n = shape.size();
    double cx = 0.0, cy = 0.0;
    double A = 0.0;

    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        double factor = (shape[i].x * shape[j].y - shape[j].x * shape[i].y);
        cx += (shape[i].x + shape[j].x) * factor;
        cy += (shape[i].y + shape[j].y) * factor;
        A += factor;
    }

    A /= 2.0;
    cx /= (6 * A);
    cy /= (6 * A);

    return Point(cx, cy);
}

int main() {
    DataReader reader;
    reader.readFromFile("data.txt");

    const vector<Point>& points = reader.getPoints();

    // Calculate the largest area of the shape formed using the given set of points
    double largestArea = calculateArea(points);
    cout << "Largest Area: " << largestArea << endl;

    // Which one point needs to be removed so that the shape formed from the remaining data is largest
    int pointToRemove = findPointToRemove(points);
    if (pointToRemove != -1) {
        cout << "Point to Remove: " << points[pointToRemove].x << " " << points[pointToRemove].y << endl;
    } else {
        cout << "No point can be removed to form a larger shape." << endl;
    }

    // Calculate a point which is equidistant from each point of the shape
    Point centerOfShape = findCenterOfShape(points);
    cout << "Center of Shape: " << centerOfShape.x << " " << centerOfShape.y << endl;

    return 0;
}