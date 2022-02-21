#pragma once
#include"Admin.h"
class User: public Admin
{
public:
	User() :Admin() { name = adress = phone = string(); pTS = new TestStat; };
	User(string s1, string s2, string s3, string s4, string s5) : Admin(s1, s2), name{ s3 }, adress{ s4 }, phone{ s5 }{};
	string get_login() { return decipher(login); }
	string get_pass() { return decipher(pass); }
	string get_name() { return name; }
	string get_category() { return pTS->categoryName; }
	int get_correct_answ() { return pTS->correctAnswers; }
	int get_mark() { return pTS->mark; }
	int get_percent() { return pTS->percentCorAns; }
	void change_name(string _name) { name = _name; }
	void change_adress(string _adress) { adress = _adress; }
	void change_phone(string _phone) { phone = _phone; }
	bool change_data_testDB(vector<User>& _db, int i);
	bool reg_user(vector<User>& _db);
	bool del_user(vector<User>& _db); 
	bool edit_data(vector<User>& _db);
	void load_data_user(vector<User>& _db);
	void save_data_user(vector<User>& _db);
	void show_user();
	void show_stat();
	void show_spec_test(vector<User>& _db);
	void show_spec_user(vector<User>& _db);
	void erase_file();
	void set_category_name(string _catName)
	{
		pTS->categoryName = _catName;
	}
	void set_corrAnsw(int _answ)
	{
		pTS->correctAnswers = _answ;
	}
	void set_mark(int _mark)
	{
		pTS->mark = _mark;
	}
	void set_percAnsw(int _percAnsw)
	{
		pTS->percentCorAns = _percAnsw;
	}
	void save_test_res();

protected:

	string name, adress, phone;
	struct TestStat
	{
		string categoryName;
		int correctAnswers, mark, percentCorAns;
	};

	friend ostream& operator << (ostream& out, const TestStat& _obj);
	TestStat* pTS;
	vector<TestStat> testDB;
};

