#include "Task.h"
#include "ThreadPool.h"
#include <iostream> 
#include <stdlib.h>
#include <time.h>
#include <memory>
using std::cout;
using std::endl;
using std::unique_ptr;

class MyTask
: public Task
{
public:
    //MyTask执行任务,根据具体的业务逻辑添加任务
    void process() override
    {
        //全局作用域解析运算符:确保调用的是全局命名空间中的srand和clock
        ::srand(::clock());         
        int number = ::rand() % 100; //产生随机数
        cout << "MyTask number = " << number << endl;
    }
};

void test()
{
    ThreadPool pool(4, 10); //1.创建线程池的对象
    pool.start();   //2.启动线程池
    
    //3.添加任务
    /* Task* ptask = new MyTask(); */
    /* pool.addTask(ptask); */
    unique_ptr<Task> ptask(new MyTask()); //改用智能指针,自动delete
    int cnt = 20;
    while(cnt--){
        pool.addTask(ptask.get());
    }
    pool.stop();    //4.关闭线程池
}

int main()
{
    test();   
    return 0;
}
