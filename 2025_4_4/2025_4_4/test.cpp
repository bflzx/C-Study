#include<iostream>
#include<set>
#include<map>
using namespace std;

void test_set1()
{
	set<int> s;
	s.insert(3);
	s.insert(1);
	s.insert(4);
	s.insert(3);
	s.insert(7);
	set<int>::iterator it = s.begin();
	while (it != s.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
}

void test_map()
{
	map<int, int> m;
	m.insert(pair<int, int>(1, 1));
	m.insert(pair<int, int>(2, 2));
	m.insert(pair<int, int>(3, 3));
	map<int, int>::iterator it = m.begin();
	while (it != m.end())
	{
		cout << (*it).first << ":"<<(*it).second<<" ";
		++it;
	}
	cout << endl;
}

int main()
{
	//test_set1();
	test_map();
	return 0;
}