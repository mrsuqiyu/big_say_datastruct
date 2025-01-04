//�����Һ���Ϊ�ṹ�Ķ�����
#include <iostream>
#define MAXSIZE 40
using namespace std;


typedef struct BiNode
{
    int data;
    struct BiNode* lchild, * rchild;
    struct BiNode(int a) { data = a; lchild = NULL; rchild = NULL; };
}BiNode, *BiTree;


//�������鴴�����ṹ ʹ�� c �е�malloc
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

//ʹ��c++�� new
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

//�ڴ���ʱ�������� �������ʶΪ -1 ʱ�ͻ���ֹ
void CreateBiTreeGetInfo(BiTree* T)
{
	int data;
	cout << "������������" << endl;
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


//����malloc��ٷ�����д��ʽ
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

//ǰ�����
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

//�������
void MidPrint(BiTree* T)
{
	if ((*T) != NULL)
	{
		MidPrint(&(*T)->lchild);
		cout << (*T)->data << " ";
		MidPrint(&(*T)->rchild);
	}
}

//�������
void EndPrint(BiTree* T)
{
	if ((*T) != NULL)
	{
		EndPrint(&(*T)->lchild);
		EndPrint(&(*T)->rchild);
		cout << (*T)->data << " ";
	}
}


//��α���ʹ�ö���ʵ��
typedef struct
{
	BiTree data[MAXSIZE];
	int rear, front;
}BiQueue;

//��ʼ������
void InitBiQueue(BiQueue* q)
{
	q->front = 0;
	q->rear = 0;
}

//�ж϶����Ƿ�Ϊ��
bool IsEmptyQueue(BiQueue* q)
{
	if (q->front == q->rear)
		return true;
	return false;
}

//�Ƿ�Ϊ��
bool IsFullQueue(BiQueue* q)
{
	if ((q->rear + 1) % MAXSIZE == q->front)
		return true;
	return false;
}

//����
void EnQueue(BiQueue* q, BiTree *e)
{
	if (IsEmptyQueue(q))
		return;
	*e = q->data[q->front];
	q->front = (q->front + 1) % MAXSIZE;
}

//���
void DnQueue(BiQueue* q, BiTree* T)
{
	if (IsFullQueue(q))
		return;
	q->data[q->rear] = *T;
	q->rear = (q->rear + 1) % MAXSIZE;
}

//��α���
void LayPrint(BiTree* T)
{
	BiQueue* biq = (BiQueue * )malloc(sizeof(BiQueue));
	InitBiQueue(biq);

	//��ͷ�ڵ����
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
    //����һ������
    int num[10] = { 1,2,3,4,5,6,7,8,-1,-1 };
	BiTree T;
	//����������Ϣ����
	CreateBiTree(&T, num, 0, sizeof(num)/sizeof(int));

	BiTree T1;
	//����������Ϣ����
	CreateBiTreeByNew(&T1, num, 0, sizeof(num) / sizeof(int));

	//�����������ݹ���
	/*BiTree T2;
	CreateBiTreeGetInfo(&T2);*/


	//���ֱ�����ʽ
	//ǰ�����
	cout << "ǰ������Ľ��Ϊ " << endl;
	PrePrint(&T);
	cout << endl;

	//�������
	cout << "��������Ľ��Ϊ" << endl;
	MidPrint(&T);
	cout << endl;

	//�������
	cout << "��������Ľ��Ϊ" << endl;
	EndPrint(&T);
	cout << endl;

	//��α���
	cout << "��α����Ľ��Ϊ " << endl;
	LayPrint(&T);


	puts("edwa");
    return 0;
}

