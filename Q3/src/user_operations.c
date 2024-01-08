#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/user_operations.h"

#define MAX_USER_DATA_LENGTH 100



void read_backup_file(char ***stored_data, int *size, const char *backup_file_name) {
    FILE *pfile = fopen(backup_file_name, "r");
    if (!pfile) {
        perror("Error opening file");
        return;
    }

    char line[MAX_USER_DATA_LENGTH];
    int lines = 0;
    char c;
    // Count the number of users in the file

    do
    {
    	c = fgetc(pfile);
    	if (c=='\n')
    	    lines++;
	} while(c!=EOF);
    *size = lines;
    
    if (lines == 0) {
        return;
    }

    // Rewind the file to the beginning
    rewind(pfile);

    // Allocate memory for stored_data
    char **data = (char **)malloc((lines) * sizeof(char *));
    if (!data) {
        perror("Memory allocation failed");
        return;
    }
//    data[lines]=NULL;

    int i = 0;
    while (i < lines) {
        fgets(line, MAX_USER_DATA_LENGTH, pfile);
        if(line==NULL){
        	perror("problem occured");
        	return;
		}
        line[strcspn(line, "\r\n")] = '\0';

        data[i] = (char *)malloc((strlen(line) + 1)*sizeof(char));
        if (!data[i]) {
            perror("Memory allocation failed");
            return;
        }
        strcpy(data[i], line);
        i++;
    }

    fclose(pfile);
    *stored_data = data;
}
void show_users(char **stored_data, int size) {
	int count = 0;
	while(count<size){
		char uname[MAX_USER_DATA_LENGTH];
    // Extract the user name from the stored data
//        if (count>size || count<0) {
//            exit(EXIT_FAILURE);
//        }
        if (!stored_data[count]) {
            perror("stored_data[count] is not initialized.\n");
            return;
        }

        char* pname = strchr((stored_data[count]), ' ');
        if(!pname){
            perror("Problem Occured.\n");
            return;
        }
        strncpy(uname, stored_data[count], (size_t)(pname-(stored_data[count])));
        uname[(int)(pname-stored_data[count])] = '\0';
        count++;
    // Capitalize the first letter of each word in the user name
        for(size_t i=0; i<strlen(uname); i++){
        	if(uname[i]=='_'){
                i++;
                if(uname[i] >= 'a' && uname[i] <= 'z') {
                    uname[i] = uname[i] -32;
                }
        	    continue;
            
            }
        	if(i==0){
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
    }

}

void new_user(char ***stored_data, int *size, const char *user_name, const char *email, const char *password) {
    int count = *size;
    // Check if the user already exists
    char new_user_data[MAX_USER_DATA_LENGTH];
    strcpy(new_user_data, user_name);
    strcat(new_user_data, " ");
    strcat(new_user_data, email);
    strcat(new_user_data, " ");
    strcat(new_user_data, password);
    new_user_data[strlen(user_name)+strlen(email)+strlen(password)+2]='\0';
//    printf("%s\n", new_user_data);
    for (int i = 0; i < count; i++) {
// Extract the user name from the stored data
//        if (count>size || count<0) {
//            exit(EXIT_FAILURE);
//        }

        char* pname = strchr((const char*)((*stored_data)[i]), ' ');
        if(!pname){
            perror("Problem Occured.\n");
            return;
        }
        char uname[MAX_USER_DATA_LENGTH];
        strncpy(uname, ((*stored_data)[i]), (size_t)(pname-(((*stored_data)[i]))));
        uname[(int)(pname-((*stored_data)[i]))] = '\0';
        if (i>*size || count<0) {
            exit(EXIT_FAILURE);
        }
        if (!(*stored_data)[i]) {
            fprintf(stderr, "stored_data[count] is not initialized.\n");
            exit(EXIT_FAILURE);
        }
//        printf("%s***%s***%d\n", uname, user_name, (uname, user_name));
        if (strcmp(uname, user_name) == 0) {
            printf("User already exists!\n");

            return;
        }

    }

    // Allocate memory for the new user data
    // Format the new user data
    // Resize the stored_data array

    (*stored_data) = (char**)realloc((*stored_data), (count + 1) * sizeof(char*));
//    *stored_data = temp;
    // Add the new user data
    if(!(*stored_data)){
        perror("Memory allocation failed");
        return;
    }
    (*stored_data)[count] = (char*)malloc((strlen(new_user_data)+1)*sizeof(char));
    if(!((*stored_data)[count])){
        perror("Memory allocation failed");
        return;
    }
    strcpy((*stored_data)[count], new_user_data);
//    (*stored_data)[count] = NULL;
    count = ++(*size);
    printf("New user added!\n");
}

void delete_user(char ***stored_data, int *size, const char *user_name) {
    int count =*size;
    // Free memory for the deleted user data
    int i;
    for (i = 0; i < count; ++i) {
    	
		char uname[MAX_USER_DATA_LENGTH];

        char* pname = strchr((const char*)((*stored_data)[i]), ' ');

        if(!(pname)){
            perror("Problem Occured");
            return;
        }
        
//        if(!(uname)){
//            perror("Memory allocation failed");
//            return;
//        }
        
        strncpy(uname, ((*stored_data)[i]), pname-((*stored_data)[i]));
//        printf("%s\n", uname);
//        printf("%s***%s***%d\n", uname, user_name, strcmp(uname, user_name));
        if (strcmp(uname, user_name) == 0) {
            free((*stored_data)[i]);

            for(int j=i; j<count-1; j++){
            	(*stored_data)[j]=(*stored_data)[j+1];
			}

//            free((*stored_data)[count-1]);
			(*stored_data)=(char**)realloc((*stored_data), (count-1)*sizeof(char*));
//			(*stored_data)[count-1]=NULL;
			(*size)--;
//			free(uname);
            break;
        }
//        free(uname);
    }
    if(i==count){
    	printf("User not found!\n");
    	return;
	}
    // Shift the remaining users to fill the gap
//    for(int j=i; j<count-1; j++){
//    	(*stored_data)[j]=(*stored_data)[j+1];
//	}
//    // Resize the stored_data array
//    (*stored_data)=(char**)realloc(*stored_data, (count -1) * sizeof(char*));
//    (*stored_data)[count - 1] = NULL;
//    *size = count-1;
//    free(uname);
    printf("User deleted!\n");
}

void email_cnt(char **stored_data, int size) {

	int mailcounter[5]={0};
	int count = size;

    char** E_data = (char**)malloc((count+1)*sizeof(char*));
    E_data[count]=NULL;
    for(int i=0; i<count; i++){
    	E_data[i] = (char*)malloc((MAX_USER_DATA_LENGTH)*sizeof(char));
	}

	for(int i=0; i<count; i++){

        char* flag1 = strchr((const char*)(stored_data[i]), '@');
        char* flag2 = strchr((const char*)((stored_data)[i]), '.');
        if(!(flag1)||!(flag2)){
            perror("Memory allocation failed");
            return;
        }
        while(flag1>flag2){
        	flag2 = strchr((const char*)((stored_data)[i])+(int)(flag2-stored_data[i]+1), '.');
		}
		if(!(flag2)){
            perror("Memory allocation failed");
            return;
        }
        strncpy(E_data[i], stored_data[i]+(int)(flag1-stored_data[i])+1, flag2-flag1-1);

        E_data[i][(int)(flag2-flag1)-1] = '\0';
        
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
    
    for (int i = 0; i < count; i++) {
        free((E_data[i]));
    }
    free(E_data);
	
    // Code here
}


void end_program(char ***stored_data, int size) {
	int count=size;
//    printf("%d\n", count);
    FILE *backup_file = fopen("HW4_Datasets_1.txt", "w");
    // Only proceed if the file opened successfully.
    if (backup_file != NULL) {
        for (int i = 0; i < count; i++) {
            // Check if string is not NULL before writing.
            if ((*stored_data)[i] != NULL) {
                fprintf(backup_file, "%s\n", (*stored_data)[i]);
            }
        }
        fclose(backup_file); // Close the file when done.
    } 
    else {
        // Handle error - file opening failed.
        perror("Error opening backup file");
        return;
    }
    for (int i = 0; i < count; i++) {
//        if((*stored_data)[i]==NULL){
//            continue;
//        }
//        printf("%s\n",(*stored_data)[i] );
        free((*stored_data)[i]);
//        printf("%s  ___  %d\n",(*stored_data)[i+1], i+1);
    }
    free(*stored_data);
//    remove("HW4_Datasets_1.txt");
    // Code Here
}
