#include <iostream>
#include <cmath>
using namespace std;

int Single_odd(int n) {
	if (n == 1) return 1;
	else return ((int)(pow(4, n - 1)) + 2 * Single_odd(n - 1));
}

int Double_even(int n) {
	if (n == 1) return 2;
	else return 2 * (Double_even(n - 1) + Single_odd(n - 1));
}

int main() {
	int T, N;
	cin >> T;
	for (int i = 0; i < T; i ++) {
		cin >> N;
		cout << Double_even(N) << endl;
	}
	return 0;
}
