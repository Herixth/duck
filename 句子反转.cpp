#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<iostream>
using namespace std;

int main() {
	char sen[100] = { 0 };
	fgets(sen, sizeof(sen), stdin);
	sen[strlen(sen) - 1] = '\0';
	
	int count = 0;
	for (int i = 0; i < strlen(sen); i ++) if (sen[i] == ' ') count ++;
	int loc1 = strlen(sen), loc2 = strlen(sen);
	for (int j = 0; j < count; j ++) {
		for ( ; ; loc1 --) if (sen[loc1] == ' ') break;
		for (int i = loc1 + 1; i < loc2; i ++)
			cout << sen[i];
		cout << ' ';
		loc2 = loc1 --;
	}
	for (int i = 0; i < loc2; i ++)
	cout << sen[i];
	cout << endl;
	
	return 0;
}
