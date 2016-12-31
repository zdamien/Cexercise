#include <string>
#include <thread>
#include <cstdio>
#include <unistd.h>

// just trying out pipes with threads

using namespace std;

int main() {
    int pipes1[2];
    pipe(pipes1);

    auto parent = [](int fd) {
        auto fh = fdopen(fd,"w");
        //setlinebuf(fh);
        setbuf(fh,nullptr); //unbuffered
        for (auto i=0;i<10;i++) {
            printf("parent %d\n",i);
            fprintf(fh, "%d\n",i);
            //fflush(fh);  //need this //not with setlinebuf or unbuf
        }
        fclose(fh);
    };
    auto child = [](int fd) {
        auto fh = fdopen(fd,"r");
        int i;
        printf("child -\n");
        while (EOF != fscanf(fh,"%d",&i)) {
            printf("child %d\n",i);
        }
        printf("child end\n");
        fclose(fh);

    };
    thread t1(parent,pipes1[1]);
    thread t2(child,pipes1[0]);
    t1.join();
    t2.join();

}
