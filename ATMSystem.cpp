#include<iostream>
#include<vector>
#include<fstream>
#include<string>

using namespace std;

struct stClient
{
	string Account_Number;
	string PIN_Code;
	string Client_Name;
	string Client_Phone;
	double Account_Balance = 0;
	bool MarkToDelete = false;

};

enum enATM_Menue
{
	Quick_Withdraw = 1, Normal_Withdraw = 2, Deposit = 3, Check_Balance = 4, Logout = 5
};


string ClientsFileName = "Client.txt";

stClient Current_Clinet;

void ShowMainMenueScreen();

vector <string> SplitLine(string Line, string Separater = "#//#")
{
	vector<string> sClient;
	short Pos = 0;
	string sWord;

	while ((Pos = Line.find(Separater)) != string::npos)
	{
		sWord = Line.substr(0, Pos);
		if (sWord != "")
		{
			sClient.push_back(sWord);
		}
		Line.erase(0, Pos + Separater.length());
	}
	if (Line != "")
	{
		sClient.push_back(Line);
	}
	return sClient;
}

stClient ConvertLineToRecord(string Line)
{
	vector <string> vCleint = SplitLine(Line);

	stClient Client;

	if (vCleint.size() >= 5)
	{
		Client.Account_Number = vCleint[0];
		Client.PIN_Code = vCleint[1];
		Client.Client_Name = vCleint[2];
		Client.Client_Phone = vCleint[3];
		Client.Account_Balance = stod(vCleint[4]);
	}
	return Client;
}

vector <stClient> LoadDataFromFile(string FileName)
{
	vector<stClient> vClients;
	fstream MyFile;

	MyFile.open(FileName, ios::in);//Reasd Mode

	if (MyFile.is_open())
	{
		string Line;
		while (getline(MyFile, Line))
		{
			if (Line != "")
			{
				vClients.push_back(ConvertLineToRecord(Line));
			}
		}
	}
	MyFile.close();

	return vClients;
}

bool ClientExisByAccount_NumberAndPIN_Cod(string Accoutn_Number, string PIN_Code, stClient &Client)
{
	vector <stClient> vClients = LoadDataFromFile(ClientsFileName);

	for (stClient& C : vClients)
	{

		if (Accoutn_Number == C.Account_Number && PIN_Code == C.PIN_Code)
		{
			Client = C;
			return true;
		}
	}
	return false;
}

bool LoadClientInfo(string Accoutn_Number, string PIN_Code)
{
	if (ClientExisByAccount_NumberAndPIN_Cod(Accoutn_Number, PIN_Code, Current_Clinet))
		return true;
	else
		return false;
}


//=================================
//ATM Menue.
//=================================


string ConvertRecordToLine(stClient Client, string Separater = "#//#")
{
	string Line;

	Line += Client.Account_Number + Separater;
	Line += Client.PIN_Code + Separater;
	Line += Client.Client_Name + Separater;
	Line += Client.Client_Phone + Separater;
	Line += to_string(Client.Account_Balance);

	return Line;
}


void SaveClientToFile(string FileNmae, vector <stClient>& vClient)
{
	fstream Myfile;

	Myfile.open(FileNmae, ios::out);//Wriet Mode.

	if (Myfile.is_open())
	{
		for (stClient& C : vClient)
		{
			Myfile << ConvertRecordToLine(C) << "\n";
		}
	}
	
	Myfile.close();
}

void DepositBalanceClient(vector <stClient> &vClients, double Amount)
{
	char Anser = 'n';
	
	cout << "\n\nAre you sur? you want to do this transaction? [y/n]  ";
	cin >> Anser;

	if (tolower(Anser) == 'y')
	{
		for (stClient& C : vClients)
		{
			if(C.Account_Number == Current_Clinet.Account_Number)
		    {
				C.Account_Balance += Amount;

				SaveClientToFile(ClientsFileName, vClients);
				cout << "\n\nDon Successfully, Account Balance: " << C.Account_Balance << endl;
				break;
		    }
		}
	}
	
}


int ReadDepositOption()
{
	int Amount = 0;

	do
	{
		cout << "\nEnter a positive deposit amount? ";
		cin >> Amount;
	} while (Amount < 0);
	
	
	return Amount;
}

void PerformDepositOption()
{
	int DepositAmount = ReadDepositOption();

	vector <stClient> vClients = LoadDataFromFile(ClientsFileName);
	DepositBalanceClient(vClients, DepositAmount);
	Current_Clinet.Account_Balance += DepositAmount;
}



void ShowDepositScreen()
{
	cout << "================================\n";
	cout << "\tDeposit Screen\n";
	cout << "================================\n";

	vector <stClient> vClients = LoadDataFromFile(ClientsFileName);

	double Amount;
	cout << "\nPlease enter the Amount of the Deposit?  ";
	cin >> Amount;


	DepositBalanceClient(vClients, Amount);
}

int ReadWithdrawAmount()
{
	int Amount;
	do
	{
		cout << "\n enter an Amount Multiple of 5`s  ";
		cin >> Amount;

	} while (Amount % 5 != 0);

	return Amount;

}

void ShowNormalWithDraw();