ostream& operator<<(ostream& out, const User::TestStat& _obj)
{
	out << _obj.categoryName << "\nCorrect answers: " << _obj.correctAnswers << "\tPercentage correct answers: "
		<< _obj.percentCorAns << "%\tMark: " << _obj.mark << endl;
	return out;
}

 bool User::reg_user(vector<User>& _db) //init User data 
{
	 cout << "Login: ";
	 cin >> login;
	 for (size_t i = 0; i < _db.size(); i++)
	 {
		 if (login == _db[i].get_login())
		 {
			 cout << "This user is already in the system, try another login.\n";
			 return false;
		 }
	 }
	 cout << "Password: ";
	 cin >> pass;
	 cin.ignore();
	 cout << "Full name: ";
	 getline(cin, name, '\n');
	 cout << "Home adres: ";
	 getline(cin, adress, '\n');
	 cout << "Phone number: ";
	 getline(cin, phone, '\n');

	 this->login = encrypt(login);
	 this->pass = encrypt(pass);

	 return true;
}
 bool User::del_user(vector<User>& _db) 
 {
	 cout << "What user do you want to delete: ";
	 cin.ignore();
	 string _name;
	 getline(cin, _name);
	 for (size_t i = 0; i < _db.size(); i++)
	 {
		 if (_db[i].get_name() == _name)
		 {
			 _db.erase(_db.begin() + i);
			 return true;
		 }
	 }
	 return false;
 }
 bool User::change_data_testDB(vector<User>& _db, int i)
 {
	 cout << "Which test do you want to change. Enter number\n: ";
	 int testNumber;
	 cin >> testNumber;
	 testNumber--;
	 if (testNumber >= _db[i].testDB.size() || testNumber < 0)
	 {
		 cout << "Bad choice\n";
		 return false;
	 }
	 int newData,choice;
	 choice = menu_message("What data do you want to change?\n1 - Correct answers\n2 - Percentage correct answers\n3 - Mark\n: ", 4);
	 if (choice == 1)
	 {
		 cout << "Enter new data: ";
		 cin >> newData;
		 _db[i].testDB[testNumber].correctAnswers = newData;
		 return true;
	 }
	 else if (choice == 2)
	 {
		 cout << "Enter new data: ";
		 cin >> newData;
		 _db[i].testDB[testNumber].percentCorAns = newData;
		 return true;
	 }
	 else
	 {
		 cout << "Enter new data: ";
		 cin >> newData;
		 _db[i].testDB[testNumber].mark = newData;
		 return true;
	 }
 }
 bool User::edit_data(vector<User>& _db)
 {
	 cout << "What user do you want to change?\n: ";
	 cin.ignore();
	 string tmp;
	 getline(cin, tmp);
	 int i = -1;
	 for (int j=0; j < _db.size(); j++)
	 {
		 if (_db[j].get_name() == tmp)
		 {
			 i = j;
			 break;
		 }
	 }
	 if (i < 0)
	 {
		 cout << "User is not found\n";
		 return false;
	 }

	 switch (menu_message("What data do you want to change?\n1 - Login\n2 - Password\n3 - Name\n4 - Adress\n5 - Phone number\n6 - Test results\n: ", 7) )
	 {
	 case 1:
	 {
		 cout << "Enter new Login: ";
		 cin >> tmp; 
		 _db[i].change_login(tmp);
		 return true;
	 }
	 break;
	 case 2:
	 {
		 cout << "Enter new Password: ";
		 cin >> tmp; 
		 _db[i].change_pass(tmp);
		 return true;
	 }
	 break;
	 case 3:
	 {
		 cin.ignore();
		 cout << "Enter new Name: ";
		 getline(cin, tmp);
		 _db[i].change_name(tmp);
		 return true;
	 }
	 break;
	 case 4:
	 {
		 cin.ignore();
		 cout << "Enter new Adress: ";
		 getline(cin, tmp);
		 _db[i].change_adress(tmp);
		 return true;
	 }
	 break;
	 case 5:
	 {
		 cin.ignore();
		 cout << "Enter new Phone number: ";
		 getline(cin, tmp);
		 _db[i].change_phone(tmp);
		 return true;
	 }
	 break;
	 case 6:
	 {
		 _db[i].show_stat();
		 if (change_data_testDB(_db, i))
			 return true;
	 }
	 break;
	 default:
		 break;
	 }
	 return false;
 }
 void User::save_data_user(vector<User>& _db) //save data to binary file 
 {
	 erase_file();
	 char end = '#';
	 ofstream file(usersPath, ios::binary | ios::app);
	 if (!file.is_open())
	 {
		 cerr << "File was not opened!\n";
		 return;
	 }
	 for (auto it : _db) {

		 int strLen = it.login.size(); //login size
		 file.write((char*)&strLen, sizeof(int)); //write login size
		 file.write((char*)it.login.c_str(), it.login.size()); // write login

		 strLen = it.pass.size();
		 file.write((char*)&strLen, sizeof(int)); //write password size
		 file.write((char*)it.pass.c_str(), it.pass.size()); //write password

		 strLen = it.name.size();
		 file.write((char*)&strLen, sizeof(int)); //write name size
		 file.write((char*)it.name.c_str(), it.name.size()); //write name 

		 strLen = it.adress.size();
		 file.write((char*)&strLen, sizeof(int)); //write adress size
		 file.write((char*)it.adress.c_str(), it.adress.size());  //write adress

		 strLen = it.phone.size();
		 file.write((char*)&strLen, sizeof(int)); //write phone size
		 file.write((char*)it.phone.c_str(), it.phone.size()); //write phone
		 for (size_t i = 0; i < it.testDB.size(); i++)
		 {
			 file.write((char*)&it.testDB[i].correctAnswers, sizeof(int));

			 file.write((char*)&it.testDB[i].percentCorAns, sizeof(int));

			 file.write((char*)&it.testDB[i].mark, sizeof(int));

			 int strLen = it.testDB[i].categoryName.size();
			 file.write((char*)&strLen, sizeof(int));
			 file.write((char*)it.testDB[i].categoryName.c_str(), it.testDB[i].categoryName.size());
		 }
		 file.write((char*)&end, sizeof(end));
	 }
	 file.close();
 }
 void User::load_data_user(vector<User>& _db) //load data from binary file
 {
	// load_test_result();
	 char  end= '#';
	 int tmp;
	 ifstream file(usersPath, ios::binary);
	 if (!file.is_open())
	 {
		 cerr << "File was not opened!\n";
		 return;
	 }
	 while (file.read((char*)&tmp, sizeof(int))) //reading data from file until eof
	 {
		// end = '0';
		// file.read((char*)&tmp, sizeof(int)); //reading login size       
		 this->login.resize(tmp);
		 file.read((char*)this->login.c_str(), tmp); //reading login
	
		 file.read((char*)&tmp, sizeof(int)); //reading pass size  
		 this->pass.resize(tmp);
		 file.read((char*)this->pass.c_str(), tmp); //reading pass  
		
		 file.read((char*)&tmp, sizeof(int)); //reading name size 
		 this->name.resize(tmp);
		 file.read((char*)this->name.c_str(), tmp);	//reading name  
	
		 file.read((char*)&tmp, sizeof(int));	//reading adress size 
		 this->adress.resize(tmp);
		 file.read((char*)this->adress.c_str(), tmp);	//reading adress  
	
		 file.read((char*)&tmp, sizeof(int));	//reading phone size 
		 this->phone.resize(tmp);
		 file.read((char*)this->phone.c_str(), tmp);	//reading phone

		 while (file.read((char*)&pTS->correctAnswers, sizeof(int)))
		 {
			 file.read((char*)&pTS->percentCorAns, sizeof(int));

			 file.read((char*)&pTS->mark, sizeof(int));

			 file.read((char*)&tmp, sizeof(int));
			 pTS->categoryName.resize(tmp);
			 file.read((char*)pTS->categoryName.c_str(), tmp);

			 this->testDB.push_back(*pTS); // 

			 int t = file.peek(); // debug

			 if (file.peek() == end)
			 {
				 file.read((char*)&end, 1);
				 break;
			 }
		 }
		 _db.push_back(*this); // add data to verctor db
		 testDB.clear();
	 }
	 file.close();
 }
 void User::show_user() //print User data
 {
	cout << "Name: " << name << "\tAdres: " << adress << "\tPhone number: " << phone << endl;
 }
 void User::show_stat()
 {
	 int i = 1;
	 if (testDB.empty())
	 {
		 cout << "You didn't pass any test\n";
		 return;
	 }
	 for (auto it : testDB)
		 cout << i++ << ") " << it.categoryName << "\nCorrect answers: " << it.correctAnswers << "\tPercentage correct answers: "
		 << it.percentCorAns << "%\tMark: " << it.mark << endl << endl;
 }
 void User::show_spec_test(vector<User>& _db)
 {
	 int choice;
	 string catName;
	 cout << "1 - Discrete mathematics\n2 - Mathematical analysis\n3 - Quantum physics\n4 - Mechanics\n: ";
	 cin >> choice;
	 switch (choice)
	 {
	 case 1:
	 {
		 catName= test1.substr(0, test1.size() - 4);
	 }
	 break;
	 case 2:
	 {
		 catName = test2.substr(0, test2.size() - 4);
	 }
	 break;
	 case 3:
	 {
		 catName = test3.substr(0, test3.size() - 4);
	 }
	 break;
	 case 4:
	 {
		 catName = test4.substr(0, test4.size() - 4);
	 }
	 break;
	 default:
		 break;
	 }
	 for (auto it : _db)
	 {
		 for (size_t i = 0; i < it.testDB.size(); i++)
		 {
			 if (it.testDB[i].categoryName == catName)
			 {
				 it.show_user();
				 cout << it.testDB[i] << endl;
			 }
		 }
	 }
 }
 void User::show_spec_user(vector<User>& _db)
 {
	 cin.ignore();
	 string _name;
	 cout << "Enter user name\n: ";
	 getline(cin, _name);
	 for (auto it : _db)
	 {
		 if (it.get_name() == _name)
			 it.show_stat();
	 }
 }
 int chek_autorization(string _login, string _pass, vector<User> _db) //cheking for valid login and password
 {
	 for (size_t i = 0; i < _db.size(); i++)
	 {
		 if (_login == _db[i].get_login()&& _pass==_db[i].get_pass())
		 {
			 cout << "Authorization confirmed.\n";
			 //_db[i].show_user();
			 return i;
		 }
	 }
	 cout << "Invalid login or password\n";
	 return -1;
 }
 void User::save_test_res()
 {
	 this->testDB.push_back(*pTS);

 }
 void User::erase_file()
 {
	 ofstream file(usersPath, ios::trunc);
	 if (!file.is_open())
	 {
		 cerr << "File was not opened!\n";
		 return;
	 } 
	 file.close();
 }