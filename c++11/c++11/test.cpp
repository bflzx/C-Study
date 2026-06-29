#include<iostream>
#include<thread>
#include<mutex>
#include<atomic>

using namespace std;

mutex mtx;
int x = 0;
//atomic<int> x;

void Add(int n)
{
	mtx.lock();
	for (int i = 0; i < n; i++)
	{
		x++;
	}
	mtx.unlock();
}

int main()
{
	thread t1(Add, 100);
	thread t2(Add, 100);

	t1.join();
	t2.join();
	cout << x << endl;
	return 0;
}