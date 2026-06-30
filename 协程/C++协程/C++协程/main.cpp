//#include <iostream>
//#include <coroutine>
//
//struct CoroRAII
//{
//	struct promise_type
//	{
//		int my_value{ 0 };
//		CoroRAII get_return_object()
//		{
//			std::cout << "get_return_object" << std::endl;
//			return CoroRAII{ std::coroutine_handle<promise_type>::from_promise(*this) };
//		}
//	
//		//决定协程创建后是否马上执行
//		//std::suspend_never:不挂起
//		//std::suspend_always:挂起
//		std::suspend_never initial_suspend()
//		{
//			return {};
//		}
//
//		void return_value(int value)
//		{
//			my_value = value;
//			std::cout << "协程函数逻辑结束" << std::endl;
//		}
//
//		//协程执行完后是否马上销毁
//		//std::suspend_never:不挂起,马上销毁资源
//		//std::suspend_always:挂起,不立即销毁,等待外部destroy释放资源
//		std::suspend_always final_suspend() noexcept
//		{
//			std::cout << "final_suspend" << std::endl;
//			return {};
//		}
//		void unhandled_exception()
//		{
//			std::cout << "未处理的异常" << std::endl;
//		}
//	};
//
//	std::coroutine_handle<promise_type> handle;
//	//构造函数初始化 handle 对象
//	CoroRAII(std::coroutine_handle<promise_type> handle)
//	{
//		std::cout << "CoroRAII 构造函数" << std::endl;
//		this->handle = handle;
//	}
//
//	//封装其他handle操作
//	void resume()
//	{
//		if (!handle.done())
//		{
//			handle.resume();
//		}
//	}
//
//	int value()
//	{
//		return handle.promise().my_value;
//	}
//
//	//析构函数初始化handle对象
//	~CoroRAII()
//	{
//		if (handle)
//		{
//			handle.destroy();
//		}
//	}
//};
//
//// 暂停:保存函数的状态(局部变量,参数信息,暂停位置等)
//// 恢复:恢复函数的状态
//CoroRAII my_coroutine()
//{
//	std::cout << "协程执行" << std::endl;
//	std::cout << "协程执行" << std::endl;
//	co_return 100;
//	std::cout << "协程执行" << std::endl;
//}
//
//int main()
//{
//	//普通函数:一旦调用,会马上执行
//	//协程函数:一旦调用,会返回协程管理对象
//	CoroRAII coro = my_coroutine();
//	std::cout << coro.value() << std::endl;
//	// 协程管理对象需要手动释放(创建协程时,编译器会在堆上给函数状态分配内存)
//	// C++ 怕我们忘记释放,要求不能直接去使用 coroutine_handle,要通过RAII的方式使用
//	//coro.destroy();
//	return 0;
//}