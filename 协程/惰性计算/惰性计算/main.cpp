#include <iostream>
#include <coroutine>
struct Generator
{
    struct promise_type
    {
        int value;

        Generator get_return_object()
        {
            return Generator(std::coroutine_handle<promise_type>::from_promise(*this));
        }

        std::suspend_always initial_suspend() { return{}; }
        std::suspend_always final_suspend() { return {}; }
        std::suspend_always yield_value(int value)
        {
            this->value = value;
            return {};
        }
        void return_void()
        {
            std::cout << "协程结束" << std::endl;
        }
        void unhandled_exception()
        {
            std::terminate();
        }
    };
    std::coroutine_handle<promise_type> handle;
    Generator(std::coroutine_handle<promise_type> h):handle(h)
    {}
    void next()
    {
        handle.resume();
    }
    int value()
    {
        return handle.promise().value;
    }
    ~Generator()
    {
        if (handle)
        {
            handle.destroy();
        }
    }
};

Generator fibonacci()
{
    int prev1 = 0;
    int prev2 = 1;

    while (true)
    {
        int current = prev1;
        int next = prev1 + prev2;

        prev1 = prev2;
        prev2 = next;

        co_yield current;
    }
}

//void demo()
//{
//    for (int i = 0; i < 5; ++i)
//    {
//        int val = fibonacci();
//        std::cout << val << std::endl;
//    }
//}

void demo()
{
    auto gen = fibonacci();
    for (int i = 0; i < 5; ++i)
    {
        gen.next();
        std::cout << gen.value() << std::endl;
    }
}

int main()
{
    demo();
    return 0;
}