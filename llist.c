/* singly linked list exercise.  Basic data structure taking int values,
 * and two sets of functions: foo1() where the list might be no more
 * than a null pointer, and the list is always returned, foo2() where
 * it's assumed there's a sentinel header */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node* next;
} node;

node* head_insert (node* list, int data){
    node* newnode = (node*) malloc(sizeof(node));
    newnode->next=list;
    newnode->data=data;
    return newnode;
}

node* tail_insert (node* list, int data){

    if (list == NULL) {
        node* newnode = (node*) malloc(sizeof(node));
        newnode->next=NULL;
        newnode->data=data;
        return newnode;
    }

    node* temp=list;
    while (temp->next != NULL)
        temp = temp->next;
    node* newnode = (node*) malloc(sizeof(node));
    newnode->next=NULL;
    newnode->data=data;
    temp->next = newnode;

    return list;
}

void print_list(const node* list) {
    // prints the 0 header of header lists becaus I haven't tried to be
    // cleverer about it.
    printf(":");
    while (list != NULL) {
        printf("%d:",list->data);
        list = list->next;
    }
    printf("\n");
}

node* delete1(node* list, int data) {
    /* version: iterative, total paranoia about inputs: no sentinel
     * node; data possibly missing; list possibly NULL. user must catch
     * return value, e.g. list = delete1(list, val); */

    node* temp = list;

    if (list == NULL) return list;
    else if (list->next == NULL && list->data != data) return list;
    else if (list->next == NULL && list->data == data) {
        free(list);
        return NULL;
    }
    else if (list->data == data) {
        temp = list->next;
        free(list);
        return temp;
    }
    else {
        while (temp->next != NULL && temp->next->data != data)
            temp = temp->next;
        if (temp->next != NULL) {
            node* t = temp->next;
            temp->next = temp->next->next;
            free(t);
            return list;
        }
    }
    return list;
}

node* make_header() {
    node* t = (node*) malloc(sizeof(node));
    t->next = NULL;
    t->data = 0;
    return t;
}

void head_insert2(node* list, int data) {
    node* temp = (node*) malloc(sizeof(node));
    temp->data = data;
    temp->next = list->next;
    list->next = temp;
}

void delete2(node* list, int data) {
    /* assumes is passed a safe header node */

    node* temp = list;
    while (temp->next != NULL && temp->next->data != data)
        temp = temp->next;
    if (temp->next != NULL) {
        node* t = temp->next;
        temp->next = temp->next->next;
        free(t);
    }
}

void destroy1 (node* list) {
    while ( list != NULL) {
        node *tmp = list;
        list = list->next;
        free (tmp);
    }
}



int main() {
    node* list=NULL;

    list = delete1(list,2);
    list = head_insert(list,1);
    print_list(list);
    list = delete1(list,2);
    list = delete1(list,1);
    print_list(list);

    printf("===\n");
    list = head_insert(list,1);
    print_list(list);
    list = head_insert(list,2);
    print_list(list);
    list = delete1(list,3);
    print_list(list);
    list = delete1(list,2);
    print_list(list);
    list = delete1(list,1);
    print_list(list);
    printf("===\n");
    list = head_insert(list,2);
    list = head_insert(list,3);
    list = head_insert(list,4);
    print_list(list);

    destroy1(list);
    printf("===\n");
    printf("===\n");

    node* list2= make_header();
    head_insert2(list2,1);
    head_insert2(list2,2);
    delete2(list2,1);
    print_list(list2);
    delete2(list2,2);
    delete2(list2,3);
    print_list(list2);

    head_insert2(list2,1);
    head_insert2(list2,2);
    head_insert2(list2,3);
    tail_insert(list2,3);
    delete2(list2,3);
    print_list(list2);
    destroy1 (list2);
}

