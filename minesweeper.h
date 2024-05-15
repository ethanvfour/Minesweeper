#ifndef MINESWEEPER
#define MINESWEEPER

#include <iostream>
#include <cstdlib> // For rand() and srand()
#include <chrono> // for std::chrono
#include <thread> // for std::this_thread::sleep_for
// #include <ctime>
#include <fstream>
#include <iomanip>
#include <random>
#include "position.h"

using namespace std;

class map{
    position ** mappy;
    std::string difficulty;
    int mapX, mapY;
    int bombs, flags;

public:
   


    map()
    {
        mappy == nullptr;
        difficulty = "";
        mapX = 0;
        mapY = 0;
        bombs = 0;
        flags = 0;
        srand((unsigned) time(NULL));
    }

    void setDifficulty(string diff)
    {
        difficulty = diff;

        if(diff == "easy")
        {
            // 5x5
            mapX = 5;
            mapY = 5;
            mappy = new position*[5];
            for(int i = 0 ; i<5; i++)
            {
                mappy[i] = new position[5];
            }
            makeBombs();
            
        }
        else if(diff == "medium")
        {
            // 10 x 10
            mapX = 10;
            mapY = 10;
            mappy = new position*[10];
            for(int i = 0 ; i<10; i++)
            {
                mappy[i] = new position[10];
            }
            makeBombs();
        }
        else if(diff == "hard")
        {
            // 15 x 15
            mapX = 15;
            mapY = 15;
            mappy = new position*[15];
            for(int i = 0 ; i<15; i++)
            {
                mappy[i] = new position[15];
            }
            makeBombs();
        }
        else
        {
            /*
                 ________
                /        \
               |  0    0  |
               |    \/    |
               |  \____/  |
                \________/
                        ...this is not an option ethan...
            */
        }
    }
    /*
        x
       y[][][][]
        [][][][]
        [][][][]
    
    */
   //  int randomNumber = min + rand() % (max - min + 1);

   /*
   // Retrieve a random number between 100 and 200
		// Offset = 100
		// Range = 101
		int random = 100 + (rand() % 101);
   
   */

    void makeBombs()
    {
        if(difficulty == "easy")//5x5
        {
            //5 bombs
            bombs = 0;
            while(bombs < 5){
                for(int i = 0; i < mapY && bombs < 5; i++)
                {
                    for(int j =0 ; j < mapX && bombs < 5; j++)
                    {
                        if((1 + (rand() % 6)) == 1){
                            if(!mappy[i][j].isThisABomb())
                            {
                                mappy[i][j].setBomb();
                                bombs++;
                            }
                        }
                    }
                }
            }
        }
        else if (difficulty == "medium")
        {
            //15 bombs
            bombs = 0;
            while(bombs < 15){
                for(int i = 0; i < mapY && bombs < 15; i++)
                {
                    for(int j =0 ; j < mapX && bombs < 15; j++)
                    {
                        if((1 + (rand() % 6)) == 1){
                            if(!mappy[i][j].isThisABomb())
                            {
                                mappy[i][j].setBomb();
                                bombs++;
                            }
                        }
                    }
                }
            }
        }
        else if(difficulty == "hard"){
            //30 bombs
            bombs = 0;
            while(bombs < 30){
                for(int i = 0; i < mapY && bombs < 30; i++)
                {
                    for(int j =0 ; j < mapX && bombs < 30; j++)
                    {
                        if((1 + (rand() % 6)) == 1){
                            if(!mappy[i][j].isThisABomb())
                            {
                                mappy[i][j].setBomb();
                                bombs++;
                            }
                        }
                    }
                }
            }
        }
        else
        {
            /*
                 _____
               /       \
              |  o   o  |
              |    ∆    |
               \  ___  /
                `-----`
            this wont happen
            */      
        }

        //printMap();//debugging
        setHowManyBombsAround();
    }


    /*
    gonna be a recursive function cuz why not


    ( ͡º ͜ʖ ͡º )
    */
    void setHowManyBombsAround(int x = 0, int y = 0)
    {
        if(((x >= mapX) || x < 0) || ((y >= mapY) || y < 0))// base case,
        {
            return;
        }
        if(!(mappy[y][x].howManyAround() == 0))//no point in checking it again
        {
            return;
        }
        if(mappy[y][x].isChecked())//is true, we checked this already
        {
            return;
        }

        if(!mappy[y][x].isThisABomb())
        {
            mappy[y][x].setHowMany(howManyBombsAroundThisPos(x, y));
        }
        mappy[y][x].checked();

        setHowManyBombsAround(x, y-1);//above
        setHowManyBombsAround(x, y+1);//below
        setHowManyBombsAround(x+1, y);//right 
        setHowManyBombsAround(x-1, y);//left
    }

