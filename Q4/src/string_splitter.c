#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 


char** splitString(const char *input, char delimiter, int *substringCount) {

    char **result = (char** )malloc(100*sizeof(char *));
	char str1[1000], str2[100];
	char* Pstr1, *pdelimiter;
	Pstr1 = &str1[0];
	strcpy(str1, input);
	while (1){
		int counter=0;
		pdelimiter = strchr(str1, delimiter);
		while(pdelimiter==Pstr1){
			strcpy(str1, pdelimiter+1+counter);
			pdelimiter = strchr(str1, delimiter);
		}
		while(pdelimiter!=NULL && str1[pdelimiter-Pstr1+1+counter]==delimiter){
			counter++;
		}
		if(!pdelimiter)
		    break;
		if(*substringCount<100)
		    result[*substringCount] = (char* )malloc(100*sizeof(char));
		strncpy(str2, str1, (pdelimiter-Pstr1+counter));
	    str2[pdelimiter-Pstr1] = '\0';
	    strcpy(str1, pdelimiter+1+counter);
		if(strlen(str2)<100&&*substringCount<100)
	        strcpy(result[*substringCount], str2);
	    (*substringCount)++;
	}
	if(*substringCount<100)
	    result[*substringCount] = (char* )malloc(100*sizeof(char));
	if(strlen(str2)<100&&*substringCount<100)
	strcpy(result[*substringCount], str1);
        (*substringCount)++;
	return result;

}

void freeSubstrings(char **substrings, int count) {

    if(substrings){
        for (int i=0; i<count; i++){
		    free(substrings[i]);
	    }
	free(substrings);
	}

}


