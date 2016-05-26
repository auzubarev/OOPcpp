#pragma once
template <typename T>
struct Node {
	T val;
	Node *next; 
	Node *prev;
	Node(T & _val, Node * _prev, Node * _next)
		: val(_val), prev(_prev), next(_next) {}
};

template <typename T>
class Container {
public:
	Container() :current(NULL), head(NULL), tail(NULL),
		noCurr(0), nSize(0) {};

	Container(const Container & object) :current(NULL), head(NULL), tail(NULL),
		noCurr(0), nSize(0) {
		for (int i = 0; i < object.size(); i++)
			pushBack(object.get(i));
	}
	
	void pushFront(const T & val) {
		T val1 = val;
		Node<T> * tmp = new Node<T>(val1, NULL, head);
		if (head != NULL)
			head->prev = tmp;
		else
			tail = tmp;
		head = tmp;
		nSize++;
		noCurr = 0;
		current = head;
	}

	void pushBack(const T & val) {
		T val1 = val;
		Node<T> * tmp = new Node<T>(val1, tail, NULL);
		if (tail != NULL)
			tail->next = tmp;
		else
			head = tmp;
		tail = tmp;
		nSize++;
		noCurr = 0;
		current = head;
	}

	void popFront() {
		if (head == NULL)
			throw "Container: empty container";
		Node<T> * tmp = head;
		head = head->next;
		if (tmp == tail)
			tail = NULL;
		delete tmp;
		nSize--;
		noCurr = 0;
		current = head;
	}

	void popBack() {
		if (head == NULL)
			throw "Container: empty container";
		Node<T> * tmp = tail;
		head = head->next;
		if (tmp == head)
			head = NULL;
		delete tmp;
		nSize--;
		noCurr = 0;
		current = head;
	}
	
	T getFront() const {
		if (head == NULL)
			throw "Container: empty container";
		return head->val;
	}
	
	T getBack() const {
		if (tail == NULL)
			throw "Container: empty container";
		return tail->val;
	};
	
	T get(int x) const {
		if (x < 0 || x >= nSize)
			throw "Container: index out of bounds";
		if (x == 0) {
			current = head;
			noCurr = 0;
		}
		if (x == nSize-1) {
			current = tail;
			noCurr = nSize - 1;
		}
		while (x < noCurr) {
			current = current->prev;
			noCurr--;
		}
		while (x > noCurr) {
			current = current->next;
			noCurr++;
		}
		return current->val;
	}
	
	bool empty() const {
		return head == NULL;
	}
	
	int size() const {
		return nSize;
	}
	
	void clear() {
		while (head != NULL)
			popFront();
	}
	
	~Container() {
		clear();
	}

private:
	mutable Node<T> *current;
	Node<T> *head;
	Node<T> *tail;
	mutable int noCurr;
	int nSize;
};