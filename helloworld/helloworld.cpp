// helloworld.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>

#include "MyThread.h"

void testFunc(int x)
{
    //std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    std::cout << "Hello World! from Thread #" << x << ".\n";
}

int main()
{
    std::cout << "Hello World! from Thread main.\n";

    const int numThreads = 10000;
    MyThread threads[numThreads];

    for (int i = 0; i < numThreads; i++)
    {
        threads[i] = MyThread(i);
        threads[i].start();

        // Single Thread
        /*MyThread helloThread = MyThread(i);
        helloThread.start();*/

        // using <thread>
        //std::thread myThread(testFunc, i);
        //myThread.detach();
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(10000));

    for (int i = 0; i < numThreads; i++)
    {
        threads[i].dismiss();
    }

    // Paladesisyon si C++. Join vs Detach.
    // Needs to know what behavior to perform once it's done.
    // To report the results back to the main thread. "success"
    // Guaranteed data from this thread can be used in the main thread.
    // thread.join() : Main thread waits for the thread to finish to "join" back together.
    // thread.detach() : Separates the thread to execute asynchronously from main thread.
    // Doc Neil says use detach all the time.
    // While join is seemingly easy to identify, in terms of real world problems, it's a restrictive solution.
    // For example, in a game with a background thread for checking if there is network connection,
    // the connection must remain throughout the lifecycle of the program. Those bg threads that are persistent,
    // join is not ideal as these threads never end.
    // In join, the point at which the thread joins back together is called the "rendezvous" point.
    // Detach has no rendezvous point so it runs independently from the main thread. Regardless of its status,
    // the main thread continues to run and terminate whenever it does.

    std::cout << "Bye World! from Thread main.\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
