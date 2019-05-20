#include "grid.h"
#include <iostream>

#include <ctime>
#include <cstdlib>


Grid::Grid(){}

Grid::Grid(int numberOfCellsX, int numberOfCellsY)
{
    this->numberOfCellsX=numberOfCellsX;
    this->numberOfCellsY=numberOfCellsY;
    //this->rule=rule;

    currentGrid = new Cell* [numberOfCellsX];
    for (int i=0;i<numberOfCellsX;++i) {
        currentGrid[i]=new Cell[numberOfCellsY];
    }
}

Grid::~Grid()
{
    //delete [] currentGrid;//if uncomment-doesnt work anything dont know why
}

void Grid::readFromFile(string filename)
{
    int x, y;
        ifstream readfile(filename);
        if (readfile.is_open())
        {
            string fileline, xx, yy;

            while (getline(readfile, fileline))
            {
                stringstream ss(fileline);

                getline(ss, xx, ' ');
                getline(ss, yy, ' ');

                x = stoi(xx);
                y = stoi(yy);
                cout<<x<<" "<<y<<endl;
                currentGrid[x][y].setState(true);
            }
        }
}

void Grid::setGlider()
{
    int startX, startY;
    //startX=((numberOfCellsX-3)/2)-1;
    startX=numberOfCellsX-7;
    startY=((numberOfCellsY-3)/2)-1;

    this->killThemAll();

    currentGrid[startX+1][startY].setState(true);
    currentGrid[startX+2][startY].setState(true);
    currentGrid[startX+1][startY+1].setState(true);
    currentGrid[startX][startY+1].setState(true);
    currentGrid[startX+2][startY+2].setState(true);
}

void Grid::setOscillator()
{
    int startX, startY;
    startX=((numberOfCellsX-1)/2)-1;
    startY=((numberOfCellsY-3)/2)-1;

    this->killThemAll();

    currentGrid[startX][startY].setState(true);
    currentGrid[startX][startY+2].setState(true);
    currentGrid[startX][startY+1].setState(true);
}

void Grid::setInvariable()
{
    int startX, startY;
    startX=((numberOfCellsX-4)/2)-1;
    startY=((numberOfCellsY-3)/2)-1;

    this->killThemAll();

    currentGrid[startX+1][startY].setState(true);
    currentGrid[startX+2][startY].setState(true);
    currentGrid[startX][startY+1].setState(true);
    currentGrid[startX+3][startY+1].setState(true);
    currentGrid[startX+1][startY+2].setState(true);
    currentGrid[startX+2][startY+2].setState(true);
}

void Grid::setRandom()
{
    int numberOfGeneratingCells;
    int x,y;
    if(numberOfCellsX*numberOfCellsY>30)
        numberOfGeneratingCells=15;
    else {
        numberOfGeneratingCells=(numberOfCellsX*numberOfCellsY)/3;
    }

    srand(time(0));
    for (int i=0;i<numberOfGeneratingCells;++i)
    {
        x=(rand() % numberOfCellsX);
        y=(rand() % numberOfCellsY);
        currentGrid[x][y].setState(true);
    }

}

