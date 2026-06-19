#include <iostream>
#include <Windows.h>
#include "PasswordManager.h"

int main() {
	// Set console encoding to support Russian characters
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");

	PasswordManager manager;

	// Terminate execution immediately if the master password check fails
	if (!manager.authenticate())
	{
		return 0;
	}

	manager.load_from_file(); // Initialize the vault with existing data from the file

	int choice;
	do
	{
		std::cout << "[1.Добавить карточку] [2.Показать все карточки с паролями] [3.Показать все карточки без паролей] [0.Выход из программы]" << std::endl;
		std::cin >> choice;
		std::cin.ignore(); // Clear the input buffer to prevent getline issues in menus

		if (choice == 1)
			manager.add_record();
		else if (choice == 2)
			manager.show_all_records_Pass();
		else if (choice == 3)
			manager.show_all_records_noPass();

	} while (choice != 0);

	manager.save_to_file(); // Persist all runtime changes back to the encrypted database

	return 0;
}