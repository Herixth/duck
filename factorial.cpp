#include <iostream>
using namespace std;

class Factorial {
public:
	Factorial(int n) : n(n) { }
	
	~Factorial() { /*DO NOTHING*/ }
	
	int GetFct() {
		int ans = 1;
		for (int inc = 2; inc <= n; inc ++) {
			ans *= inc;
		}
		return ans;
	}
private:
	int n;
};

int main() {
	
	for (int inc = 2; inc <= 9; inc ++) {
		Factorial fct(inc);
		cout << inc << "! = " << fct.GetFct() << endl;
	}
	
	return 0;
}
