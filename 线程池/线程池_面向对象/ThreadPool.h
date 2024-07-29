#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__

#include "TaskQueue.h" //成员子对象,需要引入头文件
#include <iostream>
#include <vector>
#include <thread>
using std::vector;
using std::thread;

/* class TaskQueue; //为什么成员子对象不能用类的前向声明? */
//答:需要类的对象,要引入头文件,因为需要知道类的具体结构才能确定对象的大小。
//若只需要类的指针或引用,可用类的前向声明。因为指针大小固定为8B

class ThreadPool
{
public:
    ThreadPool(size_t threadNum, size_t queSize);
    ~ThreadPool();

    void start();
    void stop();
    void addTask(Task* ptask); //添加任务
    Task* getTask();           //获取任务
    void doTask();   //线程池交给工作线程执行的任务

private:
    size_t _threadNum;       //子线程的数目
    vector<thread> _threads; //存放子线程的容器
    size_t _queSize;         //任务队列的大小
    TaskQueue _taskQue;      //存放任务的任务队列。成员子对象,只能写头文件,不能写前向声明
    bool _isExit;            //表示线程池是否退出   
};

#endif
