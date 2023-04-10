#include "binary_sort_tree.h"

typedef struct LSNode {
	NodePtr node;//数据域
	struct LSNode* next;//指针域

}LSNode, * LStack;//结点和链栈类型

typedef struct LinkStack {
	LStack top;//栈顶指针
}LinkStack;

Status initLStack(LinkStack* s) {
	(*s).top = (LSNode*)malloc(sizeof(LSNode));
	if ((*s).top == NULL) {
		printf("分配内存失败，未完成初始化！\n");
		return false;
	}
	(*s).top->node = (Node*)malloc(sizeof(Node));
	if ((*s).top->node == NULL) {
		printf("分配内存失败，未完成初始化！\n");
		return false;
	}
	(*s).top->node->value = 0;
	(*s).top->node->left = NULL;
	(*s).top->node->right = NULL;
	(*s).top->next = NULL;
	return true;
}

Status pushLStack(LinkStack* s, NodePtr NodeTemp) {
	if (s == NULL) {
		return false;
	}
	
	if ((*s).top->node->value==0) {
		(*s).top->node = NodeTemp;
		return true;
	}
	//先分配内存
	LSNode* t = (LSNode*)malloc(sizeof(LSNode));
	if (t == NULL) {
		return false;
	}
	t->node = (Node*)malloc(sizeof(Node));
	if (t->node == NULL) {
		return false;
	}
	t->node->left = NodeTemp->left;
	t->node->right = NodeTemp->right;
	t->node->value = NodeTemp->value;
	t->next = (*s).top;
	//栈顶指向新入栈的节点
	(*s).top = t;
	return true;
}

Status popLStack(LinkStack* s) {
	if ((*s).top == NULL) {
		return false;
	}
	LSNode* t = (*s).top;
	//栈顶下移
	(*s).top = (*s).top->next;
	//删除
	free(t);
	return true;
}

Status BST_init(BinarySortTreePtr p) {
	//开辟存储空间
	(*p).root = (Node*)malloc(sizeof(Node));
	if ((*p).root == NULL) {
		return false;
	}
	//初始化
	(*p).root->left = NULL;
	(*p).root->right = NULL;
	(*p).root->value = 0;
	return true;
}

Status BST_insert(BinarySortTreePtr p, ElemType e) {
	if ((*p).root != NULL) {
		NodePtr temp = (*p).root;
		//如果根的值为0，说明二叉树只是初始化，所以将其值插入根结点
		if (temp->value == 0) {
			temp->value = e;
			return true;
		}
		//foretemp为temp的上一结点，用于确定temp的位置
		NodePtr foretemp = (*p).root;
		//遍历二叉树，如果找到相同的值则不插入
		while (temp != NULL) {
			if (e > temp->value && temp != NULL) {
				foretemp = temp;
				temp = temp->right;
				continue;
			}
			else if (e < temp->value && temp != NULL)
			{
				foretemp = temp;
				temp = temp->left;
				continue;
			}
			else
			{
				return false;
			}
		}
		temp = (Node*)malloc(sizeof(Node));
		if (temp == NULL) {
			return false;
		}
		//插入
		temp->value = e;
		temp->left = NULL;
		temp->right = NULL;
		if (e > foretemp->value) {
			foretemp->right = temp;
		}
		else
		{
			foretemp->left = temp;
		}
		return true;
	}
	return false;
}

Status BST_delete(BinarySortTreePtr p, ElemType e) {
	if ((*p).root != NULL) {
		NodePtr temp = (*p).root, foretemp = (*p).root, lasttemp = (*p).root, nulltemp = (*p).root;
		int con = 0;
		while (temp != NULL) 
		{
			if (e == temp->value) 
			{
				if (temp->right != NULL) 
				{
					if (temp->right->left == NULL) {
						if (con == 0)
						{
							p->root = temp->right;
							p->root->left = temp->left;
						}
						else if (con == 1)
						{
							foretemp->left = temp->right;
							foretemp->left->left = temp->left;
						}
						else
						{
							foretemp->right = temp->right;
							foretemp->right->left = temp->left;
						}
						free(temp);
						return true;
					}
					else
					{
						nulltemp = temp->right;
						lasttemp = temp->right->left;
						while (lasttemp->left != NULL || lasttemp->right != NULL) {
							nulltemp = lasttemp;
							if (lasttemp->left != NULL)
								lasttemp = lasttemp->left;
							else
								lasttemp = lasttemp->right;
						}
						if (con == 0)
						{
							p->root = lasttemp;
							p->root->right = temp->right;
							p->root->left = temp->left;
						}
						else if (con == 1)
						{
							foretemp->left = lasttemp;
							foretemp->left->right = temp->right;
							foretemp->left->left = temp->left;
						}
						else
						{
							foretemp->right = lasttemp;
							foretemp->right->right = temp->right;
							foretemp->right->left = temp->left;
						}
						nulltemp->left = NULL;
						nulltemp->right = NULL;
						free(temp);
						return true;
					}
				}
				else 
				{
					//删除没有左右孩子的结点
					if (temp->left == NULL) 
					{
						 
						if (con == 0)
						{
							(*p).root = NULL;
						}
						else if (con == 1)
						{
							foretemp->left = temp->left;
						}
						else
							foretemp->right = temp->left;
						free(temp);
						return true;
					}
					else
					{
						//
						if (temp->left->right == NULL) 
						{
							if (con == 0)
								p->root = temp->left;
							else if (con == 1)
								foretemp->left = temp->left;
							else
								foretemp->right = temp->left;
							free(temp);
							return true;
						}
						else
						{
							nulltemp = temp->left;
							lasttemp = temp->left->right;
							while (lasttemp->left != NULL || lasttemp->right != NULL)
							{
								nulltemp = lasttemp;
								if (lasttemp->right != NULL)
									lasttemp = lasttemp->right;
								else
									lasttemp = lasttemp->left;
							}
							
							if (con == 0)
							{
								p->root = lasttemp;
								p->root->left = temp->left;
								p->root->right = temp->right;
							}
							else if (con == 1)
							{
								foretemp->left = lasttemp;
								foretemp->left->left = temp->left;
								foretemp->left->right = temp->right;
							}
							else
							{
								foretemp->right = lasttemp;
								foretemp->right->left = temp->left;
								foretemp->right->right = temp->right;
							}
							nulltemp->left = NULL;
							nulltemp->right = NULL;
							free(temp);
							return true;
						}
					}
				}
			}
			foretemp = temp;
			if (e > temp->value) 
			{
				temp = temp->right;
				con = 2;
			}
			else if (e < temp->value) 
			{
				temp = temp->left;
				con = 1;
			}
		}
		return false;
	}
	return false;
}

