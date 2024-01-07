#include "data_management.h"
#include "banking.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


struct account_information;

void account_file_creation(struct account_information *account_struct_ptr){
    char account_file_name[20];
    sprintf(account_file_name, "accounts/%s.txt", account_struct_ptr->name);
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
    free(new_account_pin_number);

    account_file_creation(&new_account);
}

void account_deposit(){
    
}