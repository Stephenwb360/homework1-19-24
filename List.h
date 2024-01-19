// Stephen Wend-Bell, 2036245, pa1

#ifndef LIST_H_INCLUDE_
#define LIST_H_INCLUDE_
#include<stdbool.h>
#include <stdio.h>

#define FORMAT "%d"  // format string for ListElement

typedef int ListElement; // should this be an int?
typedef struct ListObj* List;

// Constructors-Destructors ---------------------------------------------------

List newList(void); // Creates and returns a new empty List. //DONE
void freeList(List* pL); // Frees all heap memory associated with *pL, and sets //DONE
 // *pL to NULL.

// Access functions -----------------------------------------------------------

int length(List L); // Returns the number of elements in L. //DONE
int index(List L); // Returns index of cursor element if defined, -1 otherwise. //DONE?
int front(List L); // Returns front element of L. Pre: length()>0 //DONE
int back(List L); // Returns back element of L. Pre: length()>0 //DONE?
int get(List L); // Returns cursor element of L. Pre: length()>0, index()>=0 //DONE?
bool equals(List A, List B); // Returns true iff Lists A and B contain the same //DONE
 // sequence of elements, returns false otherwise.
bool empty(List L); //Returns true if L is empty //DONE

// Manipulation procedures ----------------------------------------------------

void clear(List L); // Resets L to its original empty state. //DONE?
void set(List L, int x); // Overwrites the cursor element’s data with x. //DONE?
 // Pre: length()>0, index()>=0
void moveFront(List L); // If L is non-empty, sets cursor under the front element, //DONE?
 // otherwise does nothing.
void moveBack(List L); // If L is non-empty, sets cursor under the back element, //DONE?
 // otherwise does nothing.
void movePrev(List L); // If cursor is defined and not at front, move cursor one //DONE?
 // step toward the front of L; if cursor is defined and at 
 // front, cursor becomes undefined; if cursor is undefined 
 // do nothing
void moveNext(List L); // If cursor is defined and not at back, move cursor one //DONE?
 // step toward the back of L; if cursor is defined and at 
 // back, cursor becomes undefined; if cursor is undefined 
 // do nothing
void prepend(List L, int x); // Insert new element into L. If L is non-empty, //DONE?
 // insertion takes place before front element.
void append(List L, int x); // Insert new element into L. If L is non-empty, //DONE
 // insertion takes place after back element.
void insertBefore(List L, int x); // Insert new element before cursor. //DONE?
 // Pre: length()>0, index()>=0
void insertAfter(List L, int x); // Insert new element after cursor. //DONE?
 // Pre: length()>0, index()>=0
void deleteFront(List L); // Delete the front element. Pre: length()>0 //DONE
void deleteBack(List L); // Delete the back element. Pre: length()>0 //DONE
void delete(List L); // Delete cursor element, making cursor undefined. //DONE
 // Pre: length()>0, index()>=0

// Other operations -----------------------------------------------------------

void printList(FILE* out, List L); // Prints to the file pointed to by out, a //DONE 
 // string representation of L consisting 
// of a space separated sequence of integers,
// with front on left.
List copyList(List L); // Returns a new List representing the same integer //DONE?
 // sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state 
// of L is unchanged.




#endif