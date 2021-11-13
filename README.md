# LC3 Deassembler for ECE 120.
So you dont have to read binaries and convert it to assembly (let computer do what its good at!). 

Usage: (Hex format)

1283
5105
0ffd
0802
1df7
506f
c080

Output: 

ADD R1, R2, R3
AND R0, R4, R5
BRnzp -3
BRn 2
ADD R6, R7, #-9
AND R0, R1, #15
JMP R2
