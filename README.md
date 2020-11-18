# PageTable--virtual-memory-DEMO
Demo of paging. attitude of OS as so to map VPN(virtual page address)  to PPN(physical page address).


The goal in this assignment is to implement simulated OS code that handles a multi-level (trie-based)
page table. You will implement two functions. The  rst function creates/destroys virtual memory
mappings in a page table. The second function checks if an address is mapped in a page table. (The
second function is needed if the OS wants to  gure out which physical address a process virtual
address maps to.)
Your code will be a simulation because it will run in a normal process. We provide two files,
os.c and os.h, which contain helper functions that simulate some OS functionality that your code
will need to call. For your convenience, there's also a main() function demonstrating usage of the
code. However, the provided main() only exercises your code in trivial ways. We recommend that
you change it to thoroughly test the functions that you implemented.
1.1 Target hardware
Our simulated OS targets an imaginary 64-bit x86-like CPU. When talking about addresses (virtual
or physical), we refer to the least signi cant bit as bit 0 and to the most signicant bit as bit 63.
Virtual addresses The virtual address size of our hardware is 64 bits, of which only the lower
57 bits are used for translation. The top 7 bits are guaranteed to be identical to bit 56, i.e., they
are either all ones or all zeroes. 

Page table structure The page/frame size is 4KB (4096 bytes). Page table nodes occupy a
physical page frame, i.e., they are 4KB in size. The size of a page table entry is 64 bits. Bit 0 is the
valid bit. Bits 1{11 are unused and must be set to zero. (This means that our target CPU does
not implement page access rights.) The top 52 bits contain the page frame number that this entry
points to. The following depicts the PTE format:

Number of page table levels To successfully complete the assignment, you must answer to
yourself: how many levels are there in our target machine's multi-level page table? As mentioned,
assume that only the lowest 57 bits of the virtual address are used for translation.
1.2 OS physical memory manager
To write code that manipulates page tables, you need to be able to perform the following: (1) obtain
the page number of an unused physical page, which marks it as used; and (2) obtain the kernel
virtual address of a given physical address. The provided os.c contains functions simulating this
functionality:
1. Use the following function to allocate a physical page (also called page frame):
uint64 t alloc page frame(void);
This function returns the physical page number of the allocated page. In this assignment, you
do not need to free physical pages. If alloc page frame() is unable to allocate a physical page,
it will exit the program. The content of the allocated page frame is all zeroes.
2. Use the following function to obtain a pointer (i.e., virtual address) to a physical address:
void* phys to virt(uint64 t phys addr);
The valid inputs to phys to virt() are addresses that reside in physical pages that were
previously returned by alloc page frame(). If it is called with an invalid input, it returns
NULL.


---------------------------------------------------------------------------------
###### do you have some comments, negative or positive review? I would like to hear you: shirawein70@gmail.com
