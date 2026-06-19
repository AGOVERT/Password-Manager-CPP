#pragma once

#pragma once
#include <vector>
#include <string>
#include "PasswordRecord.h"

class PasswordManager
{
private:
	std::vector<PasswordRecord> vault; //Records will be stored here.
	std::string filename = "data_users.txt";
	std::string master_password = "your_master_password_here"; 

	std::string encrypt_decrypt(const std::string& text) const; //Encryption function using the XOR operator

public:
	void add_record();
	void show_all_records_noPass() const;
	void show_all_records_Pass() const;
	void show_filename() const;
	void save_to_file() const;
	void load_from_file();
	bool authenticate() const;
};
