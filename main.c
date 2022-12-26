/*
    What is this Program?
    => This is a basic version of a library book lending management system

    What is the one-liner(maybe a couple.. or more, sorry) of this program?
    => The library admin will be able to add a record of lenders and check the record and delete it!

    What are going to be the exact features?
    i) Create new lending entry, this will include lender id, full name, book name, date
    ii) Search for an existing lending record
    iii) Delete a specific lending record

    BONUS: Validate whether a person already has a pending return before lending them another book and ID should be exactly 6 digits one.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct lendingRecord
{
    char lenderId[7];
    char bookName[100];
    char lenderFullName[100];
    char lendingDate[100];
};

void createEntry();
void findRecord();
int checkId(char line[], char id[]);
void deleteRecord();

int main()
{
    printf("National Library Management System 2022© All Rights Reserved\n");
    printf("What action do you want to perform?\n1. Create a new record\n2. Find an existing record\n3. Delete a record\n");

    int choice;

    do
    {
        scanf("%i", &choice);
    } while (choice < 1 || choice > 3);

    switch (choice)
    {
    case 1:
        createEntry();
        break;
    case 2:
        findRecord();
        break;
    case 3:
        deleteRecord();
        break;
    default:
        printf("An Error Occurred, restart the program.");
    }

    return 0;
}

void createEntry()
{
    struct lendingRecord lendingRec;

    fflush(stdin);

    do
    {
        printf("Lender ID: ");
        gets(lendingRec.lenderId);
    } while (strlen(lendingRec.lenderId) != 6);

    do
    {
        printf("Book Name: ");
        gets(lendingRec.bookName);
    } while (strlen(lendingRec.bookName) < 1);

    do
    {
        printf("Lender Full Name: ");
        gets(lendingRec.lenderFullName);
    } while (strlen(lendingRec.lenderFullName) < 1);

    do
    {
        printf("Date: ");
        gets(lendingRec.lendingDate);
    } while (strlen(lendingRec.lendingDate) < 1);

    FILE *filePtr;
    filePtr = fopen("records.txt", "a+");

    char singleLine[200];

    int test;

    while(fgets(singleLine, 200, filePtr) != NULL) {
        test = checkId(singleLine, lendingRec.lenderId);

        if(test == 0) {
            printf("This member has to return the previous book to lend a new one.\n");
            printf("Pending Return: %s\n", singleLine);
            fclose(filePtr);
            return;
        }
    }

    fprintf(filePtr, "%s, %s, %s, %s\n", lendingRec.lenderId, lendingRec.bookName, lendingRec.lenderFullName, lendingRec.lendingDate);
    fclose(filePtr);
}

void findRecord()
{
    char lenderId[6];
    do
    {
        printf("Enter the Lender's ID: ");
        scanf("%s", lenderId);
    } while (strlen(lenderId) != 6);

    FILE *filePtr;
    filePtr = fopen("records.txt", "r");

    char singleLine[200];

    int test = 1;

    while (fgets(singleLine, 200, filePtr) != NULL)
    {
        test = checkId(singleLine, lenderId);

        if (test == 0)
        {
            printf("%s\n", singleLine);
            break;
        }
    }

    if (test == 1)
    {
        printf("No records for this id were found!\n");
    }

    fclose(filePtr);
}

void deleteRecord()
{
    char lenderId[6];

    do
    {
        printf("Enter the Lender's ID: ");
        scanf("%s", lenderId);
    } while (strlen(lenderId) != 6);

    FILE *filePtr;
    filePtr = fopen("records.txt", "r+");

    FILE *tmpFile;
    tmpFile = fopen("tmp.txt", "w+");

    char singleLine[200];

    int test = 1;
    int changesMade = 0;

    while (fgets(singleLine, 200, filePtr) != NULL)
    {
        test = checkId(singleLine, lenderId);

        if (test == 0)
        {
            printf("%s\n", singleLine);
            changesMade++;
            continue;
        }

        fprintf(tmpFile, "%s", singleLine);
    }

    fclose(tmpFile);
    fclose(filePtr);

    rename("records.txt", "old_records.txt");
    rename("tmp.txt", "records.txt");
    remove("old_records.txt");

    if (changesMade > 0)
    {
        printf("Existing Record of ID: %s was deleted successfully!\n", lenderId);
    }
    else
    {
        printf("No records exist with that ID!\n");
    }
}

int checkId(char line[], char id[])
{

    for (int i = 0; i < 6; i++)
    {
        if (line[i] != id[i])
        {
            return 1;
        }
    }

    return 0;
}