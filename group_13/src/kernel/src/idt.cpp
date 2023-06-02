#include "idt.h"
#include <stdint.h>
#include "system.h"

extern "C" {
    extern void idt_flush(uint32_t);
}

struct idt_entry_t idt_entries[IDT_ENTRIES];
struct idt_ptr_t ptr_idt;


void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags)
{
   idt_entries[num].base_low = base & 0xFFFF;
   idt_entries[num].base_high = (base >> 16) & 0xFFFF;

   idt_entries[num].selector     = sel;
   idt_entries[num].zero = 0;
   idt_entries[num].flags   = flags /* | 0x60 */;
}

void init_idt() {
    //limits the idt value.
    ptr_idt.limit = sizeof(struct idt_entry_t) * IDT_ENTRIES - 1;    
    
    // IDT base address
    ptr_idt.base = (uint32_t)&idt_entries;

   for (int i = 0; i < 256; i++) {
        idt_entries[i].base_low = 0;
        idt_entries[i].base_high = 0;
        idt_entries[i].selector = 0;
        idt_entries[i].zero = 0;
        idt_entries[i].flags = 0;
    }
  //load the idt using the assembly function
  idt_flush((uint32_t)&ptr_idt);

  
}

void idt_load() {
  // lidt
  asm volatile("lidt %0" : : "m" (ptr_idt));

}