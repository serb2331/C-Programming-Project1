#ifndef UI_H
#define UI_H

#include "data_structs.h"

// Enum defining all possible Main menu inputs
typedef enum _MAIN_MENU_INPUTS{
    MAIN_MENU_INPUT_ACCOUNT_MENU = 1,
    MAIN_MENU_INPUT_TRANSACTION_MENU = 2,
    MAIN_MENU_INPUT_LOAD = 3,
    MAIN_MENU_INPUT_SAVE = 4,
    MAIN_MENU_INPUT_EXIT = 5
} MAIN_MENU_INPUTS;

// Enum defining all possible Account menu inputs
typedef enum _ACCOUNT_MENU_INPUTS{
    ACCOUNT_MENU_INPUT_PRINT_DETAILS = 1,
    ACCOUNT_MENU_INPUT_TRANSACTION_LOG = 2,
    ACCOUNT_MENU_INPUT_CHANGE_DETAILS = 3,
    ACCOUNT_MENU_INPUT_BACK = 4
} ACCOUNT_MENU_INPUTS;

// Enum defining all possible Transaction menu inputs
typedef enum _TRANSACTION_MENU_INPUTS{
    TRANSACTION_MENU_RECORD_TRANSACTION = 1,
    TRANSACTION_MENU_REMOVE_TRANSACTION = 2,
    TRANSACTION_MENU_MODIFY_TRANSACTION = 3,
    TRANSACTION_MENU_CALCULATE_DATE = 4,
    TRANSACTION_MENU_BACK = 5
} TRANSACTION_MENU_INPUTS;

//INPUT FUNCTIONS

int ReceiveIntUserInput();
void ReceiveCharArrayUserInput(char arr[]);
Date ReceiveDateUserInput();
TRANSACTION_TYPES ReceiveTransactionTypeUserInput();
double ReceiveDoubleUserInput();

//OUTPUT FUNCTIONS

void PrintTransactionInputDateText();
void PrintTransactionInputTypeText();
void PrintTransactionInputDescriptionText();
void PrintTransactionInputAmountText();
void PrintTransactionInputMaxError();
void PrintTransactionInputIndexText();

void PrintTransactionIndexText();

void PrintTransactionDateSumInputStartDateText();
void PrintTransactionDateSumInputEndDateText();
void PrintTransactionDateSum(int transaction_sum);
void PrintFinancialReport(int transaction_sum, int transaction_income, int transaction_expense);

void PrintAccountDetailsInputNameText();
void PrintAccountDetailsInputBalanceText();

void PrintScanInvalidInput();

void PrintStartingText();

void PrintTransactionMenu();
void PrintMainMenu();
void PrintAccountMenu();

void PrintDate(Date date);
void PrintTransaction(Transaction transaction);
void PrintAccountDetails(Account acc);
void PrintAccountTransactionLog(Account acc);

void AwaitEnterKey();

void PrintFileLoadError();
void PrintFileLoadSuccess();
void PrintFileSaveError();
void PrintFileSaveSuccess();
#endif