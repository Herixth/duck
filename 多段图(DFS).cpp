#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <vector>
using namespace std;
static const int maxn = 1000;
int ls_pay = maxn;
vector<int> ls_direct;

void Dfs(int node, const int Road_worth[12][6], int Payment, vector<int> Direct) {
	if (!node) {
		cout << "road:";
		for (int i = Direct.size() - 1; i >= 0; i --)
			i != 0 ? cout << Direct[i] << " " : cout << Direct[i] << " 12";
		cout << ";payment: " << Payment;
		if (Payment < ls_pay) {
			ls_pay = Payment;
			ls_direct.assign(Direct.begin(), Direct.end());
			cout << " get¡Ì";
		}
		cout << endl;
		return;
	}
	for (int way = 0; way < 3; way ++) {
		if (!Road_worth[node][way]) continue;
		Payment += Road_worth[node][way + 3];
		Direct.push_back(Road_worth[node][way]);
		Dfs(Direct.back() - 1, Road_worth, Payment, Direct);
		Payment -= Road_worth[node][way + 3];
		Direct.pop_back();
	}
}

int main() {
	int Road_worth[12][6] = { 0, 0, 0, 0, 0, 0,       //Road_worth[i][j], 0<=j<3 means the direction, 3<=j<6 means the value
							  1, 0, 0, 9, 0, 0,
							  1, 0, 0, 7, 0, 0,
							  1, 0, 0, 3, 0, 0,
							  1, 0, 0, 2, 0, 0,
							  2, 3, 0, 4, 2, 0,
							  2, 3, 5, 2, 7, 11,
							  2, 4, 5, 1, 11, 8,
							  6, 7, 0, 6, 4, 0,
							  6, 7, 8, 5, 3, 5,
							  8, 0, 0, 6, 0, 0,
							  9, 10, 11, 4, 2, 5 };    
	int Payment = 0;
	vector<int> Direct;
	Dfs(11, Road_worth, Payment, Direct);
    /*   output the road    */ 
	cout << ls_pay << endl;
	for (int i = ls_direct.size() - 1; i >= 0; i --)
		i ? cout << ls_direct[i] << " " : cout << ls_direct[i] << " 12" << endl;
	return 0;
}
