#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <iomanip>
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

void printBoard(ifstream & file)
{
    string line;
    cout << "Turn: Player 1" << endl;
    while(getline(file, line))
    {
        for (int i = 0; i < 4; i++)
        {
            cout << line[i] << " ";
        }
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

void minMax(ifstream & file)
{// minMax algorithm
    float time;
    clock_t t;
    t = clock();
    // algorithm goes here
    t = clock() - t;
    time = (float(t)/CLOCKS_PER_SEC);
    printResults(time);
}

void alphaBetaPruning(ifstream & file)
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
    while(choice != 3)
    {
        cout << "Enter the corresponding number to choose one of the options below: " << endl;
        cout << "1) Minmax" << endl;
        cout << "2) Alpha-beta Pruning" << endl;
        cout << "3) Quit" << endl;

        cin >> choice;
        cout << endl;

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
            printBoard(file);
            cout << endl;
            minMax(file);

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
            printBoard(file);
            cout << endl;
            alphaBetaPruning(file);
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