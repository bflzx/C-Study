#include<iostream>
#include<thread>
#include<chrono>
#include<mutex>
#include<atomic>
using namespace std;

//void func(int a)
//{
//	while (true)
//	{
//		cout << "Hello world!" << endl;
//		std::this_thread::sleep_for(chrono::microseconds(50));
//	}
//}
//
//int main()
//{
//	int a = 0;
//	thread thread1(func, a);
//	
//	
//	//thread1.join();
//	//while (true)
//	//{
//	//	cout << "Cat!" << endl;
//	//	std::this_thread::sleep_for(chrono::microseconds(50));
//	//}
//	
//	return 0;
//}
std::mutex mtx;
atomic<int> a = 10;
int globalVariable = 0;

void task1()
{
	for (int i = 0; i < 1000000; i++)
	{
		mtx.lock();
		globalVariable++;
		globalVariable--;
		mtx.unlock();
	
	}
}

int main()
{
	thread t1(task1);
	thread t2(task1);
	
	t1.join();
	t2.join();

	cout << "Current value is:" << globalVariable << endl;
	return 0;
}