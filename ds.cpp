#include <iostream>
#include<string>
#include<fstream>
#include<vector>
#include<iomanip>
#include "Bank1.h"
using namespace std;

struct stClients
{
	string AccountNumber;
	string name;
	string pincode;
	string phonenumber;
	int balance;
};
struct stUsers
{
	string username;
	string password;
	int perms;
};
enum enPerms { Showclientlist = 0, addnewclient = 1, 
	removeclient = 2,
	updateclient = 3, findclient = 4,
	showtransactiosn = 5, manageusers = 6
};
	

void StartProgram();
string ClientsRecordToLine(stClients client, string delim = "#//#")
{
	string s1;
	s1 += client.AccountNumber + delim;
	s1 += client.name + delim;
	s1 += client.phonenumber + delim;
	s1 += client.pincode + delim;
	s1 += to_string(client.balance);
	return s1;
}
void OverWriteclientsDataToFile(vector<stClients>& clients, string path = "C:\\Users\\ASHRAF\\Desktop\\c++ creted files\\myfile.txt")
{
	fstream My_file(path, ios::out);
	if (My_file.is_open())
	{
		for (stClients i : clients)
		{
			My_file << ClientsRecordToLine(i) << endl;
		}

	}
	My_file.close();
}
string JoinString(vector<string> clientdata, string delim)
{
	string s1 = "";
	for (short i = 0; i < clientdata.size() - 1; i++)
	{
		s1 += clientdata[i] + delim;
	}
	s1 += clientdata[clientdata.size() - 1];
	return s1;
}
vector<string> SplitString(string S1, string Delim)
{
	vector<string> vString;
	short pos = 0;
	string sWord;
	while ((pos = S1.find(Delim)) != std::string::npos)
	{
		sWord = S1.substr(0, pos);
		if (sWord != "")
		{
			vString.push_back(sWord);
		}
		S1.erase(0, pos + Delim.length());
	}
	if (S1 != "")
	{
		vString.push_back(S1); // it adds last word of the string.
	}
	return vString;
}
stClients ClientsLineToRecord(string line, string delim = "#//#")
{
	stClients client;
	vector <string> clientinfo;
	clientinfo = SplitString(line, delim);

	if (clientinfo.size() != 5) {
		cerr << "Error: Malformed input, expected 5 fields but got " << clientinfo.size() << endl;
		for (int i = 0; i < clientinfo.size(); i++)
			cerr << "[" << i << "]: " << clientinfo[i] << endl;
		exit(1); // or return an empty client if you prefer
	}
	client.AccountNumber = clientinfo[0];
	client.name = clientinfo[1];
	client.phonenumber = clientinfo[2];
	client.pincode = clientinfo[3];
	client.balance = stoi(clientinfo[4]);

	return client;
}

vector <stClients> FillClientsVectorFromFile(string path)
{
	vector<stClients> clients;
	string line = "";
	fstream My_File(path, ios::in);
	stClients client;
	if (My_File.is_open())
	{
		while (getline(My_File, line))
		{
			if (line.empty()) {}
			else {
				client = ClientsLineToRecord(line);
				clients.push_back(client);
			}
		}
		My_File.close();
	}


	return clients;
}


