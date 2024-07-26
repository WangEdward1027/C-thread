//线程的创建5:传递lambda表达式

#include <iostream> 
#include <thread>
using std::cout;
using std::endl;
using std::thread;

/* void threadFunc(int x){ */
/*     cout << "child thread id === " << std::this_thread::get_id() << endl; */
/*     cout << "void threadFunc(int x)" << endl; */
/*     cout << "x = " << x << endl; */
/* } */

int main()
{
    cout << "main thread id = " << std::this_thread::get_id() << endl;
    
    thread th([](int x){
              cout << "child thread id === " << std::this_thread::get_id() << endl;
              cout << "void threadFunc(int x)" << endl;
              cout << "x = " << x << endl;
              }, 5); //创建子线程

    cout << "child thread id = " << th.get_id() << endl;
    th.join(); //主线程等待子线程的退出
    
    return 0;
}
