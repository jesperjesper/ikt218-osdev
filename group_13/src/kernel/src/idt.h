//based on examples from per arne
//and james molley

#ifndef IDT_H
#define IDT_H

#include <stdint.h>
//256 because idt
#define IDT_ENTRIES 256

// //This defines the structure of the struct
//had to change to uiaint16_t
struct idt_entry_t {
  uint16_t base_low;
  uint16_t selector;
  uint8_t zero;
  uint8_t flags;
  uint16_t base_high;
} __attribute__((packed));

//Another struct; this one contains the size and base address of the idt
//pointer
struct idt_ptr_t {
  uint16_t limit;
  uint32_t base;
} __attribute__((packed));


// Initialize the IDT
void init_idt();

//sets the value of a single gate
void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags);

//loads the idt into memory
void idt_load();


#endif  //IDT_H