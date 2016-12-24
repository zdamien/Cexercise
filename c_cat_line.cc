// simple cat program, mostly C-style, in lines. Works on stdin or one
// input file.

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    auto fp = stdin;
    if (argc == 2) {
        fp = fopen(argv[1],"r");
        if (fp == nullptr) {
            fprintf(stderr, "Couldn't open file %s\n",argv[1]);
            exit(1);
        }
    }

    // being pedantic about types:
    size_t bufsize = 0;
    ssize_t nin = 0;  //signed size_t, for negative retvalues
    int nout = 0;
    char* buf = nullptr;
    // getline reallocates buf as needed
    while ( (nin = getline(&buf, &bufsize, fp)) != -1) {
        nout = printf("%s", buf);
        if (nout < nin) 
            fprintf(stderr, "ERROR: could only write %d out of %d \
                    bytes\n", nout, nin);
    }
    free(buf);
    fclose(fp);
}
