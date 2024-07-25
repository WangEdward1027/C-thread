//atomic:原子数据类型,在内部操作时自动上锁(硬件层面)
//比手动加锁效率更高

#include <iostream>
#include <thread>
#include <atomic>

using std::cout;
using std::endl;
using std::thread;
using std::atomic;

atomic<int> gCnt(0);

void threadFunc()
{
    for(size_t idx = 0; idx < 10000000; ++idx)
    {
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
