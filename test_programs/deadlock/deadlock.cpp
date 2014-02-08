#include <iostream>
#include <thread>
#include <exception>
using namespace std;

bool doNot = 1; // this bool will prevent func1 and func2 from doing their tasks
thread* fn1; // pointer to t1 thread (defined in main function)
thread* fn2; // pointer to t2 thread (defined in main function)
void func1(bool x)
{
	while(doNot) {;} // waiting for changing doNot to false (doing it in main function)
	::fn2->join(); // trying to cause deadlock
}

void func2(bool x)
{
	while(doNot) {;} // waiting for changing doNot to false (doing it in main function)
	::fn1->join(); // trying to cause deadlock
}


int main()
{
	// making threads for func1 and func2. I don't know why I've added arguments to func1 & func2
	thread t1(func1, 1); 
	thread t2(func2, 1);
	// assigning values to pointers
	::fn1 = &t1;
	::fn2 = &t2;
	::doNot = 0; // STARTING!
	t1.join();
	t2.join();
	cout << "Hello!"; // This code will never be done...
}


b
