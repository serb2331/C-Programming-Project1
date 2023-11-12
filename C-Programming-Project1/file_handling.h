#ifndef FILE_HANDLING_H
#define FILE_HANDLING_H

#include <stdio.h>
#include "data_structs.h"

void FileLoadAccount(Account *acc, FILE *input_file);
void FileSaveAccount(Account acc, FILE *input_file);


#endif