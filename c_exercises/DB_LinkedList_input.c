#include <stdio.h>
#include <stdlib.h>

#include "DB_LinkedList_lib.h"

// Forward declaration
struct node;

void create_node(struct node **headRef, int value);

int main(){

  // head pointer
  struct node* head;
  struct node* temp;

  // Initialize linked list`
  int node_data;
  printf("Input data for first node: ");
  scanf("%d", &node_data);

  // printf("%p", head)   address of the stuff it is pointing to
  // printf("%p", &head)  address of the actual pointer
   //printf("head: %p\n", head)  ;
   //printf("&head: %p\n\n", &head)  ;
  // create the first node;
  printf("\ncreate head ===\n");
  create_node(&head, node_data);  // use & on a pointer to explicitly pass the address of a pointer.

  printList(head);

  printf("\nappendTail ===\n");
  // Append to list
  appendTail(head, 10);
  appendTail(head, 2);
  appendTail(head, 20);

  printList(head);

  printf("\npushHead ===\n");
  pushHead(&head, 100);
  pushHead(&head, -5);

  printList(head);

  printf("\npopHead ===\n");
  popHead(&head);
  popHead(&head);

  printList(head);
  //printBackward(head);

  printf("\ndeleteTail ===\n");
  deleteTail(head);

  printList(head);
  //printBackward(head);

  printf("\ninsertNode ===\n");
  insertNode(&head, 99, 3);
  insertNode(&head, 66, 0);

  printList(head);
  //printBackward(head);

  printf("\ndeleteNode ===\n");
  deleteNode(&head, 4);

  printList(head);
  printBackward(head);

  free(head);
/*
  int *p;
  int c = 5;

  printf("address of pointer: %p\n", &p);
  printf("address of stuff pointed to: %p (should change next step)\n", p);
  p = &c;
  printf("address of stuff pointed to now assigned: %p\n", p);
  printf("address of variable: %p", &c);
*/
}

void create_node(struct node** headRef, int value){

  //printf("headRef: %p\n", headRef)  ;
  //printf("&headRef: %p\n", &headRef)  ;
  //printf("*headRef: %p\n", *headRef)  ;
  // struct node *new = *headRef    get the value of head

  struct node *new;
  new = malloc(sizeof(struct node));
  (*new).value = value;
  new->prev = NULL;
  new->next = NULL;

  *headRef = new;

}
