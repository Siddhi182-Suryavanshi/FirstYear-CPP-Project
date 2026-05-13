#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

class Book
{
private:
    int bookID;
    char title[50];
    char author[50];
    bool issued;

public:
    void addBook()
    {
        cout << "\nEnter Book ID: ";
        cin >> bookID;

        cin.ignore(1000, '\n');

        cout << "Enter Book Title: ";
        cin.getline(title, 50);

        cout << "Enter Author Name: ";
        cin.getline(author, 50);

        issued = false;
    }

    void displayBook()
    {
        cout << "\n------------------------";
        cout << "\nBook ID : " << bookID;
        cout << "\nTitle   : " << title;
        cout << "\nAuthor  : " << author;

        if (issued)
            cout << "\nStatus  : Issued";
        else
            cout << "\nStatus  : Available";

        cout << "\n------------------------";
    }

    int getBookID()
    {
        return bookID;
    }

    char* getTitle()
    {
        return title;
    }

    char* getAuthor()
    {
        return author;
    }

    bool isIssued()
    {
        return issued;
    }

    void issueBook()
    {
        issued = true;
    }

    void returnBook()
    {
        issued = false;
    }
};

void addBookRecord()
{
    Book b;

    ofstream file("library.dat", ios::binary | ios::app);

    b.addBook();

    file.write((char*)&b, sizeof(b));

    file.close();

    cout << "\nBook Added Successfully!\n";
}

void displayAllBooks()
{
    Book b;

    ifstream file("library.dat", ios::binary);

    if (!file)
    {
        cout << "\nNo Records Found!\n";
        return;
    }

    while (file.read((char*)&b, sizeof(b)))
    {
        b.displayBook();
    }

    file.close();
}

void searchBook()
{
    Book b;
    char search[50];
    int choice;
    bool found = false;

    ifstream file("library.dat", ios::binary);

    if (!file)
    {
        cout << "\nNo Records Found!\n";
        return;
    }

    cout << "\nSearch By:";
    cout << "\n1. Title";
    cout << "\n2. Author";
    cout << "\nEnter Choice: ";
    cin >> choice;

    cin.ignore(1000, '\n');

    cout << "Enter Search Text: ";
    cin.getline(search, 50);

    while (file.read((char*)&b, sizeof(b)))
    {
        if ((choice == 1 && strcmp(b.getTitle(), search) == 0) ||
            (choice == 2 && strcmp(b.getAuthor(), search) == 0))
        {
            b.displayBook();
            found = true;
        }
    }

    if (!found)
    {
        cout << "\nBook Not Found!\n";
    }

    file.close();
}

void issueBookRecord()
{
    Book b;
    int id;
    bool found = false;

    fstream file("library.dat", ios::binary | ios::in | ios::out);

    if (!file)
    {
        cout << "\nNo Records Found!\n";
        return;
    }

    cout << "\nEnter Book ID to Issue: ";
    cin >> id;

    while (file.read((char*)&b, sizeof(b)))
    {
        if (b.getBookID() == id)
        {
            if (!b.isIssued())
            {
                b.issueBook();

                int pos = file.tellg();

                file.seekp(pos - sizeof(b));

                file.write((char*)&b, sizeof(b));

                cout << "\nBook Issued Successfully!\n";
            }
            else
            {
                cout << "\nBook Already Issued!\n";
            }

            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "\nBook Not Found!\n";
    }

    file.close();
}

void returnBookRecord()
{
    Book b;
    int id;
    bool found = false;

    fstream file("library.dat", ios::binary | ios::in | ios::out);

    if (!file)
    {
        cout << "\nNo Records Found!\n";
        return;
    }

    cout << "\nEnter Book ID to Return: ";
    cin >> id;

    while (file.read((char*)&b, sizeof(b)))
    {
        if (b.getBookID() == id)
        {
            if (b.isIssued())
            {
                b.returnBook();

                int pos = file.tellg();

                file.seekp(pos - sizeof(b));

                file.write((char*)&b, sizeof(b));

                cout << "\nBook Returned Successfully!\n";
            }
            else
            {
                cout << "\nBook Was Not Issued!\n";
            }

            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "\nBook Not Found!\n";
    }

    file.close();
}

int main()
{
    int choice;

    do
    {
        system("cls");

        cout << "\n===== LIBRARY MANAGEMENT SYSTEM =====";
        cout << "\n1. Add Book";
        cout << "\n2. Display All Books";
        cout << "\n3. Search Book";
        cout << "\n4. Issue Book";
        cout << "\n5. Return Book";
        cout << "\n6. Exit";

        cout << "\n\nEnter Your Choice: ";
        cin >> choice;

        cin.ignore(1000, '\n');

        switch (choice)
        {
        case 1:
            addBookRecord();
            break;

        case 2:
            displayAllBooks();
            break;

        case 3:
            searchBook();
            break;

        case 4:
            issueBookRecord();
            break;

        case 5:
            returnBookRecord();
            break;

        case 6:
            cout << "\nThank You!\n";
            break;

        default:
            cout << "\nInvalid Choice!\n";
        }

        if (choice != 6)
        {
            cout << "\n\nPress Enter To Continue...";
            cin.get();
        }

    } while (choice != 6);

    return 0;
}