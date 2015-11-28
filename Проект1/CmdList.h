#pragma once

#include "platypus.h"

DEF_CMD(END, 0, {}, {}, {})
DEF_CMD(PUSH, 1,\
{\
	Cpu_push(This, *(TYPEofNUMBERS*)(cmd + (++i)));\
	i += SIZEofTYPEofNUMBERS;\
},\
{ asm_push(fInput, fOutput); },\
{ disasm_push(fInput, fOutput);)
DEF_CMD(PUSH_AX, 2, { Cpu_push_ax(This); ++i; }, {}, {})
DEF_CMD(POP_AX, 3, { Cpu_pop_ax(This); ++i; }, {}, {})
DEF_CMD(ADD, 4, { Cpu_op(This, +); ++i; }, {}, {})
DEF_CMD(SUB, 5, { Cpu_op(This, -); ++i; }, {}, {})
DEF_CMD(MUL, 6, { Cpu_op(This, *); ++i; }, {}, {})
DEF_CMD(DIV, 7, { Cpu_op(This, / ); ++i; }, {}, {})
DEF_CMD(POW, 8, { Cpu_pow(This); ++i; }, {}, {})
DEF_CMD(OUT, 9, { Cpu_out(This); ++i; }, {}, {})
DEF_CMD(DUP, 10, { Cpu_dup(This); ++i; }, {}, {})
DEF_CMD(JA, 20, { Cpu_j(This, > ); }, { asm_jump(fInput, fOutput); })
DEF_CMD(JAE, 21, { Cpu_j(This, >= ); }, { asm_jump(fInput, fOutput); })
DEF_CMD(JB, 22, { Cpu_j(This, < ); }, { asm_jump(fInput, fOutput); })
DEF_CMD(JBE, 23, { Cpu_j(This, <= ); }, { asm_jump(fInput, fOutput); })
DEF_CMD(JE, 24, { Cpu_j(This, = ); }, { asm_jump(fInput, fOutput); })
DEF_CMD(JNE, 25, { Cpu_j(This, != ); }, { asm_jump(fInput, fOutput); })
DEF_CMD(JMP, 26, { i = cmd[i + 1]; }, { asm_jump(fInput, fOutput); })