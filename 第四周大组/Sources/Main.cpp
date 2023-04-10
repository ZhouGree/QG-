#include "binary_sort_tree.h"

void visitPrint(NodePtr p) 
{
	if (p == NULL) {
		return;
	}
	printf("%d ", p->value);
	return ;
}

void showFunction() {
	printf("\n\n\n<<<Function Menu>>>\n");
	printf("   1.  初始化\n");
	printf("   2.  插入\n");
	printf("   3.  删除\n");
	printf("   4.  查询\n");
	printf("   5.  先序遍历非递归版\n");
	printf("   6.  先序遍历递归版\n");
	printf("   7.  中序遍历非递归版\n");
	printf("   8.  中序遍历递归版\n");
	printf("   9.  后序遍历非递归版\n");
	printf("   10. 后序遍历递归版\n");
	printf("   11. 层次遍历\n");
	printf("   12. 退出\n");
	printf("   请输入相应操作：");

}

int judge_int(void)
{
	int len, num = 0, arg = 1;
	char word[10] = "\0";
	int m, j = 1, k = 0;
	while (j)
	{
		scanf_s("\t\t\t\t\t%s", word, 10);
		len = strlen(word);
		for (m = 0; m < len; m++)
		{
			//出错处理，接受数字
			if (word[m] < '0' || word[m]>'9')
			{
				printf("请输入整数：");
				break;
			}
			else
			{
				if (m == len - 1)
					j = 0;
			}
		}
	}
	j = len - 1;
	//把字符换成整型
	for (m = 0; m < len; m++)
	{
		for (int i = 0; i <= j; i++)
			arg *= 10;
		num += (word[m] - '0') * arg;
		arg = 1;
		j--;
	}
	num = num / 10;
	return num;
}

int main() {
	int choice = 0, number = 0;
	BinarySortTreePtr p = NULL;
	p = (BinarySortTree*)malloc(sizeof(BinarySortTree));
	ElemType e = 8;
	//BinarySortTree pi;
	//srand((unsigned int)time(NULL));
	do {
		showFunction();
		choice = judge_int();
		system("cls");
		switch (choice) {
		case 1: 
		{
			if (BST_init(p)) {
				printf("初始化成功！\n");
			}
			else
				printf("初始化失败！\n");
			break;
		}
		case 2:
		{
			printf("1.随机插入 2.插入指定数据: ");
			choice = judge_int();
			if (choice == 1) {
				srand((unsigned int)time(NULL));
				//vector<ElemType>num;
				printf("想要插入多少个数字：");
				number = judge_int();
				for (int i = number - 1; i >= 0; i--) {
					if (BST_insert(p, rand()%100))
						printf("插入成功！\n");
					else
						printf("插入失败，该元素已存在或该二叉树为空！\n");
				}
			}
			else if (choice == 2) {
				printf("请输入要插入的数据：");
				e = judge_int();
				if (BST_insert(p, e))
					printf("插入成功！\n");
				else
					printf("插入失败，该元素已存在或该二叉树为空！\n");
			}
			else
			{
				printf("输入错误！\n");
			}
			
			break;
		}
		case 3:
		{
			printf("请输入要删除的数据：");
			e = judge_int();
			if (BST_delete(p, e))
				printf("删除成功！\n");
			else
				printf("删除失败，该二叉树为空或该数据不存在！\n");
			
			break;
		}
		case 4:
		{
			printf("请输入要查询的数据：");
			e = judge_int();
			if (BST_search(p, e))
				printf("查询成功！\n");
			else
				printf("查询失败，该二叉树为空或该数据不存在！\n");
			break;
		}
		case 5:
		{
			if(BST_preorderI(p, visitPrint) == 0)
				printf("二叉树为空！\n");
			break;
		}
		case 6:
		{
			if (p == NULL || BST_preorderR((*p).root, visitPrint) == 0)
				printf("二叉树为空！\n");
			break;
		}
		case 7:
		{
			if(BST_inorderI(p, visitPrint) == 0)
				printf("二叉树为空！\n");
			break;
		}
		case 8:
		{
			if (p == NULL || BST_inorderR((*p).root, visitPrint) == 0)
				printf("二叉树为空！\n");
			break;
		}
		case 9:
		{
			if (BST_inorderI(p, visitPrint) == 0)
				printf("二叉树为空！\n");
			break;
		}
		case 10:
		{
			if (p == NULL || BST_postorderR((*p).root, visitPrint) == 0)
				printf("二叉树为空！\n");
			break;
		}
		case 11:
		{
			if (BST_postorderI(p) == 0)
				printf("二叉树为空！\n");
			break;
		}
		case 12:
		{
			free(p);
			break;
		}
		default:
		{
			printf("请重新输入数字！（1-12）");
			break;
		}
		}
	} while (choice != 12);
}