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

//�����ڵ� 
LNode *Create_node(int Lnum){
      LNode *Lp;//�������ָ�� 
      Lp = (LNode *)malloc(sizeof(LNode));//���䶯̬����ռ� 
      Lp -> num = Lnum;//*Lpָ��num,��num��ֵ����Lnum
      Lp -> next = NULL;//*Lpָ����һ��Ԫ�ؽڵ�Ϊ��,ȷ��*Lp��ͷ�ڵ�ָ�� 
      return Lp;//����ͷ�ڵ�ָ�� 
}

//����ѭ������ 

LNode *Create_Linklist(LNode *pHead, int Lsum){
		int k;
		LNode *p, *temp;//��������ָ��
		for(k = 1; k <= Lsum; k ++){ //�������� 
			p = Create_node(k);
			//�������Ϊ�գ����������һ���ڵ㣬��nextָ��ָ������ 
			if(pHead == NULL){
			    temp = p; //��p��ֵ����temp
			    pHead = p; //��p��ֵ����pHead
			    temp -> next = pHead; //��*tempָ�����һ��λ��ΪpHead   
			}else{   //����ִ�в���ڵ���� 
			    p -> next = temp -> next;//�հ�ָ�����*p����,һ����һ������ 
			    temp -> next = p;
			    temp = p; //��p��ֵ�ٴ���temp
			}
		}
      
      return pHead;//����ͷָ�� 
}
//ִ�г��в��� 
void Delete_Linklist(LNode *pHead,int Lstart, int Ldel){
      int i, count = 1;//count������ 
      LNode *p, *temp;
      p = pHead;
      //�ҵ���M���������ڵ�λ�� 
      for(i = 1; i < Lstart; i ++) p = p -> next;
      cout << p - pHead << "   " << name[p - pHead] << endl;
      //ֻʣһ���ڵ�ʱ��ֹѭ�� 
      while(p -> next != p){ //�ҵ�Ҫ���к��ӵ�λ�� 
		for(i = 1; i < Ldel; i ++){
		    temp = p;
		    p = p -> next;
		}
		//ִ�г��в��� 
		temp -> next = p -> next;//��*tempָ��*p����Ľڵ� 
		record_f = p -> num;
		free(p);//�ͷ�*p
		count ++;
		//�����ߵ���һ������Ϊ�µĵ�һ�������� 
		p = temp -> next;
      }
      record_s = p -> num;
      free(p);
      //�����˾����У�ͷ�ڵ��ͷź�ֵΪ�� 
      pHead = NULL;
}

 /*������*/

int main(){
	int n, start, numb;
	
	LNode *pHead = NULL, *p;//ִ�г�ʼ������ 
	
	cin >> n;
	for (int i = 0; i < n; i ++)
		cin >> name[i];
	scanf("%d,%d", &start, &numb);
	
	p = Create_Linklist(pHead, n);//���ô��������� 
	Delete_Linklist(p, start, numb);//����ɾ�������� 
	
	if(record_f < record_s)
		printf("%d %d\n",record_f,record_s);
	else
		printf("%d %d\n",record_s,record_f);
	return 0;
}

