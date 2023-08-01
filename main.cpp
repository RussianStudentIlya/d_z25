#include <iostream>
#include "mySQL_db.h"
#include "Chat.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "rus");

	string host = "localhost";
	string user = "root";
	string password = "admin_password23";
	string dbName = "db_chat_dz25";
	

	mySQL_db dbConnect = mySQL_db(host, user, password, dbName);

	Chat chat_db = Chat(dbConnect);

	//cout << dbConnect.getConnectStatus();

	chat_db.startChat(); /// Запуск чата

	while (chat_db.get_ChatStart())
	{
		chat_db.chat_start_window();

		while (chat_db.get_UserExist())
		{
			chat_db.chat_menu();
		}
	}

	return 0;
}