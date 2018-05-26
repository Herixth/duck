#include <iostream>
#include <algorithm>
#include <cstring>
#include <iomanip>
using namespace std;
const int maxn = 100;
const int symbol = -1;

class List {
	public:
		List();
		~List();
		void op_Insert(int, int);
		void op_Delete(int);
		void op_Exchange(int, int);
		bool is_Empty();
		int loc_Find(int);
		void show();
	private:
		int num;
		int *list;
		int *vale;
};

List::List() {
	cin >> num;
	list = new int[num];
	vale = new int[num];
	for (int i = 1; i <= num; i ++) {
		cin >> vale[i];
		list[i - 1] = i; 
	}
	list[num] = symbol;
}

List::~List() {
	delete[] list;
	delete[] vale;
	cout << "链表已清空" << endl;
}

bool List::is_Empty() {
	return (list[0] == symbol);
}

int List::loc_Find(int loc) {
	int loc_f = 0;
	for (int i = 0; i < loc && loc_f != symbol; i ++)
		loc_f = list[loc_f];
	return loc_f;
}

void List::show() {
	cout << "当前链表为:" << endl;
	cout << "位置: ";
	for (int i = 1; i <= num; i ++) 
		cout << setw(4) << i << " ";
	cout << endl << "元素: ";
	for (int i = list[0]; i != symbol; i = list[i])
		cout << setw(4) << vale[i] << " ";
	cout << endl;
}

void List::op_Insert(int loc, int _vale) {
	vale[++ num] = _vale;	
	int loc_f = loc_Find(loc - 1);
	list[num] = list[loc_f];
	list[loc_f] = num;
}

void List::op_Delete(int loc) {
	int loc_f = loc_Find(loc - 1);
	vale[list[loc_f]] = symbol;
	list[loc_f] = list[list[loc_f]];
	num --;
}

void List::op_Exchange(int loc, int _loc) {
	if (_loc < loc) swap(loc, _loc);
	int loc_f = loc_Find(loc - 1);
	if (_loc - loc > 1) {
		int _loc_f = loc_Find(_loc - 1);
		swap(list[list[loc_f]], list[list[_loc_f]]);
		swap(list[loc_f], list[_loc_f]);
	}
	else {
		int temp = list[list[loc_f]];
		list[list[loc_f]] = list[temp];
		list[temp] = list[loc_f];
		list[loc_f] = temp;
	}
}
