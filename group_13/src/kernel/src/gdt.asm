; Like the gdt.h file, this one is copy paste.

[GLOBAL gdt_flush]   

gdt_flush:
   mov eax, [esp+4]  
   lgdt [eax]        

   mov ax, 0x10     
   mov ds, ax        
   mov es, ax
   mov fs, ax
   mov gs, ax
   mov ss, ax
   jmp 0x08:.flush   
.flush:
   ret

[global reload_segments]    
reload_segments:
   JMP   0x08:.reload_CS 
.reload_CS:
   ; Reload data segment registers:
    mov ax, 0x10     
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
   RET