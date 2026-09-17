A heap allocator is the component responsible for managing dynamically allocated memory.
```
	//C
	char *buf = malloc(100)
```
The program asks for 100 bytes of dynamically usable memory.
`malloc()` does not manually ask the kernel for exactly 100 bytes every time. Instead , the allocator manages a larger region of memory and divides it into pieces called chunks/blocks.
The allocators job essentially is to :
(i) Give programs chunks of memory
(ii) Keep track of the allocated memory
(iii) Reuse freed chunks
(iv) Obtain more memory from the OS when necessary
A common misconception is that malloc() interacts with the OS directly which is not true it does that through the allocator and it interacts with the OS only when more memory is needed through mechanisms such as `brk` , `sbrk` and `nmap`
A chunk is made up of the allocator metadata and the user data and typically the pointer for the malloc function typically points to the user-data portion , not necessarily the beginning of the entire allocator chunk
### Allocator Metadata
When using `free()` the allocator simply changes the state of the chunk and the memory may still physically contatin old bytes but the program no longer owns that allocation. That is a use-after-free.
The allocator needs bookkeeping information such as:
(i) How large is a chunk?
(ii) Is it free?
(iii) What other chunks are around it?
(iv) Where should this freed chunk go?
(v) Can it be merged with another free chunk?
When a program has a memory corruption ug htat allows writing beyound the intended buffer then you can potentially corrupt allocator  bookkeeping. A foundation of heap exploitation
### Fragmentation
It is when a program memory request cannot be satisfied by either of two individual chucks because neither is large enough. 
Given two chunks each 100 bytes and the program requests 180 bytes - this cause external fragmentation,
To overcome this the allocators implement the following strategies:
(i) Splitting chunks
(ii) Merging chunks
(iii) Maintaining free lists - a free list is simply a linked list of free chunks
(iv) Grouping similarly sized allocations
(v) Requesting large regions from the OS

There are diffirent kinds of allocators that vary from one system to another. They include:
(i) glibc's malloc - for Linux historically associated with ptmalloc
(ii) jemalloc
(iii) tcmalloc
(iv) musl's allocator
(v) mimalloc
(vi) custom application allocators
They all have different internal designds and this matters because a heap exploitation technique depends heavily on the allocator implementation and version since one technique can work on one and fail on the other
The heap is memory and the allocator is the system that manages that memory.
