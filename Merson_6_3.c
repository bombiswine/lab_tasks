#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*****************************************
*                                        *
*              user's types              *
*                                        *
*****************************************/
#define MAX_SIZE 64

typedef struct city {
    char country[MAX_SIZE];
    char name[MAX_SIZE];
    int population;
} city;

typedef enum Bool { FALSE, TRUE } Bool;

typedef enum option {
    ADD_ONE_CITY = 1,
    ADD_MANY_CITIES,
    PRINT_ALL_INFORMATION,
	DELETE_ALL_INFORMATION,
	PRINT_MOST_POPULATED_CITIES,
	EXIT_FROM_PROGRAM
} option;

enum ERRORS {MEMORY_ALLOCATION_ERROR = -31};

/*****************************************
*                                        *
*        functions' declarations         *
*                                        *
*****************************************/

void scan_natural_value(int*);

void show_menu(void);

int choose_option(void);

void add_one_city(city**, int*);

void add_many_cities(city**, int*);

void print_detailed_cities_list(city* const, const int);

void print_most_populated_cities_top_list(city* const, const int);

void clean_cities_list(city**, int*);

/****************************************/

#define TOP_LIST_POSITIONS 3

int main()
{
    city *cities_list = NULL;
    int cities_amount = 0;

    Bool stop_work = FALSE;

    do {
        show_menu();
        int chosen_option = choose_option();

        switch (chosen_option) {

            case EXIT_FROM_PROGRAM:
                free(cities_list);
                stop_work = TRUE;
                break;

            case ADD_ONE_CITY:
                add_one_city(&cities_list, &cities_amount);
                break;

            case ADD_MANY_CITIES:
                add_many_cities(&cities_list, &cities_amount);
                break;

            case PRINT_ALL_INFORMATION:
                if (cities_list != NULL) {
                    print_detailed_cities_list(cities_list, cities_amount);
                } else {
                    printf("\nCities list is empty");
                }
                break;

            case PRINT_MOST_POPULATED_CITIES:
                if (cities_amount < TOP_LIST_POSITIONS) {
                    printf(
                        "\nThere's too few information in the cities list"
                        "\nAdd some cities and information about ones to use this option"
                    );
                } else {
                    print_most_populated_cities_top_list(cities_list, cities_amount);
                }
                break;

            case DELETE_ALL_INFORMATION:
                if (cities_amount > 0) {
                    clean_cities_list(&cities_list, &cities_amount);
                } else {
                    printf("\nCities list is already empty");
                }
                break;

            default:
                printf("\nNo such option");
                break;
        }

    } while (!stop_work);

    return 0;
}

/*****************************************
*                                        *
*       functions' implementations       *
*                                        *
*****************************************/

void scan_natural_value(int* var_ptr)
{
	int var = 0;
	int input_var_amount = 0;
	int input_correct = 0;

	do {
		input_var_amount = scanf("%d", &var);
		input_correct = input_var_amount == 1;

		if (!input_correct) {
			printf(
				"\nError: input value must be positive number!"
				"\nPlease enter the correct meaning: "
			);
			fflush(stdin);
		}
		else if (var <= 0) {
			printf("\nError: input value must be positive number!");
		}

	} while (!input_correct);

	*var_ptr = var;
}

void show_menu(void)
{
	printf(
        "\nChoose the option from this list:                 \n"
		"====================================================\n"
		"| Add information about one city         (enter 1) |\n"
		"|--------------------------------------------------|\n"
		"| Add information about many cities      (enter 2) |\n"
		"|--------------------------------------------------|\n"
		"| Print detailed cities list             (enter 3) |\n"
		"|--------------------------------------------------|\n"
		"| Delete all information                 (enter 4) |\n"
		"|--------------------------------------------------|\n"
		"| Print 3 mostly populated cities        (enter 5) |\n"
		"|--------------------------------------------------|\n"
		"| Exit                                   (enter 6) |\n"
		"====================================================\n"
	);
}

int choose_option(void)
{
	int chosen_option = 0;
	printf("Your choice is: ");

	int correct_option_input = FALSE;

	while (!correct_option_input) {
		scan_natural_value(&chosen_option);

		if (chosen_option >= ADD_ONE_CITY && chosen_option <= EXIT_FROM_PROGRAM) {
			return chosen_option;
		} else {
			printf(
                "\nThere's no operation with number you have input"
				"\nPlease enter the correct meaning: "
            );

			fflush(stdin);
		}
	}
}

