#include <iostream>
#include <chrono>
#include <thread>
#include <coroutine>
#include <mutex>
#include <queue>

class EventLoop
{
public:
    void add_task(std::coroutine_handle<> handle)
    {
        {
            std::lock_guard<std::mutex> lock(my_mutex);
            my_queue.push(handle);
        }
        ++number;
    }
    void post(std::coroutine_handle<> handle)
    {
        {
            std::lock_guard<std::mutex> lock(my_mutex);
            my_queue.push(handle);
        }
        my_cv.notify_one();
    }
    void run()
    {
        while (true)
        {
            std::coroutine_handle<> my_handle;
            {
                std::unique_lock<std::mutex> lock(my_mutex);
                // 如果队列为非空，结束阻塞
                // 如果任务数为零，结束阻塞
                my_cv.wait(lock, [&] { return !my_queue.empty() || 0 == number; });
                if (my_queue.empty() && 0 == number)
                {
                    std::cout << "任务执行完毕" << std::endl;
                    break;
                }
                my_handle = my_queue.front();
                my_queue.pop();
            }
            if (!my_handle)
            {
                continue;
            }
            my_handle.resume();
            if (my_handle.done())
            {
                --number;
                my_handle.destroy();
            }
        }
    }
private:
    std::queue<std::coroutine_handle<>> my_queue;
    std::mutex my_mutex;
    std::condition_variable my_cv;
    size_t number{ 0 };
};
EventLoop eloop;

struct Task
{
    struct promise_type
    {
        Task get_return_object()
        {
            return Task{ std::coroutine_handle<promise_type>::from_promise(*this) };
        }
        std::suspend_always initial_suspend()
        {
            return {};
        }
        std::suspend_always final_suspend() noexcept
        {
            return {};
        }
        void return_void() {}
        void unhandled_exception() { std::exit(1); }
    };
    operator std::coroutine_handle<>()
    {
        return handle;
    }
    std::coroutine_handle<promise_type> handle;
    Task(std::coroutine_handle<promise_type> h) : handle(h) {}
    void resume() { handle.resume(); }
};

struct AsyncSleepFor
{
    int time{ 0 };
    bool await_ready()
    {
        return false;
    }
    void await_suspend(std::coroutine_handle<> handle)
    {
        std::thread([handle,duration = time] {
            std::this_thread::sleep_for(std::chrono::seconds(duration));
            eloop.post(handle);
            }).detach();
    }
    void await_resume() {}
};

Task task1()
{
    std::cout << "task1 执行开始" << std::endl;
    co_await AsyncSleepFor{ 5 };
    std::cout << "task1 执行结束" << std::endl;

}

Task task2()
{
    std::cout << "task2 执行开始" << std::endl;
    co_await AsyncSleepFor{ 3 };
    std::cout << "task2 执行结束" << std::endl;
}


int main()
{
    auto start = std::chrono::steady_clock::now();

    auto t1 = task1();
    auto t2 = task2();

    eloop.add_task(t1);
    eloop.add_task(t2);

    eloop.run();

    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "程序耗时:" << duration.count() << "毫秒" << std::endl;

    return 0;
}