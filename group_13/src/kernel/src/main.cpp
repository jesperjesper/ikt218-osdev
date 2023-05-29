
#include "system.h"
#include "gdt.h"

// Define entry point in asm to prevent C++ mangling
extern "C"{
    void kernel_main();
}

extern void init_gdt();

void kernel_main()
{


}
