#include <iostream>
#include <vector>
#include <string>

using namespace std;

int rowCoordsToNum(string coordinates) {    //convert row letter coordinate to a number (0,1,2)
    if ((coordinates.at(0) == 'A') 
        || (coordinates.at(0) == 'a')) {
        return 0;
    }
    else if ((coordinates.at(0) == 'B') 
        || (coordinates.at(0) == 'b')) {
        return 1;
    }
    return 2;
}

bool isFilled(string coordinates, vector<vector<char>> grid) {
    int numRow = rowCoordsToNum(coordinates);
    int numCol = coordinates.at(1) - 1;

    if (grid[numRow][numCol] == ' ') {
        return false;
    }
    else {
        return true;
    }
}

bool coordsValid(string coordinates, vector<vector<char>> grid) {   //I got stuck here. I tried to seperate everything out to make it easier to read and target the issue,
    if ((coordinates.size() == 2)                                   //but I was never able to figure out what was wrong. I ended up putting it all back together in the end in hopes that would fix something.
        && ((coordinates.at(0) == 'A') || (coordinates.at(0) == 'a') || (coordinates.at(0) == 'B')  //check for valid number and letter input
            || (coordinates.at(0) == 'b') || (coordinates.at(0) == 'C') || (coordinates.at(0) == 'c'))
        && ((coordinates.at(1) == '1') || (coordinates.at(1) == '2') || (coordinates.at(1) == '3'))
        && !isFilled(coordinates, grid)) {  //check for only 2 characters given
        return true;
    }
    return false;
}

void printGameBoard(vector<vector<char>> grid) {
    cout << endl;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            cout << grid[i][j];
            if (j != 2) {
                cout << " | ";
            }
        }
        cout << endl;
    }
}

bool win(vector<vector<char>> grid, int numRow, int column, int player) {
//check if they won
    if (((grid[numRow][0] == player) &&    //check row
        (grid[numRow][1] == player) && 
        (grid[numRow][2] == player))
        || ((grid[0][column] == player) &&    //check column
            (grid[1][column] == player) &&
            (grid[2][column] == player))) {
        return true;
    }
    if (((grid[0][0] == player) &&  //check diagonals
        (grid[1][1] == player) && 
        (grid[2][2] == player))
        ||((grid[0][2] == player) && 
            (grid[1][1] == player) && 
            (grid[2][0] == player))) {
        return true;
    }
    else {
        return false;
    }
}

bool insertCoords(vector<vector<char>>& grid, char row, int column, char player) {
    //convert the letter and number coordinates given into ones I can use in my 2D vector
    string strRow(1, row);
    int numRow = rowCoordsToNum(strRow);
    column--;

    //convert player into X or O
    if (player == 'Y') {
        player = 'X';
    }
    else {
        player = 'O';
    }

    //insert given coords
    grid[numRow][column] = player;

    //check if won
    bool ifWon = win(grid, numRow, column, player);
    return ifWon;
}

