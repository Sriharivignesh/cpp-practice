// Both threads pop from a queue and process elements
// using a global queue lock.

#include <iostream>
#include <thread>
#include <chrono>
#include <queue>
#include <mutex>

std::mutex operation_lock;

std::queue<int> global_queue;

void do_queue_operation()
{
    auto thread_id = std::this_thread::get_id();

        if(!global_queue.empty())
        {
            int element = global_queue.front();
            global_queue.pop();

            std::cout << " Thread " << thread_id << " has processed " << element << std::endl;
        }
        else
        {
            std::cout << " Queue empty. Thread " << thread_id << " is going to sleep for 100 milliseconds" << std::endl;
        }
}

void keep_printing1()
{
    while(1)
    {
        std::lock_guard<std::mutex> lock(operation_lock);
        do_queue_operation();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void keep_printing2()
{
    while(1)
    {
        std::lock_guard<std::mutex> lock(operation_lock);
        do_queue_operation();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}


int main()
{
    for(int i = 0; i < 10; i++)
    {
        global_queue.push(i);
    }

    std::thread bthread1(keep_printing1);
    bthread1.detach();

    std::thread bthread2(keep_printing2);
    bthread2.detach();

    // Sleep main threads so background threads execute
    std::this_thread::sleep_for(std::chrono::seconds(10));
    return 0;
}