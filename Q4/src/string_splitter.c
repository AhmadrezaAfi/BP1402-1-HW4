#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 


char** splitString(const char* input, char delimiter, int* substringCount ){
	char del[2];
	char* inp;
	inp = strdup(input);
	del[0]=delimiter; del[1]='\0';
	char **result = (char** )malloc(strlen(input)*sizeof(char *));
	char* token;
	token = strtok(inp, del);

	while( token != NULL ) {
        result[*substringCount] = (char* )malloc((strlen(token)+1)*sizeof(char));
        strcpy(result[*substringCount], token);
        token = strtok(NULL, del);
        (*substringCount)++;
   }
   free(inp);
   return result;
}

void freeSubstrings(char** substrings, int count){
	for (int i=0; i<count; i++){
		free(substrings[i]);
	}
	free(substrings);
}
