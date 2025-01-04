//树 森林 二叉树之间的转换
#include<iostream>
#define MAXSIZE 40

using namespace std;

typedef struct Node
{
	char data;
	struct Node* lchild, * mchild, * rchild;
}Node,* Tree;


//创建树结构
void CreateTree(Tree * T)
{
	char data;
	cout << "输入节点信息" << endl;
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

//先根遍历
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

//树转化为二叉树
void TreeToBiTree(Tree* T)
{
	if (*T)
	{
		//先到最左的节点
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

//二叉树转换为树
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

//利用数组构造森林
void CreatForest(Tree* array, int len) 
{
	int i = 0;
	while (i < len)
	{
		cout << "请输入第" << i + 1 << " 个树的信息" << endl;
		CreateTree(&array[i]);
		i++;
	}
}

//输出森林信息
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

//将森林转为二叉树
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

//二叉树转为森岭
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

	//先根遍历
	FPrint(&T);
	cout << endl;

	//将树转换为二叉树
	TreeToBiTree(&T);
	FPrint(&T);
	cout << endl;

	//将二叉树转换成树
	BiTreeToTree(&T);
	FPrint(&T);

	//构建森林
	Tree forest[MAXSIZE];
	int num = 3;

	//初始化森林
	CreatForest(forest, num);
	PrintForest(forest, num);

	//森林生成的二叉树
	Tree T2;
	ForestToBiTree(&T2, forest, num);
	FPrint(&T2);
	cout << endl;

	//二叉树转换为森林
	Tree forest2[MAXSIZE];
	BiTreeToForest(&T2, forest2, 0);
	PrintForest(forest2, num);

	cout << "我也奥结束了" << endl;
	return 0;
}