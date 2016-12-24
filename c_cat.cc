// simple cat program, mostly C-style, in blocks. Works on stdin or one
// input file.  Doesn't behave like cat(1) because of block buffering.

#include <stdio.h>
#include <stdlib.h>

const int BUFSIZE = 4096;

int main(int argc, char** argv) {
    char buf[BUFSIZE];
    auto fp = stdin;
    if (argc == 2) {
        fp = fopen(argv[1],"r");
        if (fp == NULL) {
            fprintf(stderr, "Couldn't open file %s\n",argv[1]);
            exit(1);
        }
    }

    size_t nin = BUFSIZE;
    size_t nout = BUFSIZE;
    while (nin == BUFSIZE) {
        nin = fread(buf, sizeof(char), BUFSIZE, fp);
        nout = fwrite(buf, sizeof(char), nin, stdout);
        if (nout < nin) 
            fprintf(stderr, "ERROR: could only write %d out of %d \
                    bytes\n", nout, nin);
    }
    fclose(fp);
}
