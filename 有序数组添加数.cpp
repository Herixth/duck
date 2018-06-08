#include <iostream>
#include <cstring>
using namespace std;

int main() {
	int list[4] = {1, 3, 5, 7};
	int n;
	cin >> n;
	for (int inc = 0; inc < 4; inc ++) {
		if (list[inc] > n) {
			cout << n << " ";
			n = 8;
		}
		cout << list[inc] << " ";
	}
	cout << endl;
	return 0;
}
