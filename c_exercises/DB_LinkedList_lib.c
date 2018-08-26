// Doubly Linked List
// Inserting, deleting, traversing. Sort later.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "DB_LinkedList_lib.h"

// Forward declaration
struct node;

void printList(struct node *head){
  struct node* temp = head;
  printf("Printing linked list:\n");

  for(temp; temp != NULL; temp = temp->next){
    printf("%d ", (*temp).value);
  }
  printf("\n");
}

void printBackward(struct node *head){
  printf("printing backward to test prev links: \n");
  struct node* temp = head;
  // traverse to end first
  for(temp; temp->next != NULL; temp = temp->next){
  }

  for(temp; temp != NULL; temp = temp->prev){
    printf("%d ", (*temp).value);
  }
  printf("\n");
}

// Adding to head.
// Need to use double pointer so we can pass the address of the actual pointer so we can change its value.
// pushHead(struct node *head, int value){ head = newNode} only changes the pointer value locally.
void pushHead(struct node **headRef, int value){

  struct node *head = *headRef; // get the address of the actual pointer

  struct node *newNode;

  newNode = malloc(sizeof(struct node));
  newNode->value = value;
  newNode->prev = NULL;

  // link head prev node to new node
  head->prev = newNode;

  // link new node to the head
  newNode->next = head; // link to the value

  *headRef = newNode; // change head to the new node. by chaning the pointer value.

}

// Appending at end
void appendTail(struct node *head, int value){

  struct node* newNode;

  newNode = malloc(sizeof(struct node));
  newNode->value = value;
  newNode->next = NULL;

  struct node* trav = head;

  // traverse to last node
  while (trav->next != NULL){
    trav = trav->next;
  }

  // at last node add the new node after it.
  trav->next = newNode;

  // new Node links
  newNode->prev = trav;

}

// **head, just in case they put index 0.
void insertNode(struct node **headRef, int value, int index){

  if(index == 0){
    pushHead(headRef, value);
  } else {

    // count the size of the linked list so if the user wants to append at the end.
    int i_count = 0;
    struct node *count = *headRef;
    while(count != NULL){
      i_count ++;
      count = count->next;
    }

    if(index < i_count){

      struct node* trav = *headRef;

      // traverse to node before insertion point
      for (int i = 1; i < index; i ++){
        trav = trav->next;
      }

      struct node *newNode;
      newNode = malloc(sizeof(struct node));
      newNode->value = value;

      // now link the newNode inbetween
      newNode->prev = trav;
      newNode->next = trav->next;

      //re-link node in front
      trav->next->prev = newNode;

      // re-link trav node
      trav->next = newNode;
    } else {

      // check if they really want the end.
      if ((i_count) == index){

        appendTail(*headRef, value);
      } else {
        // nothing since out of bounds
      }

    }

  }

}

// Remove the first node from the list
// Also need double pointer to alter actual pointer value at its address.
void popHead(struct node **headRef){

  struct node *temp = *headRef;

  if(temp->next != NULL){

    temp = temp->next;

    // remove prev link on the new head.
    temp->prev = NULL;

    // reference new head
    *headRef = temp;
  }

}

// Delete the very last node
void deleteTail(struct node *head){

  struct node* temp = head;
  // traverse to the second last node
  for(temp; temp->next->next != NULL; temp = temp->next){
  }

  // remove last node's previous link, dont really need this since we'll never be able to get to this node.
  (temp->next)->prev = NULL;

  // remove second last node link to last node.
  temp->next = NULL;


}

// deal with user deleting head and tail
void deleteNode(struct node **headRef,int index){

  // deletion at the head
  if(index == 0){
    popHead(headRef);
  } else {

    // count the size of the linked list so if the user wants to append at the end.
    int i_count = 0;
    struct node *count = *headRef;
    while(count != NULL){
      i_count ++;
      count = count->next;
    }

    if (index < i_count-1){

      struct node* trav = *headRef;

      // get the node before the deletion index
      for (int i = 1; i < index; i ++){
        trav = trav->next;
      }

      // relink node after index node to current
      trav->next->next->prev = trav;

      // relink current node to node after index
      trav->next = trav->next->next;
    } else {
      printf("\ncount: %d\n", i_count);
      if((i_count-1) == index){
        deleteTail(*headRef);
      }

    }
  }

}
