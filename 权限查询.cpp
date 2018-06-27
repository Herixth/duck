#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

#define __FALSE__ -1
#define __TRUE__  -2

/**
 * /
 * @param category standard_module
 */
void set_category(map<string, int> &category) {
	int num = 0;
	cin >> num;
	while (num --) {
		string msg;
		cin>> msg;
		unsigned int find_result = msg.find(':');
		string cate = string(msg, 0, find_result);
		int level   = find_result == string::npos ? -1 : atoi(string(msg, find_result + 1).c_str());
		if (!(category.find(cate) != category.end() && level <= category[cate])) {
			category[cate] = level;
		}
	}
}

/**
 * /
 * @param role     role_name to it's categories(map)
 * @param category standard_module
 */
void set_role(map<string, map <string, int> > &role, map<string, int> &category) {
	int num = 0;
	cin >> num;
	while (num --) {
		string role_name;
		cin >> role_name;
		int cate_num = 0;
		cin >> cate_num;
		map<string, int> cate_tmp;
		while (cate_num --) {
			string msg;
			cin>> msg;
			unsigned int find_result = msg.find(':');
			string cate = string(msg, 0, find_result);
			int level   = find_result == string::npos ? -1 : atoi(string(msg, find_result + 1).c_str());
			level = level > category[cate] ? category[cate] : level;
			if (!(cate_tmp.find(cate) != cate_tmp.end() && level <= cate_tmp[cate])) {
				cate_tmp[cate] = level;
			}
		}
		role[role_name] = cate_tmp;

		/*for (map<string, int>::iterator tmp = cate_tmp.begin(); tmp != cate_tmp.end(); tmp ++) {
			cout << tmp -> first << " -> " << tmp -> second << endl;
		}
		cout << endl;*/
	}
}

/**
 * /
 * @param user user_name to it's categories(map)
 * @param role lower level module
 */
void set_user(map<string, map <string, int> > &user, map<string, map <string, int> > &role) {
	int num = 0;
	cin >> num;
	while (num --) {
		string user_name;
		cin >> user_name;
		int role_num = 0;
		cin >> role_num;
		map<string, int> cate_tmp;
		while (role_num --) {
			string role_name;
			cin >> role_name;
			for (map<string, int>::iterator tmp = role[role_name].begin(); tmp != role[role_name].end(); tmp ++) {
				if (!(cate_tmp.find(tmp -> first) != cate_tmp.end() && cate_tmp[tmp -> first] >= tmp -> second)) {
					cate_tmp[tmp -> first] = tmp -> second;
				}
			}
		}
		user[user_name] = cate_tmp;
	}
}

void search(map<string, map <string, int> > &user) {
	int num = 0;
	cin >> num;
	while (num --) {
		string user_name;
		cin >> user_name;
		string msg;
		cin>> msg;
		unsigned int find_result = msg.find(':');
		string cate = string(msg, 0, find_result);
		int level   = find_result == string::npos ? -1 : atoi(string(msg, find_result + 1).c_str());
		int ans = __TRUE__;
		if (user.find(user_name) == user.end() || user[user_name].find(cate) == user[user_name].end()) {
			ans = __FALSE__;
		}
		else {
			ans = level == -1 ? (user[user_name][cate] == -1 ? __TRUE__ : user[user_name][cate]) : (level <= user[user_name][cate] ? __TRUE__ : __FALSE__);
		}
		switch (ans) {
		case __FALSE__:
			cout << "false" << endl;
			break;
		case __TRUE__:
			cout << "true" << endl;
			break;
		default:
			cout << ans << endl;
		}
	}
}

int main() {
	freopen("text.txt", "r", stdin);

	map<string, int> category;
	map<string, map <string, int> > role;
	map<string, map <string, int> > user;

	set_category(category);
	set_role(role, category);
	set_user(user, role);

	search(user);

	return 0;
}