#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*******************************************
*                                          *
*                user's types              *
*                                          *
*******************************************/

enum size_of_top { TOP_LIST_POSITIONS = 3 };

typedef enum Bool { FALSE, TRUE } Bool;

typedef enum option {
    ADD_ONE_CITY = 1,
    ADD_MANY_CITIES,
    PRINT_ALL_INFORMATION,
    DELETE_ALL_INFORMATION,
    PRINT_MOST_POPULATED_CITIES,
    EXIT_FROM_PROGRAM
} option;

enum { MEMORY_ALLOCATION_ERROR = -31 };

#define MAX_SIZE 64

typedef struct city {
    char country[MAX_SIZE];
    char name[MAX_SIZE];
    int population;
} city;

/*******************************************
*                                          *
*          functions' declarations         *
*                                          *
*******************************************/

void scan_natural_value(int*);

void show_menu(void);

int choose_option(void);

void add_one_city(city**, int*);

void add_many_cities(city**, int*);

void print_detailed_cities_list(city* const, const int);

void print_top_most_populated_cities(city* const, const int);

void clean_cities_list(city**, int*);

void demo_mode(void);

/******************************************/

int main()
{
    printf("\nDemonstration mode is launched\n");
    demo_mode();
    system("pause");

    printf("\nNow you are in the work modul\n");

    city *cities_list = NULL;
    int cities_amount = 0;
    Bool stop_work = FALSE;

    do {
        show_menu();
        int chosen_option = choose_option();

        switch (chosen_option) {

            case EXIT_FROM_PROGRAM:
                printf("\n<Exit> is chosen\n");
                free(cities_list);
                stop_work = TRUE;
                break;

            case ADD_ONE_CITY:
                printf("\n<Add information about one city> is chosen\n");
                add_one_city(&cities_list, &cities_amount);
                break;

            case ADD_MANY_CITIES:
                printf("\n<Add information about many city> is chosen\n");
                add_many_cities(&cities_list, &cities_amount);
                break;

            case PRINT_ALL_INFORMATION:
                printf("\n<Print detailed cities list> is chosen\n");

                if (cities_list != NULL) {
                    print_detailed_cities_list(cities_list, cities_amount);
                } else {
                    printf("\nCities list is empty\n");
                }
                break;

            case DELETE_ALL_INFORMATION:
                printf("\n<Delete all information > is chosen\n");

                if (cities_amount > 0) {
                    clean_cities_list(&cities_list, &cities_amount);
                } else {
                    printf("\nCities list is already empty\n");
                }
                break;

            case PRINT_MOST_POPULATED_CITIES:
                printf("\n<Print 3 mostly populated cities> is chosen\n");

                if (cities_amount < TOP_LIST_POSITIONS) {
                    printf(
                        "\nThere's too few information in the cities list"
                        "\nAdd some cities and information about ones to use this option\n"
                    );
                } else {
                    print_top_most_populated_cities(cities_list, cities_amount);
                }
                break;

            default:
                printf("\nNo such option");
                break;
        }

    } while (!stop_work);

    return 0;
}

/*******************************************
*                                          *
*         functions' implementations       *
*                                          *
*******************************************/

void scan_natural_value(int* natural_number_ptr)
{
	int natural_number = 0;
	int input_var_amount = 0;
	int input_correct = 0;

	do {
		input_var_amount = scanf("%d", &natural_number);
		input_correct = input_var_amount == 1;

		if (!input_correct || natural_number <= 0) {
			printf(
				"\nError: input value must be positive number!"
				"\nPlease enter the correct meaning: "
			);

			fflush(stdin);
		}

	} while (!input_correct || natural_number <= 0);

	*natural_number_ptr = natural_number;
}

void show_menu(void)
{
    printf(
	    "\nChoose the option from the options list\n"
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

    printf("\n<Entry succesful>\n");
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

void print_top_most_populated_cities(city* const cities_list, const int cities_amount)
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
        "\n1.%s: %d people \n2.%s: %d people\n3.%s: %d people",
        cities_list[first_city_of_top_number].name, highest_population,
        cities_list[second_city_of_top_number].name, second_high_population,
        cities_list[third_city_of_top_number].name, third_high_population

    );

    putchar('\n');
}

void clean_cities_list(city **cities_list_ptr, int *cities_amount_ptr)
{
    const int upd_cities_amount = 0;
    *cities_amount_ptr = upd_cities_amount;
    *cities_list_ptr = NULL;
}

void demo_mode(void)
{
    #define DEMO_LIST_SIZE 3

    const int demo_cities_amount = DEMO_LIST_SIZE;
    city demo_cities_list[DEMO_LIST_SIZE];

    strcpy(demo_cities_list[0].country, "Russia");
    strcpy(demo_cities_list[0].name, "St-Petersburg");
    demo_cities_list[0].population = 4991000;

    strcpy(demo_cities_list[1].country, "USA");
    strcpy(demo_cities_list[1].name, "New-York");
    demo_cities_list[1].population = 20610000;

    strcpy(demo_cities_list[2].country, "UK");
    strcpy(demo_cities_list[2].name, "London");
    demo_cities_list[2].population = 8982000;

    printf("\nDemo cities list:");
    print_detailed_cities_list(demo_cities_list, demo_cities_amount);

    print_top_most_populated_cities(demo_cities_list, demo_cities_amount);

    printf("\nDemonstration completed\n");
}
