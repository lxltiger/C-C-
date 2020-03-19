#include "stdio.h"
#include "stdlib.h"
#include "string.h"

typedef struct BiNode
{
	int data;
	struct BiNode* left;
	struct BiNode* right;
	
}BiNode;

//先序遍历，顺序为 根节点 左节点 右节点
void preTraversal(BiNode* root){
	if(NULL==root)return;
	printf("data=%d\n", root->data);
	preTraversal(root->left);
	preTraversal(root->right);

}

// 中序遍历   左节点 根节点 右节点
void inTraversal(BiNode* root){
	if(NULL==root)return;
	inTraversal(root->left);
	printf("data=%d\n", root->data);
	inTraversal(root->right);
}

// 后序遍历   左节点 右节点 根节点
void postTrasveral(BiNode* root){
	if(NULL==root)return;
	postTrasveral(root->left);
	postTrasveral(root->right);
	printf("data=%d\n", root->data);
}

// 计算叶子节点数，即左右子节点都为空
void countLeaf(BiNode* root,int* count){
	if(!root)return;
	if(!root->left&&!root->right){
		(*count)++;
	}
	countLeaf(root->left,count);
	countLeaf(root->right,count);
}
// 递归计算左右子节点的高度返回较大值
int countDepth(BiNode* root){
	if(!root)return 0;
	int left_depth=countDepth(root->left);
	int right_depth=countDepth(root->right);

	return (left_depth>right_depth?left_depth:right_depth)+1;


}

BiNode* copyTree(BiNode* root){
	if(root==NULL) return NULL;

	BiNode* node=(BiNode *)malloc(sizeof(BiNode));
	node->data=root->data;
	BiNode* left=copyTree(root->left);
	BiNode* right=copyTree(root->right);
	node->left=left;
	node->right=right;
	return node;

}

int main(int argc, char const *argv[])
{
	BiNode t1,t2,t3,t4,t5;
	BiNode* b[]={&t1,&t2,&t3,&t4,&t5};
	int len=sizeof(b)/sizeof(BiNode *);
	printf("len=%d\n", len);
	for (int i = 0; i < len; ++i)
	{
		memset(b[i],0,sizeof(BiNode));
		b[i]->data=i+1;

	}
	
	t1.left=&t2;
	t1.right=&t3;
	t2.left=&t4;
	t3.left=&t5;
	// t5.right=&t6;
	

	printf("=====preTraversal========\n");
	preTraversal(&t1);
	printf("======inTraversal=======\n");
	inTraversal(&t1);
	printf("====postTrasveral=========\n");
	postTrasveral(&t1);

	int count=0;
	countLeaf(&t1,&count);
	printf("=====the num of leaf===== :%d\n", count);

	int depth=countDepth(&t1);
	printf("=====depth=%d\n", depth);

	printf("=====copyTree \n");
	BiNode* root= copyTree(&t1);
	preTraversal(root);
	inTraversal(root);
	postTrasveral(root);
	
	return 0;
}