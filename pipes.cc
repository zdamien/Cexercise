#include "s.h"
//very basic pipe program

const int steps = 10;

void child(auto fh, int p=0) {
    char line[255];
    while (1) {
        auto ret = fgets(line, 255, fh);
        if (ret == nullptr) { 
            printf ("child EOF\n");
            break;
        }
        printf("child: %s", line);
    }

}

void parent(auto fh, int p) {
    for (int i=0; i<steps; i++) {
        auto ret = fprintf(fh, "parent step %d, child %d\n",i,p);
        fflush(fh);
        printf("parent printed %d chars\n", ret);
        //usleep(1e4);
    }
}


int fildes[2];

int main() {
    pipe(fildes);
    auto pid = fork();
    if (pid == 0) {
        close(fildes[1]); // read from parent
        auto fh = fdopen(fildes[0],"r");
        assert (fh != NULL);
        child(fh);
    }
    else  {
        close (fildes[0]); //write
        auto fh = fdopen(fildes[1],"w");
        parent(fh, pid );
    }
}
