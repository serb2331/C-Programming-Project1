#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ui.h"
#include "data_structs.h"
#include "file_handling.h"

/**
 Managing Financial Data: Create an application that allows the user to record and manage simple
financial data, such as transactions, income, and expenses.
*/

void RecordTransaction(Account *acc)
{
    /*
    Print and Scan accordingly data related to a Transaction which will pe appended to the end of the transaction_array of Account acc.
    */
    if (acc -> transaction_number < MAX_TRANSACTIONS){
        PrintTransactionInputTypeText();
        TRANSACTION_TYPES input_type = ReceiveTransactionTypeUserInput();

        PrintTransactionInputAmountText();
        double input_amount = ReceiveDoubleUserInput();

        PrintTransactionInputDateText();
        Date input_date = ReceiveDateUserInput();

        PrintTransactionInputDescriptionText();
        char input_description[150];
        ReceiveCharArrayUserInput(input_description);

        acc -> transaction_array[acc -> transaction_number] = CreateTransaction(input_date, input_type, input_amount, input_description);
        acc -> transaction_number += 1;
    }
    else
        //If the maximum number of transactions are reached, print an error and return
        PrintTransactionInputMaxError();
}

void RemoveTransaction(Account *acc)
{
    /*
    Input an index from the user and, if valid, remove the transaction at that index by moving each subsequent transaction one back until the end is reached.
    */
    PrintAccountTransactionLog(*acc);
    PrintTransactionInputIndexText();
    int transaction_index = -1;
    while (transaction_index < 0 || transaction_index >= acc -> transaction_number){
        transaction_index = ReceiveIntUserInput();
        if (transaction_index == -1)
            return;
        if (transaction_index < 0 || transaction_index >= acc -> transaction_number)
            PrintScanInvalidInput();
    }
    PrintTransactionIndexText();
    PrintTransaction(acc -> transaction_array[transaction_index]);

    for (int i = transaction_index; i < acc -> transaction_number; i += 1){
        acc -> transaction_array[i] = acc -> transaction_array[i + 1];
    }
    acc -> transaction_number -= 1;
}

void ModifyTransaction(Account *acc)
{
    /*
    Input an index from the user and, if valid, receive Transaction information from the user and update the transaction at that index with those values.
    */
    PrintAccountTransactionLog(*acc);
    PrintTransactionInputIndexText();
    int transaction_index = -1;
    while (transaction_index < 0 || transaction_index >= acc -> transaction_number){
        transaction_index = ReceiveIntUserInput();
        if (transaction_index == -1)
            return;
        if (transaction_index < 0 || transaction_index >= acc -> transaction_number)
            PrintScanInvalidInput();
    }
    PrintTransactionIndexText();
    PrintTransaction(acc -> transaction_array[transaction_index]);

    PrintTransactionInputTypeText();
    TRANSACTION_TYPES input_type = ReceiveTransactionTypeUserInput();
    acc -> transaction_array[transaction_index].transaction_type = input_type;

    PrintTransactionInputAmountText();
    double input_amount = ReceiveDoubleUserInput();
    acc -> transaction_array[transaction_index].transaction_amount = input_amount;

    PrintTransactionInputDateText();
    Date input_date = ReceiveDateUserInput();
    acc -> transaction_array[transaction_index].transaction_date = input_date;

    PrintTransactionInputDescriptionText();
    char input_description[150];
    ReceiveCharArrayUserInput(input_description);
    strcpy(acc -> transaction_array[transaction_index].description, input_description);
}

void CalculateTransactionDateSum(Account *acc)
{
    /*
    Read from input 2 dates. If the dates are chronological, compute the sum of transactions within that time frame. If not, return.
    */
    Date start_date, end_date;
    PrintTransactionDateSumInputStartDateText();
    start_date = ReceiveDateUserInput();
    PrintTransactionDateSumInputEndDateText();
    end_date = ReceiveDateUserInput();

    if (DateCalculateDayCount(start_date) > DateCalculateDayCount(end_date)){
        PrintScanInvalidInput();
        return;
    }
    else{
        int transaction_sum = 0;
        int transaction_income = 0;
        int transaction_expense = 0;
        printf("\nFinancial Report:\n\n");
        for (int i = 0; i < acc->transaction_number; i += 1){
            if (DateCalculateDayCount(acc -> transaction_array[i].transaction_date) >= DateCalculateDayCount(start_date) && DateCalculateDayCount(acc -> transaction_array[i].transaction_date) <= DateCalculateDayCount(end_date)){
                PrintTransaction(acc -> transaction_array[i]);
                printf("\n");
                if (acc -> transaction_array[i].transaction_type == TRANSACTION_INCOME)
                    transaction_income += acc -> transaction_array[i].transaction_amount;
                if (acc -> transaction_array[i].transaction_type == TRANSACTION_EXPENSE)
                    transaction_expense += acc -> transaction_array[i].transaction_amount;
            }
        }
        transaction_sum = transaction_income - transaction_expense;
        PrintFinancialReport(transaction_sum, transaction_income, transaction_expense);
    }
}


