#include "MyThread.h"

MyThread::MyThread(int id) : id(id), running(false) {}
MyThread::~MyThread() {}

void MyThread::run()
{
    this->running = true;
    while (running)
    {
        std::cout << "Hello World! from Thread #" << this->id << ".\n";
        sleep(1000);
    }
}

void MyThread::dismiss()
{
    this->running = false;
}
