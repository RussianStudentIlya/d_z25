#include "Chat.h"

Chat::Chat(mySQL_db& dbConnect) : _dbConnect(dbConnect)
{
	_dbConnect.connect_DB(_dbConnect.get_dbName());

	if (_dbConnect.getConnectStatus() != true)
	{
		_dbConnect.create_DB(_dbConnect.get_dbName());
	}
}

Chat::~Chat()
{
	delete tables[0];
	delete tables[1];
	delete tables[2];

	delete user;
	delete messag;
}

void Chat::startChat()
{
	if (_dbConnect.getConnectStatus())
	{
		tables[0] = new db_Table_Client(_dbConnect.getConnectStatus(), _dbConnect); // Создание таблицы clients исли она не существуют
		
		tables[1] = new db_Table_hPassword(_dbConnect.getConnectStatus(), _dbConnect); // Создание таблицы password_hash исли она не существуют
		
		tables[2] = new db_Table_Messages(_dbConnect.getConnectStatus(), _dbConnect); // Создать таблицу messages если она не существуют
		
		//tables[3] = new db_Table_Info_Messages(_dbConnect.getConnectStatus(), _dbConnect);// Создать таблицу info_messages если она не существуют

		/*---Если все таблицы созданы то чат старт---*/
		/*if (t_client.getStatusCreateTable() && t_messag.getStatusCreateTable() && t_h_password.getStatusCreateTable())
			this->_chatStart = true;
		else
			this->_chatStart = false;*/

		if (tables[0]->getStatusCreateTable() && tables[1]->getStatusCreateTable() && tables[2]->getStatusCreateTable())
			this->_chatStart = true;
		else
			this->_chatStart = false;
	}
}

const bool Chat::get_ChatStart() const
{
	return this->_chatStart;
}

bool Chat::user_Login()
{
	string password_h = "", login = "";
	bool result = false;
	while (true)
	{
		cout << "Введите логин: @";
		cin >> login;
		
		cout << "Введите пароль: ";
		cin >> password_h;
		cout << endl;

		/*---------------------*/
		if (this->login_and_password_comparison("@" + login, password_h))
		{
			this->_current_user_login = "@" + login;
			result = true;
			break;
		}
	}
	return result;
}

void Chat::chat_start_window()
{
	while (this->_chatStart && !this->_userExist)
	{
		int oper;

		cout << "Вход(1) | Регистрация(2) | Выход(0)" << endl;

		cout << ">>";
		cin >> oper;


		switch (oper)
		{
		case 1:
			// Метод для входа зарегестрированного пользователя
			if (this->user_Login())
				this->_userExist = true;
			else
				this->_userExist = false;
			//if (chat_db.user_Login()) cout << true << endl;
			break;
		case 2:
			//Регистрация пользователя
			if (this->user_Registration())
				this->_userExist = true;
			else
				this->_userExist = false;
			//cout << chat_db.user_Registration() << endl;
			break;
		case 0:
			//Выход
			this->_chatStart = false;
			break;
		default:
			break;
		}
	}
}

bool Chat::user_Registration()
{
	string last_name = "", name = "", patronymic = "", email = "", password_h = "", login = "";
	while (true)
	{
		SetConsoleCP(1251);
		SetConsoleOutputCP(1251);

		cout << "Введите фамилию: ";
		cin >> last_name;
		///cout << last_name << endl;

		cout << "Введите имя: ";
		cin >> name;
		//cout << endl;

		cout << "Введите отчество: ";
		cin >> patronymic;
		//cout << endl;

		cout << "Введите email: ";
		cin >> email;
		//cout << endl;

		login = "@" + last_name + "_" + name;
		cout << "Логин по умолчанию = " << login << endl;

		cout << "Введите пароль: ";
		cin >> password_h;
		cout << endl;

		/*---------------------*/
		this->user =  new User(last_name, name, patronymic, email, password_h, login);

		this->checking_user_existence(user->getLogin(), user->getUserPassword());

		string list[] = {
			user->getLastName(),
			user->getName(),
			user->getPatronymic(),
			user->getEmail(),
			user->getLogin()
		}; //last_name, name, patronymic, email, login

		bool flag_clients = tables[0]->add_in_table(list);

		///cout << user->getLogin() << endl;

		string list_2[] = {
			tables[0]->get_id_user(user->getLogin()),
			user->getUserPassword()
		}; //id_login, password

		bool flag_h_p = tables[1]->add_in_table(list_2);
		
		if (flag_clients == true && flag_h_p == true)
		{
			this->_current_user_login = user->getLogin();
			return true;
			break;
		}

	}
	return false;
}

