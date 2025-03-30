#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
    List *list = (List*)malloc(sizeof(List));
    list -> head = NULL;
    list -> tail = NULL;
    list -> current = NULL;
    return list;
}

void * firstList(List * list) {
    if (list -> head == NULL) return NULL;
    list -> current = list -> head;
    return list -> current -> data;
}

void * nextList(List * list) {
    if (list -> current == NULL || list -> current -> next == NULL) return NULL;
    list -> current = list -> current -> next;
    return list -> current -> data;
}

void * lastList(List * list) {
    if (list -> current == NULL) return NULL;
    while (list -> current -> next != NULL){
        list ->current = list -> current -> next;
    }
    list -> tail = list -> current;
    return list -> current -> data;
}

void * prevList(List * list) {
    if (list -> current == NULL || list -> current -> prev == NULL) return NULL;
    list -> current = list -> current -> prev;
    return list -> current -> data;
}

void pushFront(List * list, void * data) {
    Node* Nuevo = createNode(data);
    if (list -> head == NULL) {
        list -> head = Nuevo;
        list -> tail = Nuevo;
    } else {
        Nuevo -> next = list -> head;
        list -> head -> prev = Nuevo;
        list -> head = Nuevo;
    }
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
    if (list -> current == NULL) return;
    Node *Nuevo = createNode(data);
    Nuevo-> next = list -> current -> next;
    Nuevo-> prev = list -> current;
    if (list -> current -> next != NULL) list -> current -> next -> prev = Nuevo;
    else
        list -> tail = Nuevo;
    
    list -> current -> next = Nuevo;
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
    if (list -> current == NULL) return NULL;
    Node *Aux = list -> current;
    void *datito = Aux-> data;
    Node *AuxI = list -> current -> prev;
    Node *AuxD = list -> current -> next;
    if (AuxI != NULL) {
        AuxI -> next = AuxD;
    } else {
        list -> head = AuxD;
    }
    if (AuxD != NULL) {
        AuxD -> prev = AuxI;
    } else {
        list -> tail = AuxI;
    }
    list -> current = AuxD;
    free(Aux);
    return datito;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}