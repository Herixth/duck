#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

int main() {
	vector< vector<char> > maxtrix;
	maxtrix.push_back(vector<char>(2, 2));
	maxtrix.push_back(vector<char>(2, 3));
	for (vector< vector<char> >::iterator row = maxtrix.begin(); row != maxtrix.end(); row ++) {
		for (vector<char>::iterator col = (*row).begin(); col != (*row).end(); col ++) {
			cout << *col << " ";
		}
		cout << endl;
	}
	return 0;
}
