#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<iostream>
using namespace std;

const int N = 100;
int limitw, totv, maxv;
int option[N], cop[N];
int n;

struct bag {
	int weight;
	int value;
} a[N];

void find (int i, int tw, int tv) {
	int k;
	if (tw + a[i].weight <= limitw) {
		cop[i] = 1;
		if (i < n - 1) {
			find (i + 1, tw + a[i].weight, tv);
		} else {
			for (k = 0; k < n; k ++) 
				option[k] = cop[k];
			maxv = tv;
		}
		cop[i] = 0;
	}
	if (tv - a[i].value > maxv) {
		if (i < n - 1) {
			find (i + 1, tw, tv - a[i].value);
		} else {
			for (k = 0; k < n; k ++)
				option[k] = cop[k];
			maxv = tv - a[i].value;
		}
	}
}

int main() {
	int k, w, v;
	cout << "��Ʒ������:";
	cin >> n;
	for (totv = 0, k = 0; k < n; k ++) {
		cout << endl << "��" << k + 1 << "����Ʒ�������ͼ�ֵ:";
		cin >> w >> v;
		a[k].weight = w;
		a[k].value = v;
		totv += v;
	}
	cout << endl << "������������:";
	cin >> limitw;
	maxv = 0;
	for (k = 0; k < n; k ++)
		cop[k] = 0;
	find(0, 0, totv);
	cout << endl << "��ѵķ���Ϊ:";
	for (k = 0; k < n; k ++)
		if (option[k]) 
			cout << endl << "��" << k + 1 << "����Ʒ" << endl;
	cout << endl << "�ܼ�ֵΪ" << maxv << endl;
	return 0;	
}
