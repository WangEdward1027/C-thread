//lock_guard:生命周期结束时,自动解锁

#include <iostream>
#include <thread>
#include <mutex>

using std::cout;
using std::endl;
using std::thread;
using std::mutex;
using std::lock_guard;

int gCnt = 0;
mutex mtx;//创建互斥锁的对象

void threadFunc()
{
    for(size_t idx = 0; idx < 10000000; ++idx)
    {
        //lock_guard实现的时候，也是利用了RAII的思想
        //在构造函数中上锁，在析构函数中解锁
        //锁的粒度（锁的范围）
        lock_guard<mutex> lg(mtx);
        ++gCnt;
        //xxxxx
        //yyyy
        //zzz
    }
}

int main()
{
    thread th1(threadFunc);
    thread th2(threadFunc);

    th1.join();
    th2.join();
    cout << "gCnt = " << gCnt << endl;

    return 0;
}