    int howManyBombsAroundThisPos(int x, int y)
    {
        int bombsReturner = 0;
        for(int i = 0; i < 3; i++)//check row wise
        {
            if(i == 0)//top row
            {
                int tempX = x-1;
                int tempY = y-1;
                for(int m = 0; m < 3; m++)
                {
                    if(!((tempX < 0 || tempX >= mapX) || (tempY < 0 || tempY >= mapY)))// meaning if in range
                    {
                        if(mappy[tempY][tempX].isThisABomb())
                        {
                            bombsReturner++;
                        }
                    }
                    tempX++;         
                }
            }
            else if(i == 1)
            {
                int tempX = x-1;
                for(int m = 0; m < 3; m++)
                {
                    if(!((tempX < 0 || tempX >= mapX) || (y < 0 || y >= mapY)) && m != 1)// meaning if in range
                    {
                        if(mappy[y][tempX].isThisABomb())
                        {
                            bombsReturner++;
                        }
                    }
                    tempX++;
                }
            }
            else
            {
                int tempX = x-1;
                int tempY = y + 1;
                for(int m = 0; m < 3; m++)
                {
                    if(!((tempX < 0 || tempX >= mapX) || (tempY < 0 || tempY >= mapY)))// meaning if in range
                    {
                        if(mappy[tempY][tempX].isThisABomb())
                        {
                            bombsReturner++;
                        }
                    }
                    tempX++;
                }
            }
        }
        return bombsReturner;
    }


    void printMap()
    {
        for(int i = 0; i < mapY + 1; i++)
        {
            for(int j = 0; j < mapX + 1; j++)
            {
                cout<<flush;//debug
                if(i == 0)// top row
                {
                    if(j != 0)
                    {
                        if(j < 10)
                        {
                            cout<<to_string(j)<<"  ";
                        }
                        else
                        {
                            cout<<to_string(j)<<" ";
                        }
                    }
                    else
                    {
                        cout<<"   ";
                    }
                }
                else // not top row
                {
                    if(j == 0)//case for the left side
                    {
                        if(i < 10)
                        {
                            cout<<to_string(i)<<"  ";
                        }
                        else
                        {
                            cout<<to_string(i)<<" ";
                        }

                    }
                    else
                    {
                        /*
                        if(mappy[i-1][j-1].isThisABomb())//debugging
                        {
                            cout<<"X  ";
                        }
                        else
                        {
                            cout<<to_string(mappy[i-1][j-1].howManyAround())<<"  ";
                        }
                        /*
                        else*/ 
                        if(mappy[i-1][j-1].returnFlagStatus())
                        {
                            cout<<"F  ";
                        }
                        else if(mappy[i-1][j-1].isThisDiscovered())
                        {
                            if(mappy[i-1][j-1].howManyAround() == 0)
                            {
                                cout<<(char)0x2e<<"  ";
                            }
                            else
                            {
                                cout<<to_string(mappy[i-1][j-1].howManyAround())<<"  ";
                            }
                        }
                        else
                        {
                            cout<<"#  ";
                        }
                        //*/
                        
                    }
                }
            }
            cout<<endl;
            cout<<"Amount of bombs: "<<to_string(bombs)<<endl;
        }
    }

    string getDiff()
    {
        return difficulty;
    }

private:

    //probably gonna be the worst one, recursively too?
    void userInput(int x, int y, bool firstTime = true)/*if true, this means this the first time
                                                         is so, go check if user picked a bomb, 
                                                         if not, do the minesweeper thing where
                                                         it clears the space and shows the numbers yk?
                                                        */
    {
        bool doRecursion = false;
        if(firstTime)//will no matter what be a good x and y
        {
            /*
                We got three cases for first time
                1 - Its a bomb  :(
                    - Done in the caller
                2 - Its a square with a number
                    a) Make it discovered
                    b) return
                3 - Its a square with a zero
                    a) Make it discovered
                    recusion :)
                    up, top-right, right, bottom right, down, bottom-left, left, top left
            */
            
           if(mappy[y][x].howManyAround() != 0)// case 2
            {
                mappy[y][x].setAsDiscovered();
            }
            else// third case
            {
                doRecursion = true;
            }
        }
        else
        {
            doRecursion = true;
        }

        if(doRecursion)//wont do this if its case 1 or 2
        {
            if(((x >= mapX) || x < 0) || ((y >= mapY) || y < 0))// base case,
            {
                return;
            }
            if(mappy[y][x].isThisDiscovered() || mappy[y][x].returnFlagStatus())//another base case
            {
                return;
            }
            else if(mappy[y][x].howManyAround() != 0)
            {
                mappy[y][x].setAsDiscovered();
                return;
            }

            mappy[y][x].setAsDiscovered();

            userInput(x, y-1, false);//up
            userInput(x+1, y-1, false);//top right
            userInput(x+1, y, false);//right
            userInput(x+1, y+1, false);//bottom right
            userInput(x, y+1, false);//bottom
            userInput(x-1, y+1, false);//bottom left
            userInput(x-1, y, false);//left
            userInput(x-1, y-1, false);//top left
        }
    }

    

public:

