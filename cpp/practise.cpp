#include <iostream>
#include <string>
#include <cmath>
using namespace std;

typedef struct Teacher
{
	int age;
} Teacher;

int printTeacher(const Teacher &t){
	cout<<"ageof teacer"<<t.age<<endl;
	return 0;
}



int freeTeacher(Teacher *t){
	if (t==NULL)
	{
		return-1;
	}
	free(t);
	return 0;
}
int main(int argc, char const *argv[])
{

	float area=M_PI*pow(3,2);
	cout<<"get this "<<area<<endl;



	
	

	return 0;
}