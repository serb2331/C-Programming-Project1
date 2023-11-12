#include <stdio.h>
#include <string.h>
#include "data_structs.h"

const Date EMPTY_DATE = {.d = 0, .m = 0, .y = 0};


int DateCalculateDayCount(Date date)
{
    // Calculate the approximate day count of a Date structure in order to compare to other objects
    return date.y * 365 + date.m * 31 + date.d;
}


Transaction CreateTransaction(
    Date transaction_date,
    int transaction_type,
    double transaction_amount,
    char description[])
{
    // Constructor for the Transaction struct using the parameter variables
    Transaction new_transaction;
    new_transaction.transaction_date = transaction_date;
    new_transaction.transaction_amount = transaction_amount;
    new_transaction.transaction_type = transaction_type;
    strcpy(new_transaction.description, description);

    return new_transaction;
}

void InitializeAccount(Account *acc)
{
    // Initialize account when first starting in order to have accessible memory to work with.
    // Initialized values are maningless and will be replaced when loading or adding transactions.
    strcpy(acc -> account_name, "N/A");
    acc -> account_base_balance = 0.0;
    acc -> transaction_number = 0;
    acc -> transaction_total_amount = 0.0;
    acc -> account_balance = 0.0;

    for (int i = 0; i <= MAX_TRANSACTIONS; i += 1){
        acc -> transaction_array[i] = CreateTransaction(EMPTY_DATE, TRANSACTION_EMPTY, 0.0, "n/a");
    }
}

void UpdateBalanceAccount(Account *acc)
{
    // Calculate the total account balance by adding to the base balance the account started with, the transaction values of all transaction present in the log.
    acc -> account_balance = acc -> account_base_balance;
    acc -> transaction_total_amount = 0.0;
    for(int i = 0; i < acc -> transaction_number; i += 1){
        switch (acc -> transaction_array[i].transaction_type){
            case TRANSACTION_INCOME:
                acc -> account_balance += acc -> transaction_array[i].transaction_amount;
                acc -> transaction_total_amount += acc -> transaction_array[i].transaction_amount;
                break;
            case TRANSACTION_EXPENSE:
                acc -> account_balance -= acc -> transaction_array[i].transaction_amount;
                acc -> transaction_total_amount -= acc -> transaction_array[i].transaction_amount;
                break;
            default:
                break;
        }
    }
}