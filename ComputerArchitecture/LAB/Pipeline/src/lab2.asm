Begin:
    # Reg[1-5]: Used to record data
0x00    addi	x1,     x0,     123 		# x1 = 123  Data
0x04    addi	x2,     x1,     111 		# x2 = 234  Data
0x08    addi	x3,     x2,     111 		# x3 = 345  Data
0x0c    addi	x4,     x3,     111 		# x4 = 456  Data
0x10    addi	x5,     x4,     111 		# x5 = 567  Data
    # Reg[6-10]: Used to store test address
0x14    addi	x6,     x0,     0x0 		
0x18    addi	x7,     x0,     0x4 		
0x1c    addi	x8,     x0,     0x94 		
0x20    addi	x9,     x0,     0x98
0x24    addi	x10,    x0,     0x404
    # Reg[20]: Used to record score
0x28    addi	x20,    x0,     0			# x20 = 0   
Test_Hit:
0x2c    sw		x1,     0(x6)		        # &(0x0) = 123
0x30    sw		x2,     0(x7)		        # &(0x4) = 234
0x34    lw		x11,    0(x6)		        # x11 = 123
0x38    sw		x3,     0(x8)		        # &(0x94) = 345
0x3c    sw		x4,     0(x9)		        # &(0x98) = 456
0x40    lw		x13,    0(x8)		        # x13 = 345
0x44    lw		x12,    0(x7)		        # x12 = 234
0x48    lw		x14,    0(x9)		        # x14 = 456
0x4c    sub		x11,    x11,    x13		    # x11 = x11 - x13 = -222
0x50    sub		x12,    x12,    x14		    # x12 = x12 - x14 = -222
0x54    bne		x11,    x12,    Test_Replacement    # if Not Equal: Skip x20++
0x58    addi	x20,    x20,    1			# x20++
Test_Replacement:
0x5c    sw		x5,     0(x10)		        # &(0x404) = 567
0x60    lw      x11,    0(x7)               # x11 = &(0x4) = 234
0x64    lw      x12,    0(x10)              # x12 = &(0x404) = 567
0x68    addi    x11,    x11,    333         # x11 = x11 + 333 = 567     
0x6c    bne		x11,    x12,    Test_Dirty_Block    # if Not Equal: Skip x20++
0x70    addi	x20,    x20,    1			# x20++
Test_Dirty_Block:
0x74    lw      x11,    0(x6)               # x11 = &(0x0) = 123
0x78    lw      x12,    0(x10)              # x12 = &(0x404) = 567
0x7c    addi	x11,    x11,    444		    # x11 = x11 + 444 = 567
0x80    bne		x11,    x12,    End          # if Not Equal: Skip x20++
0x84    addi	x20,    x20,    1			# x20++
End:
    #------------Useless Loop-----------------
0x88    addi	x21,    x0,     3			
0x8c    bne		x21,    x20,    End	
    #------------Useless Loop-----------------