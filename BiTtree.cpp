//以左右孩子为结构的二叉树
#include <iostream>
#define MAXSIZE 40
using namespace std;


typedef struct BiNode
{
    int data;
    struct BiNode* lchild, * rchild;
    struct BiNode(int a) { data = a; lchild = NULL; rchild = NULL; };
}BiNode, *BiTree;


//根据数组创建述结构 使用 c 中的malloc
void CreateBiTree(BiTree* T, int *num, int sub, int len)
{
	if (num[sub] == -1 || sub >= len)
	{
		(*T) = NULL;
	}
	else
	{
		(*T) = (BiTree)malloc(sizeof(struct BiNode));
		if ((*T) != NULL)
		{
			(*T)->data = num[sub];
			CreateBiTree(&(*T)->lchild, num, 2 * sub + 1, len);
			CreateBiTree(&(*T)->rchild, num, 2 * sub + 2, len);
		}	
	}
}

//使用c++的 new
void CreateBiTreeByNew(BiTree* T, int* num, int sub, int len)
{
	if (num[sub] == -1 || sub >= len)
	{
		(*T) = NULL;
	}
	else
	{
		(*T) = new (struct BiNode)(num[sub]);
		CreateBiTreeByNew(&(*T)->lchild, num, 2 * sub + 1, len);
		CreateBiTreeByNew(&(*T)->rchild, num, 2 * sub + 2, len);
	}
}

//在创建时输入数据 当输入标识为 -1 时就会终止
void CreateBiTreeGetInfo(BiTree* T)
{
	int data;
	cout << "请输入结点数据" << endl;
	cin >> data;
	if (data == -1)
	{
		(*T) = NULL;
	}
	else
	{
		(*T) = new (struct BiNode)(data);
		CreateBiTreeGetInfo(&(*T)->lchild);
		CreateBiTreeGetInfo(&(*T)->rchild);
	}
}


//利用malloc最官方的书写方式
void CreateBiTreeS(BiTree* T)
{
	int data;
	cin >> data;
	if (data == -1)
	{
		*T = NULL;
	}
	else
	{
		*T = (BiTree)malloc(sizeof(struct BiNode));
		if (*T)
		{
			CreateBiTreeS(&(*T)->lchild);
			CreateBiTreeS(&(*T)->rchild);
		}
	}
}

//前序遍历
void PrePrint(BiTree* T) 
{
	//cout << ((*T) == NULL) << endl;
	if ((*T) != NULL)
	{
		cout << (*T)->data << " ";

		PrePrint(&(*T)->lchild);
		PrePrint(&(*T)->rchild);
	}
}

//中序遍历
void MidPrint(BiTree* T)
{
	if ((*T) != NULL)
	{
		MidPrint(&(*T)->lchild);
		cout << (*T)->data << " ";
		MidPrint(&(*T)->rchild);
	}
}

//后序遍历
void EndPrint(BiTree* T)
{
	if ((*T) != NULL)
	{
		EndPrint(&(*T)->lchild);
		EndPrint(&(*T)->rchild);
		cout << (*T)->data << " ";
	}
}


//层次遍历使用队列实现
typedef struct
{
	BiTree data[MAXSIZE];
	int rear, front;
}BiQueue;

//初始化队列
void InitBiQueue(BiQueue* q)
{
	q->front = 0;
	q->rear = 0;
}

//判断队列是否为空
bool IsEmptyQueue(BiQueue* q)
{
	if (q->front == q->rear)
		return true;
	return false;
}

//是否为满
bool IsFullQueue(BiQueue* q)
{
	if ((q->rear + 1) % MAXSIZE == q->front)
		return true;
	return false;
}

//出队
void EnQueue(BiQueue* q, BiTree *e)
{
	if (IsEmptyQueue(q))
		return;
	*e = q->data[q->front];
	q->front = (q->front + 1) % MAXSIZE;
}

//入队
void DnQueue(BiQueue* q, BiTree* T)
{
	if (IsFullQueue(q))
		return;
	q->data[q->rear] = *T;
	q->rear = (q->rear + 1) % MAXSIZE;
}

//层次遍历
void LayPrint(BiTree* T)
{
	BiQueue* biq = (BiQueue * )malloc(sizeof(BiQueue));
	InitBiQueue(biq);

	//将头节点放入
	BiTree p = *T;
	DnQueue(biq, &p);

	while (!IsEmptyQueue(biq)) 
	{
		BiTree val;
		EnQueue(biq, &val);
		cout << val ->data<< " ";
		if(val->lchild != NULL)
			DnQueue(biq, &val->lchild);
		if (val->rchild != NULL)
			DnQueue(biq, &val->rchild);
	}
	cout << endl;
}


int main2()
{
    //给定一个数组
    int num[10] = { 1,2,3,4,5,6,7,8,-1,-1 };
	BiTree T;
	//根据数组信息建立
	CreateBiTree(&T, num, 0, sizeof(num)/sizeof(int));

	BiTree T1;
	//根据数组信息建立
	CreateBiTreeByNew(&T1, num, 0, sizeof(num) / sizeof(int));

	//自身输入数据构建
	/*BiTree T2;
	CreateBiTreeGetInfo(&T2);*/


	//三种遍历方式
	//前序遍历
	cout << "前序遍历的结果为 " << endl;
	PrePrint(&T);
	cout << endl;

	//中序遍历
	cout << "中虚遍历的结果为" << endl;
	MidPrint(&T);
	cout << endl;

	//后序遍历
	cout << "后虚遍历的结果为" << endl;
	EndPrint(&T);
	cout << endl;

	//层次遍历
	cout << "层次遍历的结果为 " << endl;
	LayPrint(&T);


	puts("edwa");
    return 0;
}

