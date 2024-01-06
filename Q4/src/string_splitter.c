#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#define Max_Size 100


char** splitString(const char* input, char delimiter, int* substringCount ){
	*substringCount=0;
    char** result = (char**)malloc(1*sizeof(char*));
    char* pstr1, *pstr2;
    char pstr3[Max_Size];
    pstr1 = strdup(input);
    do{
//    	printf("%d\n", *substringCount);
        pstr2 = strchr(pstr1, delimiter);
//        printf("%s_____%s\n", pstr1, pstr2);
        if(pstr2==NULL){
            result[*substringCount] = (char*)malloc((strlen(pstr1)+1)*sizeof(char));
            strcpy(result[*substringCount], pstr1);
            result[*substringCount][strlen(pstr1)]='\0';
            break;
        }
        strncpy(pstr3, pstr1, (size_t)(pstr2-pstr1));
        pstr3[(size_t)(pstr2-pstr1)]='\0';
        result = (char**)realloc(result, (*substringCount+2)*sizeof(char*));
        result[*substringCount] = (char*)malloc((strlen(pstr3)+1)*sizeof(char));
        strcpy(result[*substringCount], pstr3);
        result[*substringCount][strlen(pstr3)]='\0';
//        printf("%s\n%s\n%s\n%s\n\n", pstr1, pstr2, pstr3, result[*substringCount]);
        (*substringCount)++;
        pstr1=pstr2+1;
        while(*(pstr1++)==delimiter){
        	result = (char**)realloc(result, (*substringCount+2)*sizeof(char*));
        	result[*substringCount]=strdup("");
        	(*substringCount)++;
		}
//	    while(*(pstr1++)==delimiter) continue;
	    pstr1--;
	}while(true);
		
//    printf("%s\n%s\n%s\n\n", result[0], result[1], result[2]);
    (*substringCount)++;
    return result;
}
    
void freeSubstrings(char** substrings, int count){
	for (int i=0; i<count; i++){
		free(substrings[i]);
	}
	free(substrings);
}