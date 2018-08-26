#ifndef LinkedList_H_  /* Include guard */
#define LinkedList_H_

struct node{
  int value;
  struct node* prev;
  struct node* next;
};

void printList(struct node *head);

void printBackward(struct node *head);

void pushHead(struct node **headRef, int value);

void appendTail(struct node *head, int value);

void insertNode(struct node **headRef, int value, int index);

void popHead(struct node **headRef);

void deleteTail(struct node *head);

void deleteNode(struct node **headRef, int index);

#endif
