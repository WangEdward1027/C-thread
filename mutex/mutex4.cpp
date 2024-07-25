//unique_lock:可以手动释放,自由控制锁的粒度(锁的范围)
//比lock_guard更灵活,但效率低

#include <iostream>
#include <thread>
#include <mutex>

using std::cout;
using std::endl;
using std::thread;
using std::mutex;
using std::unique_lock;

int gCnt = 0;
mutex mtx;//创建互斥锁的对象

void threadFunc()
{
    for(size_t idx = 0; idx < 10000000; ++idx)
    {
        //锁的粒度（锁的范围）
        //除了利用RAII的思想，在构造函数中上锁，在析构函数中
        //进行解锁外，还提供了上锁与解锁的成员函数，也就表明
        //该类的对象使用起来的时候更加灵活一些
        unique_lock<mutex> ul(mtx);
        ++gCnt;
        ul.unlock();
        //xxxxx
        ul.lock();
        //yyyy
        ul.unlock();
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