    /*
    Will check if user input is good
    Case when it will return 1
        - Good Square thats not discovered
    Case for 2
        - Hit a bomb
    Case for 3
        - Picked a square thats flagged
    Case for 4
        - Picked a square thats already discovered
    
    */
    int callerForUserInput(int x, int y)//the x and y will be decremented already
    {
        if(mappy[y][x].isThisABomb()) // case 2
        {
                /*
                
                if true, show the whole map with all the bombs
                cuz user blew up :(
                Implement it in here

                */

            return 2;
        }
        else if(mappy[y][x].returnFlagStatus())
        {
            return 3;
        } 
        else if(mappy[y][x].isThisDiscovered())
        {
            return 4;
        }
        else
        {
            userInput(x, y);
            return 1;
        }
    }


    /*
        Will return 1 if this square is discovered 

        Returns 0 otherwise
    */
    bool flaggingASquare(int x, int y)//will be decremented already
    {
        if(mappy[y][x].isThisDiscovered())
        {
            return false;
        }
        else
        {
            mappy[y][x].flagIt();
            return true;
        }

    }


    /*
        Checks if the whole map is either flagged or discovered,
        if so, it checks if the amount of bombs == amount of flags
    */
    bool checkIfGameIsDone()
    {
        for(int i = 0; i < mapY; i++)
        {
            for(int j= 0; j < mapX; j++)
            {
                if(!(mappy[i][j].isThisDiscovered() || mappy[i][j].returnFlagStatus()))
                {
                    return false;
                }
            }
        }

        if(bombs >= flags)
        {
            //need to check if these flags are even bombs
            for(int i = 0; i < mapY; i++)
            {
                for(int j= 0; j < mapX; j++)
                {
                    if(mappy[i][j].returnFlagStatus())
                    {
                        if(!mappy[i][j].isThisABomb())
                        {
                            return false;
                        }
                    }
                }
            }

            return true;
        }
        else
        {
            return false;
        }
    }
    
    
    void bombHasBeenPicked()
    {
        for(int i = 0; i < mapY + 1; i++)
        {
            for(int j = 0; j < mapX + 1; j++)
            {
                cout<<flush;//debug
                if(i == 0)// top row
                {
                    if(j != 0)
                    {
                        if(j < 10)
                        {
                            cout<<to_string(j)<<"  ";
                        }
                        else
                        {
                            cout<<to_string(j)<<" ";
                        }
                    }
                    else
                    {
                        cout<<"   ";
                    }
                }
                else // not top row
                {
                    if(j == 0)//case for the left side
                    {
                        if(i < 10)
                        {
                            cout<<to_string(i)<<"  ";
                        }
                        else
                        {
                            cout<<to_string(i)<<" ";
                        }

                    }
                    else
                    {
                        /*
                        if(mappy[i-1][j-1].isThisABomb())//debugging
                        {
                            cout<<"X  ";
                        }
                        else
                        {
                            cout<<to_string(mappy[i-1][j-1].howManyAround())<<"  ";
                        }
                        /*
                        else*/ 
                        if(mappy[i-1][j-1].isThisABomb())
                        {
                            cout<<"B  ";
                        }
                        else if(mappy[i-1][j-1].returnFlagStatus())
                        {
                            cout<<"F  ";
                        }
                        else if(mappy[i-1][j-1].isThisDiscovered())
                        {
                            if(mappy[i-1][j-1].howManyAround() == 0)
                            {
                                cout<<(char)0x2e<<"  ";// .
                            }   
                            else
                            {
                                cout<<to_string(mappy[i-1][j-1].howManyAround())<<"  ";
                            }
                        }
                        else
                        {
                            cout<<"#  ";
                        }
                        //*/
                        
                    }
                }
            }
            cout<<endl;
        }
    }



    ~map()
    {
        if(mappy != nullptr){
            for(int i = 0; i < mapY; i++)
            {
                delete [] mappy[i];
            }
            delete [] mappy;
        }
    }

    int getX()
    {
        return mapX;
    }
    int getY()
    {
        return mapY;
    }

    
};

#endif