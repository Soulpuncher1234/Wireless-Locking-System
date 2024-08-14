#include "mbed.h"
#include "keypad.h"


using namespace mbed;


Keypad::Keypad(PinName col0, PinName col1, PinName col2, PinName col3,
               PinName row0,PinName row1, PinName row2, PinName row3):
    _cols(col0,col1,col2,col3) ,_rows(row0,row1,row2,row3)    {    }


void Keypad::enablePullUp()
{
    _cols.mode(PullUp);
}


bool Keypad::getKeyPressed()
{
    _rows = 0;              // Ground all keys
    if(_cols.read()==0xff)  //Chk if key is pressed
        return false;


    return true;
}


int Keypad::getKeyIndex()
{
    if (!getKeyPressed())
        return -1;


    //Scan rows and cols and return switch index
    for(int i=0; i<4; i++) {
        _rows = ~(0x01 << i);
        for(int j=0; j<4; j++)
            if (  !( (_cols.read()>> j )& 0x1 ))
                return  j + (i*4);
    }
    return -1;
}


char Keypad::getKey()
{
    int k = getKeyIndex();
    if(k != -1)
        return  keys[k];


    return 0;
}
