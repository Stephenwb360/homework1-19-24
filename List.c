// Stephen Wend-Bell, 2036245, pa1

//-----------------------------------------------------------------------------
// List.c
// Implementation file for List ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
#include "List.h"


// structs --------------------------------------------------------------------

// private Node type
typedef struct NodeObj* Node;

// private NodeObj type
typedef struct NodeObj{
   ListElement data;
   Node next;
   int index; //every time we append, increment index
} NodeObj;

// private ListObj type
typedef struct ListObj{
   Node front;
   Node back;
   Node cursor;
   int length;
} ListObj;


// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
Node newNode(ListElement data, int index){
   Node N = malloc(sizeof(NodeObj));
   assert( N!=NULL );
   N->data = data;
   N->index = index;
   N->next = NULL;
   return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}

// newList()
// Returns reference to new empty List object.
List newList(){
   List L;
   L = malloc(sizeof(ListObj));
   assert( L!=NULL );
   L->front = L->back = L->cursor = NULL; //valgrind error was L->cursor was never initialized
   L->length = 0;
   return(L);
}

// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL.
void freeList(List* pL){
   if(pL!=NULL && *pL!=NULL) { 
      while( !empty(*pL) ) { 
         deleteFront(*pL); 
      }
      (*pL)->front = (*pL)->back = (*pL)->cursor = NULL;
      (*pL)->length = 0;
      free(*pL);
      *pL = NULL;
   }
}


// Access functions -----------------------------------------------------------

