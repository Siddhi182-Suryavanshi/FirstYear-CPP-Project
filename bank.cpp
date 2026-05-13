#include <iostream>
#include <fstream>
using namespace std;

class BankAccount
{
private:
    int accountNumber;
    char name[50];
    float balance;

public:
    void createAccount()
    {
        cout << "\nEnter Account Number: ";
        cin >> accountNumber;

        cin.ignore();

        cout << "Enter Customer Name: ";
        cin.getline(name, 50);

        cout << "Enter Initial Balance: ";
        cin >> balance;
    }

    void displayAccount()
    {
        cout << "\n---------------------------";
        cout << "\nAccount Number : " << accountNumber;
        cout << "\nCustomer Name  : " << name;
        cout << "\nBalance         : " << balance;
        cout << "\n---------------------------\n";
    }

    int getAccountNumber()
    {
        return accountNumber;
    }

    void deposit()
    {
        float amount;

        cout << "Enter amount to deposit: ";
        cin >> amount;

        balance += amount;

        cout << "Amount Deposited Successfully!\n";
    }

    void withdraw()
    {
        float amount;

        cout << "Enter amount to withdraw: ";
        cin >> amount;

        if (amount > balance)
        {
            cout << "Insufficient Balance!\n";
        }
        else
        {
            balance -= amount;
            cout << "Withdrawal Successful!\n";
        }
    }

    void saveToFile()
    {
        ofstream file("bank.txt", ios::app);

        file << accountNumber << endl;
        file << name << endl;
        file << balance << endl;

        file.close();
    }

    bool searchAccount(int accNo)
    {
        ifstream file("bank.txt");

        int acc;
        string cname;
        float bal;

        while (file >> acc)
        {
            file.ignore();

            getline(file, cname);

            file >> bal;

            if (acc == accNo)
            {
                cout << "\nAccount Found!\n";

                cout << "Account Number : " << acc << endl;
                cout << "Customer Name  : " << cname << endl;
                cout << "Balance         : " << bal << endl;

                file.close();
                return true;
            }
        }

        file.close();
        return false;
    }
};

int main()
{
    BankAccount account;

    int choice, accNo;

    do
    {
        cout << "\n===== BANK MANAGEMENT SYSTEM =====";
        cout << "\n1. Create Account";
        cout << "\n2. Deposit Money";
        cout << "\n3. Withdraw Money";
        cout << "\n4. Balance Check";
        cout << "\n5. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            account.createAccount();
            account.saveToFile();
            cout << "Account Created Successfully!\n";
            break;

        case 2:
            account.deposit();
            break;

        case 3:
            account.withdraw();
            break;

        case 4:
            cout << "Enter Account Number: ";
            cin >> accNo;

            if (!account.searchAccount(accNo))
            {
                cout << "Account Not Found!\n";
            }

            break;

        case 5:
            cout << "Thank You for Using Bank Management System!\n";
            break;

        default:
            cout << "Invalid Choice!\n";
        }

    } while (choice != 5);

    return 0;
}
