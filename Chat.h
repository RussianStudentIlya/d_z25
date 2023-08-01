#pragma once
#include <iostream>
#include "iTables.h"
#include "mySQL_db.h"
#include "db_Table.h"
#include "User.h"
#include "Message.h"
#include <memory>
#include <vector>
#include <algorithm>

using namespace std;

class Chat
{
public:
	Chat(mySQL_db& dbConnect);
	~Chat();

	void startChat(); // Запуск чата (проверяет создана ли таблица, если таблица не создана создает её)

	const bool get_ChatStart() const; // Чтение флага который показывает статус чата(старт/стоп)

	bool user_Login(); //вход зарегестрированного пользователя

	void chat_start_window(); //стартовое окно чата

	bool user_Registration(); // Регистрация пользователя

	void chat_menu(); /// меню чата после авторизации пользователя

	const bool get_UserExist() const;

	const string get_currentUserLogin() const;

	void send_Message();/// Отправить сообщение

	void list_Users();/// Список пользователей

	void incoming_and_sent_Messages(); // входящие и отправленные сообщения

private:
	mySQL_db _dbConnect;
	iTables* tables[3];
	User *user;
	Message *messag;

	bool _chatStart;

	bool _userExist; //Пользователь зарегестрирован или уже существует

	string _current_user_login; //текущий логин пользователя

	void checking_user_existence(string login, string h_password); //проверка существования пользователя в БД с такими login и password
	bool login_and_password_comparison(string login, string h_password); //сравнение логина и пароля
};

