#include <stdio.h>
#include <ctype.h>

#define PROG_SIZE (1 << 16)
#define MEM_SIZE (1 << 16)

int main() {
    char prog[PROG_SIZE];
    // Equal to 2 to the power of 16
    {
        int ch = 42;
        int i = 0;
        while (ch != EOF && i < PROG_SIZE) {
            ch = getchar();
            prog[i] = ch;
            i++;
        }
    }

    int pc = 0;
    unsigned int mem[MEM_SIZE];
    unsigned int reg[26];
    unsigned int jumps[26];

    while(pc < 1500) {
            if (prog[pc] == '+') {
                reg[prog[pc + 2] - 97] += reg[prog[pc + 1] - 97];
                pc += 3;
            }

            else if (prog[pc] == '-') {
                reg[prog[pc + 2] - 97] -= reg[prog[pc + 1] - 97];
                pc += 3;
            }

            else if (prog[pc] == '*') {
                reg[prog[pc + 2] - 97] *= reg[prog[pc + 1] - 97];
                pc += 3;
            }

            else if (prog[pc] == '/') {
                reg[prog[pc + 2] - 97] /= reg[prog[pc + 1] - 97];
                pc += 3;
            }

            else if (prog[pc] == ':') {
                jumps[prog[pc + 1] - 64] = pc;
                pc += 2;
            }

            else if (prog[pc] == '@') {
                pc = jumps[prog[pc + 1] - 64];
            }

            else if (prog[pc] == 'x') {
                unsigned int tv = 0;
                int read = 2;
                for(int i=0; i<8; i++) {
                    char ch = prog[pc + 2 + i];
                    read += 1;
                    if (isdigit(ch)) {
                        tv = (tv * 16) + (ch-48);
                    } else if (ch >= 'A' & ch <= 'F') {
                        tv = (tv * 16) + (ch-55);
                    } else { 
                        break;
                    }
                }
                if (islower(prog[pc + 1])) {
                    reg[prog[pc + 1] - 97] = tv;
                }
                pc += read-1;
            }

            else if (prog[pc] == '<' || prog[pc] == '>') {
                int regnum = prog[pc + 1]-97;
                int addr = 0;
                for(int i=3; i>=0; i--) {
                    char ch = prog[pc + 5 - i];
                    if (isdigit(ch)) {
                        addr += (ch-48) * (1 << i*4);
                    } else if ((ch) >= 'A' & ch <= 'F') {
                        addr += (ch-55) * (1 << i*4);
                    }
                }
                if (prog[pc] == '<') {
                    mem[addr] = reg[regnum];
                } else {
                    reg[regnum] = mem[addr];
                }
                pc += 5;
            }

            else if (prog[pc] == '?') {
                int val1 = reg[prog[pc + 1] - 97];
                int val2 = reg[prog[pc + 3] - 97];
                
                char comp = prog[pc + 2];


                if (comp == '=') {
                    if (val1 == val2) {
                        pc = jumps[prog[pc + 4] - 64];
                    } else {
                        pc += 5;
                    }
                }

                if (comp == '>') {
                    if (val1 > val2) {
                        pc = jumps[prog[pc + 4] - 64];
                    } else {
                        pc += 5;
                    }
                }

                if (comp == '<') {
                    if (val1 < val2) {
                        pc = jumps[prog[pc + 4] - 64];
                    } else {
                        pc += 5;
                    }
                }

                if (comp == '!') {
                    if (val1 != val2) {
                        pc = jumps[prog[pc + 4] - 64];
                    } else {
                        pc += 5;
                    }
                }
            }

            else if (prog[pc] == 'd') {
                printf("***REGISTERS***\n");
                for (int i=0; i<26; i++) {
                    if (reg[i])
                        printf("%c: %u\n", i+97, reg[i]);
                }
                printf("***MEMORY ADDRESSES***\n");
                for (int i=0; i<MEM_SIZE; i++) {
                    if (mem[i])
                        printf("%d: %u\n", i, mem[i]);
                }
                pc += 1;
            }

            else {
                pc += 1;
            }
    }
}
