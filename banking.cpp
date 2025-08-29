#include <iostream>
#include <string>
using namespace std;

class BankAccount {
protected:
    int accountNumber;
    string accountHolderName;
    double balance;

public:
    BankAccount(int accNo, string name, double initialBalance)
        : accountNumber(accNo), accountHolderName(name), balance(initialBalance) {}

    virtual void deposit(double amount) {
        balance += amount;
        cout << "Deposited: " << amount << " | New Balance: " << balance << endl;
    }

    virtual void withdraw(double amount) {
        if (amount <= balance) {
            balance -= amount;
            cout << "Withdrawn: " << amount << " | New Balance: " << balance << endl;
        } else {
            cout << "Insufficient funds!" << endl;
        }
    }

    double getBalance() const {
        return balance;
    }

    virtual void displayAccountInfo() const {
        cout << "\nAccount Number: " << accountNumber
             << "\nHolder Name: " << accountHolderName
             << "\nBalance: " << balance << endl;
    }

    virtual void calculateInterest() {
        cout << "Base account does not provide interest calculation." << endl;
    }

    virtual ~BankAccount() {} 
};

class SavingsAccount : public BankAccount {
private:
    double interestRate; 

public:
    SavingsAccount(int accNo, string name, double initialBalance, double rate)
        : BankAccount(accNo, name, initialBalance), interestRate(rate) {}

    void calculateInterest() override {
        double interest = balance * (interestRate / 100);
        cout << "Savings Interest: " << interest << endl;
    }

    void displayAccountInfo() const override {
        BankAccount::displayAccountInfo();
        cout << "Account Type: Savings\nInterest Rate: " << interestRate << "%" << endl;
    }
};

class CheckingAccount : public BankAccount {
private:
    double overdraftLimit;

public:
    CheckingAccount(int accNo, string name, double initialBalance, double limit)
        : BankAccount(accNo, name, initialBalance), overdraftLimit(limit) {}

    void withdraw(double amount) override {
        if (amount <= balance + overdraftLimit) {
            balance -= amount;
            cout << "Withdrawn: " << amount << " | New Balance: " << balance << endl;
        } else {
            cout << "Overdraft limit exceeded!" << endl;
        }
    }

    void displayAccountInfo() const override {
        BankAccount::displayAccountInfo();
        cout << "Account Type: Checking\nOverdraft Limit: " << overdraftLimit << endl;
    }
};

class FixedDepositAccount : public BankAccount {
private:
    int term;         
    double interestRate; 

public:
    FixedDepositAccount(int accNo, string name, double initialBalance, int t, double rate)
        : BankAccount(accNo, name, initialBalance), term(t), interestRate(rate) {}

    void calculateInterest() override {
        double interest = balance * (interestRate / 100) * (term / 12.0);
        cout << "Fixed Deposit Interest for " << term << " months: " << interest << endl;
    }

    void displayAccountInfo() const override {
        BankAccount::displayAccountInfo();
        cout << "Account Type: Fixed Deposit\nTerm: " << term
             << " months\nInterest Rate: " << interestRate << "%" << endl;
    }
};

int main() {
    // Create account objects
    BankAccount* accounts[3];
    accounts[0] = new SavingsAccount(101, "Alice", 5000, 5.0);
    accounts[1] = new CheckingAccount(102, "Bob", 2000, 1000);
    accounts[2] = new FixedDepositAccount(103, "Charlie", 10000, 12, 7.0);

    int choice, accIndex;
    double amount;

    do {
        cout << "\n===== Banking System Menu =====" << endl;
        cout << "1. Display Account Info" << endl;
        cout << "2. Deposit" << endl;
        cout << "3. Withdraw" << endl;
        cout << "4. Calculate Interest" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 0) break;

        cout << "Select Account: (0=Alice-Savings, 1=Bob-Checking, 2=Charlie-Fixed): ";
        cin >> accIndex;

        if (accIndex < 0 || accIndex > 2) {
            cout << "Invalid account selection!" << endl;
            continue;
        }

        switch (choice) {
        case 1:
            accounts[accIndex]->displayAccountInfo();
            break;
        case 2:
            cout << "Enter deposit amount: ";
            cin >> amount;
            accounts[accIndex]->deposit(amount);
            break;
        case 3:
            cout << "Enter withdrawal amount: ";
            cin >> amount;
            accounts[accIndex]->withdraw(amount);
            break;
        case 4:
            accounts[accIndex]->calculateInterest(); 
            break;
        default:
            cout << "Invalid choice!" << endl;
        }

    } while (true);

    for (int i = 0; i < 3; i++) delete accounts[i];

    cout << "Exiting Banking System. Goodbye!" << endl;
    return 0;
}
