//利用二叉树实现哈夫曼编码的设计

#include<iostream>
#define MAXSIZE 40

using namespace std;

typedef struct HFMNode
{
	int data;
	char flag;
	struct HFMNode* lchild, * rchild;

}HFMNode, * HFMTree;


//初始化存储所有排序的数组结构 并申请节点空间
void GetHFMArray(HFMNode** array,int *len)
{
	cout << "请输入要排序的节点个数" << endl;
	int data;
	cin >> data;
	if (data == 0)
		return;
	*len = data;

	//循环输入数字并排序生成节点
	data = 0;
	while (data < *len)
	{
		int info;
		char tag;
		cout << "请输入第" << data + 1 << "个数的权重 以及 字符值" << endl;
		cin >> info >> tag;
		// 指针数组构建 
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

//对这个数组排序按照从小到大
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
	//申请树的根节点
	*T = (HFMTree)malloc(sizeof(HFMNode));

	int start = 0;
	while (start < len - 1 )
	{
		HFMTree fir = array[start];
		HFMTree sec = array[start + 1];
	
		//新建中间节点
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

//先序遍历
void PrePrint(HFMTree* T)
{
	if (*T)
	{
		cout << (*T)->data << "  " << (*T)->flag << " ";
		PrePrint(&(*T)->lchild);
		PrePrint(&(*T)->rchild);
	}
}

//输出编码结果
void GetPrintInfo(HFMTree* T, char res[], int index)
{
	if ((*T)->lchild == NULL  && (*T)->rchild == NULL)
	{
		//如果是空就可以输出结果
		res[index] = '\0';
		cout << (*T)->data << "  的字符为  " << (*T)->flag <<  " 的编码为  " <<   res << endl;
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
	HFMTree array[MAXSIZE]; //第一个地方就是这个数字的地址
	int len;
	GetHFMArray(array, &len);
	PrintArray(array,0, len);

	//从小到大排序
	SortArray(array, 0, len);
	PrintArray(array,0, len);

	//建立哈夫曼树
	HFMTree T;
	BuildTree(&T, array, len);

	cout << "先序遍历的结果为 " << endl;
	PrePrint(&T);
	cout << endl;

	char res[MAXSIZE];
	//输出编码结果
	GetPrintInfo(&T,res, 0);

	//给出字符串得出结果
	char result[MAXSIZE];
	char ques[MAXSIZE];
	cout << "请输入需要查询的编码结果 " << endl;
	cin >> ques;


	GetRES(&T, ques, result, 0);
	cout << "编码的结果为 " << result << endl;


	cout << "结果" << endl;


	return 0;
}