#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ACCOUNTS 100
#define NAME_LENGTH 50

typedef struct {
    int accountNumber;
    char name[NAME_LENGTH];
    float balance;
} Account;

Account accounts[MAX_ACCOUNTS];
int accountCount = 0;

void createAccount() {
    if (accountCount >= MAX_ACCOUNTS) {
        printf("Bank is full! Cannot create more accounts.\n");
        return;
    }

    Account newAccount;
    newAccount.accountNumber = accountCount + 1;
    printf("Enter account holder's name: ");
    scanf(" %[^"]", newAccount.name);
    printf("Enter initial deposit amount: ");
    scanf("%f", &newAccount.balance);

    if (newAccount.balance < 0) {
        printf("Initial deposit cannot be negative.\n");
        return;
    }

    accounts[accountCount++] = newAccount;
    printf("Account created successfully! Account Number: %d\n", newAccount.accountNumber);
}

void viewAccount() {
    int accountNumber;
    printf("Enter account number to view: ");
    scanf("%d", &accountNumber);

    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].accountNumber == accountNumber) {
            printf("\nAccount Number: %d\nName: %s\nBalance: %.2f\n", 
                   accounts[i].accountNumber, accounts[i].name, accounts[i].balance);
            return;
        }
    }

    printf("Account not found.\n");
}

void deposit() {
    int accountNumber;
    float amount;
    printf("Enter account number to deposit into: ");
    scanf("%d", &accountNumber);
    printf("Enter amount to deposit: ");
    scanf("%f", &amount);

    if (amount <= 0) {
        printf("Deposit amount must be positive.\n");
        return;
    }

    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].accountNumber == accountNumber) {
            accounts[i].balance += amount;
            printf("Deposited %.2f successfully. New Balance: %.2f\n", amount, accounts[i].balance);
            return;
        }
    }

    printf("Account not found.\n");
}

void withdraw() {
    int accountNumber;
    float amount;
    printf("Enter account number to withdraw from: ");
    scanf("%d", &accountNumber);
    printf("Enter amount to withdraw: ");
    scanf("%f", &amount);

    if (amount <= 0) {
        printf("Withdrawal amount must be positive.\n");
        return;
    }

    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].accountNumber == accountNumber) {
            if (accounts[i].balance < amount) {
                printf("Insufficient funds.\n");
                return;
            }
            accounts[i].balance -= amount;
            printf("Withdrew %.2f successfully. New Balance: %.2f\n", amount, accounts[i].balance);
            return;
        }
    }

    printf("Account not found.\n");
}

void displayAllAccounts() {
    if (accountCount == 0) {
        printf("No accounts available.\n");
        return;
    }

    printf("\n%-10s%-20s%-10s\n", "Account No.", "Name", "Balance");
    printf("-----------------------------------------\n");
    for (int i = 0; i < accountCount; i++) {
        printf("%-10d%-20s%-10.2f\n", accounts[i].accountNumber, accounts[i].name, accounts[i].balance);
    }
}

void menu() {
    printf("\nBank Management System\n");
    printf("1. Create Account\n");
    printf("2. View Account\n");
    printf("3. Deposit\n");
    printf("4. Withdraw\n");
    printf("5. Display All Accounts\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    int choice;

    do {
        menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createAccount();
                break;
            case 2:
                viewAccount();
                break;
            case 3:
                deposit();
                break;
            case 4:
                withdraw();
                break;
            case 5:
                displayAllAccounts();
                break;
            case 6:
                printf("Exiting program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}
