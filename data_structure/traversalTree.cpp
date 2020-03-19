#include <iostream>
#include <stack>
using namespace std;

typedef struct BiNode
{
	int data;
	struct BiNode* left;
	struct BiNode* right;
} BiNode;

// 找节点的左节点直到没有，如果有将当前节点入栈,没有返回当前节点
BiNode* goFarLeft(BiNode* node,stack<BiNode *> *nodes){

	if (node&&nodes)
	{
		while(node->left){
			nodes->push(node);
			node=node->left;
		}
		return node;
	}

	return NULL;
}
// 
/*
非递归中序遍历
1.如果一个节点有左节点，入栈，没有返回处理此节点
2.如果一个节点有右节点，重复步骤1，没有右节点处理栈顶节点，栈顶节点本身及右节点都没访问，所以对弹出的栈顶元素，先处理
其本身，再处理其右节点
3.当栈为空 遍历结束
*/

void inOrder(BiNode *node)
{
	// 有左节点的节点都会入栈
	stack<BiNode *> nodesStack;
	// 没有左节点的节点
	BiNode *nodeWithoutLeft=NULL;
	// 1.对于一个节点，如果有左节点就入栈，没有返回此节点
	nodeWithoutLeft=goFarLeft(node,&nodesStack);
	while(nodeWithoutLeft)
	{	
		// 处理当前节点
		printf("data=%d\n", nodeWithoutLeft->data);
		if(nodeWithoutLeft->right)
		{
			nodeWithoutLeft=goFarLeft(nodeWithoutLeft->right,&nodesStack);
		}
		else if(!nodesStack.empty())
		{
			nodeWithoutLeft= nodesStack.top();
			nodesStack.pop();
		}else
		{
			nodeWithoutLeft=NULL;
		}
	}
}
int main(int argc, char const *argv[])
{
	BiNode t1,t2,t3,t4,t5;
	BiNode* nodes[]={&t1,&t2,&t3,&t4,&t5};
	int len=sizeof(nodes)/sizeof(nodes[0]);
	cout<<"len "<<len<<endl;
	for (int i = 0; i < len; ++i)
	{
		memset(nodes[i],0,sizeof(BiNode));
		nodes[i]->data=i+1;
	}

	t1.left=&t2;
	t1.right=&t3;
	t2.left=&t4;
	t3.left=&t5;

	inOrder(&t1);




	return 0;
}