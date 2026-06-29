#include<iostream>
#include<list>
using namespace std;

void Print(const list<int>& lt)
{
	list<int>::const_iterator it1 = lt.begin();
	while (it1 != lt.end())
	{
		cout << *it1 << " ";
		++it1;
	}
	cout << endl;
}
void test_list1()
{
	list<int> lt1;
	lt1.push_back(1);
	lt1.push_back(2);
	lt1.push_back(3);
	lt1.push_back(4);	
	Print(lt1);

	list<int>::reverse_iterator rit1 = lt1.rbegin();
	while (rit1 != lt1.rend())
	{
		cout << *rit1 << " ";
		++rit1;
	}
	cout << endl;
}

void test_list2()
{
	list<int> lt;
	lt.push_back(1);
	lt.push_back(2);
	lt.push_back(3);
	lt.push_back(4);
	lt.push_front(0);
	Print(lt);
}
int main()
{
	//test_list1();
	test_list2();
	return 0;
}