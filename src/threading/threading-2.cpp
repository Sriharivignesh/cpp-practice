// Print a string in a background daemon thread till main thread exits

#include <iostream>
#include <thread>
#include <chrono>
#include <string>

void keep_printing()
{
    while(1)
    {
        std::cout << "String from background thread" << std::endl;
        // Sleep this thread for 2 seconds
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

int main()
{
    std::thread bthread(keep_printing);
    bthread.detach();

    // Sleep main thread for 10 seconds to give background thread
    // a chance to execute
    std::this_thread::sleep_for(std::chrono::seconds(10));
    return 0;
}