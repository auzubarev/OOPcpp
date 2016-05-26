#pragma once
#include "Base.h"
#include "Container.h"
#include <string>

const double PI = 3.141592653589793238463;

class Shapes : public virtual Printable {
public:
	Shapes() {
		count++;
	}
	Shapes(const Shapes & object) {
		count++;
	}
	virtual double area() const = 0;
	virtual double perimeter() const = 0;
	virtual std::string type() const = 0;
	static int getCount() {
		return count;
	}
	std::string print() const {
		return "Type: " + type() + ";\n" +
			   "Area: " + str(area()) + ";\n" +
			   "Perimeter: " + str(perimeter()) + ";\n";
	}
	static void resetCount() {
		count = 0;
	}
	virtual ~Shapes() {
		count--;
	}
private:
	static int count;
};

class Point : public Shapes, public Named{
public:
	Point(const double _x, const double _y, const std::string name = "NO_NAME")
		: Named(name), Shapes(), x(_x), y(_y) {}
	std::string type() const {
		return "Point";
	}
	double area() const {
		return 0;
	}
	double perimeter() const {
		return 0;
	}
	std::string print() const {
		return Named::print() + Shapes::print() +
			"X: " + str(x) + "; Y: " + str(y) + ";\n\n";
	}
	double getX() const {
		return x;
	}
	double getY() const {
		return y;
	}
	double distance (const Point & other) const{
		return sqrt(pow(other.getX() - x, 2) + pow(other.getY() - y, 2));
	}
	bool equ (const Point & other) const {
		return (other.getX() == x) && (other.getY() == y);
	}
	double rotate(const Point & p1, const Point & p2) const{
		return (p1.getX() - x)*(p2.getY() - p1.getY()) - (p1.getY() - y)*(p2.getX() - p1.getX());
	}
private:
	const double x, y;
};

class Circle : public Shapes, public Named{
public:
	Circle(const double x, const double y, const double _radius, const std::string name = "NO_NAME")
		: Named(name), Shapes(), radius(_radius), centre (Point(x, y)){};
	std::string type() const {
		return "Circle";
	}
	double area() const {
		return PI*radius*radius;
	}
	double perimeter() const {
		return 2 * PI*radius;
	}
	std::string print() const {
		return Named::print() + Shapes::print() +
			"Centre: (" + str(centre.getX()) + ", " + str(centre.getY()) + "); \n" +
			"Radius: " + str(radius) + "; \n\n";
	}

private:
	const Point  centre;
	const double radius;
};

class Rect : public Shapes, public Named {
public:
	Rect(const double _x1, const double _y1, const double _x2, const double _y2, const std::string name = "NO_NAME")
		: Named(name), Shapes(), x1(_x1), x2(_x2), y1(_y1), y2(_y2) {
		if (!((x1 <= x2) && (y1 >= y2)))
			throw "Rect: incorrect rect";
	}
	std::string type() const {
		return "Rect";
	}
	double area() const {
		return (x2 - x1)*(y1 - y2);
	}
	double perimeter() const {
		return 2 * ((x2 - x1) + (y1 - y2));
	}
	std::string print() const {
		return Named::print() + Shapes::print() +
			"Point1: (" + str(x1) +
			", " + str(y1) + "); \n" +
			"Point2: (" + str(x2) +
			", " + str(y1) + "); \n" +
		    "Point3: (" + str(x1) +
			", " + str(y2) + "); \n" +
			"Point4: (" + str(x2) +
			", " + str(y2) + "); \n\n";
	}
private:
	const double x1, y1, x2, y2;
};

