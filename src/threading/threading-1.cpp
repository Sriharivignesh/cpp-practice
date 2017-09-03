// Print a string in a background thread forever

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
    bthread.join();
    return 0;
}