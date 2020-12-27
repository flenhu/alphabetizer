
    #include<stdio.h>
    #include<stdlib.h>
    #include<string.h>
    #include"List.h"
    #define MAX_LEN 255

int main(int argc, char * argv[])
{
    int line, count = 0;
    FILE *in, *out;
    char str[MAX_LEN];
    char** arr;

    if( argc != 3 ){
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
    }

    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");

    if (in == NULL) {
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }
    if (out == NULL) {
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }
  
    while (fgets(str, MAX_LEN, in) != NULL) {
        count++;
    }

    rewind(in); //place cursor at beginning of file

    arr = malloc(count * sizeof(char*)); //set aside space
    for(int i =0; i< count; i++) {
      arr[i] = malloc((MAX_LEN) * sizeof(char));
    }

    while(fgets(str, MAX_LEN, in) != NULL) {
      strcpy(arr[line], str);
      line++;
    }

    List L = newList();
    append(L,0); //add to front of list


    //insertion
    for(int i =1; i < count; i++) {
      char *c = arr[i];
      int j = i-1;
      moveBack(L);
      while( j>=0 && strcmp(c, arr[get(L)]) <=0 ) {
        j--;
        movePrev(L);
      }
      if(index(L)>=0) {
        insertAfter(L,i);
      }
      else{
        prepend(L,i);
      }

    }
    moveFront(L); //place cursor at front

    while (index(L) >= 0) { //print out array 
        fprintf(out, "%s", arr[get(L)]);
        moveNext(L);
    }

    fclose(in);
    fclose(out);
  
    freeList(&L);
    for (int i = 0; i < count; i++) { //free every element of array
        free(arr[i]);
    }
    free(arr);  //free the array itself

    return(0);
}