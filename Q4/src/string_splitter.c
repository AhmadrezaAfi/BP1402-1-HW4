#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 


char** splitString(const char* input, char delimiter, int* substringCount ){
	*substringCount = 0;
	int count=0;
	char del[2];
	char* inp;
	inp = strdup(input);
	del[0]=delimiter; del[1]='\0';
	char **result = (char** )malloc(strlen(input)*sizeof(char *));
	char* token;
	token = strtok(inp, del);
    if(input[count]==delimiter){
    	(*substringCount)++;
    	result[*substringCount]="";
    	count++;
    	while(input[count]==delimiter){
    		count++;
		}
	}
	while( token != NULL ) {
        result[*substringCount] = (char* )malloc((strlen(token)+1)*sizeof(char));
        strcpy(result[*substringCount], token);
		count+=(strlen(token)+1);
		if(count>=strlen(input))
		    break;
//		printf("%s,,,,,%d\n", token, count);
        if(input[count]==delimiter){
        	(*substringCount)++;
        	result[*substringCount]="";
//        	printf("1\n");
        	count++;
        	while(input[count]==delimiter){
        		count++;
			}
		}
        token = strtok(NULL, del);
        (*substringCount)++;
   }
   (*substringCount)++;
   free(inp);
   return result;
}

void freeSubstrings(char** substrings, int count){
	for (int i=0; i<count; i++){
		free(substrings[i]);
	}
	free(substrings);
}

