#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

// Transaction class to hold details of a transaction
class Transaction {
public:
    string type;  // Deposit or Withdrawal
    double amount;

    Transaction(string transactionType, double transactionAmount)
        : type(transactionType), amount(transactionAmount) {}
};

// ATM class to represent a user's account
class ATM {
private:
    string accountHolderName;
    string accountNumber;
    string pin;
    double balance;
    vector<Transaction> transactionHistory;

public:
    // Constructor
    ATM(string name, string accNum, string accountPin, double initialBalance)
        : accountHolderName(name), accountNumber(accNum), pin(accountPin), balance(initialBalance) {}

    // Getter for account number
    string getAccountNumber() const {
        return accountNumber;
    }

    // Function to validate PIN
    bool validatePin(string enteredPin) {
        return pin == enteredPin;
    }

    // Function to deposit money
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            transactionHistory.push_back(Transaction("Deposit", amount));
            cout << "Deposit successful! Your new balance is $" << fixed << setprecision(2) << balance << endl;
        } else {
            cout << "Invalid amount. Please try again." << endl;
        }
    }

    // Function to withdraw money
    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            transactionHistory.push_back(Transaction("Withdrawal", amount));
            cout << "Withdrawal successful! Your new balance is $" << fixed << setprecision(2) << balance << endl;
        } else {
            cout << "Invalid amount or insufficient balance. Please try again." << endl;
        }
    }

    // Function to check balance
    void checkBalance() {
        cout << "Your current balance is $" << fixed << setprecision(2) << balance << endl;
    }

    // Function to view transaction history
    void viewTransactionHistory() {
        cout << "Transaction History:" << endl;
        if (transactionHistory.empty()) {
            cout << "No transactions available." << endl;
        } else {
            for (const auto &transaction : transactionHistory) {
                cout << transaction.type << ": $" << fixed << setprecision(2) << transaction.amount << endl;
            }
        }
    }
};

// Main program
int main() {
    vector<ATM> accounts;

    // Sample accounts for testing
    accounts.push_back(ATM("Alpha Kamara", "123456", "1111", 500.00));
    accounts.push_back(ATM("Saffiatu Tucker", "654321", "2222", 1000.00));

    string enteredAccountNumber, enteredPin;
    ATM* currentAccount = nullptr;

    // Authentication
    bool authenticated = false;
    while (!authenticated) {
        cout << "\nEnter your account number: ";
        cin >> enteredAccountNumber;
        cout << "Enter your PIN: ";
        cin >> enteredPin;

        for (auto &account : accounts) {
            if (account.getAccountNumber() == enteredAccountNumber && account.validatePin(enteredPin)) {
                currentAccount = &account;
                authenticated = true;
                break;
            }
        }

        if (!authenticated) {
            cout << "Invalid account number or PIN. Please try again." << endl;
        }
    }

    cout << "\nWelcome, " << enteredAccountNumber << "!" << endl;

    // ATM Menu
    int choice;
    do {
        cout << "\n--- ATM Menu ---" << endl;
        cout << "1. Check Balance" << endl;
        cout << "2. Deposit Money" << endl;
        cout << "3. Withdraw Money" << endl;
        cout << "4. View Transaction History" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            currentAccount->checkBalance();
            break;
        case 2: {
            double depositAmount;
            cout << "Enter the amount to deposit: ";
            cin >> depositAmount;
            currentAccount->deposit(depositAmount);
            break;
        }
        case 3: {
            double withdrawalAmount;
            cout << "Enter the amount to withdraw: ";
            cin >> withdrawalAmount;
            currentAccount->withdraw(withdrawalAmount);
            break;
        }
        case 4:
            currentAccount->viewTransactionHistory();
            break;
        case 5:
            cout << "Thank you for using the ATM. Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 5);

    return 0;
}

