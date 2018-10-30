#include <iostream>
#include <string>
#include <fstream>
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

        string fileName;
        if (choice == 1)
        {// use minmax algorithm
            cout << "Enter a .txt file containing a 4x4 tic toe board" << endl;
            cin >> fileName;
            ifstream file(fileName.c_str());
            while(!file)
            {
                fileName = getFile(fileName);
                if(fileName == "0")
                    return 0;

                ifstream file(fileName.c_str());
            }

        }
        else if (choice == 2)
        {// perform alpha-beta pruning
            cout << "Enter a .txt file containing a 4x4 tic toe board" << endl;
            cin >> fileName;
            ifstream file(fileName.c_str());
            while(!file)
            {
                fileName = getFile(fileName);
                if(fileName == "0")
                    return 0;

                ifstream file(fileName.c_str());
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