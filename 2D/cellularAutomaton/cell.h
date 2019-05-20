#ifndef CELL_H
#define CELL_H


class Cell
{
    bool state;


public:
    Cell();
    bool getState();
    void setState(bool state);
    void operator = (const Cell &C ) {
             state = C.state;

          }
};

#endif // CELL_H
