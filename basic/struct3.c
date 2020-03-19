#include <stdio.h>
#define MAX 41

struct funds
{
	/* 账户结构体*/
	char bank[MAX];
	double bankFund;
	double saveFund;
};
double sum(double one,double two){
	return one+two;
}

/*结构体地址，参数指向原结构体*/
double sum2(const funds *anyone){
	return anyone->bankFund+anyone->saveFund;
}

/*使用结构体作为参数,参数是原结构体的副本*/
double sum3(funds anyone){
	return anyone.bankFund+anyone.saveFund;
}

int main(int argc, char const *argv[])
{
	struct funds tom={
		"China Bank",
		23.32,
		434.23
	};
		/* 使用结构体成员作为参数 */
	double total=sum(tom.bankFund,tom.saveFund);
	printf("I just save money to my account in %s,which now %.2f left\n",tom.bank,total );


	/*使用结构体地址作为参数*/
	double total2=sum2(&tom);
	printf("He just save money to my account in %s,which now %.2f left\n",tom.bank,total );

	double total3=sum3(tom);
	printf("He just save money to my account in %s,which now %.2f left\n",tom.bank,total );



	return 0;
}


