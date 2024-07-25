//线程的创建
//get_id():获取线程id

#include <iostream> 
#include <thread>
using std::cout;
using std::endl;
using std::thread;

void threadFunc(int x){
    cout << "child thread id === " << std::this_thread::get_id() << endl;
    cout << "threadFunc(int x)" << endl;
    cout << "x = " << x << endl;
}

int main()
{
    cout << "main thread id = " << std::this_thread::get_id() << endl;
    thread th(threadFunc, 1); //th是子线程
    cout << "child thread id = " << th.get_id() << endl;
    th.join();
    return 0;
}
