#include<iostream>
using namespace std;

void move(int n, char a, char b) {
	cout << n << ' ' << a << ' ' << b << endl;
}

void double_color_hanoi(int n, char a = 'a', char b = 'b', char c = 'c') {
	if (!n) return;
	double_color_hanoi(n - 1, a, c, b);
	move(n, a, b);
	double_color_hanoi(n - 1, c, b, a);
}

int main() {
	int n;
	cin >> n;
	double_color_hanoi(n);
}