void PrintHeaderForBalances(short Clients_count)
{

	cout << "                                       Client list (" << Clients_count << ") client(s)\n";
	cout << "---------------------------------------------------------------------------------------------------------\n";
	cout << "| " << left << setw(15) << "Account Number"
		<< "| " << setw(10) << "Client Name"
		//<< "| " << setw(25) << "Phone"
		//<< "| " << setw(15) << "Pincode"
		<< "| " << setw(10) << "Balance"
		<< "|\n";
	cout << "---------------------------------------------------------------------------------------------------------\n";
}
void PrintHeader(short Clients_count)
{

	cout << "                                       Client list (" << Clients_count << ") client(s)\n";
	cout << "---------------------------------------------------------------------------------------------------------\n";
	cout << "| " << left << setw(15) << "Account Number"
		<< "| " << setw(10) << "Client Name"
		<< "| " << setw(25) << "Phone"
		<< "| " << setw(15) << "Pincode"
		<< "| " << setw(10) << "Balance"
		<< "|\n";
	cout << "---------------------------------------------------------------------------------------------------------\n";
}
void Print_One_Client_For_Balances(stClients client)
{
	cout << "| " << left << setw(15) << client.AccountNumber
		<< "| " << setw(10) << client.name
		//<< "| " << setw(25) << client.pincode
		//<< "| " << setw(15) << client.phonenumber
		<< "| " << setw(10) << client.balance
		<< "|\n";
}
void Print_One_Client(stClients client)
{
	cout << "| " << left << setw(15) << client.AccountNumber
		<< "| " << setw(10) << client.name
		<< "| " << setw(25) << client.pincode
		<< "| " << setw(15) << client.phonenumber
		<< "| " << setw(10) << client.balance
		<< "|\n";
}
void PrintAllClients(vector <stClients>& clients)
{
	for (stClients i : clients)
	{
		Print_One_Client(i);
	}
}
vector <string> Update_Client_Data_From_user(string AN)
{
	vector<string> clientdata;
	string s1;
	clientdata.push_back(AN);
	cout << "name : " << endl;
	getline(cin >> ws, s1);
	clientdata.push_back(s1);
	cout << "pincode : " << endl;
	getline(cin, s1);
	clientdata.push_back(s1);
	cout << "phonenumber : " << endl;
	getline(cin, s1);
	clientdata.push_back(s1);
	cout << "balance : " << endl;
	getline(cin ,s1);
	clientdata.push_back(s1);
	return clientdata;
}
bool doesClientexict(vector<stClients> &clients,string AN)
{
	for(stClients &i :clients)
	{ 
		if (i.AccountNumber == AN)
		{
			return true;
		}
	
	}
	return false;
}
vector <string> Read_Client_Data_From_user(vector<stClients> &clients)
{
	vector<string> clientdata;
	string s1;
	cout << "AccountNumber : " << endl;
	getline(cin >> ws, s1);
	while (doesClientexict(clients, s1))
	{
		cout << "Account Number is taken please enter another one:\n";
		getline(cin >> ws, s1);
	}
	clientdata.push_back(s1);
	cout << "name : " << endl;
	getline(cin, s1);
	clientdata.push_back(s1);
	cout << "pincode : " << endl;
	getline(cin, s1);
	clientdata.push_back(s1);
	cout << "phonenumber : " << endl;
	getline(cin, s1);
	clientdata.push_back(s1);
	cout << "balance : " << endl;
	getline(cin ,s1);
	clientdata.push_back(s1);
	return clientdata;
}
short SearchClientBYAccountNUmberINvector(vector<stClients> &clients, string AN)
{
	for (short i=0;i<clients.size();i++)
	{
		if (clients[i].AccountNumber == AN)
		{
			return i;
		}
	}
	return -1;
}
 
// transactions section 

void Deposit(vector<stClients> &clients)
{
	string AN;
	int amount;
	cout << "Enter account number: \n";
	cin >> AN;
	short index;
	index = SearchClientBYAccountNUmberINvector(clients, AN);
	if (index != -1)
	{
		Print_One_Client(clients[index]);
		cout << "Enter the deposite amount: \n";
		cin >> amount;
		clients[index].balance += amount;
		cout << "Amount Deposited \n Account balance is now: " << clients[index].balance;
	}
	else
	{
		cout << "Account not found";
	}
	OverWriteclientsDataToFile(clients);
	system("pause");

}
void Withdraw(vector<stClients> &clients)
{
	string AN;
	int amount;
	cout << "Enter account number: \n";
	cin >> AN;
	short index;
	index = SearchClientBYAccountNUmberINvector(clients, AN);
	if (index != -1)
	{
		Print_One_Client(clients[index]);
		cout << "Enter the withdraw amount: \n";
		cin >> amount;
		while (amount > clients[index].balance) {
			cout << "\nAmount is too big please enter another amount";
			cin >> amount;
		}
		clients[index].balance -= amount;
		cout << "Amount withdrawed \n Account balance is now: " << clients[index].balance << endl;
	}
	else
	{
		cout << "Account not found";
	}
	OverWriteclientsDataToFile(clients);

	system("pause");

}
void ShowTotalBalances(vector<stClients> &clients)
{
	int totalbalances =0 ;
	PrintHeaderForBalances(clients.size());
	for (stClients i : clients)
	{
		Print_One_Client_For_Balances(i);
	}
	for (stClients i : clients)
	{
		totalbalances += i.balance;
	}
	cout << "\n              Total Balances is " << totalbalances;
	system("pause");

}
void ShowTransactionsMenu()
{

	cout << "========================================================\n";
	cout << "                     Transactons\n";
	cout << "========================================================\n";
	cout << "[1] Deposit\n";
	cout << "[2] Withdraw\n";
	cout << "[3] Total Balances\n";
	cout << "[4] Main menu\n";
	cout << "========================================================\n";

}
void Get_TransactionsChoice(vector<stClients> &clients,char &exittomain)
{
	short choice;
	cout << "Enter your answer[1-4]\n";
	cin >> choice;
	switch (choice)
	{
	case 1:
	{
		Deposit(clients);
		break;
	}
	case 2:
	{
		Withdraw(clients);
		break;

	}
	case 3:
	{
		ShowTotalBalances(clients);
		break;

	}
	case 4:
	{
		exittomain = 'y';
		break;

	}
	default:
		break;

	}
}
void TransactionSection(vector<stClients> &clients)
{
	char Backtomain = 'n';
	do {
		system("cls");
		ShowTransactionsMenu();
		Get_TransactionsChoice(clients, Backtomain);
	} while (toupper(Backtomain) != 'Y');
	//StartProgram();

}