void PerformNormalWithdrawOption()
{
	int WithdrawBalance = ReadWithdrawAmount();

	while (WithdrawBalance > Current_Clinet.Account_Balance)
	{
		cout << "\nThe Amount Exceeds the balance, make another choice" << endl;
		cout << "\n\nPress anykey to continue...\n";
		system("Pause>0");
		ShowNormalWithDraw();
	}

	vector <stClient> vClient = LoadDataFromFile(ClientsFileName);
	DepositBalanceClient(vClient, WithdrawBalance * -1);
	Current_Clinet.Account_Balance -= WithdrawBalance;
}

void ShowNormalWithDraw()
{
	cout << "================================\n";
	cout << "\tNormal WithDraw\n";
	cout << "================================\n";

	PerformNormalWithdrawOption();
}

short GetQuikWithdrawAmount(short Choice)
{
	switch (Choice)
	{
	case 1:
			return 20;
	case 2:
		return 50;

	case 3:
		return 100;

	case 4:
		return 200;

	case 5:
		return 400;

	case 6:
		return 600;

	case 7:
		return 800;

	case 8:
		return 1000;

	default: 
		return 0;


	}
}

short ReadQuikWithdrawOption()
{
	short Option;
	do
	{
		cout << "\nEnter what you want to do? [1 to 8]?  ";
		cin >> Option;

	} while (Option < 0 || Option > 8);

	return Option;
}

void ShowQuikWithDrawScreen();

void PerformQuikWithDrawMenue(short QuikWithdrawOption)
{
	if (QuikWithdrawOption == 9)
	{
		return;
	}

	short WithdrawBalance = GetQuikWithdrawAmount(QuikWithdrawOption);

	if (WithdrawBalance > Current_Clinet.Account_Balance)
  	{
		cout << "\nThe Amount Exceeds the balance, make another choice" << endl;

		cout << "\n\nPress anykey to countinue...\n";
		system("paose>0");
		ShowQuikWithDrawScreen();
	}

	vector <stClient> vClient = LoadDataFromFile(ClientsFileName);
	DepositBalanceClient(vClient, WithdrawBalance * -1);
	Current_Clinet.Account_Balance -= WithdrawBalance;
}

void ShowQuikWithDrawScreen()
{
	cout << "=======================================\n";
	cout << "\tQuik WithDraw\n";
	cout << "=======================================\n";
	cout <<
		"\t[1] 20\t\t[2] 50\n"
		"\t[3] 100\t\t[4] 200\n"
		"\t[5] 400\t\t[6] 600\n"
		"\t[7] 800\t\t[8] 1000\n"
		"\t[9] Exit\n";
	cout << "=======================================\n";

	cout << "Your Balance is: " << Current_Clinet.Account_Balance << endl;
	
	PerformQuikWithDrawMenue(ReadQuikWithdrawOption());
	
}



void ShowCheckBalanceScreen()
{
	cout << "================================\n";
	cout << "\tCheck Balance Screen\n";
	cout << "================================\n";

	cout << "\nYour Account Balance is: " << Current_Clinet.Account_Balance;

}

void GoBackTo_ATM_MainMenue()
{
	cout << "\n\n\n\nPrass any key to back to ATM Main Menue...";
	system("pause>0");
	ShowMainMenueScreen();
}

short ReadClientChoice()
{
	cout << "choose What do you want to do? [1 to 5]?  ";
	short Choose;
	cin >> Choose;
	return Choose;
}

void LoginScreen()
{
	bool LoginFalid = false;
	string Account_Number, PIN_Code;

	do
	{
		system("cls");
		cout << "--------------------------------\n";
		cout << "\tLogin Screen\n";
		cout << "--------------------------------\n";

		if (LoginFalid)
		{
			cout << "Invalid Account Number/Password!\n";
		}

		cout << "Enter Account Number?  ";
		cin >> Account_Number;

		cout << "\n Enter PIN Code?  ";
		cin >> PIN_Code;

		LoginFalid = !LoadClientInfo(Account_Number, PIN_Code);

	} while (LoginFalid);

	ShowMainMenueScreen();
}



void PerforATM_MainMenueOption(enATM_Menue Choice)
{
	switch (Choice)
	{
    	case enATM_Menue::Quick_Withdraw:
			system("cls");
			ShowQuikWithDrawScreen();
			GoBackTo_ATM_MainMenue();
			break;

		case enATM_Menue::Normal_Withdraw:
			system("cls");
			ShowNormalWithDraw();
			GoBackTo_ATM_MainMenue();
			break;


		case enATM_Menue::Deposit:
			system("cls");
			ShowDepositScreen();
			GoBackTo_ATM_MainMenue();
			break;


		case enATM_Menue::Check_Balance:
			system("cls");
			ShowCheckBalanceScreen();
			GoBackTo_ATM_MainMenue();
			break;


		case enATM_Menue::Logout:
			system("cls");
			LoginScreen();
			break;
	}
}


void ShowMainMenueScreen()
{
	system("cls");
	cout << "==============================================\n";
	cout << "\t\tATM Main Menue Screen\n";
	cout << "==============================================\n";
	cout << "\t[1] Quick Withdraw.\n";
	cout << "\t[2] Normal Withdraw.\n";
	cout << "\t[3] Deposit.\n";
	cout << "\t[4] Check Balance.\n";
	cout << "\t[5] Logout.\n";
	cout << "==============================================\n";

	PerforATM_MainMenueOption(enATM_Menue(ReadClientChoice()));
}

int main()
{
	LoginScreen();

	return 0;
}
