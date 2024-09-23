#include <chrono>
#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>

int a = 0;
static int static_a = 0; 
std::condition_variable cv;
std::mutex m;
std::unique_lock<std::mutex> lock(m);

void first_thread_job() {
    // [1 thread] Keep showing data
    while (true) {
        cv.wait(lock);
        std::cout << "[1] " << a << " " << static_a << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void second_thread_job() {
    // [2 thread] Keep updating data every 0.1 sec.
    while (true) {
        cv.wait(lock);
        a++;
        static_a++;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main() {
    // 建立執行緒
    std::thread first_thread(first_thread_job);
    std::thread second_thread(second_thread_job); 

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << "[Main thread] Update data after 1 sec." << std::endl;
    a = 100;
    static_a = 200;
    cv.notify_all();

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    cv.notify_all();

    // 將主執行緒暫停，等待指定的執行緒結束
    first_thread.join();
    second_thread.join();
    return 0;
}

