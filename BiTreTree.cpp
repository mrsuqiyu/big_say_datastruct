//������ͨ�������Ļ�����
//ͨ�������������������ʶǰ���ͺ�̽ڵ�

#include<iostream>

using namespace std;

typedef char ELEMTYPE;
//enum ���͵�ʹ�÷�ʽ
typedef enum {Link, Thread}PointerTag;
enum MyEnum { a, b, c };

typedef struct BiTreNode
{
	ELEMTYPE data;
	struct BiTreNode* lchild, *rchild;
	PointerTag ltag;
	PointerTag rtag;
}BiTreNode,*BiTreTree;

//����������Ϣ�������ṹ

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


//�������������
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
//����������й�������������
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
	cout << "����ͷ�ڵ�������������������Ϊ " << endl;
	p = p->lchild;
	while (p != *T)
	{
		//���ҵ������ǰ���ڵ�
		while (p->ltag == Link)
			p = p->lchild;
		cout << p->data << " ";
		//�����ǰλ��ָ����Ǻ�������ѭ���� ������Ǻ�̾͸���rchildִ��
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

	//��������������
	BuildBiTreTree(&T);

	//����һ��ͷ�ڵ� ����ָ��ø��ڵ�
	BiTreNode p;
	p.lchild = T;
	T = &p;

	//�ҵ���һ��ǰ����������ָ����ڵ�
	BiTreTree temp = T;
	while (temp->lchild != NULL)
		temp = temp->lchild;
	temp->lchild = &p;
	temp->ltag = Thread;

	//�ҵ����ҵ�ָ��
	temp = T->lchild;
	while (temp->rchild != NULL)
		temp = temp->rchild;
	temp->rchild = &p;
	temp->rtag = Thread;


	//����˫������ķ�ʽ�������е���Ϣ
	PrintAll(&T);

	cout << "asdad" << endl;


	return 0;
}