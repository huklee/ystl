#include "ystl.cpp"

template<class T>
class node{
private:
	T val;
	node* next;
public:
	node(){};
	node(const T& val){};
};

template<class T>
class list{
private:
	node<T>* head;		
public:
	list(){};
	list(const T &val){};
};
