// Both threads pop from a queue and process elements
// using a global queue lock.

#include <iostream>
#include <thread>
#include <chrono>
#include <queue>
#include <vector>
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

void queue_operator()
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
    for(int i = 0; i < 1000; i++)
    {
        global_queue.push(i);
    }

    std::thread bthreads[100];

    for(int i = 0; i < 100; i++)
    {
        bthreads[i] = std::thread(queue_operator);
        bthreads[i].detach();
    }


    // Sleep main threads so background threads execute
    std::this_thread::sleep_for(std::chrono::seconds(100));
    return 0;
}