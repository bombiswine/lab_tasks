/*
	Author: Merson Alexandr

	Group: СМБ-001-O-01

	Task#: 4.9

	Description: программа находит наименьший элемент
                в каждой строке двумерного массива
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 10

int input_matrix_dimensions(int *rows, int *columns);

void input_borders_of_range(int *left_border, int *right_border);

int borders_check(const int left_border, const int right_border);

void filling_the_matrix(int matrix[][MAX_SIZE], const int r_num, const int c_num);

int random_number(const int l_border, const int r_border);

int find_min(int matrix[][MAX_SIZE], const int row, const int c_num);

void print_the_matrix(int matrix[][MAX_SIZE], const int r_num, const int c_num);

void print_min(int matrix[][MAX_SIZE], const int r_num, const int c_num);


int main()
{
    printf("This program finds the minimal element in every string of matrix");

    int matrix[MAX_SIZE][MAX_SIZE];
    int num_of_rows = 0;
    int num_of_columns = 0;

    input_matrix_dimensions(&num_of_rows, &num_of_columns);

    filling_the_matrix(matrix, num_of_rows, num_of_columns);

    print_the_matrix(matrix, num_of_rows, num_of_columns);

    print_min(matrix, num_of_rows, num_of_columns);

    return 0;
}

void print_the_matrix(int matrix[][MAX_SIZE], const int num_of_rows, const int num_of_columns)
{
    printf("\nThe matrix:\n");
    for (int i = 0; i < num_of_rows; i++) {
        for (int j = 0; j < num_of_columns; j++) {
            printf("m[%d][%d] = %d\t", i, j, matrix[i][j]);
        }
        printf("\n");
    }

}

int random_number(const int left_border, const int right_border)
{
    int random_number = left_border + rand() % right_border;
    return random_number;
}

void filling_the_matrix(int matrix[][MAX_SIZE], const int num_of_rows, const int num_of_columns)
{
    int left_border = 0;
    int right_border = 0;

    input_borders_of_range(&left_border, &right_border);

    srand(time(NULL));
    for (int i = 0; i < num_of_rows; i++) {
        for (int j = 0; j < num_of_columns; j++) {
            matrix[i][j] = random_number(left_border, right_border);
        }
    }
}

int find_min(int matrix[][MAX_SIZE], const int row, const int num_of_columns)
{
    int min = matrix[row][0];
    for (int j = 0; j < num_of_columns; j++) {
        if (min > matrix[row][j]) {
            min = matrix[row][j];
        }
    }
    return min;
}

void print_min(int matrix[][MAX_SIZE], const int num_of_rows, const int num_of_columns)
{
    for (int row = 0; row < num_of_rows; row++) {
        int min = find_min(matrix, row, num_of_columns);
        printf("\nMinimal element in the %d row is: %d\n", row,  min);
    }
}

int input_matrix_dimensions(int *num_of_rows, int *num_of_columns)
{
    int input_var_amount = 0;
    int input_correct = 0;

    do {
        printf("\nEnter the number of rows in the matrix: ");
        input_var_amount = scanf("%d", num_of_rows);
        input_correct = input_var_amount == 1;

        if (!input_correct || *num_of_rows > MAX_SIZE || *num_of_rows <= 0) {
            printf("\nError: input value must be number in range (0, 10)!");
            fflush(stdin);
        }

    } while (!input_correct);

    input_var_amount = 0;
    input_correct = 0;

    do {
        printf("\nEnter the amount of columns in the matrix: ");
        input_var_amount = scanf("%d", num_of_columns);
        input_correct = input_var_amount == 1;

        if (!input_correct || *num_of_columns > MAX_SIZE || *num_of_columns <= 0) {
            printf("\nError: input value must be number in range (0, 10)!");
            fflush(stdin);
        }

    } while (!input_correct);
}

void input_borders_of_range(int *left_border_ptr, int *right_border_ptr)
{
    const int left_border = *left_border_ptr;
    const int right_border = *right_border_ptr;
    int correct_range = 0;
    do {
        int input_var_amount = 0;
        int input_value_is_number = 0;
        printf("\nEnter the left border: ");
        do {
            input_var_amount = scanf("%d", left_border_ptr);
            input_value_is_number = input_var_amount == 1;

            if (!input_value_is_number) {
                printf("\nInput error: input value must be number!");
                fflush(stdin);
                printf("\nPlease make input correctly: ");
            }
        } while (!input_value_is_number);

        input_var_amount = 0;
        input_value_is_number = 0;
        printf("\nEnter the right border: ");
        do {
            input_var_amount = scanf("%d", right_border_ptr);
            input_value_is_number = input_var_amount == 1;

            if (!input_value_is_number) {
                printf("\nInput error: input value must be number!");
                fflush(stdin);
                printf("\nPlease make input correctly: ");
            }
        } while (!input_value_is_number);

        correct_range = borders_check(left_border, right_border);

    } while (!correct_range);
}

int borders_check(const int left_border, const int right_border)
{
    if (left_border > right_border) {
        printf("\nError: left border of values range must be lesser then right border!");
        return 0;
    }
    else {
        return 1;
    }
}
