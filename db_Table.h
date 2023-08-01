#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "iTables.h"
#include <memory>
#include <vector>

#include <iomanip>
#include <ctime>

#include "mySQL_db.h"

class db_Table : virtual public iTables
{

protected:
	bool _statusCreateDB = false;
	//shared_ptr<mySQL_db> connect;
	mySQL_db _connect;

	string _request;
	///bool _flagCreateTable;
	MYSQL_RES* res;
	MYSQL_ROW row;

	bool add_in_table(string lits_variables[]) override;

	vector<string> show_tables(); // формирует список существующих таблиц

	bool checking_existence_table(const string tableName); //Проверка существования таблицы

	bool request_insert_from_Table(string& request) override;

	vector<string> request_select_from_Table(string& request) override; //Запрос на получение данных из таблицы БД

	string get_id_user(const string& variable) override; // Получение id пользователя

	//template<typename T> T request_select_from_Table(string& request); /// шаблонный метод на получение данных из таблиц БД

	/*vector<string> requestCreateTable = {
		"CREATE TABLE IF NOT EXISTS `clients` ( `id` int NOT NULL AUTO_INCREMENT," 
		"`last_name` varchar(255) NOT NULL, `name` varchar(255) NOT NULL, `email` text, " 
		"`login` varchar(255) NOT NULL, PRIMARY KEY(`id`))", /// --- Создание таблицы clients индекс - 0
		"CREATE TABLE IF NOT EXISTS `info_messages` ( `id_messages` int DEFAULT NULL," 
		" `date_send` date NOT NULL, `status` text NOT NULL, `delivered` tinyint(1) DEFAULT NULL, CONSTRAINT " 
		"`info_messages_chk_1` CHECK ((`status` in (_utf8mb4'read',_utf8mb4'not_read'))))", /// --- Создание таблицы info_messages индекс - 1
		"CREATE TABLE IF NOT EXISTS `messages`(`id` int NOT NULL AUTO_INCREMENT, `sender_id` int DEFAULT NULL," 
		"`recipient_id` int DEFAULT NULL, `text_messag` text, PRIMARY KEY(`id`))", /// --- Создание таблицы messages индекс - 2
		"CREATE TABLE IF NOT EXISTS `password_hash`(`clients_id` int DEFAULT NULL, "
		"`hash` varchar(32) DEFAULT NULL)" }; *//// --- Создание таблицы password_hash индекс - 3

public:
	db_Table(const bool& statusCreateDB, mySQL_db& connect);
	//db_Table(const bool& statusCreateDB, const mySQL_db& connect);
	db_Table() = default;
	~db_Table() = default;

	bool getStatusCreateTable() override;
	/// 
	///bool checking_existence_table() override;
};

class db_Table_Client : public db_Table
{
private:
	bool _createTable_Clients;
	string get_id_user(const string& variable) override;
	
	//int get_id_user(string& login);
	//int get_id_user(string& login, string& h_pass);
	
	//string get_id_clients(const string& login); // Получить id пользователя по логину
public:
	db_Table_Client(const bool& statusCreateDB, mySQL_db& connect);
	~db_Table_Client() = default;

	bool getStatusCreateTable() override;

	///const bool getFlagCreateTable() const;
	
	//bool add_in_table(const string& login, const string& last_name, string& name, string& email, string& hash_password);
	///bool add_in_table(const string& login, const string& last_name, string& name, string& email);
	bool add_in_table(string lits_variables[]) override;

	//vector<string> request_select_from_Table(string& request) override;

	///bool checking_existence_table() override;
};

class db_Table_hPassword : public db_Table
{
private:
	string get_id_user(const string& variable) override;
	bool _createTable_hp;
public:
	db_Table_hPassword(const bool& statusCreateDB, mySQL_db& connect);
	~db_Table_hPassword() = default;

	bool getStatusCreateTable() override;
	bool add_in_table(string lits_variables[]) override;
};

class db_Table_Messages : public db_Table
{
private:
	//bool _createTable_1, _createTable_2;
	bool _createTable_Messages;
	string get_current_Time_Date(); /// текущая дата и время
	vector<string> request_select_from_Table(string& request) override; //Запрос на получение данных из таблицы БД
	string get_id_user(const string& variable) override; // по id получить login пользователя

public:
	db_Table_Messages(const bool& statusCreateDB, mySQL_db& connect);
	~db_Table_Messages() = default;
	bool getStatusCreateTable() override;

	bool add_in_table(string lits_variables[]) override; // сформировать сообщение

	//bool checking_existence_table() override;
};
