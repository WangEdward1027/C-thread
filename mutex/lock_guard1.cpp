//lock_guard:保证作用域内上锁。离开作用域自动解锁

#include <iostream>
#include <thread>
#include <mutex>
using std::cout;
using std::endl;
using std::lock_guard;
using std::mutex;
using std::thread;

mutex mtx;  // 全局互斥锁

void print_thread_id(int id) {
    // 创建lock_guard对象，并传入互斥锁
    lock_guard<mutex> lock(mtx);
    // 互斥锁在作用域内被锁定
    cout << "Thread ID: " << id << endl; //加锁:保证3次cout是原子的
    // 作用域结束，互斥锁自动解锁
}

int main() {
    thread threads[10];
    // 创建并启动10个线程
    for (int i = 0; i < 10; ++i) {
        threads[i] = thread(print_thread_id, i);
    }
    // 等待所有线程完成
    for (auto &th : threads) {
        th.join();
    }
    return 0;
}
