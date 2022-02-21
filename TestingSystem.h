#pragma once
#include"User.h"
class TestingSystem
{
public:
	enum TestingSys
	{
		Discrete_Mathematics = 1, Mathematical_analysis, Quantum_physics, Mechanics, MAX_MARK = 12
	};
	TestingSystem()=default;
	void load_test(string path);
	void save_test(string path);
	void load_start_test (User& _obj, int choice);
	void init_test_questions(int choice);
	void init_question();
	void edit_test_questions(int choice);
	void edit_question(int index);
	void anwser_questions();
	void show_questions();
	void show_all_tests();
	bool chek_answer(int num)
	{
		if (num == answer)
			return true;
		return false;
	}
private:
	string question, answer_options;
	int answer, right;
	int count_questions;
	vector <TestingSystem> questions;
};
\\//
void TestingSystem::load_test(string path)
{
	int tmp;
	fstream file(path, ios::in | ios::binary);
	if (!file.is_open())
	{
		cerr << " File was not opepened!\n";
		return;
	}
	while (file.read((char*)&this->answer, sizeof(int)))
	{
		file.read((char*)&tmp, sizeof(int));
		this->question.resize(tmp);
		file.read((char*)this->question.c_str(), tmp);

		file.read((char*)&tmp, sizeof(int));
		this->answer_options.resize(tmp);
		file.read((char*)this->answer_options.c_str(), tmp);

		questions.push_back(*this);
	}
	file.close();
}

void TestingSystem::save_test(string path)
{
	fstream file(path, ios::out | ios::trunc | ios::binary);
	if (!file.is_open())
	{
		cerr << " File was not opepened!\n";
		return;
	}
	for (auto it : questions)
	{
		file.write((char*)&it.answer, sizeof(int));

		int strLen = it.question.size();
		file.write((char*)&strLen, sizeof(int));
		file.write((char*)it.question.c_str(), it.question.size());

		strLen = it.answer_options.size();
		file.write((char*)&strLen, sizeof(int));
		file.write((char*)it.answer_options.c_str(), it.answer_options.size());
	}
	file.close();
}
void TestingSystem::load_start_test(User& _obj, int _choice)
{
	string catName;
	switch (_choice)
	{
	case TestingSystem::Discrete_Mathematics:
	{
		load_test(test1);
		anwser_questions();
		catName = test1.substr(0,test1.size()-4);
	}
		break;
	case TestingSystem::Mathematical_analysis:
	{
		load_test(test2);
		anwser_questions();
		catName = test2.substr(0,test2.size()-4);
	}
		break;
	case TestingSystem::Quantum_physics:
	{
		load_test(test3);
		anwser_questions();
		catName = test3.substr(0,test3.size()-4);
	}
		break;
	case TestingSystem::Mechanics:
	{
		load_test(test3);
		anwser_questions();
		catName = test4.substr(0,test4.size()-4);
	}
		break;
	default:
		cout << "Bad choice\n";
		break;
	}
	_obj.set_category_name(catName);
	_obj.set_corrAnsw(right);
	_obj.set_percAnsw(right * 100 / questions.size());
	_obj.set_mark(right * MAX_MARK / questions.size());
	system("cls");
	cout << "Test done! Your result:\nCategory: " << _obj.get_category() << "\nCorrect answers: " << _obj.get_correct_answ() << "\tPercentage correct answers: "
		<< _obj.get_percent() << "%\tMark: " << _obj.get_mark() << endl;
	right = 0;
	questions.clear(); // ?
}


void TestingSystem::anwser_questions()
{
	int i = 1;
	for (auto it : questions)
	{
		cout << i++ << " question:\n" << it.question << "\nAnwer options:\n" << it.answer_options << "\nYour answer: ";
		int ans;
		cin >> ans;
		if (it.chek_answer(ans))
		{
			++right;
		}
	}
}

