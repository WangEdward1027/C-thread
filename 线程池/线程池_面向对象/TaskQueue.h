#ifndef __TASKQUEUE_H__
#define __TASKQUEUE_H__

#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>
using std::queue;
using std::mutex;
using std::condition_variable;

class Task; //前向声明:仅使用了别的类的指针或引用

using ElemType = Task *;

class TaskQueue
{
public:
    TaskQueue(size_t queSize);
    ~TaskQueue();
    
    void push(ElemType ptask);
    ElemType pop();
    bool empty();
    bool full();
    void wakeup();

private:
    size_t _queSize;
    queue<ElemType> _que;
    mutex _mutex;
    condition_variable _notEmpty;
    condition_variable _notFull;
    bool _flag; //判断
};

#endif
