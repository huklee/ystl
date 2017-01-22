#include <iostream>

#include <mystl/list.hpp>
#include <mystl/iterator.hpp>

void test_list()
{
	// INSERT 0 TO 9
	mystl::list<int> intList;
	for (int i = 0; i < 10; i++)
		intList.push_back(i);
	
	// STEP 1 - ERASE
	mystl::list<int>::iterator it = intList.begin();
	mystl::advance(it, 3);

	it = intList.erase(it); // ERASE 3
	std::cout << *it << std::endl; // PRINT 4

	// STEP 2 - INSERT
	it = intList.begin();
	mystl::advance(it, 2);

	it = intList.insert(it, -1); // INSERT -1
	std::cout << *(++it) << std::endl; // PRINT 2
	
	// STEP 3 - RANGE ERASE
	mystl::list<int>::iterator first = intList.begin();
	mystl::list<int>::iterator last = intList.begin();
	{
		mystl::advance(first, 6);
		mystl::advance(last, 9);
	}
	it = intList.erase(first, last); // ERASE FROM 6 TO 9
	std::cout << *it << std::endl; // PRINT 9
	
	// STEP 4 - PUSH ANYTHING
	intList.push(300, 123, 171, -400, 829, -201, 59);

	std::cout << std::endl << "\tNOT SORTED YET" << std::endl;
	std::cout << "---------------------------------------" << std::endl;
	for (auto it = intList.begin(); it != intList.end(); it.operator++())
		std::cout << *it << std::endl;

	// STEP 5 - SORT
	intList.sort();
	intList.reverse();

	std::cout << std::endl << "\tNOW THE LIST IS SORTED" << std::endl;
	std::cout << "---------------------------------------" << std::endl;
	std::cout << "---------------------------------------" << std::endl;
	for (auto it = intList.rbegin(); it != intList.rend(); it.operator++())
		std::cout << *it << std::endl;
}

void main()
{
	test_list();

	system("pause");
}