#include "PasswordManager.h"
#include <iostream>
#include <fstream>

std::string PasswordManager::encrypt_decrypt(const std::string& text) const
{
	std::string output = text; // Creating a copy for in-place modification
	for (size_t i = 0; i < text.length(); ++i)
	{
		// Xoring each character with the corresponding master password character
		output[i] = text[i] ^ master_password[i % master_password.length()];
	}
	return output;
}

void PasswordManager::add_record()
{
	PasswordRecord temp; // Creating a temporary object to hold new data
	temp.get_WebLogPass(); // Getting record data from the user via console
	vault.push_back(temp); // Storing the completed record into the dynamic array
}

void PasswordManager::show_all_records_noPass() const
{
	for (size_t j = 0; j < vault.size(); j++)
	{
		std::cout << "Пользователь №" << j + 1;
		vault[j].show_WebLog_PassHid(); // Displaying records with masked passwords
	}
}

void PasswordManager::show_all_records_Pass() const
{
	for (size_t j = 0; j < vault.size(); j++)
	{
		std::cout << "Пользователь №" << j + 1;
		vault[j].show_WebLogPass(); // Displaying records with visible passwords
	}
}

void PasswordManager::show_filename() const
{
	std::cout << " [Данные успешно сохранены в текстовый файл]: -> [" << filename << "] " << std::endl;
}

void PasswordManager::save_to_file() const
{
	std::ofstream file(filename);

	if (file.is_open())
	{
		for (size_t j = 0; j < vault.size(); j++)
		{
			// Each record field is encrypted individually and stored on a new line
			file << encrypt_decrypt(vault[j].get_website()) << std::endl;
			file << encrypt_decrypt(vault[j].get_login()) << std::endl;
			file << encrypt_decrypt(vault[j].get_password()) << std::endl;
		}
		file.close();
		show_filename();
	}
	else
	{
		std::cout << " Ошибка! [Файл не открылся!] " << std::endl;
	}
}

void PasswordManager::load_from_file()
{
	std::ifstream file(filename);

	if (file.is_open())
	{
		std::string web, log, pass;
		// Read records sequentially; each record takes exactly 3 lines in the file
		while (std::getline(file, web))
		{
			std::getline(file, log);
			std::getline(file, pass);

			// Decrypting data on the fly before restoring the object
			web = encrypt_decrypt(web);
			log = encrypt_decrypt(log);
			pass = encrypt_decrypt(pass);

			vault.push_back(PasswordRecord(web, log, pass));
		}
		file.close();
		std::cout << "[Данные успешно загружены в динамический массив!]" << std::endl;
	}
	else
	{
		std::cout << "[Локальная база данных не найдена. Будет создан новый файл при выходе!]" << std::endl;
	}
}

bool PasswordManager::authenticate() const
{
	std::string input;
	std::cout << "Введите мастер пароль для доступа к сейфу: ";
	std::getline(std::cin, input);
	std::cout << std::endl;

	if (input == master_password)
	{
		std::cout << "[Доступ разрешен!] " << std::endl;
		return true;
	}
	else
	{
		std::cout << "[Пароль неверный!!!][В достпуе отказано!!!] " << std::endl;
		return false;
	}
}