// index()
// Returns index of cursor element if defined, -1 otherwise.
int index(List L) {
   if( L==NULL ){
      printf("List Error: calling index() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( empty(L) ){
      printf("List Error: calling index() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   if(L->cursor == NULL) {
      return -1;
   }
   return(L->cursor->index); //should be done? //awaiting further testing
}

// front()
// Returns the value at the front of Q.
// Pre: !empty(Q)
ListElement front(List L){
   if( L==NULL ){
      printf("List Error: calling front() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( empty(L) ){
      printf("List Error: calling front() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   return(L->front->data);
}

// Returns back element of L. Pre: length()>0
int back(List L) {
   if( L==NULL ){
      printf("List Error: calling back() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( empty(L) ){
      printf("List Error: calling back() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   return(L->back->data); //should be done //awaiting testing
}

// length()
// Returns the length of L.
int length(List L){
   if( L==NULL ){
      printf("List Error: calling length() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   return(L->length);
}

// get()
// Returns cursor element of L. Pre: length()>0, index()>=0
int get(List L) {
   if( L==NULL ){
      printf("List Error: calling get() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( empty(L) ){
      printf("List Error: calling get() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   if( index(L) < 0) {
      printf("List Error: calling get() when Index() < 0\n");
      exit(EXIT_FAILURE);
   }
   if( L->cursor == NULL) {
      printf("List Error: calling get() when cursor == NULL\n");
      exit(EXIT_FAILURE);
   }
   return(L->cursor->data); //done, not tested
}

// empty()
// Returns true if L is empty, otherwise returns false.
bool empty(List L){
   if( L==NULL ){
      printf("List Error: calling empty() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   return(L->length==0);
}

// equals()
// Returns true if A is same int sequence as B, false otherwise.
bool equals(List A, List B){
   if( A==NULL || B==NULL ){
      printf("List Error: calling equals() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }

   bool eq;
   Node N, M;

   eq = ( A->length == B->length );
   N = A->front;
   M = B->front;
   while( eq && N!=NULL){
      eq = ( N->data==M->data );
      N = N->next;
      M = M->next;
   }
   return eq;
}


// Manipulation procedures ----------------------------------------------------

// Resets L to its original empty state.
void clear(List L) {
   if( L == NULL) {
      printf("List Error: calling clear() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }

   while(!empty(L)) {
      deleteFront(L);
   }

   L->front = L->back = L->cursor = NULL;
   L->length = 0;
   //done?

}

// Overwrites the cursor element’s data with x. 
// Pre: length()>0, index()>=0
void set(List L, int x) {
   if( L == NULL) {
      printf("List Error: calling set() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( empty(L) ) {
      printf("List Error: calling set() on empty List reference\n");
      exit(EXIT_FAILURE);
   }
   if( index(L) < 0) {
      printf("List Error: calling set() on List with index < 0\n");
      exit(EXIT_FAILURE);
   }
   L->cursor->data = x; //needs testing
}

// If L is non-empty, sets cursor under the front element,
// otherwise does nothing.
void moveFront(List L) {
   if( L == NULL) {
      printf("List Error: calling moveFront() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( empty(L)) {
      printf("List Error: calling moveFront() on empty List reference\n");
      exit(EXIT_FAILURE);
   }
   L->cursor = L->front; //done, needs testing
}

// If L is non-empty, sets cursor under the back element,
// otherwise does nothing.
void moveBack(List L) {
   if( L == NULL) {
      printf("List Error: calling moveBack() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( empty(L)) {
      printf("List Error: calling moveBack() on empty List reference\n");
      exit(EXIT_FAILURE);
   }
   L->cursor = L->back; //done, needs testing
}

// If cursor is defined and not at front, move cursor one 
// step toward the front of L; if cursor is defined and at 
// front, cursor becomes undefined; if cursor is undefined 
// do nothing
void movePrev(List L) {
   if( L == NULL) {
      printf("List Error: calling movePrev() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( empty(L)) {
      printf("List Error: calling movePrev() on empty List reference\n");
      exit(EXIT_FAILURE);
   }
   
   if(L->cursor != NULL && L->cursor != L->front) {
      Node previous = NULL;
      Node current = L->front;

      while(current->next != L->cursor) {
         current = current->next;
      }
      previous = current;
      L->cursor = previous;
   } else if(L->cursor != NULL && L->cursor == L->front) {
      L->cursor = NULL;
   }
   //done? needs testing
}

// If cursor is defined and not at back, move cursor one 
// step toward the back of L; if cursor is defined and at 
// back, cursor becomes undefined; if cursor is undefined 
// do nothing
void moveNext(List L) {
   if( L == NULL) {
      printf("List Error: calling moveNext() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( empty(L)) {
      printf("List Error: calling moveNext() on empty List reference\n");
      exit(EXIT_FAILURE);
   }

   if(L->cursor != NULL && L->cursor != L->back) {
      L->cursor = L->cursor->next;
   } else if(L->cursor != NULL && L->cursor == L->back) {
      L->cursor = NULL;
   }
   //done needs testing
}

// Insert new element into L. If L is non-empty, 
// insertion takes place before front element.
void prepend(List L, int x) {
   if( L==NULL ){
      printf("List Error: calling prepend() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }

   Node N = newNode(x, 0); //index of 0
   if(empty(L)) {
      L->front = L->back = N;
   } else{
      N->next = L->front;
      L->front = N;
   }

   //fix indices
   Node current = L->front->next;
   int index = 1;
   
   while (current != NULL) {
      current->index = index;
      current = current->next;
      index++;
   }
   L->length++;
   //done, needs testing
}

// append()
// Places new data at the back of Q.
void append(List L, int data)
{
   int index = 0;
   Node N = newNode(data, index);
   index++;

   if( L==NULL ){
      printf("List Error: calling append() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   
   if( empty(L) ) { 
      L->front = L->back = N; 
   }else{ 
      L->back->next = N; 
      L->back = N; 
   }
   L->length++;
}

// Insert new element before cursor. 
// Pre: length()>0, index()>=0
void insertBefore(List L, int x) {
   if( L==NULL ){
      printf("List Error: calling insertBefore() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( empty(L) ){
      printf("List Error: calling insertBefore() on empty List reference\n");
      exit(EXIT_FAILURE);
   }
   if( index(L) < 0 ){
      printf("List Error: calling insertBefore() on index() < 0 List reference\n");
      exit(EXIT_FAILURE);
   }

   Node current = L->front;

   while(current->next != L->cursor && current->next != NULL) { //possibly fixed?
      current = current->next;
   }
   //current is now one space before cursor, or at the same spot at Front

   Node new = newNode(x, current->index);
   //index of new node is in correct spot

   if(L->cursor == L->front) {
      new->next = L->front;
      L->front = new;
   } else {
      current->next = new;
      new->next = L->cursor;
   }

   

   //need to fix indices
   current = L->cursor;
   while(current != NULL) {
      current->index++;
      current = current->next;
   }

   L->length++;
   //done, needs testing
}

// Insert new element after cursor. 
// Pre: length()>0, index()>=0
void insertAfter(List L, int x) {
   if( L==NULL ){
      printf("List Error: calling insertAfter() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( empty(L) ){
      printf("List Error: calling insertAfter() on empty List reference\n");
      exit(EXIT_FAILURE);
   }
   if( index(L) < 0 ){
      printf("List Error: calling insertAfter() on index() < 0 List reference\n");
      exit(EXIT_FAILURE);
   }
   
   Node new = newNode(x, L->cursor->index + 1);
   if(L->cursor == L->back) {
      L->back = new;
      L->cursor->next = new;
   }else {
   new->next = L->cursor->next;
   L->cursor->next = new;
   }

   //fix indices
   if(L->cursor->next->next != NULL) {
      Node current = L->cursor->next->next;
      while(current != NULL) {
         current->index++;
         current = current->next;
      }
   } //might be correct?
      

   L->length++;
}

// deleteFront()
// Deletes data at front of L.
// Pre: !empty(L)
void deleteFront(List L){
   if( L==NULL ){
      printf("List Error: calling deleteFront() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( empty(L) ){
      printf("List Error: calling deleteFront() on an empty List\n");
      exit(EXIT_FAILURE);
   }

   Node N = L->front;
   

   if( length(L)>1 ) { 
      if(L->cursor == L->front) {
         L->cursor = L->cursor->next;
      }//added this here in case length = 1
      L->front = L->front->next; 
   }else{ 
      L->front = L->back = NULL; 
      L->cursor = NULL;
   }
   L->length--;
   
   //rearrange indices 
   Node current = L->front;
   int index = 0;
   while(current != NULL) {
      current->index = index;
      current = current->next;
      index++;
   }//doesnt seem to cause valgrind errors

   

   freeNode(&N);
}

// Delete the back element. Pre: length()>0
void deleteBack(List L) {
   if( L==NULL ){
      printf("List Error: calling deleteBack() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( empty(L) ){
      printf("List Error: calling deleteBack() on an empty List\n");
      exit(EXIT_FAILURE);
   }

   if(L->cursor == L->back) {
      Node current = L->front;
      while(current->next != L->cursor) {
         current = current->next;
      }
      L->cursor = current;
   }
   
   Node N = L->back;
   if(length(L) > 1) {
      Node current = L->front;
      while(current->next->next != NULL) {
         current = current->next;
      }
      L->back = current;
      L->back->next = NULL;
   } else {
      L->front = L->back = NULL;
   }
   L->length--;
   freeNode(&N);
}

// Delete cursor element, making cursor undefined. 
// Pre: length()>0, index()>=0
void delete(List L) {
   if( L==NULL ){
      printf("List Error: calling delete() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( empty(L) ){
      printf("List Error: calling delete() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   if(index(L) < 0) {
      printf("List Error: calling delete() on an index < 0 List\n");
      exit(EXIT_FAILURE);
   }

   if(L->cursor == L->front) {
      deleteFront(L);
   } else if(L->cursor == L->back) {
      deleteBack(L);
   } else {
      Node current = L->front;
      while(current->next != L->cursor) {
         current = current->next;
      }
      current->next = L->cursor->next;
      freeNode(&(L->cursor));
      L->cursor = NULL;
      L->length--;
   }
   //done? needs testing
}


// Other Functions ------------------------------------------------------------

// printList()
// Prints a string representation of Q consisting of a space separated list 
// of ints to stdout.
void printList(FILE *file, List L){
   Node N = NULL;

   if( L==NULL ){
      fprintf(file, "List Error: calling printList() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }

   for(N = L->front; N != NULL; N = N->next){
      fprintf(file, FORMAT" ", N->data);
   }
   fprintf(file, "\n");
}

// Returns a new List representing the same integer 
// sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state 
// of L is unchanged.
List copyList(List L) {
   if( L==NULL ){
      printf("List Error: calling copyLIst() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }

   List copy = newList(); //new empty list
   Node current = L->front;

   while(current != NULL) {
      append(copy, current->data);
      current = current->next;
   }

   return copy;
   //done?
}

