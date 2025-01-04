//基于普通二叉树的基础上
//通过中序遍历所有树来标识前驱和后继节点

#include<iostream>

using namespace std;

typedef char ELEMTYPE;
//enum 类型的使用方式
typedef enum {Link, Thread}PointerTag;
enum MyEnum { a, b, c };

typedef struct BiTreNode
{
	ELEMTYPE data;
	struct BiTreNode* lchild, *rchild;
	PointerTag ltag;
	PointerTag rtag;
}BiTreNode,*BiTreTree;

//根据输入信息建立树结构

void CreateBiTreTree(BiTreTree* T)
{
	ELEMTYPE data;
	cin >> data;
	if (data == '#')
	{
		*T = NULL;
	}
	else
	{
		*T = (BiTreTree)malloc(sizeof(BiTreNode));
		if (*T)
		{
			(*T)->data = data;
			(*T)->ltag = (*T)->rtag = Link;
			CreateBiTreTree(&(*T)->lchild);
			CreateBiTreTree(&(*T)->rchild);
		}		
	}
}


//输出中序遍历结果
void MidPrint(BiTreTree* T)
{
	if (*T != NULL)
	{
		MidPrint(&(*T)->lchild);
		cout << (*T)->data << " ";
		MidPrint(&(*T)->rchild);
	}
}

BiTreTree pre;
//在中序遍历中构建线索二叉树
void BuildBiTreTree(BiTreTree* T) 
{
	if (*T)
	{
		BuildBiTreTree(&(*T)->lchild);
		if (!(*T)->lchild)
		{
			(*T)->lchild = pre;
			(*T)->ltag = Thread;
		}
		if (pre && !pre->rchild)
		{
			pre->rchild = *T;
			pre->rtag = Thread;
		}
		pre = *T;
		BuildBiTreTree(&(*T)->rchild);
	}
}

void PrintAll(BiTreTree* T) 
{
	BiTreTree p = *T;
	cout << "带有头节点的线索二叉树遍历结果为 " << endl;
	p = p->lchild;
	while (p != *T)
	{
		//先找到最左的前驱节点
		while (p->ltag == Link)
			p = p->lchild;
		cout << p->data << " ";
		//如果当前位置指向的是后继则继续循环， 如果不是后继就根据rchild执行
		while (p->rtag == Thread && p->rchild != *T)
		{
			p = p->rchild;
			cout << p->data << " ";
		}
		p = p->rchild;
	}
	cout << endl;
}



int main3() 
{
	/*MyEnum s = a;
	cout << s << endl;*/
	BiTreTree T;
	CreateBiTreTree(&T);
	MidPrint(&T);
	cout << endl;

	//构建线索二叉树
	BuildBiTreTree(&T);

	//创建一个头节点 左孩子指向该根节点
	BiTreNode p;
	p.lchild = T;
	T = &p;

	//找到第一个前驱将其左孩子指向根节点
	BiTreTree temp = T;
	while (temp->lchild != NULL)
		temp = temp->lchild;
	temp->lchild = &p;
	temp->ltag = Thread;

	//找到最右的指针
	temp = T->lchild;
	while (temp->rchild != NULL)
		temp = temp->rchild;
	temp->rchild = &p;
	temp->rtag = Thread;


	//利用双向链表的方式遍历所有的信息
	PrintAll(&T);

	cout << "asdad" << endl;


	return 0;
}