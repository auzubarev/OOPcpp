#pragma once
#include "Shapes.h"


class Factory {
public:
	static Shapes * getRandShape();
	static Point * getRandPoint();
	static Circle * getRandCircle();
	static Rect * getRandRect();
	static Square * getRandSquare();
	static Polyline * getRandPolyline();
	static Polygon * getRandPolygon();
private:
	static double dRand(double min, double max) {
		double f = (double)rand() / RAND_MAX;
		return min + f * (max - min);
	}
	static int iRand(int min, int max) {
		return rand() % (max - min + 1) + min;
	}
};
