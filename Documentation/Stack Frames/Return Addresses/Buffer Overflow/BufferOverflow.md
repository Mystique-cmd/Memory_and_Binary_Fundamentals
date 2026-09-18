# Buffer Overflow

A buffer overflow occurs when a program writes more data into a buffer than the buffer was designed to hold. Because buffers often live within stack frames, overflowing them can overwrite adjacent memory, including:

- saved registers
- local variables
- the return address
- nearby stack metadata

## How it works

1. A function declares a local buffer such as `char buf[16];`.
2. User input is read without proper bounds checking, for example with `gets(buf)`.
3. The attacker supplies more than the buffer can hold.
4. The excess data spills past the buffer and begins overwriting nearby stack content.
5. When the function returns, the CPU uses the corrupted return address and jumps to an attacker-controlled location.

## Practical example

Compile the vulnerable example with protections disabled:

```bash
gcc -O0 -fno-stack-protector -std=gnu89 overflowvuln.c -o vuln
```

Then run it under GDB:

```gdb
break vuln
run
x/32gx $rsp
```

This allows you to inspect how the stack changes before and after the overflow is triggered.

![](./images/image1.png)
![](./images/image2.png)
![](./images/image3.png)
![](./images/image4.png)

## Why `gets()` is dangerous

Modern compilers reject `gets()` because it is inherently unsafe. It reads an unbounded number of bytes until a newline or EOF, which makes it a classic source of stack overflows.

To practice these techniques safely, a few common workarounds are used:

### Use `fgets()` instead

```c
char buf[128];
fgets(buf, sizeof(buf), stdin);
```

This is safer because it reads only up to `n-1` characters and null-terminates the buffer.

### Force legacy C mode

```bash
gcc -O0 -fno-stack-protector -std=gnu89 overflowvuln.c -o vuln
```

This allows older examples to compile on modern systems.

### Manually declare `gets()`

```c
char *gets(char *buf);
```

This is a compatibility workaround, not a recommended practice.

## Common unsafe functions

### `gets()`

- reads unlimited input
- no bound checks
- replaced by `fgets()`

### `scanf()`

Unsafe when used without width limits:

```c
scanf("%s", buf);
```

This can overwrite adjacent memory if the input exceeds the buffer size.

Safe patterns include:

```c
scanf("%63s", buf);
```

or prefer:

- `fgets()`
- `strtol()`
- `strtod()`
- `sscanf()` with controlled widths

### `strcpy()`

```c
strcpy(dest, src);
```

This copies until a null terminator is reached and performs no bounds checks.

Safer alternatives:

- `strncpy()`
- `strlcpy()`

### `strcat()`

```c
strcat(dest, src);
```

This appends source data without checking whether the destination still has space left.

Safer alternatives:

- `strncat()`
- `strlcat()`

### `sprintf()`

```c
sprintf(buf, format, ...);
```

This writes formatted output to a target buffer with no size limit.

Safe alternative:

```c
snprintf(buf, sizeof(buf), format, ...);
```

### `sscanf()`

This is safer than `scanf()` when reading from strings, but still risky without proper width control or format validation.

### `tmpnam()` and `mktemp()`

These create predictable temporary names and can be abused in race-condition attacks.

Example:

```c
char *name = tmpnam(NULL);
FILE *f = fopen(name, "w");
```

This is a classic TOCTOU issue.

Safe alternative:

- `mkstemp()`

### `system()`

```c
system(cmd);
```

This executes a shell command using the running process's privileges. If untrusted input reaches it, command injection becomes possible.

Safe alternatives:

- `execve()`
- `fork()` + `execvp()`
- avoid invoking a shell when possible

## Summary

Buffer overflow vulnerabilities arise when unchecked input is copied into a fixed-size buffer. The result is memory corruption, often leading to crashes, invalid control flow, or full code execution if the corruption reaches control data such as the saved return address.
