// interface

// the basic container
template<class T>
class node{
private:
	T val;
	node* prev;
	node* next;
public:
	node();
	node(const T& val);
};

template<class T>
class list{
private:
	node<T>* head;
public:
	list();
	list(const T &val);
};

// implementation
template<class T>
node<T>::node(){};

template<class T>
node<T>::node(const T& val){
	this->val = val;
	this->next = NULL;
	this->prev = NULL;
}

template<class T>
list<T>::list(){};

template<class T>
list<T>::list(const T &val){
	this->head = new node<T>(val);
}

// iterator (=smart pointer)
template<typename T>
class list_iterator{
	node<T>* cur;
public:
	list_iterator(node<T>* p=0): cur(p) {}
	inline list_iterator& operator++();
	inline list_iterator& operator--();
	inline bool list_iterator& operator==();
	inline bool list_iterator& operator!=();
}

// alias for iterator
typedef list_iterator<T> iterator;

iterator begin(){
	return iterator(head);
}

iterator end(){
	return iterator(0);
}
