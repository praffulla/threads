// This program runs two threads which count number of even and odd intergers in range.

//This will teach us how to create a thread in c++. Basically: thread t1(fun, args); :D

#include <iostream>
#include <climits>
#include <ctime>
#include <thread>

using namespace std;

int even = 0;
int odd = 0;

void findEven(int st, int end) {

    for(int i = st; i <=end; i++) {
        if(i%2 == 0) {
            even++;
        }
    }
}

void findOdd(int st, int end) {

    for(int i = st; i <=end; i++) {
        if(i%2 != 0) {
            odd++;
        }
    }
}


int main() {

    int start = 0;
    int end = 1000000000;

    time_t now = time(0);
    cout << "now: " << now << "\n";

    thread t1(findEven, start, end);
    thread t2(findOdd, start, end);

    t1.join();
    t2.join();
    //findEven(start, end) ;
    //findOdd(start, end);

    time_t now2 = time(0);
    cout << "time: " << now2-now << "\n";

    cout << "even: " << even << "\nodd: " << odd;

    return 0;
}
