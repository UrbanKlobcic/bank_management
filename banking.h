#ifndef BANKING_H
#define BANKING_H

struct account_num_and_pin{
    char account_number[20];
    char pin_number[5];
};

void print_welcome();
struct account_num_and_pin* bank_account_number_and_pin_allocation();
char* account_number_allocation();
char* pin_number_allocation();
int account_number_exists(char* account_number);

#endif