void Chat::chat_menu()
{
	char operation;

	cout << "Пользователь: " << this->get_currentUserLogin() << endl;

	while (this->_userExist)
	{
		cout << "(1)Входящие и отправленные сообщения | (2)Отправить сообщение | (3)Показать кто в чате | (0)Выйти ";

		cout << endl
			<< ">> ";
		cin >> operation;

		switch (operation)
		{
		case '1':
			// входящие и отправленные сообщения
			this->incoming_and_sent_Messages();
			break;
		case '2':
			//Отправить сообщение
			this->send_Message();
			break;
		case '3':
			///Список зарегестрированных
			this->list_Users();
			break;
		case '0':
			//currentUser_ = nullptr;
			this->_userExist = false;
			break;
		default:
			//cout << "сделайте выбор.." << endl;
			break;
		}
		/*cout << "Введите фамилию: ";
		cin >> last_name;
		cout << "Введите имя: ";
		cin >> name;
		cout << "Введите отчество: ";
		cin >> patronymic;
		login = "@" + last_name + "_" + name;
		cout << "Логин = " << login << endl;
		cout << "Введите email: ";
		cin >> email;
		cout << "Введите пароль: ";
		cin >> password_h;
		cout << endl;*/
	}
}

bool Chat::login_and_password_comparison(string login, string h_password)
{
	string h_p = this->user->get_hash_Login(h_password);

	string value_1 = tables[0]->get_id_user(login);
	string value_2 = tables[1]->get_id_user(h_p);

	if (value_1 == value_2)
		return true;

	return false;
}

const bool Chat::get_UserExist() const
{
	return this->_userExist;
}

const string Chat::get_currentUserLogin() const
{
	return this->_current_user_login;
}

void Chat::send_Message()
{
	//recipient - получатель
	//sender - отправитель
	string login_recipient, // login получателя 
		   text_messages, // текст сообщения
		   login_sender = this->get_currentUserLogin(); // login отправителя

	cout << "Кому отправить сообщение (введите login получателя): @";
	cin >> login_recipient;

	if (tables[0]->get_id_user("@" + login_recipient) == "-1") // проверка существования логина получателя
	{
		cout << "Не верный логин" << endl;
	}
	else
	{
		cout << "Сообщение: ";
		cin.ignore(); // игнорировать любые введенные посторонние символы
		getline(cin, text_messages); /// ввод текстового сообщения с пробелами

		//from - От
		//to - Кому
		this->messag = new Message(login_sender, "@" + login_recipient, text_messages);
		//string list[] = { login_sender, "@" + login_recipient, text_messages };
		string list[] = { messag->getFrom(), messag->getTo(), messag->getText()};

		if (tables[2]->add_in_table(list) == true)
			cout << "Сообщение пользователю: " + messag->getTo() + " отправленно." << endl;
	}
}

void Chat::list_Users()
{
	string requests = "select clients.login from clients "
		"where clients.login != '" + this->get_currentUserLogin() + "'";

	auto list = tables[0]->request_select_from_Table(requests);

	if (list.size() > 0)
	{
		for (auto& item : list)
			cout << item << endl;
	}
	else
		cout << "Список пуст." << endl;
}

void Chat::incoming_and_sent_Messages()
{
	string request = "select sender_login, recipient_login, text_messag, date_send "
		"from messages where sender_login = '" + this->get_currentUserLogin() + "' OR recipient_login = '" + this->get_currentUserLogin() + "'";

	//cout << request << endl;

	auto list = tables[2]->request_select_from_Table(request);

	for (auto& item : list)
		cout << item << endl;
}

void Chat::checking_user_existence(string login, string h_password)
{
	string value_login = tables[0]->get_id_user(login);

	string value_h_p = tables[1]->get_id_user(h_password);

	string n_login, n_h_password;
	bool f_login = false, f_h_password = false, exist_Login = false, exist_h_password = false;

	if (value_login == "-1")
		exist_Login = true;
	
	if (value_h_p == "-1")
		exist_h_password = true;

	while (exist_Login == false || exist_h_password == false)
	{
		if (exist_Login == false)
		{
			f_login = false;
			cout << "Login уже существует, его нужно изменить. " << endl;
			cout << "Введите новый логин: @";
			cin >> n_login;
			user->setLogin("@" + n_login);

			//cout << " -> " << user->getLogin() << endl;

			f_login = true;
		}

		if (exist_h_password == false)
		{
			f_h_password = false;
			cout << "Пароль уже существует, его нужно изменить. " << endl;
			cout << "Введите новый пароль: ";
			cin >> n_h_password;
			user->setUserPassword(n_h_password);

			///cout << " -> " << user->getUserPassword() << endl;

			f_h_password = true;
		}

		if (f_login)
		{
			value_login = tables[0]->get_id_user(user->getLogin());
			if (value_login == "-1")
				exist_Login = true;
		}

		if (f_h_password)
		{
			value_h_p = tables[1]->get_id_user(user->getUserPassword());

			if (value_h_p == "-1")
				exist_h_password = true;
		}

	}

	/*while (value_login != " " || value_h_p != " ")
	{
		value_login = tables[0]->get_id_user(login);
		value_h_p = tables[1]->get_id_user(h_password);

		if (value_login != " ")
		{
			cout << "Login уже существует, его нужно изменить. " << endl;
			cout << "Введите новый логин: @";
			cin >> n_login;
			user->setLogin(n_login);
			
		}

		if (value_h_p != " ")
		{
			cout << "Пароль уже существует, его нужно изменить. " << endl;
			cout << "Введите новый пароль: ";
			cin >> n_h_password;
		}
	}*/
}
