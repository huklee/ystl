#include <iostream>

#include <mystl/vector.hpp>
#include <mystl/deque.hpp>
#include <mystl/list.hpp>
#include <mystl/iterator.hpp>

template <class Container>
void test_linear_container(Container &intList)
{
	// INSERT 0 TO 9
	for (int i = 0; i < 10; i++)
		intList.push_back(i);

	// STEP 1 - ERASE
	typename Container::iterator it = intList.begin();
	mystl::advance(it, 3);

	it = intList.erase(it); // ERASE 3
	//std::cout << *it << std::endl; // PRINT 4

	// STEP 2 - INSERT
	it = intList.begin();
	mystl::advance(it, 2);

	it = intList.insert(it, -1); // INSERT -1
	//std::cout << *(++it) << std::endl; // PRINT 2

	// STEP 3 - RANGE ERASE
	typename Container::iterator first = intList.begin();
	typename Container::iterator last = intList.begin();
	{
		mystl::advance(first, 6);
		mystl::advance(last, 9);
	}
	it = intList.erase(first, last); // ERASE FROM 6 TO 9
	//std::cout << *it << std::endl; // PRINT 9
}

void test_vector()
{
	mystl::vector<int> intList;
	test_linear_container(intList);

	for (auto it = intList.begin(); it != intList.end(); it++)
		std::cout << *it << std::endl;
}

void test_deque()
{
	mystl::deque<int> intList;
	test_linear_container(intList);

	for (auto it = intList.begin(); it != intList.end(); it++)
		std::cout << *it << std::endl;
}

void test_list()
{
	// STEP 1 TO 4
	mystl::list<int> intList;
	test_linear_container(intList);
	
	// STEP 5 - SORT
	intList.sort();
	intList.reverse();

	std::cout << std::endl << "\tNOW THE LIST IS SORTED" << std::endl;
	std::cout << "---------------------------------------" << std::endl;
	std::cout << "---------------------------------------" << std::endl;
	for (auto it = intList.rbegin(); it != intList.rend(); ++it)
		std::cout << *it << std::endl;

	intList.begin();
	intList.cbegin();
	intList.rbegin();
	intList.crbegin();

	intList.end();
	intList.cend();
	intList.rend();
	intList.crend();
}

void main()
{
	test_vector();
	test_deque();
	test_list();

	system("pause");
}