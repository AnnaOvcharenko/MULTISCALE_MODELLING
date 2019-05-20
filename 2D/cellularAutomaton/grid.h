#ifndef GRID_H
#define GRID_H

#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <bitset>
#include <QPainter>
#include "cell.h"

using namespace std;

class Grid
{
public:
    int numberOfCellsX;
    int numberOfCellsY;
    Cell ** currentGrid ;
    //int rule;

public:
    Grid();
    Grid(int numberOfCellsX, int numberOfCellsY);
    ~Grid();


    //static void printGrid(QPainter painter);
    void Generate();
    void killThemAll();
    void readFromFile(string filename);
    void setGlider();
    void setOscillator();
    void setInvariable();
    void setRandom();





    static bool charToBool(char c);
    static string neighboursToString(bool left, bool current, bool right);
    static string btostr(bool a);

};

#endif // GRID_H
