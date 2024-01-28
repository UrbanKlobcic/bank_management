#include "data_management.h"
#include "banking.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAX_ACCOUNT_LENGTH 40


struct account_information;

void account_file_creation(struct account_information *account_struct_ptr){
    char account_file_name[20];
    sprintf(account_file_name, "accounts/%s.txt", account_struct_ptr -> account_num_and_pin_instance.account_number);
    FILE *file = fopen(account_file_name, "w+");

    // Check if the file was successfully opened
    if (file == NULL) {
        printf("Error opening the file!\n");
    } 

    fprintf(file, "NAME: %s \nBALANCE: %d \n", account_struct_ptr->name, account_struct_ptr->balance);
    fprintf(file, "ACCOUNT NUMBER: %s \n", account_struct_ptr->account_num_and_pin_instance.account_number);
    fprintf(file, "PIN NUMBER: %s \n", account_struct_ptr->account_num_and_pin_instance.pin_number);

    // Close the file
    fclose(file);

    printf("File created successfully.\n");
}

void add_to_account_pin_number_file(struct account_num_and_pin *new_account_pin_number){
    const char* file_path = "accounts/account_pin_numbers.txt";
    FILE *file = fopen(file_path, "a");

    // Check if the file was successfully opened
    if (file == NULL) {
        printf("Error opening the file!\n");
    } 
    
    fprintf(file, "ACCOUNT: %s PIN: %s\n", new_account_pin_number->account_number, new_account_pin_number->pin_number);

    // Close the file
    fclose(file);
}

void open_account(char* name, int balance){
    struct account_information new_account;
    new_account.balance = balance;
    strncpy(new_account.name, name, sizeof(new_account.name) - 1);
    new_account.name[sizeof(new_account.name) - 1] = '\0';
    struct account_num_and_pin* new_account_pin_number = bank_account_number_and_pin_allocation();
    
    strncpy(new_account.account_num_and_pin_instance.account_number, new_account_pin_number->account_number, sizeof(new_account_pin_number->account_number) - 1);
    new_account.account_num_and_pin_instance.account_number[sizeof(new_account.account_num_and_pin_instance.account_number) - 1] = '\0';
    
    strncpy(new_account.account_num_and_pin_instance.pin_number, new_account_pin_number->pin_number, sizeof(new_account_pin_number->pin_number) - 1);
    new_account.account_num_and_pin_instance.pin_number[sizeof(new_account.account_num_and_pin_instance.pin_number) - 1] = '\0';
    add_to_account_pin_number_file(new_account_pin_number);
    printf("Your new bank account is %s and your pin number is %s.\n", new_account_pin_number->account_number, new_account_pin_number->pin_number);
    free(new_account_pin_number);
    account_file_creation(&new_account);
}

void account_deposit(){
    
}

void account_withdraw(){
    
}

void account_close(char* line_to_remove){
    const char *folder_path = "accounts";
    char full_path[100];  // Adjust the size according to your needs
    char file_name[30];  // Adjust the size according to your needs

    // Use sscanf to extract the substring
    sscanf(line_to_remove, "ACCOUNT: %19[^P]", file_name);

    snprintf(full_path, sizeof(full_path), "%s/%s.txt", folder_path, file_name);
    printf("line to remove: %s\n", line_to_remove);
    printf("remove this file: %s\n", full_path);
    // Attempt to delete the file
    /*
    if (remove(full_path) == 0) {
        printf("File '%s' deleted successfully.\n", full_path);
        //write a code to remove a line from a file
    } else {
        perror("Error deleting file");
    }*/

}

int account_pin_exist(char* pin_number, char* bank_account){
    const char* accounts_file_path = "accounts/account_pin_numbers.txt";
    FILE *file = fopen(accounts_file_path, "r");  
    char pin_number_str[20] = "PIN: "; 

    // Check if the file was successfully opened
    if (file == NULL) {
        printf("Error opening the file!\n");
    } 
    strncat(pin_number_str, pin_number, 4);
    printf("looking for %s\n", pin_number_str);
    char line[MAX_ACCOUNT_LENGTH];
    while (fgets(line, sizeof(line), file) != NULL) {
        if (strstr(line, bank_account) != NULL) {
            if (strstr(line, pin_number_str) != NULL) {
                fclose(file);
                return 1; // Account found in the file
            }
            fclose(file);
            return 2; // Account found in the file
        }
    }
    fclose(file);
    return 0;
}