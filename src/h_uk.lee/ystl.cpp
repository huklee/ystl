// interface

template<class T>
class node{
private:
	T val;
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
}

/*
template<class T>
list::list(){};

template<class T>
list::list(const T &val){
	this->head = new node<T>(val);
}
*/
