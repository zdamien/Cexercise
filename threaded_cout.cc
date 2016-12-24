/* Inspired by https://stackoverflow.com/a/33763751/7233162

 Illustrates that printf is roughly one operation -- I believe stdio is
 locked internally by default, so prints won't interleave -- while the
 cout stream is the equivalent of several function calls, which can be
 interveaved by multiple threads using cout.  */


#include <string>
#include <iostream>
#include <thread>
#include <cstdio>
#include <unistd.h>

using namespace std;

void task(int taskNum, string msg, bool useCout=true) {
    for (int i = 0; i < 5; ++i) {
        if (useCout)
            cout << "\n#" << taskNum << ": " << msg << ": " << i << ':' << "\n";
        else
            printf("\n#%d: %s: %d:\n", taskNum, msg.c_str(), i);
        usleep(10000);
    }
}

int main() {
    //thread t1(task, 1, "ABC");  // this didn't compile
    thread t1(task, 1, "co ABC", true);
    thread t2(task, 2, "co xyz", true);
    thread t3(task, 3, "pf ABC", false);
    thread t4(task, 4, "pf ABC", false);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    return 0;
}
