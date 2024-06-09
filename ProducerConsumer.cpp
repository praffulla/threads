Always write down all the constraints before solving any thread problems:
Here are three conditions:
1. Mutual exclusion while accesing buffer. (R-W)
2. Producer can't produce more if buffer is full;
3. Consumer can't consume more if buffer is empty;

Now you can see that both producer and consumer has to signal each other for above two condition. So need a condition variable.

#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

using namespace std;

mutex m;
condition_variable cv;
deque<int> buffer;
int maxBuffSize = 50;


bool isSomeSpace() {
	if (buffer.size() < maxBuffSize )
		return true;
	return false;
}

bool isSomeItems() {
        if (!buffer.empty())
                return true;
        return false;
}

void producer(int val) {
   while(val) {
	unique_lock<mutex> ul(m);
	cv.wait(ul, isSomeSpace);
	buffer.push_back(val);
	cout << "Producer:" << val << endl;
	val--;
	cv.notify_one();
   }
  
}

void consumer() {
   while(true) {
	unique_lock<mutex> ul(m);
	cv.wait(ul, isSomeItems);
	int item = buffer.back();
	buffer.pop_back();
	cout << "Consumer: " << item << endl;
	cv.notify_one();
}

int main () {

	thread t1(producer, 100);
	thread t2(consumer);

	t1.join();
	t2.join();
}
