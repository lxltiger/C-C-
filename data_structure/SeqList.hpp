#pragma once
/*C++版线性表存储 使用模版类实现*/
template <typename T>
class SeqList
{
private:
	int len;
	int capacity;
	T *pArray;
public:
	SeqList(int capacity);
	~SeqList();
	int getLen();
	int getCapacity();
	int insert(T &t,int pos);
	int get(int pos,T &t);
	int del(int pos,T &t);

};

