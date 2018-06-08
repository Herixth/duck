#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <cstdlib>
using namespace std;

const int maxL = 10000;

int main() {
	int T;
	cin >> T;
	while (T --) {
        int L = 0, M = 0;
        cin >> L >> M;
        char buff[L + 1] = { 0 };
        while (M --) {
        	int l = 0, r = 0;
        	cin >> l >> r;
        	for (int inc = l; inc <= r; inc ++) {
        		if (!buff[inc]) {
        			buff[inc] = '1';
				}
			}
		}
		int count = 0;
		for (int stat = 0; stat <= L; stat ++) {
			if (!buff[stat]) {
				count ++;
			}
		}
		cout << count << endl;
	}
	return 0;
}
