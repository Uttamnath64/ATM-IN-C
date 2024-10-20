#include <stdio.h>
#include <string.h>
#include <time.h>
#include <conio.h>

// Define bool for compatibility in Turbo C
typedef int bool;
#define true 1
#define false 0

struct Account {
  int id;
  char cardNo[13];
  char pin[5];
  char name[21];
  float balance;
};

struct Transaction {
  int id;
  int accountId;
  float amount;
  char createdAt[20];
};

// Pointer to hold the current logged-in account
struct Account *currentAccount;

int i;
char retry, choice;

// main functions
void home();
void login();
void logout();

// system functionality
void deposit();
void withdrawal();
void viewTransaction();
void account();

// DB operations
void addTransaction(float amount);
float getAmount();
int getLastTransactionId();

// system date-time
void getCurrentDateTime(char *dateTimeStr);

// screen animation
void welcomeScreen();
void screen(char name[], bool isAnimation);

void main() {
    // show welcome screen
    welcomeScreen();
    delay(500);

    // goto login with animation
    screen("LOGIN", true);
    login();

    getch();
}

void home() {
    
    // show home option list
    printf("\n\n");
    printf("1. Deposit Amount\n");
    printf("2. Withdrawal Amount\n");
    printf("3. View Transaction\n");
    printf("4. Account\n");
    printf("5. Logout\n");
    printf("6. Exit\n");
    printf("\n\n\n");

    printf("Enter your choice: ");
    scanf(" %c", &choice);

    switch (choice) {
        case '1':
            screen("DEPOSIT", true);
            deposit();
            break;
        case '2':
            screen("WITHDRAWAL", true);
            withdrawal();
            break;
        case '3':
            screen("VIEW TRANSACTION", true);
            viewTransaction();
            break;
        case '4':
            screen("ACCOUNT", true);
            account();
            break;
        case '5':
            screen("LOGOUT", true);
            logout();
            break;
        case '6':
            exit(0); // Exit the program
            break;
        default:
            printf("Invalid choice!!\n");
    }

    delay(500);
    screen("HOME", false);
    home();
}

void deposit() {
    float amount;
    
    printf("\n\n");
    printf("Enter the amount to deposit: ");
    scanf("%f", &amount);

    if (amount > 0) {

        // update balance in struct
        currentAccount->balance += amount;

        // add deposit transaction
        addTransaction(amount);
        printf("\n\nAmount deposited successfully!!\n\n\n");

        delay(500);
        screen("HOME", false);
        home();
    } else {
        printf("\n\nInvalid amount!!\n");
    }

    delay(500);

    // ask if the user wants to retry
    printf("Do you want to retry (Y/N)?");
    scanf(" %c", &retry);

    if (retry == 'Y' || retry == 'y') {
        screen("DEPOSIT", false);
        deposit();
    } else {
        screen("HOME", false);
        home();
    }
}

void withdrawal() {
    float amount;

    printf("\n\n");
    printf("Enter the amount to withdraw: ");
    scanf("%f", &amount);

    if (amount > 0) {

        // check if sufficient balance
        if (amount <= currentAccount->balance) {

            // update balance in struct
            currentAccount->balance -= amount;

            // add withdrawal transaction
            addTransaction(-amount);
            printf("\n\nAmount withdrawn successfully!!\n");

            delay(500);
            screen("HOME", false);
            home();
        } else {
            printf("\n\nInsufficient balance!!\n");
        }
    } else {
        printf("\n\nInvalid amount!!\n");
    }

    delay(500);

    // ask if the user wants to retry
    printf("Do you want to retry (Y/N)?");
    scanf(" %c", &retry);

    if (retry == 'Y' || retry == 'y') {
        screen("WITHDRAWAL", false);
        withdrawal();
    } else {
        screen("HOME", false);
        home();
    }
}

void viewTransaction() {
    struct Transaction transaction;
    float total = 0;
    FILE *transactionDB;
    i = 0;

    // load atm_tran.csv file with reading mode
    transactionDB = fopen("atm_tran.csv", "r");
    if (transactionDB == NULL) {
        printf("Error opening transaction file!\n");
        return;
    }

    // table header
    printf("\n\n");
    printf("| %-3s | %-10s | %-15s | %-20s |\n", "#", "Id", "Amount", "CreatedAt");
    printf("|-----|------------|-----------------|----------------------|\n");

    fseek(transactionDB, 0, SEEK_SET);
    while (fscanf(transactionDB, "%d,%d,%f,%[^\n]", &transaction.id,
            &transaction.accountId, &transaction.amount, transaction.createdAt) == 4) {

        // match accountId
        if (transaction.accountId == currentAccount->id) {
            // the transaction in table format
            printf("| %-3d | %-10d | %-15.2f | %-20s |\n", (i + 1), transaction.id, transaction.amount, 
                transaction.createdAt);

            total += transaction.amount;
            i++;
        }
    }

    fclose(transactionDB);

    if (i > 0) {
        printf("\n\nTotal transactions: %d\t Balance: %.2f \n", i, total);
    } else {
        printf("\n\nNo transactions found!!\n");
    }

    delay(500);
    printf("\n\nPress any key to go back: ");
    getch();

    screen("HOME", false);
    home();
}

