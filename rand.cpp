/*************************************************************************
    > File Name: rand.cpp
    > Author: Herixth
    > Mail: 17361019875@163.com 
    > Created Time: 2018年09月09日 星期日 15时11分29秒
 ************************************************************************/

#include <iostream>
#include <algorithm>
#include <ctime>
using namespace std;

string op[3] = {
	"buy",
	"sell",
	"cancel"
};

int main() {
	srand(time(NULL));
	
	int opnum = (rand() % 5000) + 1;
	int yes = 0;
	
	for (int line = 1; line <= opnum; line ++) {
		string ops = op[rand() % 3];
		double dol = (double)(rand() % 1000000 + 1) / 100;
		long long num = (rand() % 100000000) + 1;
		if (ops == "cancel") {
			int se = rand() % line + 1;
			cout << ops.c_str() << " " << se << endl;
		}
		else {
			printf ("%s %.2lf %lld\n", ops.c_str(), dol, num);
		}
	}

	//cout << "buy" << " " << 9.00 << " " << 100 << endl;
	//cout << "buy" << " " << 8.88 << " " << 175 << endl;
	//cout << "sell" << " " << 9.00 << " " << 1000 << endl;
	//cout << "buy" << " " << 9.00 << " " << 400 << endl;
	//cout << "sell" << " " << 8.92 << " " << 400 << endl;
	//cout << "cancel " << 1 << endl;
	//cout << "cancel " << 6 << endl;
	//cout << "buy" << " " << 100.00 << " " << 50 << endl;
	return 0;
}
