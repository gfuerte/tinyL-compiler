#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "InstrUtils.h"
#include "Utils.h"

int main()
{
	Instruction *head, *tail, *cur;

	head = ReadInstructionList(stdin);
	if (!head) {
		WARNING("No instructions\n");
		exit(EXIT_FAILURE);
	}
	
	cur = head;
	while(cur != NULL) {
		if(cur->next == NULL) {
			tail = cur;
		}
		cur = cur->next;
	}

	int registers[1024];
	int variables[1024];
	cur = tail;
	while(cur != NULL) {
		int op = cur->opcode;
		switch(op) {
			case 0: //LOAD
				if(registers[cur->field1] == 1) {
					variables[cur->field2] = 1;
					cur->critical = 'c';
				}
				break;
			case 1:	//LOADI
				if(registers[cur->field1] == 1) {
					cur->critical = 'c';
				}
				break;
			case 2: //STORE
				if(variables[cur->field1] == 1) {
					registers[cur->field2] = 1;
					cur->critical = 'c';
				}
				break;
			case 3: //ADD
			case 4: //SUB
			case 5: //MUL
			case 6: //AND
			case 7: //XOR
				if(registers[cur->field1] == 1) {
					registers[cur->field2] = 1;
					registers[cur->field3] = 1;
					cur->critical = 'c';
				}
				break;
			case 8: //READ
				cur->critical = 'c';
				break;
			case 9: //WRITE
				variables[cur->field1] = 1;
				cur->critical = 'c';
				break;
			default:
				WARNING("This is not suppose to happen\n");
				exit(EXIT_FAILURE);

		}
		cur = cur->prev;
	}

	
	
	Instruction *prev;
	cur = head;
	prev = NULL;
	while(cur != NULL) {
		if(cur->critical != 'c' && prev == NULL) {
			cur = cur->next;
			cur->prev = NULL;
			head = cur;
			prev = cur;
			cur = cur->next;
		} else if(cur->critical != 'c' && cur->next == NULL) {
			prev->next = NULL;
			break;	
		} else if(cur->critical != 'c') {
			cur = cur->next;
			cur->prev = prev;
			prev->next = cur;
		} else {
			prev = cur;
			cur = cur->next;
		}
	}

	if (head) {
		PrintInstructionList(stdout, head);
		DestroyInstructionList(head);
	}
	return EXIT_SUCCESS;
}
