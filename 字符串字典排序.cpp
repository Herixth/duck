#include<iostream>
#include<cstdlib>
#include<cstring>
#include<string>
using namespace std;

int cmp(const void *a, const void *b) {
	return strcmp((char *)a, (char *)b);
}

int main() {
	char str[3][10] = { 0 };
	for (int i = 0; i < 3; i ++)
		cin >> str[i];
	qsort(str, 3, 10, cmp);
	for (int i = 0; i < 3; i ++)
		cout << str[i] << endl;
	return 0;
}
