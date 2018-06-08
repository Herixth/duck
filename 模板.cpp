#include <iostream>
#include <cstring>
#include <string>
using namespace std;

template <class Type1, class Type2> 
bool Is_Bigger(Type1 &a, Type2 &b) {
	return a > b;
}

int main() {
	string a = "1111";
	string b = "2222";
	cout << Is_Bigger(b, a);
	return 0;
}
