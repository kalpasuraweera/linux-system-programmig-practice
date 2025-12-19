#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_LEN 100
#define MAX_CONFIGS 5

//TODO: add funnctions
//TODO: create struct for the key value like in Go
//TODO: make this convertable to other types like json
//TODO: handle comments

typedef struct config_element {
char* key;
char* value;
}config_element;

int main(int argc, char *argv[]){
  config_element configs[MAX_CONFIGS];
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
  int config_count = 0;
  while((c = fgetc(in_file)) != EOF){
    //printf("%c",c);
    if(c == ' ' || c == '\t' || c == '"' || c == '\''){
     continue; 
    }else if(c == '#'){
      // this is a comment
      while((c = fgetc(in_file)) != '\n'){
	      // go till the end of that line
      }
      continue;
    }else if(c == '='){
      current_buffer[i++] = '\0';
      current_key = current_buffer;
     // if we just do like this the current_key is a pointer so the pointer will be saved in the key as the values in that point change with the loop this will not save a copy its just update with this array. so we have to allocate a new memory and copy the content to there. configs[config_count].key = current_key;
      configs[config_count].key = malloc(sizeof(char)*i);
      strcpy(configs[config_count].key,current_key);
      printf("current key: %s\n",current_key);
      i=0;
      continue;
    } else if(c == '\n'){
      current_buffer[i++] = '\0';
      current_value = current_buffer;
      configs[config_count].value = malloc(sizeof(char)*i);
      strcpy(configs[config_count++].value,current_value);
      printf("current value: %s\n\n\n",current_value);
      i=0;
      continue;
    }
    current_buffer[i++] = c; 
  }
  printf("first config %s:%s\n",configs[0].key,configs[0].value);
  fclose(in_file);
}
