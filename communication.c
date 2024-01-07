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

