#include <bits/stdc++.h>
using namespace std;

int ROW;
int COL;

typedef pair<int, int> Pair;
typedef pair<double, pair<int, int>> pPair;

vector<pair<int, int>> directions = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};

struct cell
{
    // Row and Column index of it's parent
    // Note that (0 <= i <= ROW-1) and (0 <= j <= COL-1)
    int parent_i, parent_j;
    // f = g + h
    double f, g, h;
};

bool isValid(int row, int col)
{
    // Returns true if row number and column number is in range
    return row >= 0 && row < ROW && col >= 0 && col < COL;
}

/* Description of the Grid-
   1--> The cell is not blocked
   0--> The cell is blocked
*/
bool isBlocked(vector<vector<int>> &grid, int row, int col)
{
    // Return true if the cell is blocked else false
    if (grid[row][col] == 0)
        return true;
    else
        return false;
}

bool isDestination(int row, int col, Pair destination)
{
    if (row == destination.first && col == destination.second)
        return true;
    else
        return false;
}

// A Utility Function to calculate the 'h' heuristics.
double calculateHValue(int row, int col, Pair destination)
{
    // Return using the Manhattan Distance between the two points
    return abs(row - destination.first) + abs(col - destination.second);
}

void tracePath(vector<vector<cell>> &cellDetails, Pair destination)
{
    cout << "The Path is :- " << endl;
    int row = destination.first;
    int col = destination.second;

    stack<Pair> path;

    while (!(cellDetails[row][col].parent_i == row && cellDetails[row][col].parent_j == col))
    {
        path.push({row, col});
        int temp_row = cellDetails[row][col].parent_i;
        int temp_col = cellDetails[row][col].parent_j;
        row = temp_row;
        col = temp_col;
    }

    path.push({row, col});
    while (!path.empty())
    {
        pair<int, int> current = path.top();
        path.pop();

        cout << " -> (" << current.first << "," << current.second << ") ";
    }

    return;
}

void aStarSearch(vector<vector<int>> &grid, Pair source, Pair destination)
{
    // If the source or destination is out of range
    if (isValid(source.first, source.second) == false || isValid(destination.first, destination.second) == false)
    {
        cout << "Source or Destination is Invalid" << endl;
        return;
    }

    // Either the source or the destination is blocked
    if (isBlocked(grid, source.first, source.second) == true || isBlocked(grid, destination.first, destination.second) == true)
    {
        cout << "Source or Destination is blocked" << endl;
        return;
    }

    // If the destination cell is the same as source cell
    if (isDestination(source.first, source.second, destination) == true)
    {
        cout << "We are already at the destination" << endl;
        return;
    }

    // Create a closed list and initialise it to false which
    // means that no cell has been included yet This closed
    // list is implemented as a boolean 2D array
    vector<vector<bool>> closedList(ROW, vector<bool>(COL, false));

    // Declare a 2D array of structure to hold the details of that cell
    vector<vector<cell>> cellDetails(ROW, vector<cell>(COL));

    int i, j;
    for (i = 0; i < ROW; i++)
    {
        for (j = 0; j < COL; j++)
        {
            cellDetails[i][j].f = FLT_MAX;
            cellDetails[i][j].g = FLT_MAX;
            cellDetails[i][j].h = FLT_MAX;
            cellDetails[i][j].parent_i = -1;
            cellDetails[i][j].parent_j = -1;
        }
    }

    // Initialising the parameters of the starting node
    i = source.first, j = source.second;
    cellDetails[i][j].f = 0.0;
    cellDetails[i][j].g = 0.0;
    cellDetails[i][j].h = 0.0;
    cellDetails[i][j].parent_i = i;
    cellDetails[i][j].parent_j = j;

    /*
        Create an open list having information as-
            <f, <i, j>>
            where f = g + h,
        and i, j are the row and column index of that cell
        Note that (0 <= i <= ROW-1) and (0 <= j <= COL-1)
        This open list is implemented as a set of pair of
        pair.
    */
    set<pPair> openList;

    // Put the starting cell on the open list and set its
    // 'f' as 0
    openList.insert({0.0, {i, j}});

    // We set this boolean value as false as initially
    // the destination is not reached.
    bool foundDestination = false;

    while (!openList.empty())
    {
        pPair current = *openList.begin();
        openList.erase(current);

        // Add current vertex to the closed list
        i = current.second.first;
        j = current.second.second;
        closedList[i][j] = true;

        // Generating all the 8 successor of this cell

        // To store the 'g', 'h' and 'f' of the 8 successors
        double gNew, hNew, fNew;

        for (pair<int, int> &direction : directions)
        {
            int iNew = i + direction.first;
            int jNew = j + direction.second;

            if (isValid(iNew, jNew) == true)
            {
                // If the destination cell is the same as the current successor
                if (isDestination(iNew, jNew, destination) == true)
                {
                    // Set the Parent of the destination cell
                    cellDetails[iNew][jNew].parent_i = i;
                    cellDetails[iNew][jNew].parent_j = j;
                    cout << "The destination cell is found" << endl;
                    tracePath(cellDetails, destination);
                    foundDestination = true;
                    return;
                }
                // If the successor is already on the closedList or if it is blocked, then ignore it.
                // Else do the following
                else if (closedList[iNew][jNew] == false && isBlocked(grid, iNew, jNew) == false)
                {
                    gNew = cellDetails[i][j].g + 1.0;
                    hNew = calculateHValue(iNew, jNew, destination);
                    fNew = gNew + hNew;

                    // If it isn’t on the open list, add it to
                    // the open list. Make the current square
                    // the parent of this square. Record the
                    // f, g, and h costs of the square cell
                    //                OR
                    // If it is on the open list already, check
                    // to see if this path to that square is
                    // better, using 'f' cost as the measure.
                    if (cellDetails[iNew][jNew].f == FLT_MAX || (fNew < cellDetails[iNew][jNew].f))
                    {
                        openList.insert({fNew, {iNew, jNew}});

                        // Update the details of this cell
                        cellDetails[iNew][jNew].f = fNew;
                        cellDetails[iNew][jNew].g = gNew;
                        cellDetails[iNew][jNew].h = hNew;
                        cellDetails[iNew][jNew].parent_i = i;
                        cellDetails[iNew][jNew].parent_j = j;
                    }
                }
            }
        }
    }

    // When the destination cell is not found and the open
    // list is empty, then we conclude that we failed to
    // reach the destination cell. This may happen when the
    // there is no way to destination cell (due to
    // blockages)
    if (foundDestination == false)
        cout << "Failed to find the Destination Cell" << endl;

    return;
}

int main()
{
    /*
        Description of the Grid-
            1--> The cell is not blocked
            0--> The cell is blocked
    */
    cout << "Enter the rows and cols of grid : ";
    cin >> ROW >> COL;

    vector<vector<int>> grid(ROW, vector<int>(COL));
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            cin >> grid[i][j];
        }
    }

    Pair source;
    cout << "Enter the source cell co-ordinates (x,y) : ";
    cin >> source.first >> source.second;

    Pair destination;
    cout << "Enter the destination ell co-ordinates (x,y) : ";
    cin >> destination.first >> destination.second;

    aStarSearch(grid, source, destination);

    return 0;
}