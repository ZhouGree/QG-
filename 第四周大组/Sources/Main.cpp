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
	printf("   1.  ��ʼ��\n");
	printf("   2.  ����\n");
	printf("   3.  ɾ��\n");
	printf("   4.  ��ѯ\n");
	printf("   5.  ��������ǵݹ��\n");
	printf("   6.  ��������ݹ��\n");
	printf("   7.  ��������ǵݹ��\n");
	printf("   8.  ��������ݹ��\n");
	printf("   9.  ��������ǵݹ��\n");
	printf("   10. ��������ݹ��\n");
	printf("   11. ��α���\n");
	printf("   12. �˳�\n");
	printf("   ��������Ӧ������");

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
			//��������������
			if (word[m] < '0' || word[m]>'9')
			{
				printf("������������");
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
	//���ַ���������
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
				printf("��ʼ���ɹ���\n");
			}
			else
				printf("��ʼ��ʧ�ܣ�\n");
			break;
		}
		case 2:
		{
			printf("1.������� 2.����ָ������: ");
			choice = judge_int();
			if (choice == 1) {
				srand((unsigned int)time(NULL));
				//vector<ElemType>num;
				printf("��Ҫ������ٸ����֣�");
				number = judge_int();
				for (int i = number - 1; i >= 0; i--) {
					if (BST_insert(p, rand()%100))
						printf("����ɹ���\n");
					else
						printf("����ʧ�ܣ���Ԫ���Ѵ��ڻ�ö�����Ϊ�գ�\n");
				}
			}
			else if (choice == 2) {
				printf("������Ҫ��������ݣ�");
				e = judge_int();
				if (BST_insert(p, e))
					printf("����ɹ���\n");
				else
					printf("����ʧ�ܣ���Ԫ���Ѵ��ڻ�ö�����Ϊ�գ�\n");
			}
			else
			{
				printf("�������\n");
			}
			
			break;
		}
		case 3:
		{
			printf("������Ҫɾ�������ݣ�");
			e = judge_int();
			if (BST_delete(p, e))
				printf("ɾ���ɹ���\n");
			else
				printf("ɾ��ʧ�ܣ��ö�����Ϊ�ջ�����ݲ����ڣ�\n");
			
			break;
		}
		case 4:
		{
			printf("������Ҫ��ѯ�����ݣ�");
			e = judge_int();
			if (BST_search(p, e))
				printf("��ѯ�ɹ���\n");
			else
				printf("��ѯʧ�ܣ��ö�����Ϊ�ջ�����ݲ����ڣ�\n");
			break;
		}
		case 5:
		{
			if(BST_preorderI(p, visitPrint) == 0)
				printf("������Ϊ�գ�\n");
			break;
		}
		case 6:
		{
			if (p == NULL || BST_preorderR((*p).root, visitPrint) == 0)
				printf("������Ϊ�գ�\n");
			break;
		}
		case 7:
		{
			if(BST_inorderI(p, visitPrint) == 0)
				printf("������Ϊ�գ�\n");
			break;
		}
		case 8:
		{
			if (p == NULL || BST_inorderR((*p).root, visitPrint) == 0)
				printf("������Ϊ�գ�\n");
			break;
		}
		case 9:
		{
			if (BST_inorderI(p, visitPrint) == 0)
				printf("������Ϊ�գ�\n");
			break;
		}
		case 10:
		{
			if (p == NULL || BST_postorderR((*p).root, visitPrint) == 0)
				printf("������Ϊ�գ�\n");
			break;
		}
		case 11:
		{
			if (BST_postorderI(p) == 0)
				printf("������Ϊ�գ�\n");
			break;
		}
		case 12:
		{
			free(p);
			break;
		}
		default:
		{
			printf("�������������֣���1-12��");
			break;
		}
		}
	} while (choice != 12);
}