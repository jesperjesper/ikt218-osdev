//This file, and the contents in it, are mostly based on the code founmd at
//http://www.jamesmolloy.co.uk/tutorial_html/4.-The%20GDT%20and%20IDT.html
//and in the lectures 

#ifndef GDT_H
#define GDT_H

#include <stdint.h>

//Defining the entires
#define GDT_ENTRIES 5


//This defines the structure of the struct
//had to change to uiaint16_t
struct gdt_entry
{
   uint16_t limit_low;           // The lower 16 bits of the limit.
   uint16_t base_low;            // The lower 16 bits of the base.
   uint8_t  base_middle;         // The next 8 bits of the base.          
   uint8_t  access;              // Access flags, determine what ring this segment can be used in.
   uint8_t  granularity;
   uint8_t  base_high;           // The last 8 bits of the base.
} __attribute__((packed));


struct gdt_ptr
{
   uint16_t limit;               // The upper 16 bits of all selector limits.
   uint32_t base;                // The address of the first gdt_entry_t struct.
} __attribute__((packed));

//function
void init_gdt(); 


void set_gdt_entry(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity);


#endif // GDT_H