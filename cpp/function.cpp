#include "function.hpp"


Circle::Circle(int x,int y,float radius)
{
	this->x=x;
	this->y=y;
	this->radius=radius;
}
void Circle::set(int x,int y,float radius)
{
	this->x=x;
	this->y=y;
	this->radius=radius;
}

bool Circle::intersect(Circle &circle)
{
	int xDistance=getX()-circle.getX();
	int yDistance=getY()-circle.getY();
	float distance=pow(pow(xDistance,2)+pow(yDistance,2),0.5);
	cout<<"test distance"<<distance<<endl;

	return distance<=getRadius()+circle.getRadius();
}

int Circle::getX(){return x;}
	int Circle::getY(){return y;}
	float Circle::getRadius(){return radius;}



void Circle::printToString()
{
	cout<<"x="<<x<<" y="<<y<<" radius="<<radius<<endl;
}

