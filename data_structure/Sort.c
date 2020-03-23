#include "stdio.h"

/*
＊插入排序，升序 O（n*n)
*/
void insertSort(int *array,int len){
	// 从第二个开始
	for (int i = 1; i <len; ++i)
	{
		// 插入位置和值
		int insert_pos=i;
		int insert_val=array[i];
		//  待查值依次与前面的值比较
		for (int j = i; j>0&&array[j-1]>insert_val ; --j)
		{
			//  往后移动
			array[j]=array[j-1];
			//更新插入位置
			insert_pos=j-1;
		}
		// 找到插入点后写回缓存值
		array[insert_pos]=insert_val;
		//上面循环结束后，i前的数值就是有序的，这是下次插值的基础

	}
}
// 希尔排序 ，使用分组对插入排序优化

void shelSort(int *arr,int len){
	int gap=len;
	while(gap>1){
		//分组间距 经验参数 
		gap=gap/3+1;	
		printf("gap%d\n", gap);
		// 从第一个间距位置开始插入排序
		for (int i = gap; i < len; i++)
		{
			// 记录位置和值，
			int insert_pos=i;
			// 便于找到新位置后更新
			int insert_val=arr[insert_pos];
			printf("pos=%d\n", insert_pos);
			// arr[j－gap]>insert_val 比较要插入的位置和前一个的大小
			for (int j = insert_pos; j>=gap&&arr[j-gap]>insert_val; j-=gap)
				{
					printf("j=%d,val=%d\n", j,arr[j]);
					// 如果前一个值大 往后移动 
					arr[j]=arr[j-gap];
					// 更新要插入的位置
					insert_pos=j-gap;
				}
				// 找到最终插入点 更新值
			arr[insert_pos]=insert_val;
		}
	}	
}
// todo 优化16,12,6,9,15
 int partion(int *arr,int low,int high)
 {
 	// 先将第一个值移出当pv
	int pos_value=arr[low];
	//空位
	int pos=low;
 	while(low<high){
 		// 如果低位是空位，比较高位
 		if(pos==low){
 		//如果右边高位比pv值小需要移动
 			if(arr[high]<pos_value){
 			arr[pos]=arr[high];
 			pos=high;
 			low++;
 		}else{
 			high--;
 			}
 		}
 		// 如果高位是空位，比较低位
 		if(pos==high){
 			if(arr[low]>pos_value){
 				arr[pos]=arr[low];
 				pos=low;
 				high--;
 			}else{
				low++;
 			}
 		}
 	}
 	arr[pos]=pos_value;
 	return low;

 }

 void quickSort(int *arr,int low ,int high){
 	int devider=partion(arr,low,high);
 	//左边排序
 	if(devider-1>low)
 		quickSort(arr,low,devider-1);
 	if(devider+1<high)
 		quickSort(arr,devider+1,high);
 }


int main(int argc, char const *argv[])
{
	/* code */

	int array[10]={110,30,15,2,7,9,3,12,4,100};
	// insertSort(array,10);
	// shelSort(array,10);
	quickSort(array,0,9);
	for (int i = 0; i < 10; ++i)
	{
		printf("%d ", array[i]);
	}

	return 0;
}