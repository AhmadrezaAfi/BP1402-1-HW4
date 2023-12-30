#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/user_operations.h"

// #define MAX_USER_DATA_LENGTH 100

void read_backup_file(char ***stored_data, int *size, const char *backup_file_name) {
    // Open the file
    FILE* pfile = fopen(backup_file_name, "r");

    // Count the number of users in the file
    int lines = 0;
    char c;

    do
    {
    	c = fgetc(pfile);
    	if (c=='\n')
    	    lines++;
	} while(c!=EOF);

    // Rewind the file to the beginning
    rewind(pfile);

    // Allocate memory for stored_data
    *stored_data = (char** )malloc((lines)*sizeof(char* ));
    (*stored_data)[lines]=NULL;
    for(int i=0; i<lines; i++)
        (*stored_data)[i]=(char* )malloc((*size)*sizeof(char));
    // Read user data from the file
    for(int i=0; i<lines; i++){
    	fgets((*stored_data)[i], *size, pfile);
	}
//    for(int i=0; i<lines; i++){
//        printf("1");
//    	fscanf(pfile, ("%s %s %s"), (*stored_data)[i][0], (*stored_data)[i][1], (*stored_data)[i][2]);
//	}
}
void show_users(char **stored_data, int size) {
	int count = 0;
	do{
		char* uname;
		uname = (char*)malloc(size*sizeof(char));

    // Extract the user name from the stored data
        char* pname = strchr((stored_data[count]), ' ');
        strncpy(uname, stored_data[count], pname-stored_data[count]);
        uname[(int)(pname-stored_data[count])] = '\0';
        count++;
    // Capitalize the first letter of each word in the user name
        for(int i=0; i<strlen(uname); i++){
        	if(uname[i]=='_')
        	    continue;
        	if(uname[i-1]=='_'||i==0){
	        	if(uname[i] >= 'a' && uname[i] <= 'z') {
	                uname[i] = uname[i] -32;
	            }
            }
            else{
				if(uname[i] >= 'A' && uname[i] <= 'Z') {
		            uname[i] = uname[i] +32;
		        }
	        }
		}
    // Print the formatted user name
	   printf("%s\n", uname);
    } while(stored_data[count]);
    printf("%d\n", count);

}

void new_user(char ***stored_data, int *size, const char *user_name, const char *email, const char *password) {
    int count = 0;
    while ((*stored_data)[count] != NULL) {
        count++;
    }
    // Check if the user already exists
    char *new_user_data = (char*)malloc(*size * sizeof(char));
    strcpy(new_user_data, user_name);
    strcat(new_user_data, " ");
    strcat(new_user_data, email);
    strcat(new_user_data, " ");
    strcat(new_user_data, password);

    for (int i = 0; i < count; ++i) {
        if (strcmp((*stored_data)[i], new_user_data) == 0) {
            free(new_user_data);
            printf("User already exists!\n");
            return;
        }
    }
    // Allocate memory for the new user data
    // Format the new user data
    // Resize the stored_data array
    char **temp = (char**)realloc(*stored_data, (count + 2) * sizeof(char*));
    *stored_data = temp;

    // Add the new user data
    (*stored_data)[count] = new_user_data;
    (*stored_data)[count + 1] = NULL;
    printf("New user added!\n");
}

void delete_user(char ***stored_data, int *size, const char *user_name) {
    int count = 0;
    while ((*stored_data)[count] != NULL) {
        count++;
    }
    // Free memory for the deleted user data
    int i;
    for (i = 0; i < count; ++i) {
		char* uname;
		uname = (char*)malloc((*size)*sizeof(char));

        char* pname = strchr(((*stored_data[i])), ' ');
        strncpy(uname, ((*stored_data[i])), pname-((*stored_data[i])));
        uname[(int)(pname-((*stored_data[i])))] = '\0';
        printf("%s_______%s\n", uname, user_name);
        if (strcmp(uname, user_name) == 0) {
            free((*stored_data)[i]);
            break;
        }
    }
    if(i==count){
    	printf("User not found!\n");
    	return;
	}
    // Shift the remaining users to fill the gap
    for(int j=i; j<count-1; j++){
    	(*stored_data)[j]=(*stored_data)[j+1];
	}
    // Resize the stored_data array
    (*stored_data)=(char**)realloc(*stored_data, (count -1) * sizeof(char*));
    (*stored_data)[count - 1] = NULL;
    printf("User deleted!\n");
}

void email_cnt(char **stored_data, int size) {
	int mailcounter[5]={0};
	int count = 0;
    while ((stored_data)[count] != NULL) {
        count++;
    }
    char** E_data = (char**)malloc((count+1)*sizeof(char*));
    for(int i=0; i<count; i++){
    	E_data[i] = (char*)malloc(size*sizeof(char));
	}
	printf("%d\n", count);
	E_data[count]=NULL;
	for(int i=0; i<count; i++){
        char* flag1 = strchr(stored_data[i], '@');
        char* flag2 = strchr((stored_data)[i], '.');
        if(flag1>flag2){
        	flag2 = strchr((stored_data)[i]+(int)(flag2-stored_data[i]+1), '.');
		}
        strncpy(E_data[i], stored_data[i]+(int)(flag1-stored_data[i])+1, flag2-flag1-1);
        E_data[i][(int)(flag2-flag1)] = '\0';
	}


	for(int i=0; i<count; i++){
		if(strcmp("yahoo", E_data[i])==0)
		    mailcounter[0]++;
		else if(strcmp("gmail", E_data[i])==0)
		    mailcounter[1]++;
		else if(strcmp("aut", E_data[i])==0)
		    mailcounter[2]++;
		else if(strcmp("hotmail", E_data[i])==0)
		    mailcounter[3]++;
		else
		    mailcounter[4]++;
		    
	}
	printf("Yahoo: %d\n", mailcounter[0]);
	printf("Gmail: %d\n", mailcounter[1]);
	printf("AUT: %d\n", mailcounter[2]);
	printf("Hotmail: %d\n", mailcounter[3]);
	printf("Others: %d\n", mailcounter[4]);
	
	
    // Code here
}


void end_program(char ***stored_data, int size) {
	int count=0;
    while ((stored_data)[count] != NULL) {
        count++;
    }
    FILE *backup_file = fopen("C:\\Documents\\HW4_Datasets_1.txt", "w");
    for(int i=0; i<count; i++){
    	fprintf(backup_file, "%s\n", (*stored_data)[i]);
	}
    for (int i = 0; i < count; i++) {
        free((*stored_data)[i]);
    }
    free(*stored_data);
    remove("C:\\Documents\\HW4_Datasets_1.txt");
    // Code Here
}