void TestingSystem::init_test_questions(int choice)
{
	cout << "Enter the number of questions in the test: ";
	cin >> count_questions;
	cin.ignore();
	switch (choice)
	{
	case TestingSystem::Discrete_Mathematics:
	{
		init_question();
		save_test(test1);
	}
		break;
	case TestingSystem::Mathematical_analysis:
	{
		init_question();
		save_test(test2);
	}
		break;
	case TestingSystem::Quantum_physics:
	{
		init_question();
		save_test(test3);
	}
		break;
	case TestingSystem::Mechanics:
	{
		init_question();
		save_test(test4);
	}
		break;
	default:
		cout << "Bad choice\n";
		break;
	}
	questions.clear();
}
 void TestingSystem::init_question()
{
	 string str1, str2;
	 int tmp;
	 for (size_t i = 0; i < count_questions; i++)
	 {
		 cout << "Enter question: \n";
		 getline(cin, str1);
		 cout << "Enter answer options: \n";
		 getline(cin, str2);
		 cout << "Enter the number of the correct answer: \n";
		 cin >> tmp; cin.ignore();

		 this->question = str1;
		 this->answer_options = str2;
		 this->answer = tmp;
		 questions.push_back(*this); 
	 }
}

 void TestingSystem::edit_test_questions(int choice)
 {
	 int index;
	 switch (choice)
	 {
	 case TestingSystem::Discrete_Mathematics:
	 {
		 load_test(test1);
		 show_questions();
		 cout << "Enter question number: ";
		 cin >> index;
		 if (index > questions.size())
		 {
			 cout << "Bad number\n";
			 return;
		 }
		 edit_question(index-1);
		 save_test(test1);
	 }
		 break;
	 case TestingSystem::Mathematical_analysis:
	 { 
		 load_test(test2);
		 show_questions();
		 cout << "Enter question number: ";
		 cin >> index;
		 if (index > questions.size())
		 {
			 cout << "Bad number\n";
			 break;
		 }
		 edit_question(index-1);
		 save_test(test2);
	 }
		 break;
	 case TestingSystem::Quantum_physics:
	 {
		 load_test(test3);
		 show_questions();
		 cout << "Enter question number: ";
		 cin >> index;
		 if (index > questions.size())
		 {
			 cout << "Bad number\n";
			 return;
		 }
		 edit_question(index-1);
		 save_test(test3);
	 }
		 break;
	 case TestingSystem::Mechanics:
	 {
		 load_test(test4);
		 show_questions();
		 cout << "Enter question number: ";
		 cin >> index;
		 if (index > questions.size())
		 {
			 cout << "Bad number\n";
			 return;
		 }
		 edit_question(index-1);
		 save_test(test4);
	 }
		 break;
	 default:
		 break;
	 }
	 questions.clear();
 }

 void TestingSystem::show_questions()
 {
	 system("cls");
	 int i = 1;
	 for (auto it : questions)
	 {
		 cout << i++ << " question:  " << it.question << "\nAnswer options: " << it.answer_options << "\nTrue answer: " << it.answer << endl;
		 cout << "\n";
	 }
 }

 void TestingSystem::show_all_tests()
 {

	 switch (menu_message("Which test do you want to create\\edit\\show\n1 - Discrete mathematics\n2 - Mathematical analysis\n3 - Quantum physics\n4 - Mechanics\n: ", 5))
	 {
	 case TestingSystem::Discrete_Mathematics:
	 {
		 load_test(test1);
		 show_questions();
	 }
	 break;
	 case TestingSystem::Mathematical_analysis:
	 {
		 load_test(test2);
		 show_questions();
	 }
	 break;
	 case TestingSystem::Quantum_physics:
	 {
		 load_test(test3);
		 show_questions();
	 }
	 break;
	 case TestingSystem::Mechanics:
	 {
		 load_test(test4);
		 show_questions();
	 }
	 break;
	 default:
		 break;
	 }
	 questions.clear();
 }

 void TestingSystem::edit_question(int index)
 {
	 cin.ignore();
	 string newQuestion, newAnswerOpt;
	 int newAnswer;
	 cout << "Enter new question: ";
	 getline(cin, newQuestion);
	 questions[index].question = newQuestion;
	 cout << "Enter new answer options: ";
	 getline(cin, newAnswerOpt);
	 questions[index].answer_options = newAnswerOpt;
	 cout << "Enter new answer: ";
	 cin >> newAnswer;
	 questions[index].answer = newAnswer;

 }