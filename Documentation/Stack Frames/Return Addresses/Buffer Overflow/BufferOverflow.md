# Buffer Overflow

A buffer overflow occurs when a program writes more data into a buffer than the buffer was designed to hold. Because buffers often live within stack frames, overflowing them can overwrite adjacent memory, including:

- saved registers
- local variables
- the return address
- nearby stack metadata

## How it works

1. A program has an object with a defined capacity.
2. A bug allows a write to exceed that object's bounds.
3. The out-of-bounds write may corrupt adjacent data; the result depends on the program, compiler, and runtime layout.
4. A crash or corrupted value does not by itself demonstrate control of a return address.

## Practical example

The example in [overflowvuln.c](overflowvuln.c) uses a bounded input operation and an oversized backing array to demonstrate changes across a logical field boundary. It deliberately keeps writes inside the C array and does not overwrite a saved return address:

```bash
gcc -g -O0 -Wall -Wextra overflowvuln.c -o vuln
```

Run the bounded example normally, or inspect its array in GDB:

```gdb
break overflowvuln.c:19
run
next
x/24cb state->arena
```

When the program prompts, enter 16 `A` characters followed by four `B` characters. `next` executes the bounded input call; the memory examination then shows the marker change. The input width is intentionally capped so the write stays inside the backing array; it is not a saved-return-address overwrite exercise.

## Why `gets()` is dangerous

`gets()` reads until newline or EOF without a size limit and was removed from the C standard library specification in C11. Its declaration may be absent from modern headers, and choosing an older language mode is not a safe or portable fix. Do not use it in new code.

Use a bounded interface and check its result and any truncation behavior. For example:

### Use `fgets()` instead

```c
char buf[128];
fgets(buf, sizeof(buf), stdin);
```

`fgets()` reads at most `sizeof(buf) - 1` bytes and NUL-terminates on success. Callers should still handle errors and decide how to deal with a line that did not fit.

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

This can write past the destination array if the input exceeds its capacity.

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

Prefer APIs that take the destination capacity, such as `snprintf()` for formatted strings. `strncpy()` may leave the destination unterminated when truncated, and `strlcpy()` is not available on every platform; either requires deliberate return-value and termination handling.

### `strcat()`

```c
strcat(dest, src);
```

This appends source data without checking whether the destination still has space left.

Prefer an operation that tracks the remaining destination capacity. `strncat()` and `strlcat()` have distinct semantics, and `strlcat()` is not portable to every platform; do not treat either name alone as proof of safety.

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
