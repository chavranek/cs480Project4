#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <vector>
#include <numeric>
using namespace std;

string getFile(string fileName)
{
    cout << "Could not open file." << endl;
    cout << "Please enter a valid file name or enter 3 to exit the program." << endl;
    cin >> fileName;
    if (fileName == "3")
    {
        cout << "Exiting the program" << endl;
        return "0";
    }
    else
    {
        return fileName;
    }
}

void printAndSaveBoard(ifstream & file, vector< vector<string> > & board)
{
    string line;
    string piece;
    cout << "Turn: Player 1" << endl;
    // for loop both prints and saves the values from the file
    for(int i = 0; i < 4; i++)
    {
        vector<string> row;
        getline(file, line);
        for (int j = 0; j < 4; j++)
        {
            cout << line[j] << " ";
            piece = string(1, line[j]);
            row.push_back(piece);
        }
        board.push_back(row);
        cout << endl;
    }
    file.close();
}

void printResults(float time)
{
    cout << "Root Node Value: " << endl;
    cout << "Best Move Found: " << endl;
    cout << "Number of Nodes expanded: " << endl;
    cout << fixed << setprecision(6) << "CPU Time: " << time << " seconds." << endl;
    cout << endl;
}

float eval(vector< vector<string> > board)
{   // this function looks at the current board state and returns 1 if
    // its a win for player one, a 0 if its a win for player 2, 0.5
    // if it's a tie and a -1 if it isn't a valid board.
    int ones = 0;
    int twos = 0;
    int dif = 0;

    // vectors to indicate whether a row or column has been filled for a given number
    vector<int> rowP1 (4);
    vector<int> colP1 (4);
    vector<int> rowP2 (4);
    vector<int> colP2 (4);

    // variables to hold the total value of each of the above vectors
    int rowP1Total = 0;
    int colP1Total = 0;
    int rowP2Total = 0;
    int colP2Total = 0;

    // booleans to indicate if a player has enough columns and rows to win
    bool p1Done;
    bool p2Done;

    // for loop that iterates through the board and finds 2s and 1s.
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            string curVal = board[i][j];
            if(curVal == "1")
            {
                ones++;
                rowP1[i] = 1;
                colP1[j] = 1;
            }
            else if(curVal == "2")
            {
                twos++;
                rowP2[i] = 1;
                colP2[j] = 1;
            }
        }
    }

    if(ones > twos)
    {
        dif = ones - twos;
    }
    else
    {
        dif = twos - ones;
    }

    // difference between amount of ones and twos is too great
    // and therefore it is not a valid board.
    if(dif > 1)
    {
        return -1;
    }

    // total up the values of the vectors
    rowP1Total = accumulate(rowP1.begin(), rowP1.end(), 0);
    colP1Total = accumulate(colP1.begin(), colP1.end(), 0);
    rowP2Total = accumulate(rowP2.begin(), rowP2.end(), 0);
    colP2Total = accumulate(colP2.begin(), colP2.end(), 0);

    if((rowP1Total + colP1Total) == 8)
    {
        p1Done = true;
    }
    else
    {
        p1Done = false;
    }
    if((rowP2Total + colP2Total) == 8)
    {
        p2Done = true;
    }
    else
    {
        p2Done = false;
    }
    // if both true then it is a tie
    if(p1Done && p2Done)
    {
        return 0.5;
    }
    // if p1Done is true and p2Done is false then player one has won
    else if(p1Done && !p2Done)
    {
        return 1;
    }
    // if p1Done is false and p2Done is true then player two has won
    else if(!p1Done && p2Done)
    {
        return 0;
    }
    // the game has not winner and there is no tie
    else
    {
        return 3;
    }
}

bool checkStatus(float status)
{   // checks to see if the game has been solved or not.
    if(status == -1)
    {
        cout << "\n" << "This board is invalid. Please provide a valid board." << endl;
        return true;
    }
    else if(status == 1)
    {
        cout << "\n" << "Player 1 has already won the game." << endl;
        return true;
    }
    else if(status == 0)
    {
        cout << "\n" << "Player 2 has already won the game." << endl;
        return true;
    }
    else if(status == 0.5)
    {
        cout << "\n" << "The board is in a final tied game state" << endl;
        return true;
    }
    else if(status == 3)
    {
        return false;
    }
}

void minMax(vector <vector<string> > board)
{// minMax algorithm
    float time;
    clock_t t;
    t = clock();
    // algorithm goes here

    t = clock() - t;
    time = (float(t)/CLOCKS_PER_SEC);
    printResults(time);
}

void alphaBetaPruning(vector <vector<string> > board)
{// alpha-beta pruning algorithm
    float time;
    clock_t t;
    t = clock();
    // algorithm goes here
    t = clock() - t;
    time = (float(t))/CLOCKS_PER_SEC;
    printResults(time);
}

int main()
{
    int choice = 0;
    float status = 0;
    while(choice != 3)
    {
        cout << "Enter the corresponding number to choose one of the options below: " << endl;
        cout << "1) Minmax" << endl;
        cout << "2) Alpha-beta Pruning" << endl;
        cout << "3) Quit" << endl;

        cin >> choice;
        cout << endl;

        // holds the string values of the items in the board
        vector< vector<string> > board;
        string fileName;
        if (choice == 1)
        {// use minmax algorithm
            cout << "Enter a .txt file containing a 4x4 tic toe board" << endl;
            cin >> fileName;
            ifstream file;
            file.open(fileName);
            while(!file.is_open())
            {
                fileName = getFile(fileName);
                if(fileName == "0")
                    return 0;

                file.open(fileName);
            }
            cout << endl;
            printAndSaveBoard(file, board);
            status = eval(board);
            if(checkStatus(status))
            {   // the game is either won or has an invalid board
                cout << "Provide another board to be solved." << "\n" << endl;
            }
            else
            {
                cout << endl;
                minMax(board);
            }

        }
        else if (choice == 2)
        {// perform alpha-beta pruning
            cout << "Enter a .txt file containing a 4x4 tic toe board" << endl;
            cin >> fileName;
            ifstream file;
            file.open(fileName);
            while(!file.is_open())
            {
                fileName = getFile(fileName);
                if(fileName == "0")
                    return 0;

                file.open(fileName);
            }
            cout << endl;
            printAndSaveBoard(file, board);
            status = eval(board);
            if(checkStatus(status))
            {   // the game is either won or has an invalid board
                cout << "Provide another board to be solved." << "\n" << endl;
            }
            else
            {
                cout << endl;
                alphaBetaPruning(board);
            }
        }
        else if (choice == 3)
        {// exit the program
            cout << "Exiting the program" << endl;
            return 0;
        }
        else
        {// user made an invalid choice
            cout << "Please enter either 1, 2, or 3" << endl;
        }
    }
}