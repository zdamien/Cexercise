#include "s.h"

typedef int peg_t;

void tower (int ndiscs, peg_t source, peg_t middle, peg_t target) {
    assert (ndiscs >= 1);

    if (ndiscs == 1) {
        cout << "Move disc " << ndiscs << " from " << source << " to " << target << "\n";
        return;
    }
    tower (ndiscs-1, source, target, middle);
    cout << "Move disc " << ndiscs << " from " << source << " to " << target << "\n";
    tower (ndiscs-1, middle, source, target);
}

int main(int argc, char** argv) {
    int n;
    cin >> n;
    tower(n,1,2,3);
}
