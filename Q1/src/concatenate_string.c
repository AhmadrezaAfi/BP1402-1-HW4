#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // Include ctype.h for character type functions

char* concatenate_and_manipulate(char* str1, char* str2) {
    int len1 = strlen(str1), len2 = strlen(str2);
	int len = len1 + len2 + 2;
	char* Nname = (char* )malloc(len*sizeof(char));
	strcpy(Nname, str1);
	Nname[len1] = '_';
	strcat(Nname, str2);
	char* pN = &Nname[0];
	return pN;
}