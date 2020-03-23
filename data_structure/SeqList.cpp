#include <iostream>
#include <string>
#include "SeqList.hpp"
using namespace std;

template <typename T>
SeqList<T>::SeqList(int capacity)
{
	cout<<"create"<<endl;
	pArray=new T[capacity];
	this->len=0;
	this->capacity=capacity;
}

// 析构函数 释放内存
template <typename T>
SeqList<T>::~SeqList()
{
	cout<<"release"<<endl;
	delete[] pArray;
	pArray=NULL;
	len=0;
	capacity=0;
}

template <typename T>
int SeqList<T>::getLen()
{
	return len;
}
	
	
template <typename T>
int SeqList<T>::getCapacity()
{
	return capacity;
}

template <typename T>
int SeqList<T>::insert(T &t,int pos)
{
	int ret=0;
	//参数是否有效
	if(pos<0)
	{
		ret=-1;
		printf("error when insert %d\n",ret );
		return ret;
	}
// 容量是否达到上限
	if(len>=capacity)
	{
		ret=-2;
		printf("error when insert %d\n",ret );
		return ret;
	}

	// 插入位置是否有效
	if(pos>len)
	{
		pos=len;
	}
	// 将插入点数据后移
	for (int i = len; i >pos; --i)
	{
		pArray[i]=pArray[i-1];
	}
	// 采用复制的方式实现 需要考虑浅拷贝和深拷贝
	pArray[pos]=t;
	len++;
	return ret;
}


template <typename T>
int SeqList<T>::get(int pos,T &t)
{
	if(pos<0||pos>len)
	{
		return -1;
	}
	t=pArray[pos];
	return 0;
}

template <typename T>
int SeqList<T>::del(int pos,T &t)
{
	// 删除在线性表存储空间之外
	if(pos<0||pos>=capacity)
	{
		return -1;
	}

	t=pArray[pos];
	for (int i = pos+1; i < len; ++i)
	{
		pArray[i-1]=pArray[i];
	}
	len--;
	return 0;

}

