#include "mbed.h"
#include "NHD_0216HZ.h"


#include "keypad.h"
#include <string>


//Create keypad
//            c0  c1  c2  c3  r0   r1  r2  r3    
Keypad keypad(D6, D7, D8, D9, D2, D3, D4, D5);


//Create Motor
PwmOut motor(A1);


 int main() 
 {    
    //Setup the lcd
    init_spi();
    init_lcd();


    //Use this to stop bouncing issue
    keypad.enablePullUp();
    //Decalre local variables
    string passwordInput= "";
    char key; //Get input from keypad
    string password = "1234"; //Password
    int count=0; //Keeps track of the # of keys pressed on current attempt


    while(1)
    {  
        //Grab a input from keypad 
        key = keypad.getKey();    
        //If key has been entered on the keypad
        if(key != KEY_RELEASED)
        {
            //Used to avoid multiple keys being read
            wait(0.6);
   
            passwordInput.push_back(key);
            printf("Current Password: %s\n", passwordInput.c_str()); 
            printf("Password length: %d\n\n", passwordInput.length());


            string temp = "";
            char *ptr = &passwordInput[passwordInput.length()-1];


            print_lcd(ptr);
        }
        //When user has entered 4 keys compare it with the password
        if(passwordInput.length()==4)
        {
            if(passwordInput==password)
            {
                //Print to termial success message
                printf("Door Unlocked\n");
                //Display to lcd  success message
                set_cursor(0, 1);
                print_lcd("Valid Password");
                //Unlock the door
                motor.pulsewidth(0.001f);
                wait(5);
                //After 5 seconds lock door
                motor.pulsewidth(0.002f);
                //Clear screen
                init_lcd();
            }
            else
            {
                //Dispaly fail message to terminal
                printf("Door Locked\n");
                //Display fail message to lcd
                set_cursor(0, 1);
                print_lcd("Invalid Password");
                wait(2);
                //After 2 seconds clear screen
                init_lcd();
            }
            //Reset password input
            passwordInput= "";
        }   
    }    
}
