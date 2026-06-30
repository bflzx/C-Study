//#include <iostream>
//#include <coroutine>
//
//
//struct CoroManager
//{
//	struct promise_type
//	{
//		int value;
//
//		CoroManager get_return_object()
//		{
//			return CoroManager{ std::coroutine_handle<promise_type>::from_promise(*this) };
//		}
//
//		std::suspend_always initial_suspend() { return {}; }
//		void return_void() {}
//
//		std::suspend_always yield_value(int value)
//		{
//			this->value = value;
//			return {};
//		}
//
//		std::suspend_always final_suspend() noexcept { return {}; }
//		void unhandled_exception() { std::terminate(); }
//	};
//
//	std::coroutine_handle<promise_type> handle;
//	CoroManager(std::coroutine_handle<promise_type> handle)
//	{
//		this->handle = handle;
//	}
//
//	~CoroManager()
//	{
//		if (handle)
//		{
//			handle.destroy();
//		}
//	}
//};
//
//CoroManager my_coroutine()
//{
//	co_yield 10;
//	co_yield 20;
//	co_yield 30;
//
//	co_return;
//}
//
//int main()
//{
//	CoroManager coro = my_coroutine();
//
//	coro.handle.resume();
//	std::cout << "第一次返回的值:" << coro.handle.promise().value << std::endl;
//
//	coro.handle.resume();
//	std::cout << "第二次返回的值:" << coro.handle.promise().value << std::endl;
//
//	coro.handle.resume();
//	std::cout << "第三次返回的值:" << coro.handle.promise().value << std::endl;
//
//	return 0;
//}