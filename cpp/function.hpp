#pragma once

#include <iostream>
#include <cmath>

using namespace std;

class Circle
{
	int x;
	int y;
	float radius;
public:
	Circle(int x,int y,float radius);
	void set(int x,int y,float radius);
	bool intersect(Circle &circle);
	void printToString();
	int getX();
	int getY();
	float getRadius();
	float area(){return M_PI*pow(radius,2);}
	float operator +(Circle &circle)
	{
		return area()+circle.area();
	}
};