// main menu section

void FindClient(vector<stClients>& clients)
{
	string AN;
	cout << "Enter account number: ";
	cin >> AN;
	short i;
	i = SearchClientBYAccountNUmberINvector(clients, AN);
	if (i != -1) {
		PrintHeader(1);
		Print_One_Client(clients[i]);
	}
	else
		cout << "account not found\n";
	system("pause");
}
void UpdateCLientData(vector<stClients> &clients)
{
	short accountindex;
	string AN;
	cout << "Enter the account number\n";
	cin >> AN;
	accountindex = SearchClientBYAccountNUmberINvector(clients, AN);
	PrintHeader(1);
	Print_One_Client(clients[accountindex]);
	clients[accountindex] = ClientsLineToRecord( JoinString( Update_Client_Data_From_user(AN),"#//#"));
	OverWriteclientsDataToFile(clients);
	cout << "\n Press any Key to go back...";
	system("pause");
}
void ShowMainMenu()
{

	cout << "========================================================\n";
	cout << "                    Bank project\n";
	cout << "========================================================\n";
	cout << "[1] Show clients list\n";
	cout << "[2] Add new client\n";
	cout << "[3] Delete client\n";
	cout << "[4] Update client\n";
	cout << "[5] Find client\n";
	cout << "[6] Transactions\n";
	cout << "[7] Manage users\n";
	cout << "[8] Logout\n";
	cout << "========================================================\n";

}
void Show_Clients_List(vector <stClients> &clients)
{
	PrintHeader(clients.size());
	PrintAllClients(clients);
//	cout << "\n Press any Key to go back...";


}
void Add_New_Client(vector <stClients> &clients)
{
	cout << "Add client data: \n";
	clients.push_back(ClientsLineToRecord(JoinString(Read_Client_Data_From_user(clients), "#//#")));
	OverWriteclientsDataToFile(clients);
	cout << "Client added successfully\n";
	cout << "\n Press any Key to go back...";
	system("pause");
}
void Remove_Client(vector <stClients>& clients)
{
	string AN;
	cout << "Enter the Account number: \n";
	cin >> AN;
	short account_index;
	account_index = SearchClientBYAccountNUmberINvector(clients, AN);
	if (account_index != -1)
	{
		PrintHeader(1);
		Print_One_Client(clients[account_index]);
		cout << "are you sure you want to delete it ?(y/n)";
		char deleteacc;
		cin >> deleteacc;
		if (toupper(deleteacc) == 'Y')
		{
			clients.erase(clients.begin() + account_index);
			OverWriteclientsDataToFile(clients);
			cout << "\n client deleted succsesfully\n";
		}
		
	}
	else {
		cout << "Account NOt found\n";
	}
	
	system("pause");
	
}
void DisplayExitscreen()
{
	system("cls");
	cout << "============================================================\n";
	cout << "                      PROGRAM EXIT\n";
	cout << "============================================================\n";
	/*system("pause");*/
}
string PrintLoginscreen(vector<stUsers> &users)
{
	system("cls");
	cout << "--------------------------------------------------------\n";
	cout << "                    LOG-IN                              \n";
	cout << "--------------------------------------------------------\n";
	string username, password;
	bool wronginfo = 0;
	do {
		cout << "Enter Your Username : ";
		getline(cin >> ws, username);
		cout << "Enter Your Password : ";
		cin >> password;
		for(stUsers & i : users)
		{
			if ((i.username == username) && (i.password == password))
			{
				return username;
			}
		}
		wronginfo = 1;
		cout << "Wrong Info Please try again\n";
	} while (wronginfo);
}