class Square : public Shapes, public Named{
public:
	Square(const double _x1, const double _y1, const double _x2, const double _y2, const std::string name = "NO_NAME")
		: Named(name), Shapes(), x1(_x1), x2(_x2), y1(_y1), y2(_y2){}
	double area() const {
		return pow(Point(x1, y1).distance(Point(x2, y2)), 2)/ 2;
	}
	double perimeter() const {
		return Point(x1, y1).distance(Point(x2, y2)) * 2 * sqrt(2);
	}
	std::string type() const {
		return "Square";
	}
	std::string print() const {
		return Named::print() + Shapes::print() +
			"Point1: (" + str(x1) + ", " + str(y1) + "); \n" +
			"Point2: (" + str((x1 + x2 + y1 - y2)/2) + ", " + str((y1 + y2 + x2 - x1)/2) + "); \n" +
			"Point3: (" + str((x1 + x2 + y2 - y1) / 2) + ", " + str((y1 + y2 + x1 - x2) / 2) + "); \n" +
			"Point4: (" + str(x2) + ", " + str(y2) + "); \n\n";
	}
private:
	const double x1, x2, y1, y2;
};

class Polyline : public Shapes, public Named {
public:
	Polyline(Container<Point> & _points, const std::string name = "NO_NAME") 
		: Named(name), Shapes(), points(_points) {}
	Polyline(const std::string name = "NO_NAME") : Named(name), Shapes() {
		points = Container<Point>();
	}
	void addPoint (const Point & point) {
		points.pushBack(point);
	}
	double area() const {
		return 0;
	}
	double perimeter() const {
		double sum = 0;
		for (int i = 0; i < (points.size()) - 1; i++)
			sum += points.get(i).distance(points.get(i+1));
		return sum;
	}
	std::string type() const {
		return "Polyline";
	}
	std::string print() const {
		std::string s = "";
		s += "Number of points: " + str(points.size()) + "; \n";
		for (int i = 0; i < points.size(); i++)
			s += "Point" + str(i) +
			": (" + str(points.get(i).getX()) +
			", " + str(points.get(i).getY()) + "); \n";
		return Named::print() + Shapes::print() + s +"\n";
	}
	bool isClosed() const {
		return points.get(0).equ(points.get(points.size() - 1));

	}
	bool isSimple() const {
		for (int i = 0; i < points.size() - 1; i++) {
			Point p1 = points.get(i);
			Point p2 = points.get(i+1);
			for (int j = i; j < points.size() - 1; j++)
				if (crosSeg(p1, p2, points.get(j), points.get(j + 1)))
					return false;
		}
		return true;
	}
	bool crosSeg (Point const & p1, Point const & p2, Point const & p3, Point const & p4) const {
		double ax1 = p1.getX();
		double ax2 = p2.getX();
		double ay1 = p1.getY();
		double ay2 = p2.getY();
		double bx1 = p3.getX();
		double bx2 = p4.getX();
		double by1 = p3.getY();
		double by2 = p4.getY();
		double v1 = (bx2 - bx1)*(ay1 - by1) - (by2 - by1)*(ax1 - bx1);
		double v2 = (bx2 - bx1)*(ay2 - by1) - (by2 - by1)*(ax2 - bx1);
		double v3 = (ax2 - ax1)*(by1 - ay1) - (ay2 - ay1)*(bx1 - ax1);
		double v4 = (ax2 - ax1)*(by2 - ay1) - (ay2 - ay1)*(bx2 - ax1);
		return (v1*v2 < 0) && (v3*v4 < 0);
	}

	Container<Point>  getPoints() {
		return points;
	}
	

protected:
	Container<Point> points;
};

class Polygon : public Polyline{
public:
	Polygon(Container<Point> & _points, std::string const name = "NO_NAME")
		: Polyline(_points, name) {
		if(!(isClosed() && isSimple() && points.size()>=4))
			throw "Polygon: This polyline is not polygon";
	}
	double area() const {
		double s = 0;
		for (int i = 0; i < points.size() - 1; i++)
			s += points.get(i).getX() * points.get(i + 1).getY()
				- points.get(i).getY() * points.get(i + 1).getX();
		return s/2;
	}
	std::string type() const {
		return "Polygon";
	}
private:
	Polyline::addPoint;
};


