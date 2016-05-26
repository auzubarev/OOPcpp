#pragma once
#include <cstdlib>
#include <algorithm>
#include "Shapes.h"
#include "Factory.h"

int Shapes::count;

Shapes* Factory::getRandShape() {
	int k = iRand(1, 6);
	switch (k) {
	case 1:
		return getRandCircle();
	case 2:
		return getRandPoint();
	case 3:
		return getRandPolygon();
	case 4:
		return getRandPolyline();
	case 5:
		return getRandRect();
	case 6:
		return getRandSquare();
	default:
		return NULL;
	}
}

Circle * Factory::getRandCircle() {
	return new Circle(dRand(-1000, 1000), dRand(-1000, 1000), dRand(0, 500));
}

Point * Factory::getRandPoint() {
	return new Point(dRand(-1000, 1000), dRand(-1000, 1000));
}

Rect * Factory::getRandRect() {
	double x1 = dRand(-1000, 1000);
	double y1 = dRand(-1000, 1000);
	return new Rect(x1, y1, dRand(x1, 1000), dRand(-1000, y1));
}

Square * Factory::getRandSquare() {
	return new Square(dRand(-1000, 1000), dRand(-1000, 1000),
		              dRand(-1000, 1000), dRand(-1000, 1000));
}

Polyline * Factory::getRandPolyline() {
	Polyline * pl = new Polyline();
	int N = iRand(1, 10);
	for (int i = 0; i < N; i++) {
		Point * p = getRandPoint();
		pl->addPoint(* p);
		delete p;
	}	
	return pl;
}

Polygon * Factory::getRandPolygon() {
	int N = iRand(3, 9);
	Point * * points = new Point * [N+1];
	for (int i = 0; i < N; i++) {
		Point * p = getRandPoint();
		points[i] = p;
		if (points[i]->getX() < points[0]->getX())
			std::swap(points[i], points[0]);
	}
	for (int i = 2; i < N; i++) {
		int j = i;
		while (j > 1 && (points[0]->rotate(*points[j - 1], *points[j]) < 0)) {
			std::swap(points[j - 1], points[j]);
			j -= 1;
		}
	}
	points[N] = new Point(points[0]->getX(), points[0]->getY());
	Container<Point> pl;
	for (int i = 0; i < N+1; i++) {
		pl.pushBack(*points[i]);
		delete points[i];
	}
	delete points;
	return new Polygon(pl);
}


