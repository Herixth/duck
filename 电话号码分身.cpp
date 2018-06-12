#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<iostream>
using namespace std;

int main() {
	int T;
	cin >> T;
	for (int h = 0; h < T; h ++) {
		char mid[10001] = { 0 };
		int num[3000] = { 0 };
		cin >> mid;
		int loc = 0, count = 0;
		while (loc != strlen(mid)) {
			switch (mid[loc]) {
				case 'Z':
					loc += 4;
					num[count] = 2;
					break;
				case 'O':
					loc += 3;
					num[count] = 3;
					break;
				case 'E':
					loc += 5;
					num[count] = 0;
					break;
				case 'N':
					loc == 4;
					num[count] = 1;
					break;
				case 'T':
					loc += 3 + 2 * (mid[loc + 1] == 'T');
					mid[loc + 1] == 'T' ? num[count] = 5 : num[count] = 4;
					break;
				case 'F':
					loc += 4;
					mid[loc + 1] = 'O' ? num[count] = 6 : num[count] = 7;
					break;
				case 'S':
					loc += 3 + 2 * (mid[loc + 1] == 'E');
					mid[loc + 1] == 'E' ? num[count] = 9 : num[count] = 8;
					break;
				default: break;
			}
			count ++;
		}
		for (int i = 0; i < count - 1; i ++) 
			for (int j = i + 1; j < count; j ++)
				if (num[i] > num[j])
					num[i] ^= num[j] ^= num[i] ^= num[j];
		for (int i = 0; i < count; i ++)
			cout << num[i];
		cout << endl;
	}
	return 0;
}
