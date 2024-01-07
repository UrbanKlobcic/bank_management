#include "banking.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <string.h>

#define MAX_ACCOUNT_LENGTH 40

void print_welcome(){
    printf("Welcome to the bank!");
}

struct account_num_and_pin* bank_account_number_and_pin_allocation(){
    struct account_num_and_pin* ptr_account_num_and_pin = (struct account_num_and_pin*)malloc(sizeof(struct account_num_and_pin));
    int error_flag = 1;
    if (ptr_account_num_and_pin != NULL) {
        char* account_number_ptr;
        do {
            account_number_ptr = account_number_allocation();
            if (account_number_exists(account_number_ptr)) {
                printf("Waiting for the right account\n");
                free(account_number_ptr);  // Deallocate memory if the account exists
            } else {
                printf("Right account found!\n");
            }
        } while (account_number_exists(account_number_ptr));

        char* pin_number_ptr = pin_number_allocation();
        if (account_number_ptr != NULL) {
            strncpy(ptr_account_num_and_pin->account_number, account_number_ptr, sizeof(ptr_account_num_and_pin->account_number) - 1);
            free(account_number_ptr);
        } else {
            printf("Error: Failed to allocate memory for account number.\n");
            error_flag = 0;
        }
        if (pin_number_ptr != NULL) {
            strncpy(ptr_account_num_and_pin->pin_number, pin_number_ptr, sizeof(ptr_account_num_and_pin->pin_number));
            free(pin_number_ptr);
        } else {
            printf("Error: Failed to allocate memory for account number.\n");
            error_flag = 0;
        }        
    }
    if(error_flag){
        return ptr_account_num_and_pin;
    }else{
        free(ptr_account_num_and_pin);
        return NULL;
    }
    
}

char* account_number_allocation(){
    //char account_number[20];
    char account_number_set_one[5];
    char account_number_set_two[5];
    char account_number_set_three[5];
    char account_number_set_four[5];

    const char ALLOWED[] = "0123456789";  // Allowed characters are '0' to '9'
    int index_char_array;
    int nbAllowed = sizeof(ALLOWED) - 1;
    srand(time(NULL)); // Define a seed for the random number generator
    int set_index;
    int index;
    for(set_index=1; set_index<=4; set_index++){
        //"DE12 1234 1234 1234"
        index=0;
        for(index=0; index<=4; index++){
            index_char_array = rand() % nbAllowed;
            switch (set_index) {
                case 1:
                    if(index == 4){
                        account_number_set_one[index] = '\0';
                    }else{
                        if(index>=2){
                            account_number_set_one[index] = ALLOWED[index_char_array];
                        }else{
                            account_number_set_one[0] = 'D';
                            account_number_set_one[1] = 'E'; 
                        }
                    }
                    break;
        
                case 2:
                    if(index == 4){
                        account_number_set_two[index] = '\0';
                    }else{
                        account_number_set_two[index] = ALLOWED[index_char_array];
                    }
                    break;
        
                case 3:
                    if(index == 4){
                        account_number_set_three[index] = '\0';
                    }else{
                        account_number_set_three[index] = ALLOWED[index_char_array];
                    }
                    break;

                case 4:
                    if(index == 4){
                        account_number_set_four[index] = '\0';
                    }else{
                        account_number_set_four[index] = ALLOWED[index_char_array];
                    }
                    break;
        
                default:
                    printf("Error!");
                    break;
            }
        }
    }
    size_t totalLength = snprintf(NULL, 0, "%s %s %s %s", account_number_set_one, account_number_set_two, account_number_set_three, account_number_set_four);
    char* account_number = (char*)malloc(totalLength + 1); 
    snprintf(account_number, totalLength + 1, "%s %s %s %s", account_number_set_one, account_number_set_two, account_number_set_three, account_number_set_four);
    
    return account_number;
}

char* pin_number_allocation(){
    //char account_number[20];
    char pin_number[5];

    const char ALLOWED[] = "0123456789";  // Allowed characters are '0' to '9'
    int index_char_array;
    int nbAllowed = sizeof(ALLOWED) - 1;
    srand(time(NULL)); // Define a seed for the random number generator
    int index;
    
    for(index=0; index<4; index++){
        index_char_array = rand() % nbAllowed;
        pin_number[index] = ALLOWED[index_char_array];                       
    }
    pin_number[4] = '\0';
    size_t totalLength = snprintf(NULL, 0, "%s", pin_number);
    char* pin_number_ptr = (char*)malloc(totalLength + 1); 
    snprintf(pin_number_ptr, totalLength + 1, "%s", pin_number);
    //printf("Pin code is: %s\n", pin_number_ptr);

    // Don't forget to free the allocated memory
    //free(pin_number_ptr);

    return pin_number_ptr;
}

int account_number_exists(char* account_number){
    const char* accounts_file_path = "accounts/account_pin_numbers.txt";
    FILE *file = fopen(accounts_file_path, "r");    

    // Check if the file was successfully opened
    if (file == NULL) {
        printf("Error opening the file!\n");
    } 

    char line[MAX_ACCOUNT_LENGTH];
    while (fgets(line, sizeof(line), file) != NULL) {
        if (strstr(line, account_number) != NULL) {
            fclose(file);
            return 1; // Account found in the file
        }
    }

    fclose(file);
    return 0;
}