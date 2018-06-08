#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	string s = "226";
	vector<int> ans(1, 1);
	for (int inc = 1; inc < s.length(); inc ++) {
		cout << "back " << ans.back() << endl;
		ans.push_back(ans.back() + 1 + (s[inc] + s[inc - 1] * 10 <= 26));
	}
	cout << ans.back() << endl;
	return 0;
}
