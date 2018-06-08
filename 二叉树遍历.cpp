#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<cstring>
using namespace std;
const int STACK_MAX_SIZE = 30;
const int QUEUE_MAX_SIZE = 30;
#ifndef elemType
typedef char elemType;
#endif
struct BTreeNode {
	elemType data;
	struct BTreeNode *left;
	struct BTreeNode *right;
};

void initBTree(struct BTreeNode **bt) {
	*bt = NULL;
	return;
}

void creatBTree(struct BTreeNode **bt, char *a) {
	struct BTreeNode *p;
	struct BTreeNode *s[STACK_MAX_SIZE];
	int top = -1, i = 0, k;
	*bt = NULL;
	while (a[i] != '\0') {
		switch(a[i]) {
			case ' ': break;
			case '(': 
				if (top == STACK_MAX_SIZE - 1) {
					cout << "stack is too small!" << endl;
					exit(1);
				}
				s[++top] = p;
				k = 1;
				break;
			case ')':
				if (top == -1) {
					cout << "error!" << endl;
					exit(1);
				}
				top--;
				break;
			case ',':
				k = 2;
				break;
			default:
				p = (struct BTreeNode *)malloc(sizeof(BTreeNode));
				p->data = a[i];
				p->left = p->right = NULL;
				if (*bt == NULL) {
					*bt = p;
				}else {
					if (k == 1)
						s[top]->left = p;
					else
						s[top]->right = p;
				}
		}
		i++;
	}
	return;
}

int emptyBTree(struct BTtreeNode *bt) {
	return (bt == NULL);
}

int BTreeDepth(struct BTreeNode *bt) {
	int dep1, dep2;
	if (bt == NULL)
		return 0;
	else {
		dep1 = BTreeDepth(bt->left);
		dep2 = BTreeDepth(bt->right);
		if (dep1 > dep2)
			return dep1 + 1;
		else
			return dep2 + 1;
	}
}

elemType *findBtree(struct BTreeNode *bt, elemType x) {
	elemType *p;
	if (bt == NULL)
		return NULL;
	else if (bt->data == x)
		return &(bt->data);
	else {
		if (p = findBtree(bt->left, x))
			return p;
		if (p = findBtree(bt->right, x))
			return p;
	}
	return NULL;
}

void printBTree(struct BTreeNode *bt) {
	if (bt != NULL) {
		cout << bt->data;
		if (bt->left != NULL || bt->right != NULL) {
			cout << '(';
			printBTree(bt->left);
			if (bt->right != NULL)
				cout << ',';
		}
		printBTree(bt->right);
		cout << ')';
	}
	return;
}

void clearBTree(struct BTreeNode **bt) {
	if (!bt != NULL) {
		clearBTree(&((*bt)->left));
		clearBTree(&((*bt)->right));
		free(*bt);
		*bt = NULL;
	}
	return;
}

void PreOrder(struct BTreeNode *bt) {
	if (bt != NULL) {
		cout << bt->data << ' ';
		PreOrder(bt->left);
		PreOrder(bt->right);
	}
	return;
}

void InOrder(struct BTreeNode *bt) {
	if (bt != NULL) {
		InOrder(bt->left);
		cout << bt->data << ' ';
		InOrder(bt->right);
	}
	return;
}

void PostOrder(struct BTreeNode *bt) {
	if (bt != NULL) {
		PostOrder(bt->left);
		PostOrder(bt->right);
		cout << bt->data << ' ';
	}
	return;
}

void levelorder(struct BTreeNode *bt) {
	struct BTreeNode *p;
	struct BTreeNode *q[QUEUE_MAX_SIZE];
	int front = 0, rear = 0;
	if (bt != NULL) {
		rear = (rear + 1) % QUEUE_MAX_SIZE;
		q[rear] = bt;
	}
	while (front != rear) {
		front = (front + 1) % QUEUE_MAX_SIZE;
		p = q[front];
		cout << p->data << ' ';
		if (p->left != NULL) {
			rear = (rear + 1) % QUEUE_MAX_SIZE;
			q[rear] = p->left;
		}
		if (p->right != NULL) {
			rear = (rear + 1) % QUEUE_MAX_SIZE;
			q[rear] = p->right;
		}
	}
	return;
}

int main() {
	struct BTreeNode *bt;
	char b[QUEUE_MAX_SIZE];
	elemType x, *px;
	initBTree(&bt);
	cout << "输入二叉树广义表的字符串：" << endl;
	//fgets(b, QUEUE_MAX_SIZE, stdin);
	//b[strlen(b) - 1] = '\0';
	strcpy_s(b, sizeof(b), "a(b(c),d(e(f,g),h(,i)))");
	creatBTree(&bt, b);
	if (bt != NULL)
		cout << "根节点：" << bt->data;
	cout << "以广义表的形式输出：" << endl;
	printBTree(bt);

	cout << endl << "前序：";
	PreOrder(bt);
	
	cout << endl << "中序：";
	InOrder(bt);

	cout << endl << "后序：";
	PostOrder(bt);

	cout << endl << "按层：";
	levelorder(bt);

	cout << endl << "输入一个待查找的字符：" << endl;
	cin >> x;
	px = findBtree(bt, x);
	if (px)
		cout << "查找成功：" << *px << endl;
	else
		cout << "查找失败：" << endl;

	cout << "二叉树的深度为：" << BTreeDepth(bt) << endl;
	clearBTree(&bt);
	system("Pause");
	return 0;
}