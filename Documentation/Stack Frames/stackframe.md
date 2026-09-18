# Stack Frames

A stack frame, also known as an activation record, is a block of memory on the call stack used to store information about a single function call while it is executing.

## What a stack frame contains

A typical stack frame stores:

- function parameters (arguments)
- local variables
- the return address, which tells the program where to resume execution after the function returns
- saved registers
- the previous frame pointer, used to restore the caller's stack frame

## Lifecycle of a function call

When a function is called:

1. A new stack frame is pushed onto the call stack.
2. The function executes using its own local variables and parameters.
3. When the function finishes, its frame is popped off the stack.
4. Control returns to the caller using the stored return address.

## Why stack frames matter

Stack frames are essential because they:

- allow nested function calls and recursion
- isolate local variables between different function calls
- preserve the correct return location after a function completes
- help debuggers generate stack traces showing call flow

Understanding stack frames is crucial when analyzing crashes, reverse engineering binaries, and exploiting memory-corruption bugs.
