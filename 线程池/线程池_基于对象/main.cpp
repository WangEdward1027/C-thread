#include "ThreadPool.h"
#include <iostream> 
#include <stdlib.h>
#include <time.h>
#include <memory>
#include <functional>
using std::cout;
using std::endl;
using std::unique_ptr;
using std::bind;

class MyTask
{
public:
    //MyTask执行任务,根据具体的业务逻辑添加任务
    void process(int x) 
    {
        //全局作用域解析运算符:确保调用的是全局命名空间中的srand和clock
        ::srand(::clock());         
        int number = ::rand() % 100; //产生随机数
        cout << "MyTask number = " << number << endl;
        /* cout << "x = " << x << endl; */
    }
};

void test()
{
    ThreadPool pool(4, 10); //1.创建线程池的对象
    pool.start();   //2.启动线程池
    
    //3.添加任务
    unique_ptr<MyTask> ptask(new MyTask()); //改用智能指针,自动delete
    int cnt = 20;
    while(cnt--){
        pool.addTask(bind(&MyTask::process, ptask.get(), 100)); //基于对象
    }
    pool.stop();    //4.关闭线程池
}

int main()
{
    test();   
    return 0;
}
