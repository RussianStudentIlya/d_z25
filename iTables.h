#pragma once
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class iTables
{
public:
	virtual ~iTables() = default;
	virtual bool getStatusCreateTable() = 0;
	virtual vector<string> request_select_from_Table(string& request) = 0; //Запрос на получение данных из таблицы БД
	virtual bool request_insert_from_Table(string &request) = 0; //Запрос на добавление данных в таблицу БД
	virtual bool add_in_table(string lits_variables[]) = 0;

	virtual string get_id_user(const string& variable) = 0; /// получение id пользователя
};
