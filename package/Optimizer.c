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

	cur = tail;
	while(cur != NULL) {
		int op = cur->opcode;
		switch(op) {
			case 0:
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
			case 7:
				break;
			case 8:
				cur->critical = 'c';
				break;
			case 9:
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
