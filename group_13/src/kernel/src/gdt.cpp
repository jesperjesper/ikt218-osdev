#include "gdt.h"
#include <stdint.h>
#include "system.h"


struct gdt_entry gdt_entries[GDT_ENTRIES];
struct gdt_ptr ptr_gdt;

//This allows us to use the flush function we made in our assembly file
extern "C" {
    extern void gdt_flush(uint32_t);
}
extern "C" {
  extern void reload_segments();
}

void init_gdt() asm ("init_gdt");


// Set the value of one GDT entry.
static void gdt_set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
   gdt_entries[num].base_low    = (base & 0xFFFF);
   gdt_entries[num].base_middle = (base >> 16) & 0xFF;
   gdt_entries[num].base_high   = (base >> 24) & 0xFF;

   gdt_entries[num].limit_low   = (limit & 0xFFFF);
   gdt_entries[num].granularity = (limit >> 16) & 0x0F;

   gdt_entries[num].granularity |= gran & 0xF0;
   gdt_entries[num].access      = access;
} 

//This setups up the gdt and creates entries for the null, code, dataand user mode code/data segments
void init_gdt()
{
    ptr_gdt.limit = sizeof(struct gdt_entry) * GDT_ENTRIES - 1;
    ptr_gdt.base = (uint32_t)&gdt_entries;


    //this sets the value of each segment 
    gdt_set_gate(0, 0, 0, 0, 0);                // Null segment
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment
    gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code segment
    gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode data segment

   
    //uses the function we made in gdt.asm and loads the gdt into memory
    gdt_flush((uint32_t)&ptr_gdt);
    reload_segments();
}