#include "communication.h"
#include "data_management.h"
#include <string.h>
#include <stdio.h>

#define MAX_BUFFER_SIZE 256

void communicate(){
    while(1){
        pars_command();
    }
}

void empty_buffer(char* buffer) {
    buffer[0] = '\0';
}

void pars_command(){
    printf("Hello, enter a command:\n");
    printf("1 Withdrawal\n");
    printf("2 Deposit\n");
    printf("3 Open an account\n");
    printf("4 Close an account\n");
    char communication_buffer[MAX_BUFFER_SIZE];
    int command_selected = 0;
    if (fgets(communication_buffer, sizeof(communication_buffer), stdin) != NULL) {
        // Process input
        //if (sscanf(communication_buffer, "%d %s %d", &command_selected, name, &value) == 3) {
        if (1 == sscanf(communication_buffer, "%d", &command_selected)) {
           
            /* open an account command */
            if(command_selected == 3){
                printf("To open an account please enter your name and first deposit:\n");
                empty_buffer(communication_buffer);
                char name[MAX_BUFFER_SIZE];
                int balance;
                if (fgets(communication_buffer, sizeof(communication_buffer), stdin) != NULL) {
                    if (sscanf(communication_buffer, "%s %d", name, &balance) == 2) {//process input
                        open_account(name, balance);
                    }
                }
            }else if(command_selected == 2){
                printf("To deposit on an account please enter your bank account:\n");
                empty_buffer(communication_buffer);
                char bank_account[MAX_BUFFER_SIZE];
                char pin_number[MAX_BUFFER_SIZE];
                if (fgets(communication_buffer, sizeof(communication_buffer), stdin) != NULL) {
                    if (sscanf(communication_buffer, "%19[^\n]", bank_account) == 1) {//process input 
                        
                    }
                }
                printf("And now your pin number:\n");
                if (fgets(communication_buffer, sizeof(communication_buffer), stdin) != NULL) {
                    if (sscanf(communication_buffer, "%s", pin_number) == 1) {//process input
                        
                    }
                }
                printf("bank account %s \npin number: %s \n", bank_account, pin_number);
                int account_pin_exist_return_value = account_pin_exist(pin_number, bank_account);
                if(account_pin_exist_return_value==0){
                    printf("No such bank account\n");
                }else if(account_pin_exist_return_value==1){
                    printf("correct bank account and pin number\n");
                }else if(account_pin_exist_return_value==2){
                    printf("Wrong pin number\n");
                }
            }
        } else {
            printf("No correct command detected.");
        }
    } else {
        // Handle error
        printf("No correct command detected.");
    }

    empty_buffer(communication_buffer);
    
}

