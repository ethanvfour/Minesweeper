#include <iostream>
#include <cstdlib> // For rand() and srand()
#include <chrono>  // for std::chrono
#include <thread>  // for std::this_thread::sleep_for
// #include <ctime>
#include <fstream>
#include <iomanip>
#include "minesweeper.h"

using namespace std;

/*

normal square looks like O
square thats discovered either has a number, or o

*/

void nop()
{
    // a nop
}

void coolOutput(string wah)
{
    cout << "\033[2J\033[1;1H" << flush;
    for (int i = 0; i < wah.length(); i++)
    {
        cout << wah[i] << flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
    }
}
void coolOutputNoClear(string wah)
{
    for (int i = 0; i < wah.length(); i++)
    {
        cout << wah[i] << flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
    }
}
void oooScaryOutput(string wah)
{
    cout << "\033[2J\033[1;1H" << flush;
    for(int i = 0; i< wah.length();i++)
    {
        cout<<wah[i]<<flush;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

// when you get user input, make sure to minus x and y by one

int main()
{
    map game;
    coolOutput("Welcome to MineSweeper at home!\n");
    std::this_thread::sleep_for(std::chrono::seconds(1));
    int userChoice = -1;
    while (true)
    {
        string temp = "";
        coolOutputNoClear("What difficulty do you want? (case sensitive) \n");
        coolOutputNoClear("1 - Easy\n");
        coolOutputNoClear("2 - Medium\n");
        coolOutputNoClear("3 - Hard\n**");
        getline(cin, temp);
        if (temp.length() == 1)
        {
            if (temp == "1")
            {
                userChoice = stoi(temp);
                break;
            }
            else if (temp == "2")
            {
                userChoice = stoi(temp);
                break;
            }
            else if (temp == "3")
            {
                userChoice = stoi(temp);
                break;
            }
            else
            {
                coolOutput("Not a choice.\n");
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        }
        else
        {
            coolOutput("Not a choice.\n");
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
    string userDiff = "";
    switch (userChoice)
    {
    case 1:
        /* code */
        userDiff = "easy";
        break;
    case 2:
        userDiff = "medium";
        break;

    case 3:
        userDiff = "hard";
        break;
    default:
        break;
    }
    game.setDifficulty(userDiff);

    coolOutput("");
    bool userFailed = false;
    bool gameDone = false;
    while (!gameDone)
    {

        coolOutput("");
        /*
        first ask user if they want to flag a block or pick a block
        forgot all about that
        */
        int userChoice = -1;
        while (true)
        {

            game.printMap();
            coolOutputNoClear("Flag or Pick Square?\n 1             2\n**");
            cin >> userChoice;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(200, '\n');
                coolOutput("Not good input\n");
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
            else if (!(1 == userChoice || userChoice == 2))
            {
                coolOutput("Not good input\n");
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
            else
            {
                break;
            }
        }
        coolOutput("");
        if(userChoice==1){
            int x = -1, y = -1;
            bool userChoiceBad = true;
            while (userChoiceBad)
            {
                while (true)
                {
                    game.printMap();
                    coolOutputNoClear("\nGive Column Number\n**");
                    cin >> x;
                    if (cin.fail())
                    {
                        cin.clear();
                        cin.ignore(200, '\n');
                        coolOutput("Not good input\n");
                        std::this_thread::sleep_for(std::chrono::seconds(1));
                    }
                    else if (x < 0 || x > game.getX())
                    {
                        coolOutput("Not good input\n");
                        std::this_thread::sleep_for(std::chrono::seconds(1));
                    }
                    else
                    {
                        break;
                    }
                }
                while (true)
                {
                    coolOutput("");
                    game.printMap();
                    coolOutputNoClear("\nNow give row number\n**");
                    cin >> y;
                    if (cin.fail())
                    {
                        cin.clear();
                        cin.ignore(200, '\n');
                        coolOutput("Not good input\n");
                        std::this_thread::sleep_for(std::chrono::seconds(1));
                    }
                    else if (y < 0 || y > game.getY())
                    {
                        coolOutput("Not good input\n");
                        std::this_thread::sleep_for(std::chrono::seconds(1));
                    }
                    else
                    {
                        break;
                    }
                }
                if(!game.flaggingASquare(x-1,y-1))
                {
                    coolOutput("Square is already discovered\n");
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                }
                else
                {
                    userChoiceBad = false;
                }
                
            }
        }
        else{ //user wants to pick a square
            int x = -1, y = -1;
            bool userChoiceBad = true;
            while (userChoiceBad)
            {
                while (true)
                {
                    game.printMap();
                    coolOutputNoClear("\nGive Column Number\n**");
                    cin >> x;

                    if (cin.fail())
                    {
                        cin.clear();
                        cin.ignore(200, '\n');
                        coolOutput("Not good input\n");
                        std::this_thread::sleep_for(std::chrono::seconds(1));
                    }
                    else if (x < 0 || x > game.getX())
                    {
                        coolOutput("Not good input\n");
                        std::this_thread::sleep_for(std::chrono::seconds(1));
                    }
                    else
                    {
                        break;
                    }
                }
                while (true)
                {
                    coolOutput("");
                    game.printMap();
                    coolOutputNoClear("\nNow give row number\n**");
                    cin >> y;
                    if (cin.fail())
                    {
                        cin.clear();
                        cin.ignore(200, '\n');
                        coolOutput("Not good input\n");
                        std::this_thread::sleep_for(std::chrono::seconds(1));
                    }
                    else if (y < 0 || y > game.getY())
                    {
                        coolOutput("Not good input\n");
                        std::this_thread::sleep_for(std::chrono::seconds(1));
                    }
                    else
                    {
                        break;
                    }
                }
                int outcomeFromUserInput = game.callerForUserInput(x-1,y-1);
                if(outcomeFromUserInput == 2)
                {
                    userFailed = true;//means bomb blew up :*(
                    gameDone = true;
                    userChoiceBad = false;
                } 
                else if(outcomeFromUserInput == 3)
                {
                    //means user picked a square that was flagged
                    coolOutput("Cannot pick square! Square specified is flagged!\n");
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                }
                else if(outcomeFromUserInput == 4)
                {
                    //means user picked a square that was discovered
                    coolOutput("Cannot pick square! Square specified is discovered!\n");
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                }
                else//meaning 1
                {
                    userChoiceBad = false;
                }
            }
        }
       
        //now we check if game is done

        if(game.checkIfGameIsDone())
        {
            gameDone = true;
        }
        
    }

    if(userFailed)//means user chose a bomb
    {
        oooScaryOutput("uh oh ...\n");
        cout<<"BOOOOOOOOOOOOOOOOOOOOOOOOOOOOOM!\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
        coolOutputNoClear("You have pressed a bomb!\n");
        std::this_thread::sleep_for(std::chrono::seconds(1));
        coolOutputNoClear("Here's the bomb locations.\n");
        game.bombHasBeenPicked();
        std::this_thread::sleep_for(std::chrono::seconds(1));
        coolOutputNoClear("Press enter to exit.");
        string garbage;
        cin.clear();
        cin.ignore(256,'\n');
        getline(cin, garbage);
    }
    else
    {
        coolOutput("WHOA!\n");
        std::this_thread::sleep_for(std::chrono::seconds(1));
        coolOutputNoClear("You actually did it!\n");
        std::this_thread::sleep_for(std::chrono::seconds(1));
        coolOutputNoClear("Great Job\n");
        std::this_thread::sleep_for(std::chrono::seconds(1));
        coolOutputNoClear("Here's the bomb locations.\n");
        game.bombHasBeenPicked();
        std::this_thread::sleep_for(std::chrono::seconds(1));
        coolOutputNoClear("Press enter to exit.");
        string garbage;
        cin.clear();
        cin.ignore(256,'\n');
        getline(cin, garbage);
    }
}
