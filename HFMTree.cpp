//���ö�����ʵ�ֹ�������������

#include<iostream>
#define MAXSIZE 40

using namespace std;

typedef struct HFMNode
{
	int data;
	char flag;
	struct HFMNode* lchild, * rchild;

}HFMNode, * HFMTree;


//��ʼ���洢�������������ṹ ������ڵ�ռ�
void GetHFMArray(HFMNode** array,int *len)
{
	cout << "������Ҫ����Ľڵ����" << endl;
	int data;
	cin >> data;
	if (data == 0)
		return;
	*len = data;

	//ѭ���������ֲ��������ɽڵ�
	data = 0;
	while (data < *len)
	{
		int info;
		char tag;
		cout << "�������" << data + 1 << "������Ȩ�� �Լ� �ַ�ֵ" << endl;
		cin >> info >> tag;
		// ָ�����鹹�� 
		array[data] = (HFMNode*)malloc(sizeof(HFMNode));
		if (array[data])
		{
			array[data]->data = info;
			array[data]->flag = tag;
			array[data]->lchild = NULL;
			array[data]->rchild = NULL;
		}
		data++;
	}
}

void PrintArray(HFMTree* array, int start, int len)
{
	for (int i = start; i < len; i++)
	{
		cout << array[i]->data << " ";
	}
	cout << endl;
}

//��������������մ�С����
void SortArray(HFMTree* array, int start, int len)
{
	for (int i = 0; i < len - 1; i++)
	{
		for (int j = start; j < len - i - 1; j++)
		{ 
			if (array[j]->data > array[j + 1]->data)
			{
				HFMTree temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
			}
		}
	}
}

void BuildTree(HFMTree* T,HFMTree* array, int len) 
{
	//�������ĸ��ڵ�
	*T = (HFMTree)malloc(sizeof(HFMNode));

	int start = 0;
	while (start < len - 1 )
	{
		HFMTree fir = array[start];
		HFMTree sec = array[start + 1];
	
		//�½��м�ڵ�
		HFMTree temp = (HFMTree)malloc(sizeof(HFMNode));
		if (temp)
		{
			temp->data = fir->data + sec->data;
			temp->lchild = fir;
			temp->rchild = sec;

			start++;
			array[start] = temp;
		}
		SortArray(array, start, len);
	}
	cout << array[start]->data << endl;
	*T = array[start];
}

//�������
void PrePrint(HFMTree* T)
{
	if (*T)
	{
		cout << (*T)->data << "  " << (*T)->flag << " ";
		PrePrint(&(*T)->lchild);
		PrePrint(&(*T)->rchild);
	}
}

//���������
void GetPrintInfo(HFMTree* T, char res[], int index)
{
	if ((*T)->lchild == NULL  && (*T)->rchild == NULL)
	{
		//����ǿվͿ���������
		res[index] = '\0';
		cout << (*T)->data << "  ���ַ�Ϊ  " << (*T)->flag <<  " �ı���Ϊ  " <<   res << endl;
		return;
	}
	else
	{
		res[index] = '0';
		GetPrintInfo(&(*T)->lchild, res, index + 1);
		res[index] = '1';
		GetPrintInfo(&(*T)->rchild, res, index + 1);
	}
}


void GetRES(HFMTree* T,char* que,char *resu, int index) 
{
	HFMTree p = *T;
	int len = strlen(que);

	int i = 0;
	HFMTree res = *T;
	while (i < len) 
	{
		if (que[i] == '1')
			res = res->rchild;
		if (que[i] == '0')
			res = res->lchild;
		
		if (res->lchild == NULL && res->rchild == NULL)
		{
			resu[index++] = res->flag;
			res = *T;
		}
		i++;
	}
	resu[index] = '\0';
}


int main4() 
{
	HFMTree array[MAXSIZE]; //��һ���ط�����������ֵĵ�ַ
	int len;
	GetHFMArray(array, &len);
	PrintArray(array,0, len);

	//��С��������
	SortArray(array, 0, len);
	PrintArray(array,0, len);

	//������������
	HFMTree T;
	BuildTree(&T, array, len);

	cout << "��������Ľ��Ϊ " << endl;
	PrePrint(&T);
	cout << endl;

	char res[MAXSIZE];
	//���������
	GetPrintInfo(&T,res, 0);

	//�����ַ����ó����
	char result[MAXSIZE];
	char ques[MAXSIZE];
	cout << "��������Ҫ��ѯ�ı����� " << endl;
	cin >> ques;


	GetRES(&T, ques, result, 0);
	cout << "����Ľ��Ϊ " << result << endl;


	cout << "���" << endl;


	return 0;
}