#include <iostream>
#include <cmath>
using namespace std;

class Integer {
public:
	Integer(int n) : d(n) { }
	
	~Integer() { /*DO NOTHING*/ }
	
	int GetD() { return d; }
	
	void SetD(int n) { d = n; }
	
	bool IsOdd() { return !(d % 2); }
	
	bool IsPrime() {
		for (int inc = 2; inc <= (int)sqrt(d); inc ++) {
			if (!(d % inc)) {
				return false;
			}
		}
		return true;
	}
private:
	int d;			
};

int main() {
	Integer test01(15);
	Integer test02(31);
	cout << "num01: " << test01.GetD() << endl;
	test01.SetD(17);
	cout << "num01: " << test01.GetD() << endl;
	cout << "IsOdd: " << (test01.IsOdd() ? "Yes" : "No") << endl;
	cout << "IsPrime: " << (test01.IsPrime() ? "Yes" : "No") << endl << endl;
	
	cout << "num02: " << test02.GetD() << endl;
	test02.SetD(32);
	cout << "num02: " << test02.GetD() << endl;
	cout << "IsOdd: " << (test02.IsOdd() ? "Yes" : "No") << endl;
	cout << "IsPrime: " << (test02.IsPrime() ? "Yes" : "No") << endl;
}
