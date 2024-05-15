#ifndef POSITION_H
#define POSITION_H

class position
{
    int x, y;
    bool isBomb = false;
    bool isDiscovered = false; //meaning, if false, its still decided to be uncovered
                               //if true, its uncovered, if so display either how many bombs around, or if no bombs, just say @ 
    int howManyBombsAroundMe;
    bool alreadyChecked = false; //will turn true when setHowManyBombsAround checks it
    bool isFlagged = false;
public:
    position()
    {
        x = 0;
        y = 0;
        howManyBombsAroundMe = 0;
    }

    position(int x, int y)
    {
        this->x = x;
        this->y = y;
    }

    void setBomb()
    {
        isBomb = true;
    }
    void setAsDiscovered()
    {
        isDiscovered = true;
    }
    bool isThisDiscovered()
    {
        return isDiscovered;
    }
    bool isThisABomb(){
        return isBomb;
    }
    void setHowMany(int bombs)
    {
        howManyBombsAroundMe = bombs;
    }
    int howManyAround()
    {
        return howManyBombsAroundMe;
    }
    void checked()
    {
        alreadyChecked = true;
    }
    bool isChecked()
    {
        return alreadyChecked;
    }
    void flagIt()
    {
        isFlagged = !isFlagged;
    }
    
    bool returnFlagStatus()
    {
        return isFlagged;
    }

};

#endif