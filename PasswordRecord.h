#pragma once

#pragma once
#include <iostream>
#include <string>

/**
 * @brief Represents a single account credential entry (Website, Login, Password).
 * Handles data encapsulation, console I/O, and password masking for secure display.
 */

class PasswordRecord
{
private:
	std::string website;
	std::string login;
	std::string password;

public:
	PasswordRecord() = default;

	PasswordRecord(const std::string& web, const std::string& log, const std::string& pass)
		: website(web), login(log), password(pass)
	{
	}

	
	void set_website(const std::string& w) { website = w; }
	void set_login(const std::string& l) { login = l; }
	void set_password(const std::string& p) { password = p; }

	std::string get_website() const { return website; }
	std::string get_login() const { return login; }
	std::string get_password() const { return password; }

	
	void get_WebLogPass()
	{
		std::cout << "Сайт: ";   std::getline(std::cin, website);
		std::cout << "Имя: ";    std::getline(std::cin, login);
		std::cout << "Пароль: "; std::getline(std::cin, password);
	}

	void show_WebLogPass() const
	{
		std::cout << " Сайт: [" << website << "] Логин: |" << login << "| Пароль: " << password << std::endl;
	}

	void show_WebLog_PassHid() const
	{
		std::string masked(password.length(), '*');
		std::cout << " Сайт: [" << website << "] Логин: |" << login << "| Пароль: " << masked << std::endl;
	}
};
