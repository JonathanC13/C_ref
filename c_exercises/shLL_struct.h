// Linked list node
struct sh_node{
  int value;
  struct sh_node* next;
  struct sh_node* prev;
};


// creating shared node not working so how about a struct that contains struct pointers
// doesn't work
/*
struct sh_LL_array{
  struct sh_node *head_pt;  // just one for now.
};
*/

/*
They are using the shared memory but reader is not reading the correct value;

I think I found the problem, the malloc for creating a node overwrote the reader reference and not to the
shared memory.
  So, I think I can just set the values without the conventional way of creating a linked list.
  But this is redundant since when creating a shared memory is will be done by the OS and can be indexed already.
  Also the size of the shared memory is set at beginning so the benefits of linked list insertion and deletion are limited.

  A very unnecessary solution could be continually create share memory locations and link them.
    shared_1[0].next = shared_2[0]

Very complex problem, possible solutions:
  1. Duplicate linked lists in each process, but need synchronization to keep the lists the same
  2. Use a server to manage the list, send commands
  3. Could fork, since they will duplciate the linked list. Still need to sync them when changes are made.
*/
