#include <iostream>
#include <coroutine>

struct MyAwaiter
{
    // 1. 是否直接执行
    bool await_ready() const noexcept
    {
        bool flag = true;
        std::cout << "是否执行：" << std::boolalpha << flag << std::endl;
        // true 不挂起：直接执行 await_resume 函数
        // false 挂起：直接执行 await_suspend 函数
        return flag;
    }

    // 2. 挂起时调用
    void await_suspend(std::coroutine_handle<> h) noexcept
    {
        std::cout << "协程挂起" << std::endl;
    }

    // 3. 恢复时调用
    int await_resume() noexcept
    {
        std::cout << "协程执行" << std::endl;
        return 100;
    }
};

struct CoroManager
{
    struct promise_type
    {
        int value;

        CoroManager get_return_object()
        {
            return CoroManager{ std::coroutine_handle<promise_type>::from_promise(*this) };
        }

        std::suspend_always initial_suspend()
        {
            return {};
        }

        void return_void()
        {
            std::cout << "协程结束" << std::endl;
        }

        std::suspend_always final_suspend() noexcept
        {
            return {};
        }

        void unhandled_exception()
        {
            std::terminate();
        }
    };

    std::coroutine_handle<promise_type> handle;
    CoroManager(std::coroutine_handle<promise_type> handle)
    {
        this->handle = handle;
    }

    ~CoroManager()
    {
        if (handle)
        {
            handle.destroy();
            std::cout << "协程销毁" << std::endl;
        }
    }
};

CoroManager coro_function()
{
    int ret = co_await MyAwaiter();
    std::cout << "协程结果: " << ret << std::endl;
    co_return;
}

int main()
{
    CoroManager coro = coro_function();
    coro.handle.resume();

    return 0;
}