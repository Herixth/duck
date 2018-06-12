#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<cstdlib>
using namespace std;

char s[10001];
int main() {
	cin >> s;
	int len = strlen(s);
	for (int i = 0; i < len; i ++)
		if (s[i] >= 'A' && s[i] <= 'Z') s[i] += 'a' - 'A';
	for (int i = 0; i < len - 1; i ++)
		for (int j = i + 1; j < len; j ++)
			if (s[i] > s[j])
				s[i] ^= s[j] ^= s[i] ^= s[j];
	int num[27] = { 0 };
	int count = 0;
	num[0] ++;
	for (int i = 1; i < len; i ++) {
		if (s[i] == s[i - 1]) num[count] ++;
		else num[++ count] ++;
	}
	count ++;
	for (int j = 0; j < count - 1; j ++)
		for (int h = j + 1; h < count; h ++)
			if (num[j] < num[h]) 
				num[j] ^= num[h] ^= num[j] ^= num[h];
	int sum = 0;
	for (int i = 0; i < count; i ++)
		sum += (26 - i) * num[i];
	cout << sum << endl;
} 
