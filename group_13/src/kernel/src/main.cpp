
#include "system.h"
#include "gdt.h"
// Define entry point in asm to prevent C++ mangling
extern "C"{
    void kernel_main();
}

void kernel_main()
{

}