Status BST_search(BinarySortTreePtr p, ElemType e) {
	if ((*p).root != NULL) {
		NodePtr temp = (*p).root;
		while (temp != NULL) {
			if (e > temp->value) {
				temp = temp->right;
			}
			else if (e < temp->value) {
				temp = temp->left;
			}
			else
			{
				printf("%d\n", temp->value);
				return true;
			}
		}
		return false;
	}
	return false;
}

Status BST_preorderI(BinarySortTreePtr p, void (*visit)(NodePtr node)) {
	if ((*p).root != NULL) {
		NodePtr temp = (*p).root;
		//LinkStack* s = (LinkStack*)malloc(sizeof(LinkStack));
		//assert(s);
		//initLStack(s);
		
		stack<NodePtr>s;
		//根结点先入栈
		s.push(temp);
			
			while (!s.empty()) {
				//记住栈顶结点
				temp = s.top();
				
				visit(temp);
				//出栈
				s.pop();
				//根据出栈的结点，将它的左右孩子入栈（右孩子先入栈）
				if (temp->right != NULL) {
					s.push(temp->right);
				}
				if (temp->left != NULL) {
					s.push(temp->left);
				}
			}
			return true;
	}
	return false;
}

Status BST_preorderR(NodePtr root, void (*visit)(NodePtr node)) {
	if (root != NULL) {
		visit(root);
		BST_preorderR(root->left,visit);
		BST_preorderR(root->right, visit);
		return true;
	}
	return false;
}

Status BST_inorderI(BinarySortTreePtr p, void (*visit)(NodePtr node)) {
	if ((*p).root != NULL) {

		NodePtr temp = (*p).root;
		/*LinkStack* s = (LinkStack*)malloc(sizeof(LinkStack));
		assert(s);
		initLStack(s);
		while (temp != NULL) {
			while (temp->left != NULL)
			{
				pushLStack(s, temp->left);
				temp = temp->left;
			}
			visit(temp);
			while (temp->right == NULL) {
				temp = (*s).top->node;
				visit(temp);
				popLStack(s);
				if ((*s).top == NULL) {
					return true;
				}
			}
			//visit(temp->right);
			temp = temp->right;
		}*/
		
		//vector<ElemType>vec;


		//p不为空

		stack<NodePtr>s;
		//p不为空 或栈不为空
		while (temp != NULL || !s.empty()) {
			//根结点先入栈
			if (temp != NULL) {
				s.push(temp);
				//为了让左孩子先入栈
				temp = temp->left;
			}
			else {
				//原先的temp无左孩子，则出栈
				temp = s.top(); 
				s.pop();
				visit(temp);
				//为了让右孩子入栈
				temp = temp->right;
			}
		}
		return true;
	}
	return false;
}

Status BST_inorderR(NodePtr root, void (*visit)(NodePtr node)) {
	if (root != NULL) {
		BST_inorderR(root->left, visit);
		visit(root);
		BST_inorderR(root->right, visit);
		return true;
	}
	return false;
}

Status BST_postorderI(BinarySortTreePtr p) {
	if ((*p).root != NULL) {
		NodePtr temp = (*p).root;
		stack<NodePtr>s;
		s.push(temp);
		vector<ElemType>v;
		//将先序遍历的无递归版的左右孩子入栈序列调换，则得到后序遍历的逆顺序，将存入数组，从后往前输出
		while (!s.empty()) {
			temp = s.top();

			//visit(temp);
			v.push_back(temp->value);
			s.pop();
			
			if (temp->left != NULL) {
				s.push(temp->left);
			}
			if (temp->right != NULL) {
				s.push(temp->right);
			}
		}
		for (int i = v.size()-1; i >= 0; i--) {
			printf("%d ", v[i]);
		}
		return true;
	}
	return false;
}

Status BST_postorderR(NodePtr root, void (*visit)(NodePtr node)) {
	if (root != NULL) {
		BST_postorderR(root->left, visit);
		BST_postorderR(root->right, visit);
		visit(root);
		return true;
	}
	return false;
}

Status BST_levelOrder(BinarySortTreePtr p, void (*visit)(NodePtr node)) {
	if ((*p).root != NULL) {
		NodePtr temp = (*p).root;
		std::queue<NodePtr> Nqueue;
		//根节点先入队
		Nqueue.push(temp);
		while ( ! Nqueue.empty())
		{
			//出队
			temp = Nqueue.front();
			visit(temp);
			Nqueue.pop();
			//出队的结点的左右孩子先后入队
			if (temp->left != NULL) {
				Nqueue.push(temp->left);
			}
			if (temp->right != NULL) {
				Nqueue.push(temp->right);
			}
		}

		return true;
	}
	return false;
}