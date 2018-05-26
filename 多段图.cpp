#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <vector>
using namespace std;
static const int maxn = 1000;

void Dynamic_plan(const int Road_worth[12][6], vector< vector<int> > &Payment, vector< vector<int> > &Direct) {
	Payment[0][0] = 0;
	for (int num = 1; num < 12; num ++) {  //each node 
		for (int way = 0; way < 3; way ++) {
			if (!Road_worth[num][way]) continue;
			Payment[num][way] = Payment[Road_worth[num][way] - 1][0] + Road_worth[num][way + 3];
			Direct[num][way] = Road_worth[num][way];
		}
		for (int i = 0; i < 3; i ++) 
			for (int j = i + 1; j < 3; j ++) 
				if (Payment[num][j] < Payment[num][i]) {
					swap(Payment[num][j], Payment[num][i]);
					swap(Direct[num][j], Direct[num][i]);
				}
		
		cout << "node: " << num + 1 << "; Payment_min: " << Payment[num][0] << "; Direct: " << Direct[num][0] << endl;  		
		
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
	vector< vector <int> > Payment(12, vector<int> (3, maxn));
	vector< vector <int> > Direct(12 ,vector<int> (3, 0));
	Dynamic_plan(Road_worth, Payment, Direct);
	cout << Payment[11][0] << endl;
    /*   output the road    */ 
	vector<int> out(1, 12);
	for (int i = 11; i != 0; i = Direct[i][0] - 1)  
		out.push_back(Direct[i][0]);
	while (out.begin() != out.end()) {
		cout << out.back() << " ";
		out.pop_back();
	}	
	return 0;
}
