#include <iostream>
#include <fstream>
#include <cstring>
#include <ctype.h>
using namespace std;
const int max_num = 101;
const int max_len = 202;
char address[max_num][max_len];
char infor[max_num][max_len];
int role[max_num][max_len / 3];
int role_num[max_num];
int needsearch[max_num];

/**
 * 读入信息并处理. 
 * @param num 第几条规则 
 */
void Input_role(int num) {
	char midstr[max_len] = { 0 };
	cin >> midstr >> infor[num];
	int loc = 0;
	for (loc = 0; loc < strlen(midstr); loc ++) {
		if (midstr[loc] == '/') needsearch[num] ++;
		if (midstr[loc] == '<') break;
	}
	strncpy(address[num], midstr, loc);     //outline address
	for ( ; loc < strlen(midstr); loc ++) {
		if (midstr[loc] == '<') {
			switch (midstr[loc + 1]) {
			case 'i':
				role[num][role_num[num] ++] = 1;  // <int>
				break;
			case 's':
				role[num][role_num[num] ++] = 2;  // <str>
				break;
			case 'p':
				role[num][role_num[num] ++] = 3;  // <path>
				break;
			default: break; 
			}
		}
	}
}

/**
 * @param midstr 待解决的数组
 * @param n 规则的总数 
 */
void Solve(char midstr[], int n) {
	char addressmidstr[max_len] = { 0 };
	char store[20][50] = { 0 };
	for (int i = 0; i < n; i ++) {   // to every defined role
		memset(addressmidstr, 0, sizeof(addressmidstr));
		memset(store, 0, sizeof(store));
		int count = 0, loc;
		for (loc = 0; loc < strlen(midstr); loc ++) {
			addressmidstr[loc] = midstr[loc];
			if (midstr[loc] == '/') count ++;
			if (count == needsearch[i]) 
				break;
		} 
		loc ++;
		int lll = 0;
		if (strcmp(addressmidstr, address[i]))  // continue if not matched
			continue;	
		bool matched = true;
		for (int j = 0; j < role_num[i]; j ++) {
			switch (role[i][j]) {
			case 1:
				lll = 0;
				for ( ; loc < strlen(midstr); loc ++) {
					if (midstr[loc] == '/') {
						loc ++;
						break;
					}
					if (!isdigit(midstr[loc])) {
						matched = false;
						break;
					}
					if (!strlen(store[j]) && midstr[loc] == '0') continue;
					store[j][lll ++] = midstr[loc];
				} 
				break;
			case 2:
				lll = 0;
				for ( ; loc < strlen(midstr); loc ++) {
					if (midstr[loc] == '/') {
						loc ++;
						break;
					}
					store[j][lll ++] = midstr[loc];
				}
				break;
			case 3:
				if (!strlen(midstr + loc)) matched = false;
				strcpy(store[j], midstr + loc);
				if (store[j][strlen(store[j]) - 1] == '/') 
					store[j][strlen(store[j]) - 1] = 0;
				break;
			default: break;
			}
			if (!matched) break;
		}
		if (role[i][role_num[i] - 1] != 3 && strlen(midstr + loc)) matched = false;
		if (!matched) continue;
		cout << infor[i];
		for (int g = 0; g < role_num[i]; g ++)
			cout << " " << store[g];
		cout << endl;
		return;
	}
	cout << "404" << endl;
}

int main() {
	#ifdef DEBUG
	freopen("test.txt", "r", stdin);
	#endif
	int n, m;
	cin >> n >> m;     //role_num and op_num	
	for (int i = 0; i < n; i ++)
		Input_role(i);
	for (int j = 0; j < m; j ++) {
		char midstr[101] = { 0 };
		cin >> midstr;
		Solve(midstr, n);
	}
	return 0;
}
