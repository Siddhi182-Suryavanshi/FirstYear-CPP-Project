#include <iostream>
using namespace std;

char board[3][3];
char currentPlayer;

// Function to initialize the board
void initializeBoard()
{
    char ch = '1';

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = ch++;
        }
    }
}

// Function to display the board
void displayBoard()
{
    cout << "\n";

    for (int i = 0; i < 3; i++)
    {
        cout << " ";

        for (int j = 0; j < 3; j++)
        {
            cout << board[i][j];

            if (j < 2)
                cout << " | ";
        }

        cout << "\n";

        if (i < 2)
            cout << "---|---|---\n";
    }

    cout << "\n";
}

// Function to change player
void switchPlayer()
{
    if (currentPlayer == 'X')
        currentPlayer = 'O';
    else
        currentPlayer = 'X';
}

// Function to check winner
bool checkWinner()
{
    // Rows and Columns
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] == board[i][1] &&
            board[i][1] == board[i][2])
            return true;

        if (board[0][i] == board[1][i] &&
            board[1][i] == board[2][i])
            return true;
    }

    // Diagonals
    if (board[0][0] == board[1][1] &&
        board[1][1] == board[2][2])
        return true;

    if (board[0][2] == board[1][1] &&
        board[1][1] == board[2][0])
        return true;

    return false;
}

// Function to check draw
bool checkDraw()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] != 'X' && board[i][j] != 'O')
                return false;
        }
    }

    return true;
}

// Function to make move
void makeMove()
{
    int choice;
    int row, col;

    while (true)
    {
        cout << "Player " << currentPlayer << ", enter position (1-9): ";
        cin >> choice;

        if (choice < 1 || choice > 9)
        {
            cout << "Invalid position! Try again.\n";
            continue;
        }

        row = (choice - 1) / 3;
        col = (choice - 1) % 3;

        if (board[row][col] != 'X' && board[row][col] != 'O')
        {
            board[row][col] = currentPlayer;
            break;
        }
        else
        {
            cout << "Position already taken! Try again.\n";
        }
    }
}

int main()
{
    char replay;

    do
    {
        initializeBoard();
        currentPlayer = 'X';

        bool gameOver = false;

        cout << "\n===== TIC TAC TOE GAME =====\n";

        while (!gameOver)
        {
            displayBoard();

            makeMove();

            if (checkWinner())
            {
                displayBoard();
                cout << "Player " << currentPlayer << " wins!\n";
                gameOver = true;
            }
            else if (checkDraw())
            {
                displayBoard();
                cout << "Game Draw!\n";
                gameOver = true;
            }
            else
            {
                switchPlayer();
            }
        }

        cout << "\nDo you want to play again? (y/n): ";
        cin >> replay;

    } while (replay == 'y' || replay == 'Y');

    cout << "\nThank you for playing!\n";

    return 0;
}