/*
	Author: Merson Alexandr

	Group: ÑÌÁ-001-O-01

	Task#: 2.3

	Description: Ñ÷¸ò÷èê îòðèöàòåëüíûõ ÷èñåë
				 â ââîäèìîé ïîñëåäîâàòåëüíîñòè.
*/

#include <stdio.h>

int main()
{
	double element;
	int count;
	int input_var_amount;
	int input_value_is_number;

	printf("\n This program counts the number of negative numbers in the sequence"
		   "\n If you want to end the program enter 0 \n");
	count = 0;
	while (element != 0) {
		printf(" Enter the element of sequence: ");
		do {
		    input_var_amount = scanf("%lf", &element);
		    input_value_is_number = input_var_amount == 1;

		    if (!input_value_is_number) {
			printf("\n Input error: input value must be number!");
			fflush(stdin);
			printf("\n Please enter the element of sequence correctly: ");
		    }
		} while (!input_value_is_number);

		if (element < 0) { count++; }
	}

	printf("\n There is %d negatives in this sequence \n", count);

	return 0;
}
