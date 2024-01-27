#ifndef ACCOUNT_MANAGEMENT_H
#define ACCOUNT_MANAGEMENT_H

#include "banking.h"

struct account_information{
    char name[20];
    int balance;
    struct account_num_and_pin account_num_and_pin_instance; 
};

void account_file_creation(struct account_information *account_struct_ptr);
void add_to_account_pin_number_file(struct account_num_and_pin *new_account_pin_account);
void open_account(char* name, int balance);
int account_pin_exist(char* pin_number, char* bank_account);
void account_close();
void account_withdraw();
void account_deposit();

#endif