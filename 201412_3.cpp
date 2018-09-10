/*************************************************************************
    > File Name: 201412_3.cpp
    > Author: Herithx
    > Mail: 17361019875@163.com 
    > Created Time: 2018年09月09日 星期日 13时28分19秒
 ************************************************************************/

#include <iostream>
#include <cstring>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long LL;
typedef double DB;

const DB eps = 1e-6;
struct Bag {
	string op;
	DB dollars;
	LL num;
	Bag (string op, DB dollars, LL num) : op(op), dollars(dollars), num(num) { }
	bool operator < (const Bag obj) {
		return this->dollars - obj.dollars < 0;
	}
};

vector<Bag> records;

DB ans_d = 0;
LL ans_n = 0;

void reads_() {
	char op[10] = { 0 };
	while (cin >> op) {
		if (op[0] != 'c') {
			DB dollars = 0;
			LL num = 0;
			scanf("%lf%lld\n", &dollars, &num);
			records.push_back(Bag(string(op), dollars, num));
		}
		else {
			int opnum = 0;
			scanf("%d\n", &opnum);
			//records.erase(records.begin() + opnum - 1);
			records.push_back(Bag(string(""), -1 , opnum)); 
			if (records[opnum - 1].dollars == -1) 
				records[opnum - 1].num = -1;
		}
	}

	for (vector<Bag>::reverse_iterator it = records.rbegin(); it != records.rend(); it ++) {
		if ((*it).dollars == -1)
		if ((*it).num != -1) {
			records[(*it).num - 1].num = -1;
			(*it).num = -1;
		}
	}
	sort(records.begin(), records.end());
}

void solve_() {
	LL money = 0;
	for (vector<Bag>::iterator it = records.begin(); it != records.end(); it ++) {
		if ((*it).op == "sell") {
			if ((*it).num == -1) continue;
			money = (*it).num += money;  
		}
	}
	money = 0;
	for (vector<Bag>::reverse_iterator it = records.rbegin(); it != records.rend(); it ++) {
		if ((*it).op == "buy") {
			if ((*it).num == -1) continue; 
			money = (*it).num += money;
		}
	}

	for (vector<Bag>::iterator it = records.begin(); it != records.end(); it ++) {
		if ((*it).num == -1) continue;
		DB level = (*it).dollars;
		LL head = (*it).num;
		LL last = 0;
		if ((*it).op == "buy") {
			int loc = it - records.begin();
			while (loc > 0) {
				loc --;
				if (records[loc].op == "sell") {
                     last = records[loc].num;
                     break;
                 }

			}
    	}
		else {
			vector<Bag>::iterator is = it + 1;
			while (is != records.end()) {
				if ((*is).op == "buy") {
					last = (*is).num;
					break;
				}
				is ++;
			}
		}
		last = min(head, last);
		if (last >= ans_n) {
			ans_d = max(ans_d, level);
			ans_n = last;
		}
	}
	
	printf("%.2lf %lld\n", ans_d, ans_n);
}


int main() {
	reads_();

	solve_();
	
	return 0;
}
