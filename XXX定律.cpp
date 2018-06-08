#include <iostream>
using namespace std;

int main() {
	while (true) {
		int n;
		cin >> n;
		if (!n) break;
		int stat = 0;
		while (n != 1) {
			stat ++;
			if (n % 2) {
				n = (3 * n + 1) / 2;
			}
			else {
				n /= 2;
			}
		}
		cout << stat << endl;
	}
	return 0;
}