void ModifyAccountDetails(Account *acc)
{
    /*
    Receive new account information and update it accordingly.
    */
    PrintAccountDetailsInputNameText();
    char input_name[100];
    ReceiveCharArrayUserInput(input_name);
    
    PrintAccountDetailsInputBalanceText();
    double input_balance = ReceiveDoubleUserInput();

    strcpy(acc -> account_name, input_name);
    acc -> account_base_balance = input_balance;
}

void StartApplication()
{
    // Initialize the used account
    Account user_account;
    InitializeAccount(&user_account);

    // File declarations for saving and loading.
    FILE *load_file, *save_file;

    PrintStartingText();
    AwaitEnterKey();

    int main_menu_input = 0;
    while (main_menu_input != MAIN_MENU_INPUT_EXIT){
        system("clear");
        PrintMainMenu();
        // Receive main menu option
        main_menu_input = ReceiveIntUserInput();
        switch (main_menu_input)
        {
            case MAIN_MENU_INPUT_ACCOUNT_MENU:

                int account_menu_input = 0;
                while (account_menu_input != ACCOUNT_MENU_INPUT_BACK){
                    system("clear");
                    PrintAccountMenu();
                    // Receive account menu option
                    account_menu_input = ReceiveIntUserInput();
                    switch (account_menu_input){
                        case ACCOUNT_MENU_INPUT_PRINT_DETAILS:  
                            // Print account details
                            PrintAccountDetails(user_account);
                            AwaitEnterKey();
                            break;
                        case ACCOUNT_MENU_INPUT_TRANSACTION_LOG:
                            // Print account transaction log
                            PrintAccountTransactionLog(user_account);
                            AwaitEnterKey();
                            break;
                        case ACCOUNT_MENU_INPUT_CHANGE_DETAILS:
                            // Change account details
                            ModifyAccountDetails(&user_account);
                            // Update the account balance to show transaction sum as well
                            UpdateBalanceAccount(&user_account);
                            AwaitEnterKey();
                            break;
                        case ACCOUNT_MENU_INPUT_BACK:
                            // Go back to main menu
                            break;
                        default:
                            // Invalid input
                            PrintScanInvalidInput();
                            break;
                    }
                }
                break;
            case MAIN_MENU_INPUT_TRANSACTION_MENU:
                int transaction_menu_input = 0;
                while (transaction_menu_input != TRANSACTION_MENU_BACK){
                    system("clear");
                    PrintTransactionMenu();
                    // Receive transaction menu option
                    transaction_menu_input = ReceiveIntUserInput();
                    switch (transaction_menu_input){
                        case TRANSACTION_MENU_RECORD_TRANSACTION:
                            // Record a transaction and add it to the account log
                            RecordTransaction(&user_account);
                            // Update the balance to include the newly added transaction
                            UpdateBalanceAccount(&user_account);
                            AwaitEnterKey();
                            break;
                        case TRANSACTION_MENU_REMOVE_TRANSACTION:
                            // Remove a transaction from the log
                            RemoveTransaction(&user_account);
                            // Update the balance to exclude the removed transaction
                            UpdateBalanceAccount(&user_account);
                            break;
                        case TRANSACTION_MENU_MODIFY_TRANSACTION:
                            // Modify a transaction in the log
                            ModifyTransaction(&user_account);
                            // Update the balance to include the changed transaction
                            UpdateBalanceAccount(&user_account);
                            AwaitEnterKey();
                            break;
                        case TRANSACTION_MENU_CALCULATE_DATE:
                            // Calculate the sum of transactions in a specific time-frame
                            CalculateTransactionDateSum(&user_account);
                            AwaitEnterKey();
                            break;
                        case TRANSACTION_MENU_BACK:
                            // Go back to main menu
                            break;
                        default:
                            // Invalid input
                            PrintScanInvalidInput();
                            break;
                    }
                }
                break;
            case MAIN_MENU_INPUT_LOAD:
                // Load data from text file
                load_file = fopen("account_details.txt", "r");
                if (load_file == NULL){
                    // If any issues opening the file
                    PrintFileLoadError();
                    AwaitEnterKey();
                }
                else{
                    // If successfull, then the file has valid data
                    FileLoadAccount(&user_account, load_file);
                    PrintFileLoadSuccess();
                    AwaitEnterKey();
                }
                // After reading, calculate the balance
                UpdateBalanceAccount(&user_account);
                // and close the file
                fclose(load_file);
                break;
            case MAIN_MENU_INPUT_SAVE:
                // Save data to text file
                save_file = fopen("account_details.txt", "w");
                if (save_file == NULL){
                    // If any issues opening the file
                    PrintFileSaveError();
                    AwaitEnterKey();
                }
                else{
                    //If successfull, save account data to the file
                    FileSaveAccount(user_account, save_file);
                    PrintFileSaveSuccess();
                    AwaitEnterKey();
                }
                // And close the file
                fclose(save_file);
                break;
            case MAIN_MENU_INPUT_EXIT:
                // Leave the program
                printf("\nBye!\n");
                break;
            default:
                // Invalid input 
                PrintScanInvalidInput();
                break;
        }
    }
    return;
}


int main()
{
    // START THE APP!!
    StartApplication();
    return 0;
}