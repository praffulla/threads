#include <iostream>
#include <semaphore>
#include <thread>
#include <chrono>

using namespace std;

std::binary_semaphore mainToThread{0};
std::binary_semaphore threadToMain{0};

void myFun() {

	cout << "thread: waiting for main to give me signal" << endl;
	mainToThread.acquire();
	cout << "thread: doing my work " << endl;
	std::this_thread::sleep_for(std::chrono::seconds(5));
	threadToMain.release();
	cout << "thread: main can finish now" << endl;
}

int main () {

	thread t1(myFun);

	cout << "main: started my work " << endl;

	std::this_thread::sleep_for(std::chrono::seconds(1));
	cout << "main: thread can start its work" << endl;
	mainToThread.release();

	threadToMain.acquire();
	cout << "main: my last work " << endl;

	t1.join();


}
