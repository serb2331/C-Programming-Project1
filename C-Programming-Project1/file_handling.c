#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_structs.h"
#include "file_handling.h"

void FileLoadAccount(Account *acc, FILE *load_file)
{
    // Function that reads all possible account information from "load_file"
    // First reads all data as strings and converts it to the proper type using stdlib functions
    int a;
    fscanf(load_file, "%[^\n]", acc -> account_name);

    char string_input[500];
    fscanf(load_file, "%s", &string_input);
    acc -> account_base_balance = atof(string_input);
    fscanf(load_file, "%s", &string_input);
    acc -> transaction_number = atoi(string_input);

    for (int i = 0; i < acc->transaction_number; i += 1){

        fscanf(load_file, "%s", &string_input);
        acc -> transaction_array[i].transaction_type = atoi(string_input);
        fscanf(load_file, "%s", &string_input);
        acc -> transaction_array[i].transaction_amount = atof(string_input);
        fscanf(load_file, "%s", &string_input);
        acc -> transaction_array[i].transaction_date.d = atoi(string_input);
        fscanf(load_file, "%s", &string_input);
        acc -> transaction_array[i].transaction_date.m = atoi(string_input);
        fscanf(load_file, "%s", &string_input);
        acc -> transaction_array[i].transaction_date.y = atoi(string_input);
        fscanf(load_file, " %[^\n]", &string_input);
        strcpy(acc -> transaction_array[i].description, string_input);
    }
}

void FileSaveAccount(Account acc, FILE *save_file)
{
    // Saves all account data to "save_file" with the form:
    /*
    Account details - name
    Account details - balance
    Accoutn details - nr of transactions

    -- for each transaction
    Transaction - type
                - value
                - date
                - description
    --
    
    */
    fprintf(save_file, "%s\n", acc.account_name);
    fprintf(save_file, "%lf\n", acc.account_base_balance);
    fprintf(save_file, "%d\n", acc.transaction_number);

    for (int i = 0; i < acc.transaction_number; i += 1){
        fprintf(save_file, "%d\n", acc.transaction_array[i].transaction_type);
        fprintf(save_file, "%lf\n", acc.transaction_array[i].transaction_amount);
        fprintf(save_file, "%d %d %d\n", acc.transaction_array[i].transaction_date.d, acc.transaction_array[i].transaction_date.m, acc.transaction_array[i].transaction_date.y);
        fprintf(save_file, "%s\n", acc.transaction_array[i].description);
    }
}