void Grid::Generate()
{
     Cell **tmpGrid = new Cell* [numberOfCellsX];
    for (int i=0;i<numberOfCellsX;++i) {
        tmpGrid[i]=new Cell[numberOfCellsY];
    }

    for (int i=0;i<numberOfCellsX;++i) {
        for (int j=0;j<numberOfCellsY;++j) {
            tmpGrid[i][j]=currentGrid[i][j];
        }
    }

    int aliveNeighbour;

    for (int i=0;i<numberOfCellsX;++i) {
        for (int j=0;j<numberOfCellsY;++j) {
            aliveNeighbour=0;

            if(i==0){
                if(j==0){
                    if(tmpGrid[0][numberOfCellsY-1].getState()) aliveNeighbour++;
                    if(tmpGrid[1][numberOfCellsY-1].getState()) aliveNeighbour++;
                    if(tmpGrid[numberOfCellsX-1][numberOfCellsY-1].getState()) aliveNeighbour++;

                    if(tmpGrid[1][0].getState()) aliveNeighbour++;
                    if(tmpGrid[numberOfCellsX-1][0].getState()) aliveNeighbour++;

                    if(tmpGrid[0][1].getState()) aliveNeighbour++;
                    if(tmpGrid[1][1].getState()) aliveNeighbour++;
                    if(tmpGrid[numberOfCellsX-1][1].getState()) aliveNeighbour++;
                }
                else if(j==(numberOfCellsY-1)) {
                    if(tmpGrid[0][numberOfCellsY-2].getState()) aliveNeighbour++;
                    if(tmpGrid[1][numberOfCellsY-2].getState()) aliveNeighbour++;
                    if(tmpGrid[numberOfCellsX-1][numberOfCellsY-2].getState()) aliveNeighbour++;

                    if(tmpGrid[1][numberOfCellsY-1].getState()) aliveNeighbour++;
                    if(tmpGrid[numberOfCellsX-1][numberOfCellsY-1].getState()) aliveNeighbour++;

                    if(tmpGrid[0][0].getState()) aliveNeighbour++;
                    if(tmpGrid[1][0].getState()) aliveNeighbour++;
                    if(tmpGrid[numberOfCellsX-1][0].getState()) aliveNeighbour++;

                }
                else {
                    if(tmpGrid[i][j+1].getState()) aliveNeighbour++;
                    if(tmpGrid[i+1][j+1].getState()) aliveNeighbour++;
                    if(tmpGrid[numberOfCellsX-1][j+1].getState()) aliveNeighbour++;

                    if(tmpGrid[i+1][j].getState()) aliveNeighbour++;
                    if(tmpGrid[numberOfCellsX-1][j].getState()) aliveNeighbour++;

                    if(tmpGrid[i][j-1].getState()) aliveNeighbour++;
                    if(tmpGrid[i+1][j-1].getState()) aliveNeighbour++;
                    if(tmpGrid[numberOfCellsX-1][j-1].getState()) aliveNeighbour++;

                }

            }
            else if (i==(numberOfCellsX-1)) {
                if(j==0){
                    if(tmpGrid[0][numberOfCellsY-1].getState()) aliveNeighbour++;
                    if(tmpGrid[numberOfCellsX-2][numberOfCellsY-1].getState()) aliveNeighbour++;
                    if(tmpGrid[numberOfCellsX-1][numberOfCellsY-1].getState()) aliveNeighbour++;

                    if(tmpGrid[0][0].getState()) aliveNeighbour++;
                    if(tmpGrid[numberOfCellsX-2][0].getState()) aliveNeighbour++;

                    if(tmpGrid[0][1].getState()) aliveNeighbour++;
                    if(tmpGrid[numberOfCellsX-2][1].getState()) aliveNeighbour++;
                    if(tmpGrid[numberOfCellsX-1][1].getState()) aliveNeighbour++;

                }
                else if(j==(numberOfCellsY-1)) {
                    if(tmpGrid[0][numberOfCellsY-2].getState()) aliveNeighbour++;
                    if(tmpGrid[numberOfCellsX-2][numberOfCellsY-2].getState()) aliveNeighbour++;
                    if(tmpGrid[numberOfCellsX-1][numberOfCellsY-2].getState()) aliveNeighbour++;

                    if(tmpGrid[0][numberOfCellsY-1].getState()) aliveNeighbour++;
                    if(tmpGrid[numberOfCellsX-2][numberOfCellsY-1].getState()) aliveNeighbour++;

                    if(tmpGrid[0][0].getState()) aliveNeighbour++;
                    if(tmpGrid[numberOfCellsX-2][0].getState()) aliveNeighbour++;
                    if(tmpGrid[numberOfCellsX-1][0].getState()) aliveNeighbour++;

                }
                else {
                    if(tmpGrid[i][j-1].getState()) aliveNeighbour++;
                    if(tmpGrid[i-1][j-1].getState()) aliveNeighbour++;
                    if(tmpGrid[0][j-1].getState()) aliveNeighbour++;

                    if(tmpGrid[0][j].getState()) aliveNeighbour++;
                    if(tmpGrid[i-1][j].getState()) aliveNeighbour++;

                    if(tmpGrid[0][j+1].getState()) aliveNeighbour++;
                    if(tmpGrid[i][j+1].getState()) aliveNeighbour++;
                    if(tmpGrid[i-1][j+1].getState()) aliveNeighbour++;

                }
            }
            else if (j==0) {
                if(tmpGrid[i][numberOfCellsY-1].getState()) aliveNeighbour++;
                if(tmpGrid[i-1][numberOfCellsY-1].getState()) aliveNeighbour++;
                if(tmpGrid[i+1][numberOfCellsY-1].getState()) aliveNeighbour++;

                if(tmpGrid[i+1][0].getState()) aliveNeighbour++;
                if(tmpGrid[i-1][0].getState()) aliveNeighbour++;

                if(tmpGrid[i+1][1].getState()) aliveNeighbour++;
                if(tmpGrid[i][1].getState()) aliveNeighbour++;
                if(tmpGrid[i-1][1].getState()) aliveNeighbour++;

            }
            else if (j==(numberOfCellsY-1)) {
                if(tmpGrid[i][numberOfCellsY-2].getState()) aliveNeighbour++;
                if(tmpGrid[i-1][numberOfCellsY-2].getState()) aliveNeighbour++;
                if(tmpGrid[i+1][numberOfCellsY-2].getState()) aliveNeighbour++;

                if(tmpGrid[i+1][j].getState()) aliveNeighbour++;
                if(tmpGrid[i-1][j].getState()) aliveNeighbour++;

                if(tmpGrid[i+1][0].getState()) aliveNeighbour++;
                if(tmpGrid[i][0].getState()) aliveNeighbour++;
                if(tmpGrid[i-1][0].getState()) aliveNeighbour++;

            }
            else {
                if(tmpGrid[i][j-1].getState()) aliveNeighbour++;
                if(tmpGrid[i-1][j-1].getState()) aliveNeighbour++;
                if(tmpGrid[i+1][j-1].getState()) aliveNeighbour++;

                if(tmpGrid[i+1][j].getState()) aliveNeighbour++;
                if(tmpGrid[i-1][j].getState()) aliveNeighbour++;

                if(tmpGrid[i+1][j+1].getState()) aliveNeighbour++;
                if(tmpGrid[i][j+1].getState()) aliveNeighbour++;
                if(tmpGrid[i-1][j+1].getState()) aliveNeighbour++;
            }



            if (!tmpGrid[i][j].getState()){
                if(aliveNeighbour==3){
                    currentGrid[i][j].setState(true);
                }
            }
            else{
                if((aliveNeighbour<2)||(aliveNeighbour>3))
                    currentGrid[i][j].setState(false);
            }


        }
    }
     cout<<"generating"<<endl;

}

void Grid::killThemAll()
{
    for (int i=0;i<numberOfCellsX;++i) {
        for (int j=0;j<numberOfCellsY;++j) {
            currentGrid[i][j].setState(false);
        }
    }
}

bool Grid::charToBool(char c)
{
    if(c=='0')
        return false;
    else
        return true;
}

string Grid::neighboursToString(bool left, bool current, bool right)
{
    string result;
    result=btostr(left)+btostr(current)+btostr(right);
    return result;
}

string Grid::btostr(bool a)
{
    return a ? "1" : "0";
}


