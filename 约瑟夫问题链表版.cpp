#include <stdio.h>
#include <iostream>
#include <math.h>
#include <string.h>
#include <stdlib.h>
using namespace std;

char name[65][20];
int record_f, record_s;

typedef struct LNode{
      int num;
      struct LNode *next;
}LNode;

//创建节点 
LNode *Create_node(int Lnum){
      LNode *Lp;//创建结点指针 
      Lp = (LNode *)malloc(sizeof(LNode));//分配动态储存空间 
      Lp -> num = Lnum;//*Lp指向num,把num的值传给Lnum
      Lp -> next = NULL;//*Lp指向下一个元素节点为空,确定*Lp是头节点指针 
      return Lp;//返回头节点指针 
}

//创建循环链表 

LNode *Create_Linklist(LNode *pHead, int Lsum){
		int k;
		LNode *p, *temp;//创建两个指针
		for(k = 1; k <= Lsum; k ++){ //遍历链表 
			p = Create_node(k);
			//如果链表为空，创建链表第一个节点，其next指针指向自身 
			if(pHead == NULL){
			    temp = p; //把p的值传给temp
			    pHead = p; //把p的值传给pHead
			    temp -> next = pHead; //让*temp指向的下一个位置为pHead   
			}else{   //否则执行插入节点操作 
			    p -> next = temp -> next;//空白指针跟着*p后面,一个接一个插入 
			    temp -> next = p;
			    temp = p; //把p的值再传给temp
			}
		}
      
      return pHead;//返回头指针 
}
//执行出列操作 
void Delete_Linklist(LNode *pHead,int Lstart, int Ldel){
      int i, count = 1;//count计数器 
      LNode *p, *temp;
      p = pHead;
      //找到第M个孩子坐在的位置 
      for(i = 1; i < Lstart; i ++) p = p -> next;
      cout << p - pHead << "   " << name[p - pHead] << endl;
      //只剩一个节点时终止循环 
      while(p -> next != p){ //找到要出列孩子的位置 
		for(i = 1; i < Ldel; i ++){
		    temp = p;
		    p = p -> next;
		}
		//执行出列操作 
		temp -> next = p -> next;//让*temp指向*p后面的节点 
		record_f = p -> num;
		free(p);//释放*p
		count ++;
		//出列者的下一个孩子为新的第一个报数者 
		p = temp -> next;
      }
      record_s = p -> num;
      free(p);
      //所有人均出列，头节点释放后赋值为空 
      pHead = NULL;
}

 /*主函数*/

int main(){
	int n, start, numb;
	
	LNode *pHead = NULL, *p;//执行初始化操作 
	
	cin >> n;
	for (int i = 0; i < n; i ++)
		cin >> name[i];
	scanf("%d,%d", &start, &numb);
	
	p = Create_Linklist(pHead, n);//调用创建链表函数 
	Delete_Linklist(p, start, numb);//调用删除链表函数 
	
	if(record_f < record_s)
		printf("%d %d\n",record_f,record_s);
	else
		printf("%d %d\n",record_s,record_f);
	return 0;
}

