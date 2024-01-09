#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <conio.h>


typedef struct Products Products;
typedef struct Category Category;

//Products struct -->
struct Products {
	char name[20];
	int price;
	int quantity;
};

//Category Struct --->
struct Category {
	char name[20];
	int number_of_products;

	Products *products;
};

//Function of gotoXY ===>
COORD coord = {0, 0}; // this is global variable
void gotoxy(int x, int y) {
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//Function of change color ==>
void color(int ForgC) {
	WORD wColor;
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
		wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
		SetConsoleTextAttribute(hStdOut, wColor);
	}
	return;
}

// hide the cursor -->
void hide_cursor() {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

//show cursor
void show_cursor() {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100; // The size of the cursor
	info.bVisible = TRUE; // Make the cursor visible
	SetConsoleCursorInfo(consoleHandle, &info);
}

// Validation the number input -->
int number_validation(char *message) {

	int input, temp, status;

	printf("%s ", message);
	status = scanf("%d", &input);
	while (status != 1 || input == 0) {
		while ((temp = getchar()) != EOF && temp != '\n');
		color(12);
		printf("Enter Valid Number: ");
		status = scanf("%d", &input);
		color(7);
	}

	return input;
}

//Successful Message
void successful_message(char *message) {
	system("cls");
	gotoxy(35, 12);
	color(14);
	printf("%s", message);
	getch();
}

//display menu function ===>
void display_menu(int option_selected) {
	system("cls");
	gotoxy(31, 7);
	color(9);
	printf("<<  Welcome to Moudy's  store  >>\n");

	//option----->[0]
	gotoxy(42, 10);
	if (option_selected == 0) {
		color(10);
		printf("-> ");
	} else {
		color(7);
		printf(" ");
	}
	printf("Category");
	//option----->[1]
	gotoxy(42, 12);
	if (option_selected == 1) {
		color(10);
		printf("-> ");
	} else {
		color(7);
		printf(" ");
	}
	printf("products");

//	option----->[2]
	gotoxy(42, 14);
	if (option_selected == 2) {
		color(10);
		printf("-> ");
	} else {
		color(7);
		printf(" ");
	}
	printf("view products");

	//option----->[3]
	gotoxy(42, 16);
	if (option_selected == 3) {
		color(10);
		printf("-> ");
	} else {
		color(7);
		printf(" ");
	}
	printf("Make Order");

	//option----->[4]
	gotoxy(42, 18);
	if (option_selected == 4) {
		color(10);
		printf("-> ");
	} else {
		color(7);
		printf(" ");
	}
	printf("Exit");


}

//mini_menu function ==>
void mini_menu(int option, char *first_option, char *second_option, char *third_option) {
	gotoxy(38, 10);
	if (option == 0) {
		color(9);
	} else {
		color(7);
	}
	printf("%s", first_option);


	gotoxy(38, 13);
	if (option == 1) {
		color(9);
	} else {
		color(7);
	}
	printf("%s", second_option);

	if (*third_option != '\0') {
		if (*third_option != 'n') {
			gotoxy(38, 16);
			if (option == 2) {
				color(9);
			} else {
				color(7);
			}
			printf("%s", third_option);
		}
	}
}


//Add Categories Function
void add_categories(int *size_of_categories, Category **categories) {
	int additional_categories = 0;
	int total_size;

	if (*size_of_categories == 0) {
		*size_of_categories = number_validation("How many categories would you add: \n");
		*categories = (Category *)calloc(*size_of_categories, sizeof(Category));

		for (int i = 0; i < *size_of_categories; i++) {
			int if_unique;
			do {
				if_unique = 1;
				printf("Category %d Name: ", i + 1);
				scanf("%19s", (*categories)[i].name);


				for (int j = 0; j < i; j++) {
					if (strcmp((*categories)[i].name, (*categories)[j].name) == 0) {

						if_unique = 0;
						printf("This name of category is already used, use another name: \n");
						break;
					}
				}
			} while (!if_unique);

			(*categories)[i].number_of_products = 0;
		}

		if (*size_of_categories > 1) {
			successful_message("Categories Added successfully");
			return;
		} else if (*size_of_categories == 1) {
			successful_message("Category Added successfully");
			return;
		}
	} else {
		additional_categories = number_validation("How many additional categories would you add: ");
		total_size = additional_categories + *size_of_categories;
		*categories = (Category *)realloc(*categories, total_size * sizeof(Category));

		for (int i = *size_of_categories; i < total_size; i++) {
			int if_unique;
			do {
				if_unique = 1;
				printf("Category %d Name: ", i + 1);
				scanf("%19s", (*categories)[i].name);

				for (int j = 0; j < i; j++) {
					if (strcmp((*categories)[i].name, (*categories)[j].name) == 0) {
						if_unique = 0;
						printf("This name of category is already used, use another name: ");
						break;
					}
				}
			} while (!if_unique);

			(*categories)[i].number_of_products = 0;
			(*categories)[i].products = NULL;
		}

		*size_of_categories = total_size;

		if (additional_categories > 1) {
			successful_message("Categories Added successfully");
		} else {
			successful_message("Category Added successfully");
		}
	}
}

void delete_category(int *size_of_categories, Category **categories) {
	int key_pressed, option = 0, add_more = 1;

	int delete_category_number = 0;
	if (*size_of_categories == 0) {
		gotoxy(34, 12);
//		color(4);
		system("cls");
		printf("There is no categories to delete.");
		getch();
		return;
	}
	for (int i = 0; i < *size_of_categories; i++) {
		printf("Category <%d> : %s\n", i + 1, (*categories)[i].name);
	}
	printf("\n");
	do {

		delete_category_number = number_validation("Which Category you would delete: ");

	} while (delete_category_number > *size_of_categories);

	delete_category_number -= 1;

	do {
		system("cls");
		gotoxy(22, 6);
		printf("Are you sure you want to delete category, %s !", (*categories)[delete_category_number].name);
		mini_menu(option, "Delete", "Cancel", "n");
		key_pressed = getch();

		if (key_pressed == 224) {
			key_pressed = getch();
			if (key_pressed == 72) {
				if (option > 0) {
					option--;
				} else {
					option = 1;
				}
			} else if (key_pressed == 80) {
				if (option < 1) {
					option++;
				} else {
					option = 0;
				}
			}
		} else if (key_pressed == 13) {
			system("cls");
			if (option == 0) {
				add_more = 1; // Continue adding products
			} else {
				add_more = 0; // Complete the order
			}
			break; // Break out of the loop after a choice is made

		}

	} while (1);

	////////////////////
	if (add_more) {
		if ((*categories)[delete_category_number].products != NULL)
			free((*categories)[delete_category_number].products);


		for (int i = delete_category_number; i < *size_of_categories; i++) {
			(*categories)[i] = (*categories)[i + 1];
		}
		*size_of_categories -= 1;
		(*categories) = (Category *) realloc(*categories, (*size_of_categories) * sizeof(Category));

		//Successful message
		successful_message("Category deleted successfully");
	} else return;


}

// New function for category menu
void category_menu(int *size_of_categories, Category **categories) {
	int option = 0;
	int key_pressed;

	do {
		mini_menu(option, "Add Category", "Delete Category", "Back");

		key_pressed = getch();


		if (key_pressed == 224) {
			key_pressed = getch();


			if (key_pressed == 72) {
				if (option > 0) {
					option--;
				} else if (option == 0) {
					option = 2;
				}
			} else if (key_pressed == 80) {
				if (option < 2) {
					option++;
				} else if (option == 2) {
					option = 0;
				}
			}

		} else if (key_pressed == 13) {
			system("cls");
//			color(4);
			switch (option) {
				case 0:
					show_cursor();
					add_categories(size_of_categories, categories);
					system("cls");
					break;
				case 1:
					delete_category(size_of_categories, categories);
					system("cls");
					break;
				case 2:
					return;
			}

		} else if (key_pressed == 8) {
			system("cls");
			option = 0;
			return;
		}

	} while (1);
}

//Add products function -->
void add_product(int size_of_categories, Category *categories) {
	if (size_of_categories == 0) {
		system("cls");
		printf("Add category first");
		return;
	}
	int number;
	int total_products = 0;
	int temp = 0;

	system("cls");
	for (int i = 0; i < size_of_categories; i++) {
		printf("Category <%d> %s\n", i + 1, (categories)[i].name);
		printf("----------\n");
	}

	do {
		number = number_validation("Enter number of category you will add products in: ");
	} while (number > size_of_categories);

	number--;

	system("cls");
	if (categories[number].number_of_products == 0) {

		(categories)[number].number_of_products = number_validation("How many product you would add: ");

		(categories)[number].products = (Products *) calloc((categories)[number].number_of_products, sizeof(Products));

		for (int i = 0; i < (categories)[number].number_of_products; i++) {
			printf("Product [%d]\n", i + 1);
			printf("name: ");
			scanf("  %19s", (categories)[number].products[i].name);
			(categories)[number].products[i].price = number_validation("Price: ");
			(categories)[number].products[i].quantity = number_validation("Quantity: ");
			printf("\n");

		}

		if (categories[number].number_of_products > 1) {
			successful_message("Products Added successfully");
		} else {
			successful_message("Product Add successfully");
		}
	} else {
		temp = number_validation("How many additional product you would add: ");
		total_products = (categories)[number].number_of_products + temp;
		categories[number].products = (Products *) realloc(categories[number].products,
														   total_products * sizeof(Products));

		for (int i = (categories)[number].number_of_products; i < total_products; i++) {
			printf("Product [%d]\n", i + 1);
			printf("name: ");
			scanf("  %19s", (categories)[number].products[i].name);
			(categories)[number].products[i].price = number_validation("Price: ");
			(categories)[number].products[i].quantity = number_validation("Quantity: ");

			printf("\n");

		}
		if (temp > 1) {
			successful_message("Products Added successfully");
		} else {
			successful_message("Product Add successfully");
		}
		categories[number].number_of_products = total_products;
	}

}

void delete_product(int size_of_categories, Category *categories) {
	int option = 0, key_pressed, delete_item = 1;
	int category_index, product_index;
	if (size_of_categories <= 0) {
		printf("No categories available.\n");
		getch();
		system("cls");
		return;
	}


	for (int i = 0; i < size_of_categories; ++i) {
		if (categories[i].number_of_products == 0) continue;
		printf("%d. %s\n", i + 1, (categories)[i].name);
	}
	do {
		do {
			category_index = number_validation("Select a category to delete a product from: ");

//			if (categories[category_index - 1].number_of_products == 0) {
//				printf("\n\t\t\tThere is no products in this category\n\n");
//
//			}
		} while (category_index > size_of_categories);

	} while (categories[category_index - 1].number_of_products == 0);

	category_index -= 1;

	// Display products for user to choose
	printf("Select a product to delete:\n");
	for (int i = 0; i < (categories)[category_index].number_of_products; ++i) {
		printf("%d. %s\n", i + 1, (categories)[category_index].products[i].name);
	}
	do {
		product_index = number_validation("Select a product to delete: ");
	} while (product_index > (categories)[category_index].number_of_products);

	product_index -= 1;

	do {
		system("cls");
		gotoxy(22, 6);
		printf("Are you sure you want to delete product, %s !",
			   (categories)[category_index].products[product_index].name);
		mini_menu(option, "Delete", "Cancel", "n");
		key_pressed = getch();

		if (key_pressed == 224) {
			key_pressed = getch();
			if (key_pressed == 72) {
				if (option > 0) {
					option--;
				} else {
					option = 1;
				}
			} else if (key_pressed == 80) {
				if (option < 1) {
					option++;
				} else {
					option = 0;
				}
			}
		} else if (key_pressed == 13) {
			system("cls");
			if (option == 0) {
				delete_item = 1;
			} else {
				delete_item = 0;
			}
			break;

		}

	} while (1);
	if (delete_item) {
		// Delete the selected product
		for (int i = product_index; i < (categories)[category_index].number_of_products - 1; ++i) {
			(categories)[category_index].products[i] = (categories)[category_index].products[i + 1];
		}
		(categories)[category_index].number_of_products -= 1;

		successful_message("Product deleted successfully");
		system("cls");
	} else return;
}

void move_product(Category *categories, int size_of_categories) {
	color(7);
	show_cursor();
	int category_from = 0;
	int moved_product = 0;
	int category_to = 0;
	if (size_of_categories <= 1) {
		printf("Not enough categories to move a product.\n");
		getch();
		return;
	}
	for (int i = 0; i < size_of_categories; i++) {
		if (categories[i].number_of_products == 0) continue;
		printf("%d. %s\n", i + 1, (categories)[i].name);

	}
	// 1 -> choose which category will move from -->
	do {
		category_from = number_validation("In which category is your product: ");
	} while (category_from > size_of_categories);
	category_from -= 1;

	if (categories[category_from].number_of_products == 0) {
		printf("No products available in this category.\n");
		getch();
		return;
	}

// 2 -> choose the product that will move

	printf("\n");

	for (int i = 0; i < (categories)[category_from].number_of_products; ++i) {
		printf("%d. %s\n", i + 1, (categories)[category_from].products[i].name);
	}
	do {
		moved_product = number_validation("Select a product to Move: ");
	} while (moved_product > categories[category_from].number_of_products|| moved_product < 1) ;
	printf("\n");
	moved_product -= 1;
// 3-> choose which category will move to

	for (int i = 0; i < size_of_categories; i++) {
		printf("%d. %s\n", i + 1, (categories)[i].name);

	}
	// 1 -> choose which category will move from -->
	do {
		category_to = number_validation("Select a category to move the product to: ");
		if (category_to - 1 == category_from) {
			color(4);
			printf("Can not move product to the same category.  choose different category.\n");
			color(7);
		}
	} while (category_to > size_of_categories || category_to < 1 || category_to - 1 == category_from);
	category_to -= 1;

	printf("\n");

// 4-> Add product to the new category


	(categories)[category_to].products = (Products *) realloc((categories)[category_to].products,
															  ((categories)[category_to].number_of_products + 1) *
															  sizeof(Products));
	(categories)[category_to].number_of_products += 1;
	categories[category_to].products[categories[category_to].number_of_products -
									 1] = categories[category_from].products[moved_product];

// 5-> remove the product from its main category
	for (int i = moved_product; i < (categories)[category_from].number_of_products; ++i) {
		(categories)[category_from].products[i] = (categories)[category_from].products[i + 1];
	}
	(categories)[category_from].number_of_products -= 1;


	//Successful message
	successful_message("Product moved successfully");

}

//Function mini menu of add product ==>
void product_menu(int size_of_categories, Category *categories) {
	int option = 0;
	int key_pressed;

	do {
		mini_menu(option, "Add Product", "Delete Product", "Move Product");

		key_pressed = getch();

		if (key_pressed == 224) {
			key_pressed = getch();


			if (key_pressed == 72) {
				if (option > 0) {
					option--;
				} else if (option == 0) {
					option = 2;
				}
			} else if (key_pressed == 80) {
				if (option < 2) {
					option++;
				} else if (option == 2) {
					option = 0;
				}
			}

		} else if (key_pressed == 13) {
			system("cls");
//			color(4);
			switch (option) {
				case 0:
					show_cursor();
					add_product(size_of_categories, categories);
//
					system("cls");
					break;
				case 1:
					delete_product(size_of_categories, categories);
					break;
				case 2:
					move_product(categories, size_of_categories);
					system("cls");
			}

		} else if (key_pressed == 8)  // Backspace key
		{
			system("cls");
			option = 0;
			return;
		}

	} while (1);
}

//Function display product
void display_products(int size_of_categories, int *selected_category_index, Category **categories) {

	if (size_of_categories == 0) {
		printf("No categories to display.\n");
		getch();
		return;
	}

	for (int i = 0; i < size_of_categories; i++) {
		printf("Category <%d> : %s\n", i + 1, (*categories)[i].name);
	}
	printf("\n");
	show_cursor();
	do {
		*selected_category_index = number_validation("Enter  number of the category to view products: ");
	} while (*selected_category_index > size_of_categories);
	hide_cursor();
	*selected_category_index -= 1;


	if ((*categories)[*selected_category_index].number_of_products == 0) {
		printf("There are no products in this category.\n");
		getch();
		return;
	}


	for (int i = 0; i < (*categories)[*selected_category_index].number_of_products; i++) {
		printf("Product (%d)\n", i + 1);
		printf("Name:     %s\n", (*categories)[*selected_category_index].products[i].name);
		printf("Price:    %d\n", (*categories)[*selected_category_index].products[i].price);
		printf("Quantity: %d\n", (*categories)[*selected_category_index].products[i].quantity);
		printf("\n");

	}
	color(4);
	printf("Press any key to return");
	getch();
}

//Function Move-product ==>
void make_order(Category *categories, int size_of_categories) {
	Products *order = NULL;
	int category_index, product_index, total_price;
	int key_pressed, size_of_products = 0, quantity = 0;
	int option = 0, add_more = 1;


	if (size_of_categories <= 0) {
		printf("No categories available.\n");
		getch();
//		system("cls");
		return;
	}
	do {
		system("cls");

//		color(7);
		// Display categories for user to choose
		for (int i = 0; i < size_of_categories; ++i) {
//

			printf("%d. %s\n", i + 1, (categories)[i].name);
		}
		printf("\n");
		do {
			category_index = number_validation("\tChose the Category: ");
		} while (category_index < 1 ||category_index > size_of_categories);
		category_index -= 1;
		printf("\n");
		if (categories[category_index].number_of_products == 0) {
			printf("There are no products in this category.\n");
			getch();
			continue;
		}
		// Display products for user to choose
		for (int i = 0; i < (categories)[category_index].number_of_products; ++i) {
			printf("%d. %s\n", i + 1, (categories)[category_index].products[i].name);
		}
		do {
			product_index = number_validation("\tChose the Product: ");
		} while (product_index > categories[category_index].number_of_products);
		product_index -= 1;
		printf("\n");
		char temp[10];
		if (categories[category_index].products[product_index].quantity > 1) {
			gotoxy(30, 12);
			printf("There are only %d pieces of %s available\n",
				   categories[category_index].products[product_index].quantity,
				   categories[category_index].products[product_index].name);
			do {
				quantity = number_validation("\nHow many pieces would you like to buy: ");
			} while (quantity > categories[category_index].products[product_index].quantity);
		} else {
			printf("Only one piece of %s is available, ", categories[category_index].products[product_index].name);
			do {
				quantity = number_validation("Please enter '1' to purchase it: ");
			} while (quantity > categories[category_index].products[product_index].quantity);
		}
		printf("\n");

		//add product into the order array->
		order = (Products *) realloc(order, (size_of_products + 1) * sizeof(Products));

		strcpy(order[size_of_products].name, categories[category_index].products[product_index].name);
		order[size_of_products].price = categories[category_index].products[product_index].price;
		order[size_of_products].quantity = quantity;
		size_of_products += 1;

		if (quantity == categories[category_index].products[product_index].quantity) {

			for (int i = product_index; i < (categories)[category_index].number_of_products; ++i) {
				(categories)[category_index].products[i] = (categories)[category_index].products[i + 1];
			}

			(categories)[category_index].number_of_products -= 1;
		} else {
			categories[category_index].products[product_index].quantity -= quantity;
		}


		do {
			system("cls");
			mini_menu(option, "Yes, add more products", "No, complete the order", "n");
			key_pressed = getch();

			if (key_pressed == 224) {
				key_pressed = getch();
				if (key_pressed == 72) {
					if (option > 0) {
						option--;
					} else {
						option = 1;
					}
				} else if (key_pressed == 80) {
					if (option < 1) {
						option++;
					} else {
						option = 0;
					}
				}
			} else if (key_pressed == 13) {
				system("cls");
//				color(4);
				if (option == 0) {
					add_more = 1;
				} else {
					add_more = 0;
				}
				break;
			}

		} while (1);


	} while (add_more);


	for (int i = 0; i < size_of_products; i++) {
		total_price += order[i].price * order[i].quantity;
	}

	//Successful message
	system("cls");
	color(12);
	printf("Your order contain: ");
	printf("\n");
	printf("\n");
	char item[10];
	for (int i = 0; i < size_of_products; i++) {
		if (order[i].quantity > 1) {

			strcpy(item, "items");
		} else {

			strcpy(item, "item");
		}

		printf("%d  %s of product: %s - price: %d$\n", order[i].quantity, item, order[i].name, order[i].price);
	}
	printf("\n");
	printf("Total price of your order: %d$", total_price);
	free(order);

}
int main() {
	hide_cursor();
	int option_selected = 0;
	int key_pressed;
	int size_of_categories = 0;
	Category *categories = NULL;
	int selected_category_index = 0;
	int option = 0;


	//	run the menu --->
	do {
		display_menu(option_selected);
		key_pressed = getch();


		if (key_pressed == 224)  // Arrow key
		{
			key_pressed = getch();  // Read arrow key code

			// Move selection up
			if (key_pressed == 72) {
				if (option_selected > 0) {
					option_selected--;
				} else if (option_selected == 0) {
					option_selected = 4;
				}
			}

				// Move selection down
			else if (key_pressed == 80) {
				if (option_selected < 4) {
					option_selected++;
				} else if (option_selected == 4) {
					option_selected = 0;
				}
			}

		} else if (key_pressed == 13) {
			system("cls");

			//Show info in each option
			switch (option_selected) {
				//Add category -->
				case 0:
					category_menu(&size_of_categories, &categories);
					break;

					//Add products -->
				case 1:
					product_menu(size_of_categories, categories);
					break;
					//Display all products-->
				case 2:
					display_products(size_of_categories, &selected_category_index, &categories);
//					getch();
					break;
					//Make Order-->
				case 3:
					make_order(categories, size_of_categories);
					getch();
					break;
					//Exit -->
				case 4:
					printf("Ending the menu.\n");
					return 0;
			}

		} else if (key_pressed == 8) {
			system("cls");
			break;
		}
	} while (1);


	return 0;
}
