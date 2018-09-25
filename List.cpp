/*************************************************************************
    > File Name: List.cpp
    > Author: Herixth
    > Mail: 17361019875@163.com 
    > Created Time: 2018年09月20日 星期四 17时49分57秒
 ************************************************************************/

#include <iostream>
#include <algorithm>
#include <cstring>
#include <assert.h>
#include <cstddef>
using namespace std;

const int defaultSize = 1e5 + 1;

/***************************************/
/*array-based list*/
template <typename E> class List {
public:
	List() { }
	virtual ~List() { }

	virtual void clear() = 0;
	virtual void insert(const E& item) = 0;
	virtual void append(const E& item) = 0;
	virtual E remove() = 0;
	virtual void moveToStart() = 0;
	virtual void moveToEnd() = 0;
	virtual void prev() = 0;
	virtual void next() = 0;
	virtual int length() const = 0;
	virtual int currPos() = 0;
	virtual void moveToPos(int pos) = 0;
	virtual const E& getValue() const = 0;
private:
	void operator = (const List &) { }
	List (const List &) { }
};

template <typename E>
class AList : public List<E> {
public:
	AList(int size = defaultSize) {
		maxSize = size;
		listSize = curr = 0;
		listArray = new E[maxSize];
	}
	
	~AList() {
		delete [] listArray;
	}

	void clear() {
		//delete []listArray;
		listSize = curr = 0;
		//listArray = new E[maxSize];
	}

	void insert(const E& it) {
		assert(listSize < maxSize);
		for (int inc = listSize; inc > curr; inc --)
			listArray[inc] = listArray[inc - 1];
		listArray[curr] = it;
		listSize ++;
	}

	void append(const E &it) {
		assert(listSize < maxSize);
		listArray[listSize ++] = it;
	}

	E remove() {
		assert((curr >= 0) && (curr < listSize));
		E it = listArray[curr];
		for (int inc = curr; inc < listSize - 1; inc ++)
			listArray[inc] = listArray[inc + 1];
		listSize --;
		return it;
	}

	void moveToStart() { curr = 0; }
	void moveToEnd() { curr = listSize; }
	void prev() { if (curr) curr --; }
	void next() { if (curr < listSize) curr ++; }

	int length() const { return listSize; }
	int currPos() const { return curr; }

	void moveToPos(int pos) {
		assert((pos >= 0) && (pos <= listSize));
		curr = pos;
	}

	const E& getValue() const {
		assert((curr >= 0) && (curr < listSize));
		return listArray[curr];
	}

private:
	int maxSize;
	int listSize;
	int curr;
	E* listArray;
};

/***************************************/
/*Linked list*/
template <typename E> class Link {
public:
	E element;
	Link *next;

	Link(const E &elemval, Link *nextval = NULL) {
		element = elemval;
		next = nextval;
	}
	Link(Link *nextval = NULL) {
		next = nextval;
	}
	
	void *operator new (size_t) {
		if (freelist == NULL) return ::new Link;
		Link<E> *temp = freelist;
		freelist = freelist -> next;
		return temp;
	}

	void operator delete (void *ptr) {
		((Link<E> *)ptr) -> next = freelist;
		freelist = (Link<E> *)ptr;
	}

private:
	static Link<E>* freelist;
};

template <typename E>
Link<E>* Link<E>::freelist = NULL;

template <typename E>
class LList : public Link<E> {
public:
	LList(int size = defaultSize) { init(); }
	~LList() { removeAll(); }
	
	void print() const {
		for (Link<E> *temp = head; temp != tail; temp = temp -> next) {
			cout << temp -> next -> element << " ";
		}
		cout << endl;
	}

	void clear() {
		removeAll();
		init();
	}

	void insert(const E &it) {
		curr -> next = new Link<E> (it, curr -> next);
		if (tail == curr) tail = curr -> next;
		cnt ++;
	}

	void append(const E &it) {
		tail = tail -> next = new Link<E> (it, NULL);
		cnt ++;
	}

	E remove() {
		assert(curr -> next != NULL);
		Link<E> *temp = curr -> next;
		if (tail == curr -> next) tail = curr;
		curr -> next = temp -> next;
		E val = temp -> element;
		delete temp;
		cnt --;
		return val;
	}

	E remove_prev() {
		assert(curr != head);
		Link<E> *temp = curr;
		curr = curr -> next;
		curr > next = curr -> next -> next;
		E val = temp -> element;
		cnt --;
		delete temp;
		return val;
	}

	void moveToStart() {
		curr = head;
	}

	void moveToEnd() {
		curr = tail;
	}

	void prev() {
		if (curr == head) return;
		Link<E> *temp = head;
		while (temp -> next != curr)
			temp = temp -> next;
		curr = temp;
	}

	void next() {
		if (curr != tail) 
			curr = curr -> next;
	}

	int length() const {
		return cnt;
	}

	int currPos() const {
		Link<E> *temp = head;
		int pos = 0;
		for (pos = 0; curr != temp; pos ++)
			temp = temp -> next;
		return pos;
	}

	void moveToPos(int pos) {
		assert((pos >= 0) && (pos <= cnt));
		curr = head;
		for (int inc = 0; inc < pos; inc ++) 
			curr = curr -> next;
	}

	const E& getValue() const {
		assert(curr -> next != NULL);
		return curr -> next -> element;
	}

	bool isEnd() {
		return curr -> next == NULL;
	}

	const E& getLastValue() const {
		return tail -> element;
	}
private:
	Link<E> *head;
	Link<E> *tail;
	Link<E> *curr;
	int cnt;                //size of list

	void init() {
		curr = tail = head = new Link<E>;
		cnt = 0;
	}

	void removeAll() {
		while (head != tail) {
			curr = head;
			head = curr -> next;
			delete curr;
		}
	}

};


template <typename E>
LList<E> LList_Merge(LList<E> list_F, LList<E> list_S) {
	LList<E> small = list_F.getLastValue() < list_S.getLastValue() ? list_F : list_S;
	LList<E> big   = list_S.getLastValue() >= list_F.getLastValue() ? list_S : list_F;
	while (!big.isEnd() && !small.isEnd()) {
		if (small.getValue() < big.getValue()) {
			big.insert(small.getValue());
			small.next();
			continue;
		}

		big.next();
	}
	return big;
}

int main() {
	
	LList<int> list_F;
	LList<int> list_S;
	list_F.append(1); list_F.append(4); list_F.append(7);
	list_S.append(2); list_S.append(3); list_S.append(8);
	int len = list_F.length() + list_S.length();
	LList_Merge(list_F, list_S).print();

	return 0;
}
