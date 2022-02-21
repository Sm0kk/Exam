#include"TestingSystem.h"

int main()
{
	Admin admin;
	User user;
	TestingSystem tst; 
	vector <User> usersDB;
	size_t choice = 0, prevMenu = 1;
	string login, pass, tmp;

	while (true)
	{
		system("cls");
		cout << "Entrance to the Testing system\n";
		switch (menu_message("1 - Guest mode\n2 - Administrator mode\n3 - Exit from app\n: ",4))
		{
		case USERMODE:
		{ 
			system("cls");
			cout << "Guest mode activated\n";
			system("pause");
			while (prevMenu!=0)
		{ 
			switch (menu_message("1 - Login\n2 - Register\n3 - Return to main menu\n: ", 4))
			{
			case LOGINUSER:
			{
				system("cls");
				if (usersDB.empty())
				{
					cout << "No users detected! Please register or load data from file\n";
					break;
				}
				cout << "Login: ";
				cin >> login;
				cout << "Password: ";
				cin >> pass;
				system("cls");
				int chek = chek_autorization(login, pass, usersDB);
				if (chek >= 0)
				{

					usersDB[chek].show_user();
					choice = menu3_user(); 
					while (choice)
					{
						if (choice == 1)
						{
							usersDB[chek].show_stat();
						
						}
						else if (choice == 2)
						{
							choice= menu_message("Which test do you want to take:\n1-Discrete Mathematics\n2-Mathematical analysis\n3-Quantum physics\n4-Mechanics\n: ", 5);
							if (choice < 0 || choice > 4)
							{
								cout << "Bad choice\n";
							}
							system("cls");
							tst.load_start_test(usersDB[chek], choice);
							usersDB[chek].save_test_res();
						}
						cout << endl;
						choice = menu3_user();
					}
				}
				break;
			} 
			case REGISTERUSER:
			{
				system("cls");
				cout << "REGISTERUSER\n";
				if (user.reg_user(usersDB))
				usersDB.push_back(user);
				break;
			}
			case RETURNTOMAIN:
			{
				system("cls");
				prevMenu = 0;
				break;
			}
			}
		}
			break;
		}
		case ADMINMODE:
		{
			system("cls");
			cout << "***Administrator mode activated***\n";
			
				admin.load_data();
				if (admin.chek_admin()) {
					cout << "Administrator not found. Please register.\n\n"
						<< "Login: ";
					cin >> login;
					cout << "Password: ";
					cin >> pass;
					admin.reg_admin(login, pass);
					system("cls");
					cout << "Administrator user successfuly created!\n";
				}
				cout << "Please login.\n\n";
				cout << "Username: ";
				cin >> login;
				cout << "Password: ";
				cin >> pass;
				system("cls");
			while (prevMenu != 0)
				{
				if (admin.check_authorization(login, pass)) {
					switch (menu_message("Administrator logged in.\n1 - Change login and password\n2 - Save\\Load users data to\\from file\n3 - User management\n4 - View statistics\n5 - Test Management\n6 - Return to main menu\n: ", 7))
					{
					case CHANGE_LOGIN_PASSWORD:
					{
						system("cls");
						cout << "Enter new Login: ";
						cin >> login;
						cout << "Enter new Password: ";
						cin >> pass;
						admin.change_login(login);
						admin.change_pass(pass);
						admin.save_data();
						cout << "Login and password changed!\n";
						break;
					}
					case SAVE_LOAD_DATA:
					{
						system("cls");
						cout << "1 - Save all data to file\n2 - Load data from file\n: ";
						cin >> choice;
						if (choice==1)
						{
							user.save_data_user(usersDB);
							cout << "User data was saved!\n";
							system("pause");
							}
						else 
							{
							user.load_data_user(usersDB);
							cout << "User data loaded!\n";
							system("pause");
							}
						break;
					}
					case USER_MANAGEMENT:
					{
						system("cls");
						choice = menu_message("1 - Create user\n2 - Delete user\n3 - Modification user\n: ", 4);
						if (choice==1)
						{
							if (user.reg_user(usersDB))
								usersDB.push_back(user);
							cout << "User created!\n";
						}
						else if (choice == 2)
						{
							for (auto it : usersDB)
							{
								it.show_user();
							}
							if (user.del_user(usersDB))
							{
								cout << "User has been deleted\n";
								user.save_data_user(usersDB);
							}
							else cout << "User has not been find\n";
						}
						else
						{
							for (auto it : usersDB)
							{
								it.show_user();
							}
							if (user.edit_data(usersDB))
							{
								cout << "User has been edited\n";
								user.save_data_user(usersDB);
							}
							else cout << "User has not been edited\n";
						}
						break;
					}
					case VIEW_STAT:
					{
						choice = menu_message("1 - Viewing test results for specific tests\n2 - Viewing test results for specific users\n: ", 3);
						if (choice == 1)
						{
							system("cls");
							user.show_spec_test(usersDB);
						}
						else if (choice == 2)
						{
							system("cls");
							for (auto it : usersDB)
							{
								it.show_user();
							}
							user.show_spec_user(usersDB);
						}
						break;
					}
					case TEST_MANAGEMENT:
					{
						choice = menu_message("1 - Create test\n2 - Edit test\n3 - Print test\n4 - Return to main menu\n: ", 5);
						if (choice == 1)
						{
							system("cls");
							tst.init_test_questions(menu_message("Which test do you want to create\\edit\\show\n1 - Discrete mathematics\n2 - Mathematical analysis\n3 - Quantum physics\n4 - Mechanics\n: ", 5));
						}
						else if (choice == 2){
							system("cls");
							tst.edit_test_questions(menu_message("Which test do you want to edit:\n1 - Discrete mathematics\n2 - Mathematical analysis\n3 - Quantum physics\n4 - Mechanics\n: ", 5));
						}
						else if (choice == 3)
						{
							system("cls");
							tst.show_all_tests();
						}
						break;
					}
					case PREV_MENU_2:
					{
						system("cls");
						prevMenu = 0;
						break;
					}
					default:
						break;
					}
					}
				else {
					cout << "Incorrect login or password!\nReturn to main\n";
					system("pause");
					prevMenu = 0;
				}
				}
				break;
			}
		case EXIT:
		{
			cout << "EXIT\n";
			return 1;
			break;
		}
		}
		prevMenu = 1;
	}
	return 1;
 }