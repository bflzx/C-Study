#include<iostream>

using namespace std;

class Date {
	friend ostream& operator<<(ostream& out, Date d);
	friend istream& operator>>(istream& in, Date& d);
public:
	Date(int year = 0, int month = 1, int day = 1)
		:_year(year),
		_month(month),
		_day(day)
	{
	}

private:
	int _year;
	int _month;
	int _day;
};

ostream& operator<<(ostream& out, Date d)
{
	cout << d._year << d._month << d._day;
	return out;
}
istream& operator>>(istream& in, Date& d)
{
	in >> d._year >> d._month >> d._day;
	return in;
}

int main()
{
	Date d1(1, 2, 3);
	Date d2 = 1;
	Date d3 = { 1,2 };
	Date d4 = { 1,2,3, };
	cin >> d1;
	cout << d1;
	return 0;
}