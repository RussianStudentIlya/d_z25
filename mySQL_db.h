#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "mysql.h"

using namespace std;

class mySQL_db
{
public:
	mySQL_db(const string &host, const string &user, const string &password, const string& dbName);
	//~mySQL_db();
	~mySQL_db() = default;
	bool connect_DB(const string& dbName); // Подключение к существующей БД
	bool create_DB(const string& dbName); // Создание новой БД
	void connection_new_DB(const string& dbName); // Подключение к новой БД
	const string get_dbName() const; // Получить имя созданной БД
	const bool getConnectStatus() const;

	MYSQL* getMYSQL() { return &this->mysql; }


protected:
	string _host;
	string _user;
	string _password;
	string _dbName;

	MYSQL mysql;

	bool _connectStatus;

};

