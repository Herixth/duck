#include <iostream>
#include <string>
#include <cstdlib>
#include <algorithm>
using namespace std;

void Standard(string &mid, int type) {
	int loc = 0;
	while (loc < mid.length()) {
		if (loc && mid[loc] == '.' && mid[loc + 1] != '.') {
			mid.erase(loc, 1);
			continue;
		}
		if (mid[loc] == '.' && mid[loc + 1] == '.') {
			if (type) {
				int loc_tmp = mid.find_last_of('/', loc - 2);
				mid.erase(loc_tmp + 1, loc + 1 - loc_tmp);
				loc = loc_tmp;
			}
			else {
				loc += 2;
			}
			continue;
		}
		if (loc && mid[loc - 1] == '/' && mid[loc] == '/') {
			mid.erase(loc, 1);
			continue;
		}
		if (mid[loc] == '/' && mid[loc + 1] == '/') {
			mid.erase(loc, 1);
			loc ++;
			continue;
		}
		loc ++;
	}
	
	if (mid[mid.length() - 1] == '/' && mid.length() - 1) {
		mid.erase(mid.length() - 1, 1);
	}
}

void Solving(const string &path_now, string &input_) {
	if (input_.empty()) {
		cout << path_now.c_str() << endl;
		return;
	}
	Standard(input_, 0);      //标准化路径 

	int loc = 0;
	string ans;
	if (input_[0] == '.') {
		ans = path_now;
	}
	while (loc < input_.length()) {
		if (input_[loc] == '.') {
			if (ans[ans.length() - 1] == '/' && ans.length() == 1) {
				loc += 3;
				continue;
			}
			if (ans[ans.length() - 1] == '/') {
				ans.erase(ans.length() - 1, 1);
			}
			int loc_x = ans.find_last_of("/");
			ans.erase(loc_x + 1, ans.length() - loc_x - 1);
			
			
			loc += 3;
		}
		else {
		    int loc_tmp = input_.find_first_of(".", loc);
		    loc_tmp = loc_tmp == string::npos ? input_.length() : loc_tmp;
		    
			for (int tmp = loc; tmp < loc_tmp; tmp ++) {
				ans += input_[tmp];
			}			
			
			loc = loc_tmp;
		}
	}
	
	while (ans.length() - 1 && ans[ans.length() - 1] == '/') {
		ans.erase(ans.length() - 1, 1);
	}
	cout << ans.c_str() << endl;
	return;
}

int main() {
#ifdef DEBUG
	freopen("path_data.txt", "r", stdin);
#endif	
	int num = 0;
	string path_now;
	cin >> num;
	char tmp = getchar();   //eat enter
	getline(cin, path_now);
	Standard(path_now, 1);
	
	
	for (int inc = 0; inc < num; inc ++) {
		string input_;
		getline(cin, input_);
		
		Solving(path_now, input_);
	}
	
	
	return 0;
}
