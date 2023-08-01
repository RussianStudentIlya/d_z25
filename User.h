#pragma once
#include <string>
using namespace std;

class User
{
private:
	string _login; // логин пользователя
	string _last_name; // Фамилия пользователя
	const string _name; // Имя пользователя
	string _email;
	const string _patronymic; // Отчество
	string _hash_password;  // пароль


public:
	User(const string& last_name, const string& name, const string& patronymic, const string& email, const string &hash_password, const string& login):
	_last_name(last_name), _name(name), _patronymic(patronymic), _email(email), _login(login)
	{
		setUserPassword(hash_password);
	}


	const string& getLastName() const { return this->_last_name; } /// прочитать фамилию пользователя
	void setLastName(const string& last_name)  { _last_name = last_name; }/// изменит

	const string& getName() const { return this->_name; } /// прочитать имя пользователя
	///void setName(const string& name) { _name = name; }/// изменит

	const string& getPatronymic() const { return this->_patronymic; } /// прочитать отчество пользователя
	///void setName(const string& name) { _name = name; }/// изменит

	const string& getEmail() const { return this->_email; } /// прочитать email
	void setEmail(const string& email) { _email = email; }/// изменит

	const string& getUserPassword() const { return this->_hash_password; } /// прочитать пароль пользователя
	void setUserPassword(const string& password) /// изменит пароль пользователя 
	{
		int sum = 0;
		for (int i = 0; i < password.size(); ++i)
		{
			sum += password[i];
		}

		this->_hash_password = to_string(sum);
	}

	string get_hash_Login(const string& password)
	{
		int sum = 0;
		for (int i = 0; i < password.size(); ++i)
		{
			sum += password[i];
		}

		return to_string(sum);
	}

	const string& getLogin() const { return this->_login; } /// прочитать логин
	void setLogin(const string& login) { this->_login = login; } // изменить логин
};