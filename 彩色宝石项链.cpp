#include<string>
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;

int main() {
	string list;
	while (cin >> list) {
		vector<int> store, store1, store2;
		int len = list.length();
		list += list;
		for (int i = 0; i < len; i ++) {
			if (list[i] < 'A' || list[i] > 'E') continue;
			int count = 0, j;
			char wa[5] = {'A', 'B', 'C', 'D', 'E'};
			for (j = i; j < len + 5; j ++) {
				if (list[j] >= 'A' && list[j] <= 'E') {
					for (int h = 0; h < 5; h ++) 
						if (wa[h] == list[j]) {
							wa[h] = '1';
							count ++;
							break;
						}
				}
				if (count == 5) break;
			}
			if (count != 5) continue;
			store.push_back(j - i + 1);
			store1.push_back(i);
			store2.push_back(j);
		}
		if (store.begin() == store.end()) {
			cout << len << endl;
		} else {
			int min = store.front(), loc = 0;
			for (int i = 1; i < store.size(); i ++) min > store[i] ? min = store[i], loc = i : min = min;		
			cout << len - min << endl;
//			cout << "区间" << store1[loc] << "  " << store2[loc]  << " 长度" << len << endl;
//			for (int i = store1[loc]; i <= store2[loc]; i ++)
//			cout << list[i] << " ";
//			cout << endl;
		}
		list.clear();
	}
	return 0;
}
