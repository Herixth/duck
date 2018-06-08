#include <iostream>
#include <cstring>
using namespace std;

int main() {
	long long minx = 0;
	long long step = 0;
	int n;
	cin >> n;
	for (int inc = 0; inc < n; inc ++) {
		long num = 0;
		cin >> num;
		step += num;
		if (step < minx) {
			minx = step;
		}
	}
	cout << -minx << endl;
	return 0;
}
