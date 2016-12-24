#include "s.h"

// parent to child echo

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
    char line[255];
    while(true) {
        auto fret = fgets(line,255,stdin);
        if (!fret) break;
        int ret = write(fh, line,strlen(line));
        // ^ not strlent +1; writing the null makes child fgets fail
        //auto ret = fprintf(fh, line);
        //fflush(fh);
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
        //auto fh = fdopen(fildes[1],"w");
        auto fh = fildes[1];
        parent(fh, pid );
    }
}
