#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 

int main(){
    int count;
    char **result = splitString("Hello,World,Test", ',', &count);
    if(count==3)
        printf("1"); 
    printf("%d", strcmp(result[0], "Hello"));
//    EXPECT_STREQ(result[0], "Hello");
//    EXPECT_STREQ(result[1], "World");
//    EXPECT_STREQ(result[2], "Test");
    freeSubstrings(result, count);
}

char** splitString(const char *input, char delimiter, int *substringCount) {
    // Hint 1: Count delimiters to determine substring count.
    // Hint 2: extract and allocate memory for each substring.


    // Sample Case 1:
    // Input: "One;Two;Three;Four", delimiter = ';', substringCount points to an integer
    // Expected Output: ["One", "Two", "Three", "Four"]
    // After execution, *substringCount should be updated to 4

    // Sample Case 2:
    // Input: "SingleString", delimiter = ',', substringCount points to an integer
    // Expected Output: ["SingleString"]
    // After execution, *substringCount should be updated to 1
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
		result[*substringCount] = (char* )malloc(100*sizeof(char));
		strncpy(str2, str1, (pdelimiter-Pstr1+counter));
	    str2[pdelimiter-Pstr1] = '\0';
	    strcpy(str1, pdelimiter+1+counter);
	    strcpy(result[*substringCount], str2);
	    (*substringCount)++;
	}
	result[*substringCount] = (char* )malloc(100*sizeof(char));
	strcpy(result[*substringCount], str1);
    (*substringCount)++;
	return result;

}

void freeSubstrings(char **substrings, int count) {
    // Hint: Free each substring, then free the substring array.

    // Sample Case:
    // Input: Array of substrings ["Hello", "World", "Test"], count = 3
    // Operation: Frees memory for each substring and then the array itself
    for (int i=0; i<count; i++){
		free(substrings[i]);
	}
	free(substrings);

}