int main() {
    bool quit = false;

    vector<vector<char>> grid(3, vector<char> (3, ' '));

    cout << "Welcome to Tic-Tac-Toe!" << endl << endl;

    while (!quit) {
        char userYesOrNo = '-';
        bool firstTime = true;
        bool firstTurn = true;
        bool userFirst = false;
        bool continueToGame = false;
        int moves = 0;
        bool gameWon = false;
        string coords = "";
        int computerRowNum = -1;
        string computerRowChar = "";
        int computerColumn = -1;
        int winner = -1;    //0 for player winning, 1 for computer winning
        char tryAgain = '-';  //player input 'Y' or 'N' determining if they try again

        cout << "Would you like to go first or would you like the computer to go first?" << endl
            << "Enter Y for you or C for computer." << endl;
        cin >> userYesOrNo;

        while (!continueToGame) {
            if ((userYesOrNo == 'Y') || (userYesOrNo == 'y')) {
                continueToGame = true;
                userFirst = true;
            }
            else if ((userYesOrNo == 'C') || (userYesOrNo == 'c')) {
                continueToGame = true;
                userFirst = false;
            }
            else {
                cout << "Please enter Y or C." << endl;
                cin >> userYesOrNo;
            }
        }
        if (firstTime) {
            cout << endl << "You play Tic-Tac-Toe by inputting coordinates where you would like to place your letter. You will be X's." << endl;
            cout << "To input coordinates, you give me a letter for the row (A, B, C), then a number for the column (1, 2, 3)." << endl;
            cout << "For example: A1" << endl;
        }

        printGameBoard(grid);

        while ((moves < 9) && (gameWon == false)) {
            
            if (!firstTurn) {
                printGameBoard(grid);
            }

            if (userFirst) {
                if ((moves % 2) == 0) {
                    if (!firstTurn) {
                        cout << "Your turn." << endl;
                    }
                    else if (firstTurn && userFirst) {
                        cout << endl << "You are up first. Enter a coordinate." << endl;
                    }
                    firstTurn = false;
                    cin >> coords;
                    while (!coordsValid(coords, grid)) {
                        cout << "Invalid or full coordinates. Try again." << endl;
                        cin >> coords;
                    }
                    if (insertCoords(grid, coords.at(0), coords.at(1), 'Y')) {
                        winner = 0;
                        break;
                    }
                }  
                else {  //computer's turn
                    computerRowNum = rand() % 3;
                    if (computerRowNum == 0) {
                        computerRowChar = 'A';
                    }
                    else if (computerRowNum == 1) {
                        computerRowChar = 'B';
                    }
                    else {
                        computerRowChar = 'C';
                    }
                    computerColumn = rand() % 3;
                    coords = computerRowChar + string(1, computerColumn);
                    while (!coordsValid(coords, grid)) {    //generate random computer input
                        computerRowNum = rand() % 3;
                        if (computerRowNum == 0) {
                            computerRowChar = 'A';
                        }
                        else if (computerRowNum == 1) {
                            computerRowChar = 'B';
                        }
                        else {
                            computerRowChar = 'C';
                        }
                        computerColumn = rand() % 3;
                        coords = computerRowChar + string(1, computerColumn);  
                    }
                    if (insertCoords(grid, coords.at(0), coords.at(1), 'Y')) {
                        winner = 1;
                        break;
                    }
                }
            }
            else if (!userFirst) {
                if ((moves % 2) != 0) {
                    if (!firstTurn) {
                        cout << "Your turn." << endl;
                    }
                    else if (firstTurn && userFirst) {
                        cout << endl << "You are up first. Enter a coordinate." << endl;
                    }
                    firstTurn = false;
                    cin >> coords;
                    while (!coordsValid(coords, grid)) {
                        cout << "Invalid or full coordinates. Try again." << endl;
                        cin >> coords;
                    }
                    if (insertCoords(grid, coords.at(0), coords.at(1), 'Y')) {
                        winner = 0;
                        break;
                    }
                }  
                else {  //computer's turn
                    computerRowNum = rand() % 3;
                    if (computerRowNum == 0) {
                        computerRowChar = 'A';
                    }
                    else if (computerRowNum == 1) {
                        computerRowChar = 'B';
                    }
                    else {
                        computerRowChar = 'C';
                    }
                    computerColumn = rand() % 3;
                    coords = computerRowChar + string(1, computerColumn);
                    while (!coordsValid(coords, grid)) {    //generate random computer input
                        computerRowNum = rand() % 3;
                        if (computerRowNum == 0) {
                            computerRowChar = 'A';
                        }
                        else if (computerRowNum == 1) {
                            computerRowChar = 'B';
                        }
                        else {
                            computerRowChar = 'C';
                        }
                        computerColumn = rand() % 3;
                        coords = computerRowChar + string(1, computerColumn);
                    }
                    if (insertCoords(grid, coords.at(0), coords.at(1), 'Y')) {
                        winner = 1;
                        break;
                    }
                }
            }
            moves++;
        }
        if (winner == 1) {
            cout << "The computer won." << endl << "Try again? Type Y or N." << endl;
            cin >> tryAgain;
            continueToGame = false;
            while (continueToGame)
            if ((tryAgain == 'N') || (tryAgain == 'n')) {
                quit = true;
                break;
            }
            else if ((tryAgain == 'Y') || (tryAgain == 'y')) {
                quit = false;
                break;
            }
            else {
                cout << "Invalid input. Type Y or N." << endl;
            }
        }
        else if (winner == 0) {
            cout << "Congratulations, you won!" << endl << "Try again? Type Y or N." << endl;
            cin >> tryAgain;
            continueToGame = false;
            while (continueToGame)
            if ((tryAgain == 'N') || (tryAgain == 'n')) {
                quit = true;
                break;
            }
            else if ((tryAgain == 'Y') || (tryAgain == 'y')) {
                quit = false;
                break;
            }
            else {
                cout << "Invalid input. Type Y or N." << endl;
            }
        }
        else if (moves == 9 && gameWon == false) {
            cout << "It's a draw. Try Again? Type Y or N." << endl;
            cin >> tryAgain;
            continueToGame = false;
            while (continueToGame)
            if ((tryAgain == 'N') || (tryAgain == 'n')) {
                quit = true;
                break;
            }
            else if ((tryAgain == 'Y') || (tryAgain == 'y')) {
                quit = false;
                break;
            }
            else {
                cout << "Invalid input. Type Y or N." << endl;
            }
        }

        firstTime = false;
    }
    cout << "Thank you for playing!" << endl;
    return 0;
}