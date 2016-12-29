// self-test on my ability to do backtracking.  Took 30 minutes in total.

#include "s.h"

using QarrayT = vector<int>;

bool valid (const QarrayT &qa, int column) {
    for (int i=0; i<column; i++) {
        if (qa[i] == qa[column]) //queens share a row
            return false;
        if (column-i == abs(qa[column]-qa[i]))
            return false; //queens share a diagonal
    }
    return true;
}

// In this case backtracking works even without copying the array.
pair<bool, QarrayT> queens (QarrayT &qa, int column) {
    for (int row=0; row<8; row++) {
        qa[column]=row;
        if (!valid(qa, column))
            continue;
        if (column == 7)
            return make_pair(true, qa);
        auto result = queens(qa, column+1);
        if (result.first) // done!
            return result;
        else
            ; //nothing to do, just making the loop explicit
    }
    return make_pair(false,qa);  // no valid assignment
}

// prints at 90 degrees to how I labeled things.  Chessboard squares
// maked for easy visual confirmation of no-diagonal sharing.
void print_board(const QarrayT &qa) {
    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            cout << ((qa[i]==j) ? 'Q' : ( (i+j)%2 ? '.' : '_' ));
        }
        cout << "\n";
    }
}

int main() {
    QarrayT qa(8,-1);
    pr_cont (qa);
    print_board(qa);
    auto res = queens(qa,0);
    if (res.first) {
        pr_cont (res.second);
        print_board(res.second);
    }
}
