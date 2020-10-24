/*
	Author: Merson Alexandr

	Group: СМБ-001-O-01

	Task#: 3.19

	Description: нахождение пар последовательных элементов,
				 отношение которых меньше числа пи.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char way_choice();

void scan_array(double numbers[], const int S, const char choice);

void find_pairs(double numbers[], int pairs_numbers[], const int S);

void print_pairs(double numbers[], int pairs_numbers[], const int S);

void show_array (double numbers[], const int S);

int input_border();

int main()
{
    #define SIZE 21
	double numbers[SIZE];
	int pairs_numbers[SIZE];

	for (int i = 0; i < SIZE; i++) {
		pairs_numbers[i] = 0;
	}
	printf(" Choose the way to fill the array: if you want to do it by your hands enter k"
		"\n Else if you want to fill the array automatically enter a");
	const char user_choice = way_choice();
	scan_array(numbers, SIZE, user_choice);
	find_pairs(numbers, pairs_numbers, SIZE);
	show_array(numbers, SIZE);
	print_pairs(numbers, pairs_numbers, SIZE);

	return 0;
}

char way_choice()
{
	char choice;
	printf(" \n Your choice is: ");
	do {
		fflush(stdin);
		scanf("%c", &choice);

		if (choice != 'a' && choice != 'k') {
			printf(" Input error: choose the correct meaning: ");
		}
	} while (choice != 'a' && choice != 'k');

	return choice;
}

int input_border()
{
    int border;
    scanf("%d", &border);

    return border;
}

void scan_array(double numbers[], const int S, const char choice)
{
	if (choice == 'k') {
		for (int i = 0; i < S; i++) {
			int input_var_amount;
			int input_correct;
			do {
				printf("\n Enter the %d number: ", i + 1);
				input_var_amount = scanf("%4lf", &numbers[i]);
				input_correct = input_var_amount == 2;

				if (!input_correct) {
					printf("\n Error: input value must be number!");
					fflush(stdin);
					printf("\n Please enter the %d number: ", i + 1);
				}
			} while (!input_correct);
		}
	}
	else if (choice == 'a') {
		srand(time(NULL));
        int borders_input_correct;
        int interval_left_border;
        int interval_right_border;

        do {
            borders_input_correct = 1;
            printf("\n Enter the left border of values range: ");
            interval_left_border = input_border();
            printf("\n Enter the left border of values range: ");
            interval_right_border = input_border();

            if (interval_right_border < interval_left_border) {
                printf ("\n Error!: left border of values range"
                        "\n must be lesser then right border");
                borders_input_correct = 0;
            }
        } while(!borders_input_correct);

		for (int i = 0; i < S; i++) {
			numbers[i] = (rand() / (RAND_MAX + 1.0)) *
                (interval_right_border - interval_left_border) + interval_left_border;
		}
	}
}

void find_pairs(double numbers[], int pairs_numbers[], const int S)
{
	const double Pi = 3.141592653589793;

	for (int i = 0; i < S - 1; i++) {
		if ((numbers[i] * numbers[i + 1] != 0) || (numbers[i] == 0 && numbers[i + 1] != 0)) {
			if (numbers[i] / numbers[i + 1] < Pi) {
				pairs_numbers[i]++;
			}
		}
	}
}

void print_pairs(double numbers[], int pairs_numbers[], const int S)
{
	printf("\n\n This program has find next pairs: ");
    int pair_number = 0;
	for (int i = 0; i < S + 1; i++) {
		if (pairs_numbers[i] != 0) {
            pair_number++;
			printf("\n %d: (%8.5lf, %8.5lf)", pair_number, numbers[i], numbers[i + 1]);
		}
	}
}

void show_array (double numbers[], const int S) {
    printf("\n Array: ");
    for (int i = 0; i < S; i++) {
        printf("\n a[%d] = %8.5lf", i, numbers[i]);
    }
}
