# Heap Allocators

A heap allocator is responsible for managing dynamically allocated memory.

```c
char *buf = malloc(100);
```

This asks the program for 100 bytes of usable memory. However, `malloc()` does not directly ask the kernel for exactly 100 bytes each time. Instead, the allocator manages a larger region of memory and splits it into chunks or blocks.

## What the allocator does

The allocator's job is to:

- give programs chunks of memory
- track allocated memory
- reuse freed chunks
- request more memory from the OS when needed

A common misconception is that `malloc()` directly interacts with the OS for every request. In reality, it usually interacts with the allocator, and the allocator requests more memory from the OS through mechanisms such as `brk`, `sbrk`, or `mmap` only when necessary.

## Chunks and metadata

A chunk contains allocator metadata and the user-visible data area. Usually, the pointer returned by `malloc()` points to the user data portion, not necessarily to the beginning of the entire chunk.

## Allocator bookkeeping

When a program calls `free()`, the allocator typically updates the chunk state rather than wiping the memory contents. The bytes may still remain in memory physically, but the program no longer owns that allocation.

This can lead to issues such as use-after-free.

The allocator stores bookkeeping information such as:

- how large the chunk is
- whether it is free or allocated
- what neighboring chunks exist
- where a freed chunk should go
- whether it can be merged with another free chunk

If a memory-corruption bug allows a program to write beyond the intended buffer, the allocator metadata may also be corrupted. This is a fundamental concept in heap exploitation.

## Fragmentation

Fragmentation occurs when a request cannot be satisfied by the available free chunks because they are too small or poorly arranged.

For example, if there are two free chunks of 100 bytes each and the program requests 180 bytes, the allocator cannot satisfy the request without splitting or rearranging memory.

To handle this, allocators usually implement:

- chunk splitting
- chunk merging
- free lists
- grouping by allocation size
- requesting large regions from the OS

## Different allocator implementations

Different systems use different heap allocators. Examples include:

- glibc `malloc` (historically based on ptmalloc)
- jemalloc
- tcmalloc
- musl allocator
- mimalloc
- custom application-specific allocators

These implementations differ internally, and this matters because an exploitation technique may work against one allocator but fail against another. The heap is memory, but the allocator is the subsystem that manages it.
