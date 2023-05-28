/*
    Assignment-4
    Implement a solution for a Constraint Satisfaction Problem using Branch and Bound and Backtracking for n-queens problem or a graph coloring problem.
*/

#include <bits/stdc++.h>
using namespace std;

/* N-Queens solved using BackTracking Technique */
bool isPossible(vector<string> &board, int row, int col)
{
    // Checking the Same Column
    for (int i = row - 1; i >= 0; i--)
    {
        if (board[i][col] == 'Q')
            return false;
    }

    // Checking the Upper Left Diagonal
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--)
    {
        if (board[i][j] == 'Q')
            return false;
    }

    // Checking the Upper Right Diagonal
    for (int i = row - 1, j = col + 1; i >= 0 && j < board.size(); i--, j++)
    {
        if (board[i][j] == 'Q')
            return false;
    }

    return true;
}

void solveNQueens_BackTracking(vector<string> &board, int n, int row, vector<vector<string>> &result)
{
    if (row == n)
    {
        result.push_back(board);
        return;
    }

    for (int col = 0; col < n; col++)
    {
        if (isPossible(board, row, col))
        {
            board[row][col] = 'Q';
            solveNQueens_BackTracking(board, n, row + 1, result);
            board[row][col] = '.';
        }
    }
}
void solveNQueens_BackTracking(int n, vector<vector<string>> &result)
{
    vector<string> board(n, string(n, '.'));
    solveNQueens_BackTracking(board, n, 0, result);
}

/* N-Queens solved using Branch and Bound Technique */
void solveNQueens_BranchAndBound(vector<string> &board, int &n, int row, vector<bool> &columns, vector<bool> &normalDiagonals, vector<bool> &reverseDiagonals, vector<vector<string>> &result)
{
    if (row == n)
    {
        result.push_back(board);
        return;
    }

    for (int col = 0; col < n; col++)
    {
        if (columns[col] == false && normalDiagonals[(row + col)] == false && reverseDiagonals[(row - col + (n - 1))] == false)
        {
            board[row][col] = 'Q';
            columns[col] = true;
            normalDiagonals[(row + col)] = true;
            reverseDiagonals[(row - col + (n - 1))] = true;

            solveNQueens_BranchAndBound(board, n, row + 1, columns, normalDiagonals, reverseDiagonals, result);

            columns[col] = false;
            normalDiagonals[(row + col)] = false;
            reverseDiagonals[(row - col + (n - 1))] = false;
            board[row][col] = '.';
        }
    }
}
void solveNQueens_BranchAndBound(int n, vector<vector<string>> &result)
{
    vector<string> board(n, string(n, '.'));

    vector<bool> columns(n, false);
    vector<bool> normalDiagonals(2 * n - 1, false);  // Upward Diagonals. Each cell is represented by (row + col)
    vector<bool> reverseDiagonals(2 * n - 1, false); // Downward Diagonals. Each cell is represented by (row - col + n -1);

    solveNQueens_BranchAndBound(board, n, 0, columns, normalDiagonals, reverseDiagonals, result);
}

int main()
{
    int n;
    cout << "Enter the number of Queens : ";
    cin >> n;
    cout << endl;

    int option;
    cout << " -------------------- MENU -------------------- " << endl;
    cout << " 1. N Queens solve using BackTracking Technique" << endl;
    cout << " 2. N Queens solve using Branch and Bound Technique" << endl;
    cout << "Enter the option: ";
    cin >> option;

    vector<vector<string>> result;
    if (option == 1)
    {
        solveNQueens_BackTracking(n, result);
    }
    else if (option == 2)
    {
        solveNQueens_BranchAndBound(n, result);
    }
    else
    {
        cout << "Invalid Option" << endl;
        return 0;
    }

    for (int i = 0; i < result.size(); i++)
    {
        cout << "Solution-" << (i + 1) << endl;
        for (string row : result[i])
        {
            cout << row << endl;
        }
        cout << endl;
    }

    return 0;
}