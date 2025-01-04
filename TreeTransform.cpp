//�� ɭ�� ������֮���ת��
#include<iostream>
#define MAXSIZE 40

using namespace std;

typedef struct Node
{
	char data;
	struct Node* lchild, * mchild, * rchild;
}Node,* Tree;


//�������ṹ
void CreateTree(Tree * T)
{
	char data;
	cout << "����ڵ���Ϣ" << endl;
	cin >> data;

	if (data == '#')
	{
		*T = NULL;
	}
	else
	{
		*T = (Tree)malloc(sizeof(Node));
		if (*T)
		{
			(*T)->data = data;
			CreateTree(&(*T)->lchild);
			CreateTree(&(*T)->mchild);
			CreateTree(&(*T)->rchild);
		}
	}
}

//�ȸ�����
void FPrint(Tree * T) 
{
	if (*T)
	{
		cout << (*T)->data << " ";
		FPrint(&(*T)->lchild);
		FPrint(&(*T)->mchild);
		FPrint(&(*T)->rchild);	
	}
}

//��ת��Ϊ������
void TreeToBiTree(Tree* T)
{
	if (*T)
	{
		//�ȵ�����Ľڵ�
		TreeToBiTree(&(*T)->lchild);
		TreeToBiTree(&(*T)->mchild);
		TreeToBiTree(&(*T)->rchild);
		if ((*T)->rchild != NULL)
		{
			(*T)->mchild->rchild = (*T)->rchild;
			(*T)->rchild = NULL;
		}

		if ((*T)->mchild != NULL)
		{
			(*T)->lchild->rchild = (*T)->mchild;
			(*T)->mchild = NULL;
		}
	}
}

//������ת��Ϊ��
void BiTreeToTree(Tree* T) 
{
	if (*T)
	{
		if ((*T)->lchild != NULL)
		{
			Tree temp = (*T)->lchild;
			int index = 0;
			while (temp->rchild != NULL)
			{
				if (index == 0)
				{
					(*T)->mchild = temp->rchild;
					temp->rchild = NULL;
					temp = (*T)->mchild;
					index++;
					continue;
				}
				if (index == 1)
				{
					(*T)->rchild = temp->rchild;
					temp->rchild = NULL;
					temp = (*T)->rchild;
					index++;
					continue;
				}
			}
		}
		BiTreeToTree(&(*T)->lchild);
		BiTreeToTree(&(*T)->mchild);
		BiTreeToTree(&(*T)->rchild);
	}
}

//�������鹹��ɭ��
void CreatForest(Tree* array, int len) 
{
	int i = 0;
	while (i < len)
	{
		cout << "�������" << i + 1 << " ��������Ϣ" << endl;
		CreateTree(&array[i]);
		i++;
	}
}

//���ɭ����Ϣ
void PrintForest(Tree* array, int len) 
{
	int i = 0;
	while (i < len)
	{
		FPrint(&array[i]);
		cout << endl;
		i++;
	}
}

//��ɭ��תΪ������
void ForestToBiTree(Tree* T, Tree* array, int len)
{
	TreeToBiTree(&array[0]);
	*T = array[0];
	Tree temp = *T;
	int i = 1;
	while (i < len)
	{
		TreeToBiTree(&array[i]);
		temp->rchild = array[i];
		temp = array[i];
		i++;
	}
}

//������תΪɭ��
void BiTreeToForest(Tree* T, Tree* array, int len)
{
	if (*T)
	{
		BiTreeToForest(&(*T)->rchild, array, len + 1);
		
		array[len] = (*T);
		if ((*T)->rchild != NULL)
			(*T)->rchild = NULL;
		BiTreeToTree(&array[len]);
	}
}


int main() 
{
	Tree T;
	CreateTree(&T);

	//�ȸ�����
	FPrint(&T);
	cout << endl;

	//����ת��Ϊ������
	TreeToBiTree(&T);
	FPrint(&T);
	cout << endl;

	//��������ת������
	BiTreeToTree(&T);
	FPrint(&T);

	//����ɭ��
	Tree forest[MAXSIZE];
	int num = 3;

	//��ʼ��ɭ��
	CreatForest(forest, num);
	PrintForest(forest, num);

	//ɭ�����ɵĶ�����
	Tree T2;
	ForestToBiTree(&T2, forest, num);
	FPrint(&T2);
	cout << endl;

	//������ת��Ϊɭ��
	Tree forest2[MAXSIZE];
	BiTreeToForest(&T2, forest2, 0);
	PrintForest(forest2, num);

	cout << "��Ҳ�½�����" << endl;
	return 0;
}