
#include "system.h"
#include "gdt.h"

// Define entry point in asm to prevent C++ mangling
extern "C"{
    void kernel_main();
}



//This is a fucntion for clearing the terminal screen
//Iterates over the screen coordinates
void clear_screen()
{
    const int screenWidth = 80;
    const int screenHeight = 25;
    const char blankChar = ' ';
    const char attributeByte = 0x07;

    char* vidptr = reinterpret_cast<char*>(0xb8000); // video mem begins here.

    for (int y = 0; y < screenHeight; ++y)
    {
        for (int x = 0; x < screenWidth; ++x)
        {
            const int position = (y * screenWidth + x) * 2;
            vidptr[position] = blankChar;
            vidptr[position + 1] = attributeByte;
        }
    }
}

//this is the function for writing to the terminal
//it calls the clear screen function
void terminal_write(const char* str)
{

    clear_screen();
    char* vidptr = reinterpret_cast<char*>(0xb8000); // video mem begins here.
    const char attributeByte = 0x07;

    int position = 0;

    while (*str != '\0')
    {
        vidptr[position] = *str;
        vidptr[position + 1] = attributeByte;
        ++str;
        position += 2;
    }
}



void kernel_main()
{
    void init_gdt(); 
  
    terminal_write("Hello World!");

    while (1)
    {
    }
}