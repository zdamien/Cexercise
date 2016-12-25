// clang -std=c++14 -lpthread -lstdc++ fork.cc
// or clang++ -std=c++14 -lpthread fork.cc

#include "ss.h"

// basic fork 

/*
void pr_cont(const auto &c) {
        for (auto i : c)
                    cout << i;
            cout << "\n";
}
*/
//not using this, just testing I can do it.
auto pr_cont = [](const auto &c) {
        for (auto i : c)
                    cout << i;
            cout << "\n";
};


const int steps = 5;

void child(int p=0) {
    for (int i=0; i<steps; i++) {
        printf("child step %d\n",i);
        usleep (20000);
    }
}

void parent(int p) {
    for (int i=0; i<steps; i++) {
        printf("parent step %d, child %d\n",i,p);
        usleep (20000);
    }
}


int main() {
    auto pid = fork();
    if (pid == 0) {
        child();
    }
    else 
        parent(pid);
}
