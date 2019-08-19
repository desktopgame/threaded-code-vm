#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stack.h"

typedef enum opcode_t
{
	op_lit,
	op_add,
	op_sub,
	op_mul,
	op_div,
	op_mod,
	op_disp
} opcode_t;

typedef void *jump_addr_t;

static void vm_exec(opcode_t *program)
{
	static jump_addr_t table[] = {
		&&LABEL_LIT,
		&&LABEL_ADD,
		&&LABEL_SUB,
		&&LABEL_MUL,
		&&LABEL_DIV,
		&&LABEL_MOD,
		&&LABEL_DISP,
	};
	bnStack *stack = bnNewStack();
	int PC = 0;
	goto *table[PC];
LABEL_LIT:
{
	printf("LIT\n");
	bnPushStack(stack, (void *)program[++PC]);
	goto *table[program[++PC]];
}
LABEL_ADD:
{
	printf("ADD\n");
	int a = (int)bnPopStack(stack);
	int b = (int)bnPopStack(stack);
	bnPushStack(stack, (void *)(a + b));
	goto *table[program[++PC]];
}
LABEL_SUB:
{
	printf("SUB\n");
	int a = (int)bnPopStack(stack);
	int b = (int)bnPopStack(stack);
	bnPushStack(stack, (void *)(a - b));
	goto *table[program[++PC]];
}
LABEL_MUL:
{
	printf("MUL\n");
	int a = (int)bnPopStack(stack);
	int b = (int)bnPopStack(stack);
	bnPushStack(stack, (void *)(a * b));
	goto *table[program[++PC]];
}
LABEL_DIV:
{
	printf("DIV\n");
	int a = (int)bnPopStack(stack);
	int b = (int)bnPopStack(stack);
	bnPushStack(stack, (void *)(a / b));
	goto *table[program[++PC]];
}
LABEL_MOD:
{
	printf("MOD\n");
	int a = (int)bnPopStack(stack);
	int b = (int)bnPopStack(stack);
	bnPushStack(stack, (void *)(a % b));
	goto *table[program[++PC]];
}
LABEL_DISP:
{
	printf("DISP\n");
	printf("value: %d\n", (int)bnPopStack(stack));
}
	bnDeleteStack(stack, NULL);
}

int main(int argc, char *argv[])
{
	opcode_t program[] = {
		op_lit,
		10,
		op_lit,
		5,
		op_add,
		op_disp};
	vm_exec(program);
	return 0;
}