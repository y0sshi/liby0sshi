#!/bin/python3

import y0sshi

## open zynq-PL
fpga = y0sshi.pspl("/dev/uio0")

## script
print('###########################')
print('# read  [address]         #')
print('# write [address] [value] #')
print('# exit                    #')
print('###########################')
loop = True
while loop:
    print('>> ', end='')
    stdin :str = input()
    if   stdin.split()[0] == 'exit'  :
        loop  = False
    elif stdin.split()[0] == 'read'  :
        addr  = int(stdin.split()[1])
        value = fpga.read(addr)
        print(hex(value))
    elif stdin.split()[0] == 'write' :
        addr  = int(stdin.split()[1])
        value = int(stdin.split()[2])
        fpga.write(addr, value)
