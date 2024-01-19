// Stephen Wend-Bell, 2036245, pa1
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include "List.h"

#define MAX_LEN 300

char* duplicateString(char* source);

int main(int argc, char * argv[]){

   int token_count, line_count;
   FILE *in, *out;
   char line[MAX_LEN];
   char tokenBuffer[MAX_LEN];
   char* token;

   //list
   List Steph = newList();
   char *lines[MAX_LEN];

   // check command line for correct number of arguments
   if( argc != 3 ){
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
   }

   // open files for reading and writing 
   in = fopen(argv[1], "r");
      if( in==NULL ){
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }

   out = fopen(argv[2], "w");
   if( out==NULL ){
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
   }

   // read each line of input file, then count and print tokens
   line_count = 0;
   while( fgets(line, MAX_LEN, in) != NULL)  {

        lines[line_count] = duplicateString(line);
        if (lines[line_count] == NULL) {
            fprintf(out, "Memory allocation failed.\n");
            exit(EXIT_FAILURE);
        }

        line_count++;



      // get tokens in this line
      token_count = 0;
      tokenBuffer[0] = '\0';

      // get first token
      token = strtok(line, " \n");

      while( token!=NULL ){ // we have a token
         // update token buffer
         strcat(tokenBuffer, "   ");
         strcat(tokenBuffer, token);
         strcat(tokenBuffer, "\n");
         token_count++;

         // get next token
         token = strtok(NULL, " \n");
      }

      

      // print tokens in this line
    //   fprintf(out, "line %d contains %d ", line_count, token_count);
    //   fprintf(out, "token%s: \n", token_count==1?"":"s" );
    //   fprintf(out, "%s\n", tokenBuffer);
      //fprintf(out, "%s\n", lines[line_count-1]);
   }

    //List sorting
    //sort the strings, and store the index values in the list as data

    append(Steph, 0);

    for(int i = 1; i < line_count; i++) {
        moveFront(Steph);
        if(index(Steph) == -1) {
            printf("Index of Steph is -1");
            exit(EXIT_FAILURE);
        }
        while(strcmp(lines[i], lines[get(Steph)]) > 0) { //if true, s1 comes after s2
            moveNext(Steph);
            if(index(Steph) == -1) {
                moveBack(Steph);
                break;
            }
        }
        if(strcmp(lines[i], lines[get(Steph)]) > 0) {
            insertAfter(Steph, i);
        } else {
            insertBefore(Steph, i); //CONTINUE HERE //ERROR WITH insertBefore() in List.C causing a seg fault
            //PROBABLY to do with a list with only one element, it is trying to access the element before it
        }

        
    }
    
    //printList(out, Steph); //previous was 0 4 3 1 2
    moveFront(Steph);
    for(int i = 0; i < length(Steph); i++) {
        fprintf(out, "%s\n", lines[get(Steph)]);
        moveNext(Steph);
    }


//    fprintf(out, "%s%s%s", lines[0], lines[1], lines[2]);
   
//    if(strcmp(lines[1], lines[2]) < 0) {
//     fprintf(out, "%s", lines[1]);
//    } else {
//     fprintf(out, "%s", lines[2]);
//    }

   // close files 
   fclose(in);
   fclose(out);

   return(0);
}

char* duplicateString(char *source) {
    size_t length = strlen(source);

    if(length > 0 && source[length - 1] == '\n') {
        length--;
    }

    char* duplicate = malloc(length + 1);
    if (duplicate != NULL) {
        strncpy(duplicate, source, length);
        duplicate[length] = '\0';
    }
    return duplicate;
}

