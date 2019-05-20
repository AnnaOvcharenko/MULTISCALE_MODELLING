#include "cell.h"

Cell::Cell()
{
    this->state = false;
}

bool Cell::getState()
{
    return this->state;
}

void Cell::setState(bool state)
{
    this->state=state;
}

