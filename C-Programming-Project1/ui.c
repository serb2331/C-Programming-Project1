#include <stdio.h>
#include <string.h>
#include "data_structs.h"
#include "ui.h"

// Input Functions

int ReceiveIntUserInput()
{
    // Scans input from the input stream as long as it is not an int and returns it once it is given an int.
    int input;
    int scan_result;
    while (1){
        scan_result = scanf("%d", &input);
        if (scan_result != 1){
            // scanf error
            PrintScanInvalidInput();

            // Clear the input stream so scanf doesn't read already inputted data
            while (getchar() != '\n');

            continue;
        }
        break;
    }
    while (getchar() != '\n');
    return input;
}

void ReceiveCharArrayUserInput(char arr[])
{
    // Reads a char array from the input stream
    int scan_result;
    scan_result = scanf("%[^\n]%*c", arr);
}

Date ReceiveDateUserInput()
{
    // Scans data from the input stream and formats it to be of type Data.
    // Also checks so that day, month and year are real values.
    int input_day;
    int input_month;
    int input_year;
    int scan_result;
    Date return_date;
    while (1){
        scan_result = scanf("%d %d %d", &input_day, &input_month, &input_year);
        if (scan_result != 3){
            // scanf error
            PrintScanInvalidInput();

            // Clear the input stream so scanf doesn't read already inputted data
            while (getchar() != '\n');

            continue;
        }
        if (input_day < 1 || input_day > 31 || input_month < 1 || input_month > 12 || input_year < 0 || input_year > 2030){
            PrintScanInvalidInput();
            continue;
        }
        return_date.d = input_day;
        return_date.m = input_month;
        return_date.y = input_year;
        break;
    }
    while (getchar() != '\n');
    return return_date;
}

TRANSACTION_TYPES ReceiveTransactionTypeUserInput()
{
    // Scans an int from the input stream and checks so it is only of the possible transaction types (1 or 2)
    TRANSACTION_TYPES input;
    int scan_result;
    while (1){
        scan_result = scanf("%d", &input);
        if (scan_result != 1){
            // scanf error
            PrintScanInvalidInput();

            // Clear the input stream so scanf doesn't read already inputted data
            while (getchar() != '\n');

            continue;
        }
        if (input != TRANSACTION_EXPENSE && input != TRANSACTION_INCOME){
            PrintScanInvalidInput();
            continue;
        }
        break;
    }
    while (getchar() != '\n');
    return input;
}

double ReceiveDoubleUserInput()
{
    // Scans input stream until a double is given
    double input;
    int scan_result;
    while (1){
        scan_result = scanf("%lf", &input);
        if (scan_result != 1){
            // scanf error
            PrintScanInvalidInput();

            // Clear the input stream so scanf doesn't read already inputted data
            while (getchar() != '\n');

            continue;
        }
        if (input < 0.0){
            PrintScanInvalidInput();
            continue;
        }
        break;
    }
    while (getchar() != '\n');
    return input;
}

// Output Functions

void PrintTransactionInputDateText()
{
    printf("\nInput transaction date (\"dd mm yyyy\")\n");
}

void PrintTransactionInputTypeText()
{
    printf("\nInput transaction type:\n");
    printf("1 - INCOME, 2 - EXPENSE\n");
}

void PrintTransactionInputDescriptionText()
{
    printf("\nInput transaction description:\n");
}

void PrintTransactionInputAmountText()
{
    printf("\nInput transaction amount:\n");
}

void PrintTransactionInputMaxError()
{
    printf("\nMaximum transaction number reached!!!\n");
}

void PrintTransactionInputIndexText()
{
    printf("\nInput transaction index (\"-1\" for return):\n");
}


void PrintTransactionDateSumInputStartDateText()
{
    printf("\nInput start date for calculation (\"d m y\")\n");
}

void PrintTransactionDateSumInputEndDateText()
{
    printf("\nInput end date for calculation (\"d m y\")\n");
}

void PrintFinancialReport(int transaction_sum, int transaction_income, int transaction_expense)
{
    printf("\nThe sum of all transactions from the inputted time interval is:\n");
    printf("%d\n", transaction_sum);
    printf("\nThe sum of all income transactions from the inputted time interval is:\n");
    printf("%d\n", transaction_income);
    printf("\nThe sum of all expense transactions from the inputted time interval is:\n");
    printf("%d\n", transaction_expense);
}


void PrintAccountDetailsInputBalanceText()
{
    printf("\nInput new base account balance(will add transactions):\n");
}

void PrintAccountDetailsInputNameText()
{
    printf("\nInput new account name:\n");
}


void PrintStartingText()
{
    printf("Hello, User! This application will help you manage your financial needs.\nPlease Follow the given instructions in order to manage your transactions and your account details.\n");
}

void PrintTransactionIndexText()
{
    printf("\nThe transaction at that index is:\n");
}


void PrintTransactionMenu()
{
    printf("This menu will help you with anything related to transactions!\n");
    printf("1 - Record transaction.\n");
    printf("2 - Remove transaction.\n");
    printf("3 - Modify transaction.\n");
    printf("4 - Calculate transactions in a certain time interval.\n");
    printf("5 - Go back to main menu.\n");
}

void PrintMainMenu()
{
    printf("This is the main menu!\n");
    printf("1 - Account Menu.\n");
    printf("2 - Transaction Menu.\n");
    printf("3 - Load transactions and account details from file.\n");
    printf("4 - Save transactions and account details to file.\n");
    printf("5 - Exit application.\n");
}

void PrintAccountMenu()
{
    printf("This menu will help you manage your account\n");
    printf("1 - Print account details.\n");
    printf("2 - Print account transaction log.\n");
    printf("3 - Change account details.\n");
    printf("4 - Go back to main menu.\n");
}

void PrintScanInvalidInput()
{
    printf("Invalid input!\n");
}

void PrintDate(Date date)
{
    // Formats a Date object as d/m/y output
    printf("%d/%d/%d", date.d, date.m, date.y);
}

void PrintTransaction(Transaction transaction)
{
    // Prints all the data of a Transaction with labels
    printf("Type: ");
    switch (transaction.transaction_type){
        case 1:
            printf("Income\n");
            break;
        case 2:
            printf("Expense\n");
            break;
    }
    printf("Value: %lf\n", transaction.transaction_amount);
    printf("Date(d/m/y): ");
    PrintDate(transaction.transaction_date);
    printf("\n");
    printf("Desc: %s\n", transaction.description);
}

void PrintAccountDetails(Account acc)
{
    // Prints Account details with labels
    printf("\n");
    printf("Account Name: %s\n", acc.account_name);
    printf("Account balance: %lf\n", acc.account_balance); 
}

void PrintAccountTransactionLog(Account acc)
{
    // Prints whole transaction log with index and labels
    for (int i = 0; i < acc.transaction_number; i += 1){
        printf("\nTransaction Index: %d\n", i);
        PrintTransaction(acc.transaction_array[i]);
    }  
}


void AwaitEnterKey()
{
    // Menu function that reads input stream until enter key.
    printf("\nPress Enter.\n");
    scanf("%c");
}


void PrintFileLoadError()
{
    printf("\nError while loading data! Try again or change file contents.\n");
}

void PrintFileLoadSuccess()
{
    printf("\nData loaded successfully!\n");
}

void PrintFileSaveError()
{
    printf("\nError while saving data!!\n");
}

void PrintFileSaveSuccess()
{
    printf("\nData saved successfully!\n");
}