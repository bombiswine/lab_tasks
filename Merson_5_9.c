#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

#define OUTPUT_DEBUG_INFO 1

void make_new_str(char**, char*, char*, const int, const int, int*);

int def_new_str_size(char*, char*, const int, const int);

void del_cur_char_copies(char, char*, const int);

int get_allocatable_str(char**, int* const);

void make_deallocate_str(char**);

void show_new_str(char*, const int);

int main()
{
	char* first_str = NULL;
	int first_str_size = 0;
	get_allocatable_str(&first_str, &first_str_size);

	char* second_str = NULL;
	int second_str_size = 0;
	get_allocatable_str(&second_str, &second_str_size);

	char* new_str = NULL;
	int new_str_size = 0;
	make_new_str(&new_str, first_str, second_str, first_str_size, second_str_size, &new_str_size);

	show_new_str(new_str, new_str_size);

	make_deallocate_str(&first_str);
	make_deallocate_str(&second_str);
	make_deallocate_str(&new_str);

	return 0;
}

void make_new_str(char** new_str_ptr, char* first_str, char* second_str,
                  const int first_str_size, const int second_str_size, int* new_str_size_ptr)
{
	const int new_str_size = def_new_str_size(first_str, second_str, first_str_size, second_str_size);
	char* new_str = (char*)malloc(new_str_size * sizeof(char));
	assert(new_str != NULL);

	int inx = 0;
	do {
        for (int i = 0; i < first_str_size; i++) {
            if (first_str[i] != ' ' && first_str[i] != '\0') {
                for (int j = 0; j < second_str_size; j++) {
                    if (first_str[i] == second_str[j]) {
                        new_str[inx] = first_str[i];
                        inx += 1;
                        break;
                    }
                }
            } else {continue;}
        }
	} while(inx < new_str_size - 1);

	new_str[new_str_size - 1] = '\0';
	*new_str_ptr = new_str;
	*new_str_size_ptr = new_str_size;
}

int def_new_str_size(char* first_str, char* second_str, const int first_str_size, const int second_str_size)
{
	int common_chars_amount = 0;
	const int size_ends = 1;
	for (int i = 0; i < first_str_size - size_ends; i++) {
		char current_char = first_str[i];
		if (isprint(current_char) && !isspace(current_char)) {
			for (int j = 0; j < second_str_size - size_ends; j++) {
				if (current_char == second_str[j]) {
					common_chars_amount += 1;

                    #if OUTPUT_DEBUG_INFO
					printf("\ncom ch am = %d\n", common_chars_amount);
					printf("\ncom chr is: %c\n", current_char);
					#endif // OUTPUT_DEBUG_INFO

					del_cur_char_copies(current_char, first_str, first_str_size);
					del_cur_char_copies(current_char, second_str, second_str_size);
				}
			}
		}
	}

	const int new_str_size = common_chars_amount + size_ends;

	return new_str_size;
}

void del_cur_char_copies(char current_char, char* str, const int str_size)
{
	int amount_of_repeat = 0;
	int fixed_index = 0;

	for (int i = 0; i < str_size; i++) {
		if (str[i] == current_char) {
			amount_of_repeat += 1;
			if (amount_of_repeat == 1) {
				fixed_index = i;
				amount_of_repeat = 1;
			}

			if (amount_of_repeat > 1 && fixed_index != i) {
				str[i] = ' ';
			}
		}
	}
	puts(str);
}

int get_allocatable_str(char** str_ptr, int* const len_ptr)
{
	static int number_of_str = 1;
	printf("Please, enter the %d string:\n", number_of_str);
	number_of_str += 1;
	const int init_size = 10;

	int size = init_size;
	char* str = (char*)malloc(init_size * sizeof(char));
	assert(str != NULL);

	char symbol = 0;
	int index_of_symbol = 0;
	const char input_end = '\n';

	do {
		symbol = getchar();
		str[index_of_symbol] = symbol;
		index_of_symbol += 1;

		if (index_of_symbol == size) {
			const int reallocate_size = size + init_size;
			char* str_temp_realloc = (char*)realloc(str, reallocate_size * sizeof(char));
			if (str_temp_realloc != NULL) {
				str = str_temp_realloc;
				size = reallocate_size;
			} else {
				free(str);
				return -1;
			}
		}
	} while (symbol != input_end);

	const int size_of_ends = 1;
	const int reallocate_size = index_of_symbol + size_of_ends;
	char* str_temp_realloc = (char*)realloc(str, reallocate_size * sizeof(char));
	if (str_temp_realloc != NULL) {
		str = str_temp_realloc;
		size = reallocate_size;
		str[size - 1] = '\0';
	} else {
		free(str);
		return -1;
	}

	*str_ptr = str;
	*len_ptr = size;

	return 0;
}

void make_deallocate_str(char** str_ptr)
{
	free(*str_ptr);
	*str_ptr = NULL;
}

void show_new_str(char* new_str, const int new_str_size)
{
	if (new_str_size == 1) {
		printf("\nThis strings don't have any common characters\n");
	} else {
		printf("\nThere's %d common character(s)"
                "in two strings: ", new_str_size - 1);
		puts(new_str);
	}
}
