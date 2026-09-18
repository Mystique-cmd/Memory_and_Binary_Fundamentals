# ELF and PE Formats

Executable file formats define how compiled code is represented so an operating system can load, map, link, and execute it. Two of the most important formats are ELF and PE.

- ELF is used primarily on Linux and other Unix-like systems.
- PE is used primarily on Windows.

## ELF (Executable and Linkable Format)

ELF is common in:

- BSD
- Linux
- Unix-like systems
- Embedded systems
- Android

An ELF file is structured in a way that supports both linking and execution.

### High-level ELF layout

An ELF file typically contains:

- ELF header
- Program header table
- Sections
- Section header table

Common sections include:

- `.text` - executable machine code
- `.rodata` - read-only data
- `.data` - initialized writable global/static data
- `.bss` - uninitialized or zero-initialized global/static data
- `.symtab` - symbol table
- `.strtab` - string table

### Two views of an ELF file

There are two important ways of interpreting an ELF file:

1. Linking view
   - Used by compilers, linkers, debuggers, and binary-analysis tools.
   - Focuses on sections.

2. Execution view
   - Used by the OS loader.
   - Focuses on segments and memory mapping.

### ELF header

The ELF header contains metadata about the file, such as:

- magic number
- architecture
- 32-bit vs 64-bit
- endianness
- entry point
- program header location
- section header location
- number of sections
- number of program headers

It is inspected using:

```bash
readelf -h program
```

You can also inspect the file header bytes at the beginning of the binary with commands such as:

```bash
xxd program | head
```

## Sections vs Segments

Sections describe the file from the perspective of the compiler, linker, and tools.

Segments describe what the OS loader needs to map into memory. Permissions such as read, write, and execute are critical at this stage.

## ELF program headers

Program headers are inspected using:

```bash
readelf -l program
```

Common program header types include:

- `LOAD`
- `INTERP`
- `DYNAMIC`
- `GNU_STACK`
- `GNU_RELRO`

## ELF entry point

The entry point is not the same as `main()`. The CPU starts execution at the ELF entry point, which typically jumps into startup code such as:

```text
ELF entry -> _start -> runtime initialization -> __libc_start_main -> main()
```

The CPU does not know what `main` is; `main` is simply a C abstraction.

## Dynamic linking

Modern Linux programs usually depend on shared libraries. ELF stores the metadata needed for these dependencies.

Useful commands include:

```bash
ldd program
readelf -d program
```

Important concepts include:

- `DT_NEEDED`
- `PLT`
- `GOT`
- `.dynamic`

These are essential in binary exploitation and reverse engineering.

## PE (Portable Executable)

PE is the native executable format used on Windows. It is used for files such as:

- `.exe`
- `.dll`
- `.sys`

PE files traditionally begin with a DOS header signature `MZ` (`4D 5A` in hex). This is checked using a command similar to the ELF case.

```bash
xxd program.exe | head
```

This DOS header contains a pointer to the PE header.

## PE signature

The PE signature is:

```text
PE\0\0
```

It is located at the file offset indicated by the `e_lfanew` field.

## PE optional header

Although called optional, this header is extremely important for executable images. It contains metadata such as:

- entry point
- image base
- section alignment
- file alignment
- image size
- subsystem
- DLL characteristics
- data directories

The actual entry address is conceptually:

```text
Image Base + Address of Entry Point
```

## PE sections

Common PE sections include:

- `.text` - executable code
- `.rdata` - read-only data such as strings and constants
- `.data` - writable initialized data
- `.rsrc` - resources like icons, dialogs, and version information
- `.reloc` - relocation information

This matters when the executable is not loaded at its preferred address.

## PE data directories

PE data directories point to structures such as:

- Export table
- Import table
- Resource table
- Exception table
- Certificate table
- Base relocation table
- Debug information
- TLS information

## PE imports

When a Windows program calls a function such as `CreateFile()`, the actual implementation may live in a DLL rather than inside the executable itself. The PE contains import information describing these dependencies.

This is analogous to ELF dynamic linking.

## PE exports

DLLs can expose functions for use by other programs. Those functions can then be imported by another module.

## Practical investigation with `hello`

Using the code in `hello.c`, investigate the binary with the following commands:

```bash
file hello
readelf -h hello
readelf -S hello
readelf -l hello
readelf -d hello
readelf -s hello
objdump -d hello
```

The goal is not to understand every line, but to answer the following:

- What architecture is the binary?
- What is the entry point?
- Where is `.text`?
- Where is `.data`?
- Which regions are executable?
- What shared libraries does it depend on?
- What is the relationship between the file layout and the process memory layout?


