void add_information(city* city_ptr)
{
    printf("\nEnter the country: ");

    char country_of_city[MAX_SIZE];
    scanf("%s", country_of_city);
    strcpy(city_ptr -> country, country_of_city);

    printf("Enter the city name: ");

    char city_name[MAX_SIZE];
    scanf("%s", city_name);
    strcpy(city_ptr -> name, city_name);

    printf("Enter city population: ");

    int city_population = 0;
    scan_natural_value(&city_population);
    city_ptr -> population = city_population;
}

void add_one_city(city** cities_list_ptr, int* cities_amount_ptr)
{
    int start_cities_amount = *cities_amount_ptr;
    int upd_cities_amount = start_cities_amount + 1;
    city *upd_cities_list = *cities_list_ptr;

    upd_cities_list = (city *)realloc(upd_cities_list, upd_cities_amount * sizeof(city));

    if (upd_cities_list != NULL) {
        const int last_added_city_number = upd_cities_amount - 1;
        city *last_added_city_ptr = &upd_cities_list[last_added_city_number];

        add_information(last_added_city_ptr);

        *cities_list_ptr = upd_cities_list;
        *cities_amount_ptr = upd_cities_amount;
    } else {
        printf("\nMemory allocation error");
        exit(MEMORY_ALLOCATION_ERROR);
    }
}

void add_many_cities(city** cities_list_ptr, int* cities_amount_ptr)
{
    int start_cities_amount = *cities_amount_ptr;
    city *upd_cities_list = *cities_list_ptr;

    printf("\nEnter amount cities you want to add to the cities list: ");
    int adding_cities_amount = 0;
    scan_natural_value(&adding_cities_amount);

    int upd_cities_amount = start_cities_amount + adding_cities_amount;

    upd_cities_list = (city *)realloc(upd_cities_list, upd_cities_amount * sizeof(city));

    if (upd_cities_list != NULL) {
        for (int added_city_num = 0; added_city_num < adding_cities_amount; added_city_num++) {
            city *added_city_ptr = &upd_cities_list[added_city_num];

            add_information(added_city_ptr);
        }

        *cities_list_ptr = upd_cities_list;
        *cities_amount_ptr = upd_cities_amount;
    } else {
        printf("\nMemory allocation error");
        exit(MEMORY_ALLOCATION_ERROR);
    }

}

void print_detailed_cities_list(city* const cities_list, const int cities_amount)
{
    for (int city_number = 0; city_number < cities_amount; city_number++) {

        int number_of_position_in_list = city_number + 1;

        printf(
            "\nInformation about %d city"
            "\n\tCountry: %s\n\tName: %s\n\tPopulation: %d people",
            number_of_position_in_list,
            cities_list[city_number].country,
            cities_list[city_number].name,
            cities_list[city_number].population
        );

        putchar('\n');
    }
}

void print_most_populated_cities_top_list(city* const cities_list, const int cities_amount)
{
    /**find 1-t city of population rate**/

    int highest_population = 0;
    int first_city_of_top_number = 0;

    for (int city_number = 0; city_number < cities_amount; city_number++) {
        city current_city = cities_list[city_number];

        if (highest_population < current_city.population) {
            highest_population = current_city.population;
            first_city_of_top_number = city_number;
        }
    }
    /**find 2-d city of population rate**/

    int second_high_population = 0;
    int second_city_of_top_number = 0;

    for (int city_number = 0; city_number < cities_amount; city_number++) {
        city current_city = cities_list[city_number];

        if (second_high_population < current_city.population
            && current_city.population < highest_population) {

            second_high_population = current_city.population;
            second_city_of_top_number = city_number;
        }
    }

    /**find 3-d city of population rate**/

    int third_high_population = 0;
    int third_city_of_top_number = 0;

    for (int city_number = 0; city_number < cities_amount; city_number++) {
        city current_city = cities_list[city_number];

        if (third_high_population < current_city.population
            && current_city.population < second_high_population) {

            third_high_population = current_city.population;
            third_city_of_top_number = city_number;
        }
    }

    /**print top 3 mostly populated cities of the list**/

    printf(
        "\nTop 3 mostly populated cities of the list:"
        "\n1.%s:\n\t%d people \n2.%s:\n\t%d people\n3.%s:\n\t%d people",
        cities_list[first_city_of_top_number].name, highest_population,
        cities_list[second_city_of_top_number].name, second_high_population,
        cities_list[third_city_of_top_number].name, third_high_population
    );
}

void clean_cities_list(city **cities_list_ptr, int *cities_amount_ptr)
{
    const int upd_cities_amount = 0;
    *cities_amount_ptr = upd_cities_amount;
    *cities_list_ptr = NULL;
}
