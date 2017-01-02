// Got told implementing a doubly linked list might be an interview
// question, so making sure I can do it, fast and correct. 21 minutes.

#include "s.h"

class not_found {};

struct Node {
    int val;
    Node* next;
    Node* prev;
    Node() : val(0), next(nullptr), prev(nullptr) {}
};

class Dlist { // doubly linked list
    Node head;
    Node tail;
    Node* get_node(int v);
public:
    Dlist();
    ~Dlist();
    void push_front(int v);
    void push_back(int v);
    bool in(int v);
    void del(int v);
    void print();
    void rprint();
};

Dlist::Dlist() {
    head.next = &tail;
    tail.prev = &head;
}

Node* Dlist::get_node(int v) {
    Node* np = head.next;
    while (np != &tail && np->val != v)
        np = np->next;
    if (np == &tail)
        throw not_found();
    else return np;
}

bool Dlist::in(int v) {
    try {
        Node *np = get_node(v);
        return true;
    }
    catch (not_found e) {
        return false;
    }
}

void Dlist::push_front (int v) {
    Node *np = new Node;
    np->val = v;
    np->prev = &head;
    np->next = head.next;
    head.next->prev = np;
    head.next = np;
}

void Dlist::push_back (int v) {
    Node *np = new Node;
    np->val = v;
    np->next = &tail;
    np->prev = tail.prev;
    tail.prev->next = np;
    tail.prev = np;
}

void Dlist::print() {
    Node *np = head.next;
    while (np != &tail) {
        cout << np->val << ":";
        np = np->next;
    }
    cout << "\n";
}

Dlist::~Dlist() {
    Node *np = head.next;
    Node * tmp;
    while (np != &tail) {
        tmp = np;
        np = np->next;
        delete tmp;
    }
}

// 17 minutes ^  

void Dlist::del (int v) {
    Node *np = get_node(v);
    np->prev->next = np->next;
    np->next->prev = np->prev;
    delete np;
}

void Dlist::rprint() {
    Node *np = tail.prev;
    while (np != &head) {
        cout << np->val << ":";
        np = np->prev;
    }
    cout << "\n";
}

// ^ another 4 minutes

int main() {
    Dlist dl;
    cout << dl.in(3) << "\n";
    dl.push_back(1);
    dl.push_back(2);
    dl.push_back(3);
    dl.print();
    dl.push_front(4);
    dl.push_front(5);
    dl.push_front(6);
    dl.print();
    cout << dl.in(3) << "\n";
    cout << dl.in(5) << "\n";
    cout << dl.in(7) << "\n";
    dl.del(5);
    dl.print();
    dl.rprint();
    dl.del(3);
    dl.print();
    dl.push_back(7);
    dl.print();
    dl.rprint();
}