// manage users functions

string DetermineUserPerms()
{
	int perms = 0;
	char fullAcc = 'n';
	cout << "Do you wanna give this user full Access ?(y/n) " << endl;
	cin >> fullAcc;
	if (toupper(fullAcc) == 'Y')
	{
		perms = -1;
		return to_string(perms);
	}
	else {
		char choice = 'n';
		cout << "Do you want the user to be able to Show clients list?(y/n) : ";
		cin >> choice;
		if (toupper(choice) == 'Y')
			perms |= (1 << enPerms::Showclientlist);

		cout << "Do you want the user to be able to Add New Clients?(y/n) : ";
		cin >> choice;
		if (toupper(choice) == 'Y')
			perms |= (1 << enPerms::addnewclient);

		cout << "Do you want the user to be able to Remove Clients ?(y/n) : ";
		cin >> choice;
		if (toupper(choice) == 'Y')
			perms |= (1 << enPerms::removeclient);

		cout << "Do you want the user to be able to Search for clients?(y/n) : ";
		cin >> choice;
		if (toupper(choice) == 'Y')
			perms |= (1 << enPerms::findclient);

		cout << "Do you want the user to be able to Manage Transactions?(y/n) : ";
		cin >> choice;
		if (toupper(choice) == 'Y')
			perms |= (1 << enPerms::showtransactiosn);

		cout << "Do you want the user to be able to Manage Users?(y/n) : ";
		cin >> choice;
		if (toupper(choice) == 'Y')
			perms |= (1 << enPerms::manageusers);
	}

	return to_string(perms);
}
short SearchUserBYAccountNUmberINvector(vector<stUsers>& users, string UN)
{
	for (short i = 0; i < users.size(); i++)
	{
		if (users[i].username == UN)
		{
			return i;
		}
	}
	return -1;
}
string UsersRecordToLine(stUsers &user, string delim = "#//#")
{
	string s1;
	s1 += user.username+ delim;
	s1 += user.password+ delim;
	s1 += to_string(user.perms);
	return s1;
}
void OverWriteUserssDataToFile(vector<stUsers>& users, string path = "C:\\Users\\ASHRAF\\Desktop\\c++ creted files\\users.txt")
{
	fstream My_file(path, ios::out);
	if (My_file.is_open())
	{
		for (stUsers i : users)
		{
			My_file << UsersRecordToLine(i) << endl;
		}

	}
	My_file.close();
}
stUsers UsersLineToRecord(string line, string delim = "#//#")
{
	stUsers user;
	vector <string> userinfo;
	userinfo = SplitString(line, delim);

	if (userinfo.size() != 3) {
		cerr << "Error: Malformed input, expected 3 fields but got " << userinfo.size() << endl;
		for (int i = 0; i < userinfo.size(); i++)
			cerr << "[" << i << "]: " << userinfo[i] << endl;
		exit(1); // or return an empty client if you prefer
	}

	user.username = userinfo[0];
	user.password = userinfo[1];
	user.perms = stoi(userinfo[2]);


	return user;
}
bool doesUserexict(vector<stUsers>& users, string UN)
{
	for (stUsers& i : users)
	{
		if (i.username == UN)
		{
			return true;
		}

	}
	return false;
}
vector <stUsers> FillUsersVectorFromFile(string path)
{
	vector<stUsers> users;
	string line = "";
	fstream My_File(path, ios::in);
	stUsers user;
	if (My_File.is_open())
	{
		while (getline(My_File, line))
		{
			if (!line.empty())
			{
				user = UsersLineToRecord(line);
				users.push_back(user);
			}
		}
		My_File.close();
	}
	return users;
}
vector <string> Read_User_Data_From_user(vector<stUsers>& users)
{
	vector<string> userdata;
	string s1;
	cout << "Username : " << endl;
	getline(cin >> ws, s1);
	while (doesUserexict(users, s1))
	{
		cout << "User is already registered:\n";
		getline(cin >> ws, s1);
	}
	userdata.push_back(s1);
	cout << "Password : " << endl;
	getline(cin, s1);
	userdata.push_back(s1);
	// s1 should have the prem value here 
	s1 = DetermineUserPerms();
	userdata.push_back(s1);
	
	// get user permissions
	
	return userdata;
}
void Add_New_User(vector <stUsers>& users)
{
	cout << "Add user data: \n";
	users.push_back(UsersLineToRecord(JoinString(Read_User_Data_From_user(users), "#//#")));
	OverWriteUserssDataToFile(users);
	cout << "user added successfully\n";
	
}
void PrintHeaderForUsers()
{

	cout << "                                             Users list                                                  \n";
	cout << "---------------------------------------------------------------------------------------------------------\n";
	cout << "| " << left << setw(15) << "Username"
		<< "| " << setw(10) << "Password"
		<< "| " << setw(25) << "permissions"
		<< "|\n";
	cout << "---------------------------------------------------------------------------------------------------------\n";
}
void PrintOneUser(stUsers &user)
{
	cout << "| " << left << setw(15) << user.username
		<< "| " << setw(10) << user.password
		<< "| " << setw(25) << user.perms
		<< "|\n";
}
void PrintALlUsers(vector <stUsers> &users)
{
	for (stUsers i : users)
	{
		PrintOneUser(i);
	}
}
void ListUsers(vector <stUsers> &users)
{
	PrintHeaderForUsers();
	PrintALlUsers(users);
}
void Remove_User(vector <stUsers>& users)
{
	string UN;
	cout << "Enter the username: \n";
	cin >> UN;
	short account_index;
	account_index = SearchUserBYAccountNUmberINvector(users, UN);
	if (account_index != -1)
	{
		PrintHeaderForUsers();
		PrintOneUser(users[account_index]);
		cout << "are you sure you want to delete it ?(y/n)";
		char deleteacc;
		cin >> deleteacc;
		if (toupper(deleteacc) == 'Y')
		{
			users.erase(users.begin() + account_index);
			OverWriteUserssDataToFile(users);
			cout << "\n user deleted succsesfully\n";
		}

	}
	else {
		cout << "Account NOt found\n";
	}

	system("pause");

}
vector <string> Update_User_Data_From_user(vector<stUsers>users,string UN)
{
	vector<string> Userdata;
	string s1;
	cout << "Username : " << endl;
	getline(cin >> ws, s1);
	Userdata.push_back(s1);
	cout << "Password : " << endl;
	getline(cin, s1);
	Userdata.push_back(s1);
	s1 = DetermineUserPerms();
	Userdata.push_back(s1);
	
	return Userdata;
}
void Update_user(vector <stUsers>& users)
{ 
	short accountindex;
	string UN;
	cout << "Enter the username\n";
	getline(cin >> ws, UN);
	accountindex = SearchUserBYAccountNUmberINvector(users, UN);
	if (accountindex != -1) {
		PrintHeaderForUsers;
		PrintOneUser(users[accountindex]);
		users[accountindex] = UsersLineToRecord(JoinString(Update_User_Data_From_user(users,UN), "#//#"));
		OverWriteUserssDataToFile(users);
	}
	else {
		cout << "Account not found";
	}

}
void Find_User(vector<stUsers>& users)
{
	string UN;
	cout << "Enter The Username : ";
	getline(cin >> ws, UN);
	short i = SearchUserBYAccountNUmberINvector(users, UN);
	if (i != -1) {
		PrintOneUser(users[i]);
	}
	else {
		cout << "Account NOt found";
	}
}
void GetManageUsersChoice(vector <stUsers> &users,char &mainmenu)
{
	short choice;
	cout << "Enter a number [1-6]\n";
	cin >> choice;
	switch (choice)
	{
	case 1:
	{
		system("cls");
		ListUsers(users);
		cout << "\n Press any Key to go back...";
		system("pause>0");
		break;
	}
	case 2:
	{
		system("cls");
		Add_New_User(users);
		cout << "\n Press any Key to go back...";
		system("pause>0");
		break;

	}
	case 3:
	{
		system("cls");
		Remove_User(users);
		cout << "\n Press any Key to go back...";
		system("pause>0");
		break;
	}
	case 4:
	{
		system("cls");
		Update_user(users);
		cout << "\n Press any Key to go back...";
		system("pause>0");
		break;
	}
	case 5:
	{
		system("cls");
		Find_User(users);
		cout << "\n Press any Key to go back...";
		system("pause>0");
		break;
	}
	case 6:
	{
		mainmenu = 'y';
		break;
	}

	default:
		break;
	}
}

