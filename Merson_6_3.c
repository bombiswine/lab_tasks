#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "safe_inputs.h"

/*******************************************
*               user's types               *
*******************************************/
typedef enum Bool { FALSE, TRUE } Bool;

typedef enum option {
    EXIT_FROM_PROGRAM,
    ADD_ONE_CITY,
    ADD_MANY_CITIES,
    PRINT_ALL_INFORMATION,
    DELETE_ALL_INFORMATION,
    PRINT_CITIES_TOP,
} option;

enum { MEMORY_ALLOCATION_ERROR = -31 };

#define BUFSZ 64

typedef struct city {
    char country[BUFSZ];
    char name[BUFSZ];
    int population;
} city;

/*******************************************
*          functions' declarations         *
*******************************************/

void show_menu(void);

int choose_option(void);

void get_city_name(city* const, city* const, const int);

void add_information(city*, city* const, const int);

void add_one_city(city**, int*);

void add_many_cities(city**, int*);

void print_detailed_cities_list(city* const, const int);

void print_top_most_populated_cities(city* const, const int);

void clean_cities_list(city**, int*);

void exit_from_program(city* cities_list);

void demo_mode(void);

/***************************************/

int main()
{
    demo_mode();

    printf("\nWork mode is launched\n");

    city *cities_list = NULL;
    int cities_amount = 0;

    Bool stop_work = FALSE;

    do {
        show_menu();

        int chosen_option = choose_option();

        switch (chosen_option) {
            case EXIT_FROM_PROGRAM:
                exit_from_program(cities_list);
                stop_work = TRUE;
                break;

            case ADD_ONE_CITY:
                add_one_city(&cities_list, &cities_amount);
                break;

            case ADD_MANY_CITIES:
                add_many_cities(&cities_list, &cities_amount);
                break;

            case PRINT_ALL_INFORMATION:
                 print_detailed_cities_list(cities_list, cities_amount);
                break;

            case DELETE_ALL_INFORMATION:
                clean_cities_list(&cities_list, &cities_amount);
                break;

            case PRINT_CITIES_TOP:
                print_top_most_populated_cities(cities_list, cities_amount);
                break;
        }

    } while (!stop_work);

    return 0;
}

/*******************************************
*         functions' implementations       *
*******************************************/

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
	    "| Exit                                   (enter 0) |\n"
	    "====================================================\n"
    );
}

int choose_option(void)
{
    int chosen_option = 0;
    int option_input_correct = FALSE;

    printf("Your choice is: ");

    do {
	chosen_option = scan_whole_number();

	if (chosen_option < EXIT_FROM_PROGRAM || chosen_option > PRINT_CITIES_TOP) {
		printf("\nNo such operation\nMake enter correct meaning: ");
		fflush(stdin);
	} else {
            	option_input_correct = TRUE;
	} 
    } while (!option_input_correct);
    
    return chosen_option;
}

void add_information(city* city_ptr, city* const cities_list, const int cities_amount)
{
    fflush(stdin); //for not skipping country input because of '\n' in the buffer

    printf("\nEnter the country: ");
    char country_of_city[BUFSZ];
    get_static_str(country_of_city, BUFSZ);
    strcpy(city_ptr -> country, country_of_city);
    fflush(stdin);

    printf("Enter the city name: ");
    get_city_name(city_ptr, cities_list, cities_amount);
    fflush(stdin);

    printf("Enter city population: ");
    const int city_population = scan_natural_value();
    city_ptr -> population = city_population;

    printf("\n<Entry succes>\n");
}

void get_city_name(city* const city_ptr, city* const cities_list, const int cities_amount)
{
    char city_name[BUFSZ];
    int input_name_correct = FALSE;

    strcpy_s(city_name, BUFSZ, fgets(city_name, BUFSZ, stdin));

    do {
        for (int city_num = 0; city_num < cities_amount; city_num++) {
            city* current_city_ptr = &cities_list[city_num];

            Bool same_country = !(strcmp(city_ptr -> country, current_city_ptr -> country));

            if (same_country) {
                Bool same_names = !(strcmp(city_name, current_city_ptr -> name));

                if (same_names) {
                    printf("\nError: this city is already added\nEnter another name: ");
                    fflush(stdin);
                    strcpy_s(city_name, BUFSZ, fgets(city_name, BUFSZ, stdin));
                } else {
                    input_name_correct = TRUE;
                }
            }
        }
    } while (!input_name_correct);

    strcpy_s(city_ptr -> name, BUFSZ, city_name);
}

