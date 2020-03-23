#include "SeqList.cpp"

/*C++版线性存储测试*/
struct Teacher
{
	int age;
};

//  测试数据类型为结构体的线性表
void test()
{
	Teacher t1,t2,t3,temp;
	t1.age=10;
	t2.age=20;
	t3.age=40;
	SeqList<Teacher> teachers(10);
	teachers.insert(t1,0);
	teachers.insert(t2,0);
	teachers.insert(t3,0);

	for (int i = 0; i < 3; ++i)
	{
		teachers.get(i,temp);
		cout<<temp.age<<'\t'<<endl;
	}

	while(teachers.getLen()>0)
	{
		teachers.del(0,temp);
		cout<<temp.age<<'\t'<<endl;

	}

}

void test2()
{
	Teacher t1,t2,t3;

	/*t1.age=10;
	t2.age=20;
	t3.age=40;
*/
	Teacher *p1=&t1;
	Teacher *p2=&t2;
	Teacher *p3=&t3;

	p1->age=10;
	p2->age=20;
	p3->age=40;
	SeqList<Teacher *> teachers(10);
	
	teachers.insert(p1,0);
	teachers.insert(p2,0);
	teachers.insert(p3,0);

	Teacher *temp=NULL;
	for (int i = 0; i < 3; ++i)
	{
		teachers.get(i,temp);
		cout<<temp->age<<'\t';
	}

	printf("\n---------------\n");
	while(teachers.getLen()>0)
	{
		teachers.del(0,temp);
		cout<<temp->age<<'\t'<<endl;

	}

}

int main(int argc, char const *argv[])
{
	test2();
	return 0;
}