void ShowAccessDeniedMessage()
{
	cout << "\n------------------------------------\n";
	cout << "Access Denied, \nYou dont Have Permission To Do this, \nPlease Conact Your Admin.";
		cout << "\n------------------------------------\n";
}

void ShowManageUsersScreen()
{
	system("cls");
	cout << "=====================================================\n";
	cout << "                 Manage Users Screen                 \n";
	cout << "=====================================================\n";
	cout << "[1] List Users.\n";
	cout << "[2] Add New User.\n";
	cout << "[3] Delete User.\n";
	cout << "[4] Update User.\n";
	cout << "[5] Find User.\n";
	cout << "[6] Main Menu.\n";
	cout << "=====================================================\n";
}
void ManageUsersSection(vector <stUsers> &users)
{
	char Mainmenu = 'n';
	do {
		ShowManageUsersScreen();
		GetManageUsersChoice(users , Mainmenu);
	} while (toupper(Mainmenu) != 'Y');
}
void Get_User_choice(vector<stClients>& clients,char &exit, vector <stUsers> &users,string currentusername)
{
	short i;
	i = SearchUserBYAccountNUmberINvector(users, currentusername);
	short choice;
	cout << "Enter your answer[1-6]\n";
	cin >> choice;
	switch (choice)
	{
	case 1:
	{
		if (users[i].perms & (1 << enPerms::Showclientlist))
		{
			system("cls");
			Show_Clients_List(clients);
			system("pause");

		}
		else
		{
			system("cls");
			ShowAccessDeniedMessage();
				system("pause");
		}
		break;
	}
	case 2:
	{
		if (users[i].perms & (1 << enPerms::addnewclient)) 
		{
			system("cls");
			Add_New_Client(clients);
			system("pause");

		}
		else
		{
			system("cls");
			ShowAccessDeniedMessage();
			system("pause");
		}
		break;

	}
	case 3:
	{
		if (users[i].perms & (1 << enPerms::removeclient))
		{
			system("cls");
			Remove_Client(clients);
			system("pause");
		}
		else
		{
			system("cls");
			ShowAccessDeniedMessage();
			system("pause");
		}
		break;

	}
	case 4:
	{
		if (users[i].perms & (1 << enPerms::updateclient))
		{
			system("cls");
			UpdateCLientData(clients);
			system("pause");
		}
		else
		{
			system("cls");
			ShowAccessDeniedMessage();
			system("pause");
		}
		break;

	}
	case 5:
	{
		if (users[i].perms & (1 << enPerms::findclient)) {
			system("cls");
			FindClient(clients);
			system("pause");
		}
		else
		{
			system("cls");
			ShowAccessDeniedMessage();
			system("pause");
		}
		break;

	}
	
	case 6:
	{
		if (users[i].perms & (1 << enPerms::showtransactiosn)) {
			system("cls");
			TransactionSection(clients);
			

		}
		else
		{
			system("cls");
			ShowAccessDeniedMessage();
			system("pause");
		}
		break;

	}
	case 7:
	{
		if (users[i].perms & (1 << enPerms::manageusers)) {
			system("cls");
			ManageUsersSection(users);
		}
		else
		{
			system("cls");
			ShowAccessDeniedMessage();
			system("pause");
		}
		break;
	}
	case 8:
	{
		exit = 'y';
		break;
	}
	default:
		break;
	}
}

void StartProgram()
{
	vector<stClients> clients;
	clients = FillClientsVectorFromFile("C:\\Users\\ASHRAF\\Desktop\\c++ creted files\\myfile.txt");

	vector<stUsers> users;
	 users = FillUsersVectorFromFile("C:\\Users\\ASHRAF\\Desktop\\c++ creted files\\users.txt");
	 string currentusername;
	 currentusername = PrintLoginscreen(users);
	
	 char exitprogram = 'n';
	
	do {
		system("cls");
		ShowMainMenu();
		Get_User_choice(clients, exitprogram, users,currentusername);
	} while (toupper(exitprogram) != 'Y');
	DisplayExitscreen();
}

int main()
{
	StartProgram();
}
