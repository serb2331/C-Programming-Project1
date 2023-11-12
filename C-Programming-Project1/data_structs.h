#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H

#define MAX_TRANSACTIONS 100
typedef struct _Date{
    //Standard date structure
    int d;
    int m;
    int y;
} Date;

typedef enum _TRANSACTION_TYPES{
    TRANSACTION_INCOME = 1,
    TRANSACTION_EXPENSE = 2,
    TRANSACTION_EMPTY = -1
} TRANSACTION_TYPES;

typedef struct _Transaction{
    // Holds all useful information about a Transaction.
    Date transaction_date;
    // Type can be either expense or income.
    int transaction_type;
    double transaction_amount;
    char description[150];

} Transaction;

typedef struct _Account{
    // Holds all useful information about the Account.
    char account_name[100];
    // Holds the total account balance
    double account_balance;
    // account_base_balance is the balance the account is initialized/created with
    double account_base_balance;
    double transaction_total_amount;
    int transaction_number;
    Transaction transaction_array[101];
} Account;

Transaction CreateTransaction(
    Date transaction_date,
    int transaction_type,
    double transaction_amount,
    char description[]);

int DateCalculateDayCount(Date date);

void InitializeAccount(Account *acc);
void UpdateBalanceAccount(Account *acc);

#endif