void add_one_city(city** cities_list_ptr, int* cities_amount_ptr)
{
    printf("\n<Add information about one city> is chosen\n");

    int start_cities_amount = *cities_amount_ptr;
    int upd_cities_amount = start_cities_amount + 1;
    city* upd_cities_list = *cities_list_ptr;

    upd_cities_list = (city*)realloc(upd_cities_list, upd_cities_amount * sizeof(city));

    if (upd_cities_list != NULL) {
        const int last_added_city_number = upd_cities_amount - 1;
        city *last_added_city_ptr = &upd_cities_list[last_added_city_number];

        add_information(last_added_city_ptr, upd_cities_list, upd_cities_amount);

        *cities_list_ptr = upd_cities_list;
        *cities_amount_ptr = upd_cities_amount;
    } else {
        printf("\nMemory allocation error");
        exit(MEMORY_ALLOCATION_ERROR);
    }
}

void add_many_cities(city** cities_list_ptr, int* cities_amount_ptr)
{
    printf("\n<Add information about many city> is chosen\n");

    int start_cities_amount = *cities_amount_ptr;
    city* upd_cities_list = *cities_list_ptr;

    printf("\nEnter amount cities you want to add to the cities list: ");
    const int adding_cities_amount = scan_natural_value();

    int upd_cities_amount = start_cities_amount + adding_cities_amount;

    upd_cities_list = (city*)realloc(upd_cities_list, upd_cities_amount * sizeof(city));

    if (upd_cities_list != NULL) {
        for (int city_num = start_cities_amount; city_num < upd_cities_amount; city_num++) {
            city* added_city_ptr = &upd_cities_list[city_num];
            add_information(added_city_ptr, upd_cities_list, upd_cities_amount);
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
    printf("\n<Print detailed cities list> is chosen\n");

    if (cities_amount > 0) {
        for (int city_number = 0; city_number < cities_amount; city_number++) {
            int number_of_position_in_list = city_number + 1;
            printf(
                "\nInformation about %d city"
                "\n\tCountry: %s\n\tName: %s\n\tPopulation: %d people\n",
                number_of_position_in_list,
                cities_list[city_number].country,
                cities_list[city_number].name,
                cities_list[city_number].population
            );
        }
	    
    } else {
        printf(
            "\nThere's too few information in the cities list"
            "\nAdd some cities and information about ones to use this option\n"
        );
    }
}

void print_top_most_populated_cities(city* const cities_list, const int cities_amount)
{
    printf("\n<Print 3 mostly populated cities> is chosen\n");
	
    enum { TOP_LIST_POSITIONS = 3 };
    enum { FIRST, SECOND, THIRD };

    if (cities_amount >= TOP_LIST_POSITIONS) {
        int highest_population = 0;
        int second_high_population = 0;
        int third_high_population = 0;

        city* top_cities_list[TOP_LIST_POSITIONS] = {NULL, NULL, NULL};

        for (int city_number = 0; city_number < cities_amount; city_number++) {
            city current_city = cities_list[city_number];

            if (highest_population < current_city.population) {
                top_cities_list[THIRD] = top_cities_list[SECOND];
                top_cities_list[SECOND] = top_cities_list[FIRST];
                top_cities_list[FIRST] = &cities_list[city_number];
                highest_population = current_city.population;
            }

            else if (second_high_population < current_city.population) {
                top_cities_list[THIRD] = top_cities_list[SECOND];
                top_cities_list[SECOND] = &cities_list[city_number];
                second_high_population = current_city.population;
            }

            else if (third_high_population < current_city.population) {
                top_cities_list[THIRD] = &cities_list[city_number];
                third_high_population = current_city.population;
            }
        }

        printf(
            "\nTop 3 mostly populated cities of the list:"
            "\n1.%s: %d people \n2.%s: %d people\n3.%s: %d people\n",
            top_cities_list[FIRST] -> name, top_cities_list[FIRST] -> population,
            top_cities_list[SECOND] -> name, top_cities_list[SECOND] -> population,
            top_cities_list[THIRD] -> name, top_cities_list[THIRD] -> population

        );

    } else {
        printf(
            "\nThere's too few information in the cities list"
            "\nAdd some cities and information about ones to use this option\n"
        );
    }
}

void clean_cities_list(city** cities_list_ptr, int* cities_amount_ptr)
{
    printf("\n<Delete all information > is chosen\n");

    int const cities_amount = *cities_amount_ptr;

    if (cities_amount > 0) {
        *cities_amount_ptr = 0;
        *cities_list_ptr = NULL;
    }

    printf("\nCities list is empty\n");
}

void exit_from_program(city* cities_list)
{
    printf("\n<Exit> is chosen\n");
    free(cities_list);
}

void demo_mode(void)
{
    printf("\nDemonstration mode is launched\n");

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

    system("pause");
}
