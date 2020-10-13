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
			tail->critical = 'c';
		}
		cur = cur->next;
	}

	cur = tail;
	while(cur != NULL) {
		cur = cur->prev;
	}

	if (head) {
		PrintInstructionList(stdout, head);
		DestroyInstructionList(head);
	}
	return EXIT_SUCCESS;
}
