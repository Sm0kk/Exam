#pragma once
#include"Header1.h"
class Admin
{
public:
	Admin() { login = pass = string(); };
	Admin(string s1, string s2) : login{ s1 }, pass{ s2 }{};
	void reg_admin(string l, string p);
	bool check_authorization(string lgn, string pswrd);
	void change_login(string lgn);
	void change_pass(string pswd);
	bool is_empty_file(string path);
	void load_data();
	void save_data();
	bool chek_admin();
protected:
	string login, pass;
};

void Admin::reg_admin(string lgn, string pswd)
{

	login = encrypt(lgn);
	pass = encrypt(pswd);
	save_data();

}
bool Admin::check_authorization(string lgn, string pswd)
{
	if (decipher(login) == lgn && decipher(pass) == pswd)
		return true;
	else
		return false;
}

void Admin::change_login(string lgn)
{
	login = encrypt(lgn);
}
void Admin::change_pass(string pswd)
{
	pass = encrypt(pswd);
}

bool Admin::is_empty_file(string path)
{
	ifstream in(path);
	bool isepmty = true;
	string str;
	if (!in.is_open())
	{
		cerr << "File not found\n";
		return false;
	}
	while (in >> str)
	{
		isepmty = false;
	}
	in.close();
	return isepmty;
}
void Admin::load_data()
{
	ifstream file(adminPath, ios::binary);
	if (!file.is_open())
	{
		return;
	}
	int tmp;
	while (file.read((char*)&tmp, sizeof(int)))
	{
		this->login.resize(tmp);
		file.read((char*)this->login.c_str(), tmp);

		file.read((char*)&tmp, sizeof(int));
		this->pass.resize(tmp);
		file.read((char*)this->pass.c_str(), tmp);
	}
	file.close();
}

void Admin::save_data()
{
	ofstream file(adminPath, ios::binary | ios::trunc);
	if (!file.is_open())
		cerr << "Error!\n";

	int strLen = this->login.size();
	file.write((char*)&strLen, sizeof(int));
	file.write((char*)this->login.c_str(), this->login.size());

	strLen = this->pass.size();
	file.write((char*)&strLen, sizeof(int));
	file.write((char*)this->pass.c_str(), this->pass.size());

	file.close();
}

bool Admin::chek_admin()
{
	if (login.empty())
		return true;
	else return false;
}