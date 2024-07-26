//生产者消费者模型

#include <iostream> 
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <stdlib.h>   //随机种子
#include <time.h>     //时间
#include <unistd.h>
using std::cout;
using std::endl;
using std::thread;
using std::queue;
using std::mutex;
using std::unique_lock;
using std::condition_variable;

class TaskQueue
{
public:
    TaskQueue(size_t capacity);
    ~TaskQueue();
    
    void push(const int &value);
    int  pop();
    bool empty() const;
    bool full() const;

private:
    size_t _capacity; //仓库容量
    queue<int> _que;
    mutex _mutex;
    condition_variable _notEmpty;
    condition_variable _notFull;
};

TaskQueue::TaskQueue(size_t capacity)
: _capacity(capacity)
, _que()
, _mutex()
, _notEmpty()
, _notFull()
{

}

TaskQueue::~TaskQueue()
{

}

//添加任务与获取任务
void TaskQueue::push(const int &value)
{
    unique_lock<mutex> ul(_mutex);
    while(full()){
        _notFull.wait(ul);
    }
    _que.push(value);
    ul.unlock();           //解锁:控制锁的粒度
    _notEmpty.notify_one();//唤醒消费者
}

int TaskQueue::pop()
{
    unique_lock<mutex> ul(_mutex);
    while(empty()){
        _notEmpty.wait(ul);
    }
    int tmp = _que.front();
    _que.pop();
    ul.unlock();          //解锁
    _notFull.notify_one();//唤醒生产者
    return tmp;
}

//判断空还是满
bool TaskQueue::empty() const
{
    return 0 == _que.size();
}

bool TaskQueue::full() const
{
    return _capacity == _que.size();
}

void produceThreadFunc()
{
    
}

//生产者:生产商品
class Producer
{
public:
    Producer(){}

    ~Producer(){}

    void produce(TaskQueue &taskQueue)
    {
        ::srand(::clock());
        int cnt = 20;
        while(cnt--){
            int number = ::rand() % 100; //产生随机数
            cout << "produce : " << number << endl;
            taskQueue.push(number);
            sleep(1);
        }
    }
};

//消费者:消费商品
class Consumer
{
public:
    Consumer(){}

    ~Consumer(){}

    void consume(TaskQueue &taskQueue)
    {
        int cnt = 10;
        while(cnt--){
            int number = taskQueue.pop();
            cout << "consume : " << number << endl;
            sleep(1);
        }
    }
};

int main()
{
    TaskQueue taskque(20);
    Producer producer;   //生产者 
    Consumer consumer1;  //消费者1
    Consumer consumer2;  //消费者2
    
    thread pro(&Producer::produce, &producer, std::ref(taskque));
    thread con1(&Consumer::consume, &consumer1, std::ref(taskque));   
    thread con2(&Consumer::consume, &consumer2, std::ref(taskque));   

    pro.join();
    con1.join();
    con2.join();

    return 0;
}
