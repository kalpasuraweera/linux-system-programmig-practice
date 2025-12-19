#include <stdio.h>
#include <stdlib.h>

#define BUFFER_LEN 100
//TODO: add funnctions
//TODO: create struct for the key value like in Go
//TODO: make this convertable to other types like json
//TODO: handle comments
int main(int argc, char *argv[]){
  FILE* in_file = fopen("test.env", "r");
  if(in_file == NULL){
    printf("File doesn't exisist\n");
    exit(1);
  }
  printf("Starting Extraction...\n");
  char c;
  char current_buffer[BUFFER_LEN];
  char *current_key = NULL;
  char *current_value = NULL; 
  int i = 0;
  while((c = fgetc(in_file)) != EOF){
    //printf("%c",c);
    if(c == ' ' || c == '\t' || c == '"' || c == '\''){
     continue; 
    }else if(c == '='){
      current_buffer[i++] = '\0';
      current_key = current_buffer;
      printf("current key: %s\n",current_key);
      i=0;
      continue;
    } else if(c == '\n'){
      current_buffer[i++] = '\0';
      current_value = current_buffer;
      printf("current value: %s\n\n\n",current_value);
      i=0;
      continue;
    }
    current_buffer[i++] = c; 
  }
  fclose(in_file);
}
