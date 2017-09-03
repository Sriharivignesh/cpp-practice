// Implement simple thread locking
// Obtain lock to either increment or decrement
// a global variable and print the variable value

#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <mutex>

std::mutex operation_lock;

int variable = 0;

void print_variable()
{
    std::cout << "variable: " << variable << std::endl;
}

void keep_printing1()
{
    while(1)
    {
        std::lock_guard<std::mutex> lock(operation_lock);

        variable += 1;
        print_variable();

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void keep_printing2()
{
    while(1)
    {
        std::lock_guard<std::mutex> lock(operation_lock);

        variable -= 1;
        print_variable();

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}


int main()
{
    std::thread bthread1(keep_printing1);
    bthread1.detach();

    std::thread bthread2(keep_printing2);
    bthread2.detach();

    // Sleep main threads so background threads execute
    std::this_thread::sleep_for(std::chrono::seconds(10));
    return 0;
}