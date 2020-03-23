
#include "main.h"
#include "function.cpp"

template <typename T>
T findSmaller(T input1,T input2);

class Money
{
private:
	int value;
	friend Money operator+(Money &m1,Money &m2);
	friend Money operator++(Money &m);
	friend Money operator++(Money &m,int);
 friend ostream&  operator<<(ostream &out,Money &m);

public:
	Money(int value){this->value=value;}
	int getMoney(){return value;}
	Money operator-(Money &m1){
		return Money(this->value-m1.value);
	}
	Money& operator--(){
		value-=20;
		return *this;
	}
	Money& operator--(int){
		Money &temp=*this;
		value-=30;
		return temp;
	}
	
};
Money operator+(Money &m1,Money &m2){
	return Money(m1.value+m2.value);
}

 Money operator++(Money &m){
 	m.value+=10;
 	return m;
 }

 Money operator++(Money &m,int){
	Money &temp=m;
	m.value+=20;
	return temp;
}


 ostream&  operator<<(ostream &out,Money &m){
	
	out<<"hei "<<m.value<<endl;
	return out;
}

int main(int argc, char const *argv[])
{
	
	Money m1(100);
	Money m2(200);
	Money m3=m1-m2;
	cout<<m3.getMoney()<<endl;
	++m1;
	cout<<"value "<<m1.getMoney()<<endl;
	--m2;
	cout<<"value "<<m2.getMoney()<<endl;
	--m2;
	cout<<"value "<<m2.getMoney()<<endl;
	m1++;
	cout<<"value m1 "<<m1.getMoney()<<endl;
	m2--;
	cout<<"value m2 "<<m2.getMoney()<<endl;
	cout<<m2<<"disd ";
	return 0;
}

template <typename T>
T findSmaller(T input1,T input2)
{
	return input1>input2?input2:input1;
}