void account() {

    // display account information
    printf("\n\n");
    printf("Account ID: %d\n", currentAccount->id);
    printf("Account Name: %s\n", currentAccount->name);
    printf("Account Card Number: %s\n", currentAccount->cardNo);
    printf("Account Pin Number: %s\n", currentAccount->pin);
    printf("Account Balance: %.2f\n", currentAccount->balance);

    delay(500);
    printf("\n\nPress any key to go back: ");
    getch();

    screen("HOME", false);
    home();
}

void login() {
    FILE *accountDB;
    struct Account account;
    char cardNo[12];
    char pin[4];

    // load account.csv file with reading mode
    accountDB = fopen("account.csv", "r");
    if (accountDB == NULL) {
        printf("Error opening database files!\n");
        return;
    }

    // input cardNo and pin
    printf("\n\n");
    printf("Enter Card No: ");
    scanf("%s", cardNo);
    printf("Enter Pin: ");
    scanf("%s", pin);

    // Read each account record and compare cardNo and pin
    fseek(accountDB, 0, SEEK_SET);
    while (fscanf(accountDB, "%d,%[^,],%[^,],%[^\n]", &account.id, account.cardNo,
            account.pin, account.name) == 4) {
        if (strcmp(account.cardNo, cardNo) == 0 && strcmp(account.pin, pin) == 0) {
            
            // Set the logged-in account
            currentAccount = &account;
            account.balance = getAmount();
            currentAccount = &account; // re-set with balance

            // goto home screen with animation
            screen("HOME", true);
            home();
            return;
        }
    }

    fclose(accountDB);

    // cardNo and pin not match
    printf("Invalid Card No or Pin!!\n");

    // ask if the user wants to retry
    delay(500);
    printf("Do you want to retry (Y/N)?");
    scanf(" %c", &retry);

    if (retry == 'Y' || retry == 'y') {
        screen("LOGIN", false);
        login();
    } else {
        exit(0);
    }
}

void logout() {

    // ask for logout
    printf("\n\nAre you sure you want to logout? (y/n): ");
    scanf(" %c", &choice);

    if (choice == 'y') {
        screen("LOGIN", false);
        login();
    }

    delay(500);
    printf("\n\nPress any key to go back: ");
    getch();

    screen("HOME", false);
    home();
}

void addTransaction(float amount) {
    struct Transaction newTransaction;
    FILE *transactionDB;

    // load atm_tran.csv file with appending and reading mode
    transactionDB = fopen("atm_tran.csv", "a+");
    if (transactionDB == NULL) {
        printf("Error opening database files!\n");
        return;
    }


    newTransaction.id = getLastTransactionId() + 1;
    newTransaction.accountId = currentAccount->id;
    newTransaction.amount = amount;

    // get current date and time
    getCurrentDateTime(newTransaction.createdAt);

    // Write transaction to file
    fprintf(transactionDB, "%d,%d,%.2f,%s\n", newTransaction.id, newTransaction.accountId, 
        newTransaction.amount, newTransaction.createdAt);

    fflush(transactionDB);
    fclose(transactionDB);
}

float getAmount() {
    struct Transaction transaction;
    FILE *transactionDB;
    float total = 0;

    // load atm_tran.csv file with reading mode
    transactionDB = fopen("atm_tran.csv", "r");
    if (transactionDB == NULL) {
        printf("Error opening database files!\n");
        return 0;
    }

    fseek(transactionDB, 0, SEEK_SET); // Reset file pointer to start
    while (fscanf(transactionDB, "%d,%d,%f,%[^\n]", &transaction.id, &transaction.accountId, 
            &transaction.amount, transaction.createdAt) == 4) {
        if (transaction.accountId == currentAccount->id) {
            total += transaction.amount;
        }
    }

    fclose(transactionDB);
    return total;
}

int getLastTransactionId() {
    FILE *transactionDB;
    struct Transaction transaction;
    int id = 0;

    // load atm_tran.csv file with reading mode
    transactionDB = fopen("atm_tran.csv", "r");
    if (transactionDB == NULL) {
        printf("Error opening database files!\n");
        return 0;
    }

    fseek(transactionDB, 0, SEEK_SET);
    while (fscanf(transactionDB, "%d,%d,%f,%[^\n]", &transaction.id, &transaction.accountId, 
            &transaction.amount, transaction.createdAt) == 4) {
        id = transaction.id;
    }

    fclose(transactionDB);
    return id;
}

void getCurrentDateTime(char *buffer) {
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);

    // format the date and time
    strftime(buffer, 20, "%Y-%m-%d %H:%M:%S", tm_info);
}

void welcomeScreen() {
    char name[20] = "WELCOME TO ATM";
    int size = 40 - (strlen(name) / 2);
    
    // clear screen
    clrscr();

    printf("\n\n\n\n\n\n\n\n\n\n");
    for (i = 0; i < size; i++) {
        printf(" ");
    }

    printf("%s\n", name);

    for (i = 0; i < size - 1; i++) {
        printf(" ");
    }

    for (i = 0; i < strlen(name) + 2; i++) {
        delay(20);
        printf("-");
    }
}

void screen(char name[], bool isAnimation) {
    int size = 40 - (strlen(name) / 2);
    
    // clear screen
    clrscr();

    printf("\n");
    for (i = 0; i < size; i++) {
        printf(" ");
    }

    printf("%s\n", name);
    
    for (i = 0; i < 80; i++) {
        if (isAnimation) {
            delay(10);
        }
        printf("-");
    }
}