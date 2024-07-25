//RAII思想:实现MutexLockGuard类

#include <iostream>
#include <thread>
#include <mutex>

using std::cout;
using std::endl;
using std::thread;
using std::mutex;

int gCnt = 0;
mutex mtx;//创建互斥锁的对象
/* mutex mtx2; */

//利用RAII的思想：利用栈对象的生命周期管理资源
class MutexLockGuard
{
public:
    MutexLockGuard(mutex &metx)  //引用
    : _mtx(metx)
    {
        _mtx.lock();//在构造函数中上锁
    }

    ~MutexLockGuard()
    {
        _mtx.unlock();//在析构函数中进行解锁
    }
private:
    mutex &_mtx;  //引用
};

void threadFunc()
{
    for(size_t idx = 0; idx < 10000000; ++idx)
    {
    	//创建MutexLockGuard类的栈对象,生命周期结束时自动析构,解锁
        MutexLockGuard autoLock(mtx);
        ++gCnt;
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
