#include "s.h"

//sample uses of popen()

int main() {
    auto fh = popen ("ls -Fsh","r");
    char line[255];
    while (fgets(line,255, fh) != nullptr) 
        printf("%s",line);
    pclose(fh);
    printf("====\n");
    fh = popen("cat","w");
    setlinebuf(fh);
    while (fgets(line,255, stdin) != nullptr) {
        fprintf(fh, "%s", line);
        //fflush(fh);  //don't need after setlinebuf()
    }
    pclose(fh);

}
