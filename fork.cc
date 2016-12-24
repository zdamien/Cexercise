#include "s.h"

// basic fork 

const int steps = 5;

void child(int p=0) {
    for (int i=0; i<steps; i++) {
        printf("child step %d\n",i);
        sleep (0.2);
    }
}

void parent(int p) {
    for (int i=0; i<steps; i++) {
        printf("parent step %d, child %d\n",i,p);
        sleep (0.3);
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
