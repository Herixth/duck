#include <iostream>
#include <cmath>
#include <cstring>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <cctype>
using namespace std;

const int maxn = 1e2 + 1;


int N, M;

vector<string> add_parts;

bool is_int(string &str) {
	bool head = true;
	for (string::iterator tmp = str.begin(); tmp != str.end(); ) {
		if (isdigit(*tmp)) {
			if (head && *tmp == '0') {
				tmp = str.erase(tmp);
			}
			else {
				head = false;
				tmp ++;
			}
		}
		else {
			return false;
		}
	}
	return true;
}

bool is_str(string &str) {
	return !str.empty() && str.find('/', 0) == string::npos;
}

bool is_path(string &str) {
	return !str.empty();
}

void whole_to_parts(vector<string> &parts,const string &whole) {
	int loc_head = 1;
	int loc_back = 1;
	int len = whole.length();
	while ((loc_back = whole.find_first_of('/', loc_head)) != string::npos) {
		parts.push_back(whole.substr(loc_head, loc_back - loc_head));
		cout << parts.back().c_str() << endl;
		loc_head = ++ loc_back;
	}
	if (loc_head < len) {
		parts.push_back(whole.substr(loc_head, len - loc_head).c_str());
	}
}

struct Role {
	vector<string> parts;
	string obj;
	Role () { 
		parts.clear();
		add_parts.clear();
	}
	
	void read_in(string whole, string obj__) {
		this->obj = obj__;
		whole_to_parts(parts, whole);
	}
	
	bool matching() {
		vector<string> param;
		if (add_parts.size() < parts.size()) return false;
		vector<string>::iterator add_it = add_parts.begin();
		for (vector<string>::iterator rol = parts.begin(); rol != parts.end(); rol ++) {
			if ((*rol)[0] != '<') {
				if (*rol != *add_it) return false;
			}
			else {
				string pas;
				switch ((*rol)[1]) {
				case 'i':
					if (!is_int(*add_it))
						return false;
					param.push_back(*add_it);
					break;
				case 's':
					if (!is_str(*add_it)) 
						return false;
					param.push_back(*add_it);
					break;
				case 'p':
					if (!is_path(*add_it))
						return false;
					while (add_it != add_parts.end()) {
						if (add_it + 1 == add_parts.end())
							pas += *add_it;
						else
							pas += *add_it + "/";
						add_it ++;
					}
					param.push_back(pas);
					printf("%s", obj.c_str());
					
					for (vector<string>::iterator ans = param.begin(); ans != param.end(); ans ++) {
						printf(" %s", (*ans).c_str());
					}
					printf("\n");
					
					return true;
					break;
				default:
					break;
				}
			}
			add_it ++;
			if (add_it == add_parts.end()) {
				if (rol + 1 == parts.end()) {
					printf("%s", obj.c_str());	
					for (vector<string>::iterator ans = param.begin(); ans != param.end(); ans ++) {
						printf(" %s", (*ans).c_str());
					}
					printf("\n");	
					return true;			
				}
				else 
					return false;
			}
		}
		return false;
	}
} role[maxn];

void read_roles() {
	scanf("%d%d\n", &N, &M);
	for (int inc = 0; inc < N; inc ++) {
		char role_[maxn] = { 0 };
		char obj__[maxn] = { 0 };
		scanf("%s %s", role_, obj__);
		role[inc].read_in(string(role_), string(obj__));
	}
}

void match_add() {
	for (int add_ = 0; add_ < M; add_ ++) {
		char add[maxn] = { 0 };
		scanf("%s", add);
		string adds(add);
		add_parts.clear();
		whole_to_parts(add_parts, adds);
		
//		for (vector<string>::iterator pa = add_parts.begin(); pa != add_parts.end(); pa ++) {
//			cout << (*pa).c_str() << endl;
//		}
		
		bool result = false;
		for (int role_order = 0; role_order < N; role_order ++) {
			result = role[role_order].matching();		
			if (result) break;
		}
		if (!result) printf("404\n");
	}
}

int main() {
#ifdef DEBUG
	freopen("test.txt", "r", stdin);
#endif
	read_roles();
		
	match_add();
	
	return 0;
}
