// Stephen Wend-Bell, 2036245, pa1

//-----------------------------------------------------------------------------
// ListTest.c
// Another test client for List ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"List.h"

int main(int argc, char* argv[]){

    FILE *outputFile = fopen("output.txt", "w");
    if(outputFile == NULL) {
        fprintf(stderr, "Error opening file\n");
        exit(EXIT_FAILURE);
    }
    int i;
    List Q = newList();
    List R = newList();

   printf("\n");

   for(i=1; i<=10; i++){
      append(Q, i);
   }
   printList(outputFile, Q);

   for(i=1; i<=5; i++){
      deleteFront(Q);
   }
   printList(outputFile, Q);

   for(i=11; i<=15; i++){
      append(Q, i);
   }
   printList(outputFile, Q);

   for(i=16; i<=19; i++){
      append(Q, i);
   }
   printList(outputFile, Q);
   printf("\n");

   for(i=13; i<=19; i++){
      deleteFront(Q);
      append(R, i);
   }
   printList(outputFile, Q);
   printList(outputFile, R);
   fprintf(outputFile, "Q==R is %s\n\n", equals(Q, R)?"true":"false");

   append(Q, 20);
   append(R, 200);
   printList(outputFile, Q);
   printList(outputFile, R);
   fprintf(outputFile, "Q==R is %s\n\n", equals(Q, R)?"true":"false");

   freeList(&Q);
   freeList(&R);
   //return(EXIT_SUCCESS);
   /* Output:

1 2 3 4 5 6 7 8 9 10
6 7 8 9 10
6 7 8 9 10 11 12 13 14 15
6 7 8 9 10 11 12 13 14 15 16 17 18 19

13 14 15 16 17 18 19
13 14 15 16 17 18 19
Q==R is true

13 14 15 16 17 18 19 20
13 14 15 16 17 18 19 200
Q==R is false

*/

//MY NEW TESTING
fprintf(outputFile, "\nMy New Testing Starts here:\n");
List Steph = newList();

for(int i = 5; i <= 20; i++) {
    append(Steph, i);
}
fprintf(outputFile, "Printing list:\n");
printList(outputFile, Steph);

for(int i = 21; i <= 25; i++) {
    prepend(Steph, i);
}
fprintf(outputFile, "Prepending list:\n");
printList(outputFile, Steph);

fprintf(outputFile, "Length of list is: %d\n", length(Steph));
fprintf(outputFile, "Index (should be -1) of list Steph is: %d\n", index(Steph));

moveFront(Steph);
fprintf(outputFile, "Moved cursor under front element\n");
fprintf(outputFile, "Index of cursor is: %d\n", index(Steph));

moveNext(Steph);
fprintf(outputFile, "Moved cursor to the next element\n");
fprintf(outputFile, "Index of cursor is: %d\n", index(Steph));

moveNext(Steph);
moveNext(Steph);
moveNext(Steph);
movePrev(Steph);
movePrev(Steph);
fprintf(outputFile, "Index should be 2, Index: %d\n\n", index(Steph));

fprintf(outputFile, "Inserting an element before the cursor at index: %d\n", index(Steph));
insertBefore(Steph, 42);
printList(outputFile, Steph); //fixed?

fprintf(outputFile, "Cursor element at Index: %d is %d\n", index(Steph), get(Steph));
movePrev(Steph);
fprintf(outputFile, "Cursor element at Index: %d is %d\n", index(Steph), get(Steph));
moveNext(Steph);
moveNext(Steph);
fprintf(outputFile, "Cursor element at Index: %d is %d\n", index(Steph), get(Steph));

fprintf(outputFile, "Inserting element 420 after Index: %d\n", index(Steph));
insertAfter(Steph, 420);
printList(outputFile, Steph);

moveNext(Steph);
fprintf(outputFile, "Cursor element at Index: %d is %d\n", index(Steph), get(Steph));
moveNext(Steph);
fprintf(outputFile, "Cursor element at Index: %d is %d\n", index(Steph), get(Steph));

fprintf(outputFile, "Deleting cursor element at Index: %d\n", index(Steph));
delete(Steph);
printList(outputFile, Steph);

moveFront(Steph);
fprintf(outputFile, "Moved cursor to front. Cursor element at Index: %d is %d\n", index(Steph), get(Steph));

fprintf(outputFile, "Deleting front and back elements of list\n");
deleteFront(Steph);
deleteBack(Steph);
printList(outputFile, Steph);
fprintf(outputFile, "Cursor element at Index: %d is %d\n", index(Steph), get(Steph));
moveNext(Steph);
fprintf(outputFile, "Cursor element at Index: %d is %d\n", index(Steph), get(Steph));

fprintf(outputFile, "Moving cursor to last element in list. Index: %d\n", index(Steph));
moveBack(Steph);
fprintf(outputFile, "Cursor element at Index: %d is %d\n", index(Steph), get(Steph));
printList(outputFile, Steph);
fprintf(outputFile, "Deleting last element in list\n");
deleteBack(Steph);
printList(outputFile, Steph);
fprintf(outputFile, "Cursor element at Index: %d is %d\n", index(Steph), get(Steph));

List copy = copyList(Steph);
fprintf(outputFile, "Printing copy of list Steph:\n");
printList(outputFile, copy);
fprintf(outputFile, "deleting list copy\n");
clear(copy);
printList(outputFile, copy);

fprintf(outputFile, "Front and Back values of list Steph are %d and %d\n", front(Steph), back(Steph));
printList(outputFile, Steph);

moveBack(Steph);
fprintf(outputFile, "Cursor element at Index: %d is %d\n", index(Steph), get(Steph));

append(copy, 1);
moveFront(copy);
fprintf(outputFile, "Index of cursor in copy is: %d\n", index(copy));

clear(copy);
append(copy, 1);
moveFront(copy);
insertBefore(copy, 3);
printList(outputFile, copy);


freeList(&Steph);
freeList(&copy);
}
