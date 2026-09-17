A stack frame is also known as an activation record.
It is a block of memory on the call stack that stores information about a single function call while it is executing.
A typical stack frame stores:
i) Function parameters ( arguments )
ii) Local variables
iii) Return addresses - where execution continues after the function returns
iv) Saved registers
v) Previous Frame pointer - used to restore the callers stack frame
When a function is called:
(i) A new stack frame is pushed onto the call stack
(ii) The function executes using its own local variables and parameters
(iii) When the function finishes, it stack frame is popped off the stack
(iv) Control returns to the caller using the stored return address
The stack frames are important because:
(i) They allow function calls to be nested ( recursion )
(ii) They keep local variables isolated between function calls
(iii) They enable the program to return the correct location after function completes
(iv) They help debuggers produce stack traces showing the sequence of function calls
