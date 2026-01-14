#include <iostream>
#include <ctime>
#include <windows.h>

using namespace std;

void Main_Menu();

short Array_Number[3][3] = { {1,2,3} , {4,5,6} , {7,8,9} };

char Array_X_O[3][3] = { {'a','a','a'} , {'a','a','a'} , {'a','a','a'} };

short Who_Is_Player = 0;

void Play_Tone(short Frequency, short Duration) { Beep(Frequency, Duration); }

void Tone_Place_O() { Play_Tone(392, 120); }

void Tone_Place_X() { Play_Tone(329, 120); }

void Tone_Win() {
	Play_Tone(329, 160);
	Play_Tone(392, 160);
	Play_Tone(523, 160);
}

void Tone_Error() { Play_Tone(220, 200); }

void Tone_Move() { Play_Tone(261, 120); }

int Random_Number(int From, int To) {
	int Random_Number = 0;
	Random_Number = rand() % (To - From + 1) + From;
	return  Random_Number;
}

short Read_Choice_Another_Player() {
	short Choice = 0;
	do {
		cout << "\n\t\t\t\t\t\t \033[33mChoose The Player : \033[34m";
		cin >> Choice;
		Tone_Move();
	} while (Choice > 2 || Choice < 1);

	return Choice;
}

enum en_Choice_Player { Player = 1, Computer = 2 };

enum en_Player_Winner { Player_O_1 = 1, Player_X_2 = 2, Computer_X = 3, No_Winner = 4 };

bool Is_Their_Any_Element_In_Array_X_O(short Choice) {

	if (Choice >= 1 && Choice <= 3) {
		if (Array_X_O[0][Choice - 1] == 'X' || Array_X_O[0][Choice - 1] == 'O')
			return true;
	}
	else if (Choice >= 4 && Choice <= 6) {

		short j = 0;
		switch (Choice)
		{
		case 4: j = 0; break;
		case 5: j = 1; break;
		case 6: j = 2; break;
		}

		if (Array_X_O[1][j] == 'X' || Array_X_O[1][j] == 'O')
			return true;
	}
	else if (Choice >= 7 && Choice <= 9) {

		short j = 0;
		switch (Choice)
		{
		case 7: j = 0; break;
		case 8: j = 1; break;
		case 9: j = 2; break;
		}

		if (Array_X_O[2][j] == 'X' || Array_X_O[2][j] == 'O')
			return true;
	}

	return false;
}

short Read_Choice_O() {
	short Choice = 0;
	do {
		cout << "\n\033[33m\t    Chose Your Position - Player <\033[32mO\033[0m\033[33m> : \033[0m \033[36m";
		cin >> Choice;
		Tone_Place_O();
	} while (Choice > 9 || Choice < 1 || (Is_Their_Any_Element_In_Array_X_O(Choice) == true));
	return  Choice;
}

short Read_Choice_X() {
	short Choice = 0;
	do {
		cout << "\n\033[33m\t    Chose Your Position - Player <\033[31mX\033[0m\033[33m> : \033[0m \033[36m";
		cin >> Choice;
		Tone_Place_X();
	} while (Choice > 9 || Choice < 1 || (Is_Their_Any_Element_In_Array_X_O(Choice) == true));
	return  Choice;
}

short Read_Choice_computer_X() {
	short Choice = 0;
	do {
		cout << "\n\033[33m\t    Chose Your Position - Computer <\033[31mX\033[0m\033[33m> : \033[0m \033[36m";
		Choice = Random_Number(1, 9);
		cout << Choice;
		Tone_Place_X();
	} while ((Is_Their_Any_Element_In_Array_X_O(Choice) == true));
	return  Choice;
}

void Draw_Main_Menu() {

	cout << " \n\n\t\t\t\033[35m __________\033[0m\n";

	for (short i = 0; i < 3; i++) {

		cout << "\t\t\t\033[35m| \033[0m";

		for (short j = 0; j < 3; j++) {

			cout << "\033[36m" << Array_Number[i][j] << "\033[0m" << "  ";

		}

		cout << "\033[35m|\033[0m" << endl;
	}
	cout << "  \t\t\t\033[35m __________\033[0m\n";
}

void Draw_Menu_After_Turn(short Number, char Choice) {

	cout << " \n\n\t\t\t\033[35m __________\033[0m\n";

	for (short i = 0; i < 3; i++) {

		cout << "\t\t\t\033[35m| \033[0m";

		for (short j = 0; j < 3; j++) {

			if (Number == Array_Number[i][j]) {

				Array_X_O[i][j] = Choice;

				if (Choice == 'X')
					cout << "\033[31m" << Array_X_O[i][j] << "\033[0m" << "  ";
				else if (Choice == 'O')
					cout << "\033[32m" << Array_X_O[i][j] << "\033[0m" << "  ";

			}
			else if (Array_X_O[i][j] == 'X' || Array_X_O[i][j] == 'O') {

				if (Array_X_O[i][j] == 'X')
					cout << "\033[31m" << Array_X_O[i][j] << "\033[0m" << "  ";
				else if (Array_X_O[i][j] == 'O')
					cout << "\033[32m" << Array_X_O[i][j] << "\033[0m" << "  ";

			}
			else {
				cout << "\033[36m" << Array_Number[i][j] << "\033[0m" << "  ";
			}
		}

		cout << "\033[35m|\033[0m" << endl;
	}
	cout << " \t\t\t\033[35m __________\033[0m\n";
}

en_Player_Winner Check_Winner() {

	if (Array_X_O[0][0] == 'O') {  // 1 


		if (Array_X_O[0][1] == 'O' && Array_X_O[0][2] == 'O') // 1 2 3 
			return en_Player_Winner::Player_O_1;
		else if (Array_X_O[1][0] == 'O' && Array_X_O[2][0] == 'O')  // 1  4  7 
			return en_Player_Winner::Player_O_1;
		else if (Array_X_O[1][1] == 'O' && Array_X_O[2][2] == 'O') // 1 5 9 
			return en_Player_Winner::Player_O_1;

	}


	if (Array_X_O[2][2] == 'O') { // 9


		if (Array_X_O[1][2] == 'O' && Array_X_O[0][2] == 'O') // 9 6 3 
			return en_Player_Winner::Player_O_1;
		else if (Array_X_O[2][0] == 'O' && Array_X_O[2][1] == 'O')  // 9 8 7 
			return en_Player_Winner::Player_O_1;


	}

	if (Array_X_O[0][2] == 'O') { //  3 5 7
		if (Array_X_O[1][1] == 'O' && Array_X_O[2][0] == 'O')
			return en_Player_Winner::Player_O_1;
	}

	if (Array_X_O[1][0] == 'O') { //4 5 6 
		if (Array_X_O[1][1] == 'O' && Array_X_O[1][2] == 'O')
			return en_Player_Winner::Player_O_1;
	}

	if (Array_X_O[0][1] == 'O' && Array_X_O[1][1] == 'O' && Array_X_O[2][1] == 'O') {  // 2 5 8 
		return en_Player_Winner::Player_O_1;
	}

	/////////////////////////////////////////////////////////////////////////////////

	if (Who_Is_Player == 1) {

		if (Array_X_O[0][0] == 'X') {  // 1 


			if (Array_X_O[0][1] == 'X' && Array_X_O[0][2] == 'X') // 1 2 3 
				return en_Player_Winner::Player_X_2;
			else if (Array_X_O[1][0] == 'X' && Array_X_O[2][0] == 'X')  // 1  4  7 
				return en_Player_Winner::Player_X_2;
			else if (Array_X_O[1][1] == 'X' && Array_X_O[2][2] == 'X') // 1 5 9 
				return en_Player_Winner::Player_X_2;

		}

		if (Array_X_O[2][2] == 'X') { // 9


			if (Array_X_O[1][2] == 'X' && Array_X_O[0][2] == 'X') // 9 6 3 
				return en_Player_Winner::Player_X_2;
			else if (Array_X_O[2][0] == 'X' && Array_X_O[2][1] == 'X')  // 9 8 7 
				return en_Player_Winner::Player_X_2;


		}


		if (Array_X_O[0][2] == 'X') { //  3 5 7
			if (Array_X_O[1][1] == 'X' && Array_X_O[2][0] == 'X')
				return en_Player_Winner::Player_X_2;
		}


		if (Array_X_O[1][0] == 'X') { //4 5 6 
			if (Array_X_O[1][1] == 'X' && Array_X_O[1][2] == 'X')
				return en_Player_Winner::Player_X_2;
		}

		if (Array_X_O[0][1] == 'X' && Array_X_O[1][1] == 'X' && Array_X_O[2][1] == 'X') {  // 2 5 8 
			return en_Player_Winner::Player_X_2;
		}
	}
	else if (Who_Is_Player == 2) {

		if (Array_X_O[0][0] == 'X') {  // 1 


			if (Array_X_O[0][1] == 'X' && Array_X_O[0][2] == 'X') // 1 2 3 
				return en_Player_Winner::Computer_X;
			else if (Array_X_O[1][0] == 'X' && Array_X_O[2][0] == 'X')  // 1  4  7 
				return en_Player_Winner::Computer_X;
			else if (Array_X_O[1][1] == 'X' && Array_X_O[2][2] == 'X') // 1 5 9 
				return en_Player_Winner::Computer_X;

		}

		if (Array_X_O[2][2] == 'X') { // 9


			if (Array_X_O[1][2] == 'X' && Array_X_O[0][2] == 'X') // 9 6 3 
				return en_Player_Winner::Computer_X;
			else if (Array_X_O[2][0] == 'X' && Array_X_O[2][1] == 'X')  // 9 8 7 
				return en_Player_Winner::Computer_X;


		}


		if (Array_X_O[0][2] == 'X') { //  3 5 7
			if (Array_X_O[1][1] == 'X' && Array_X_O[2][0] == 'X')
				return en_Player_Winner::Computer_X;
		}


		if (Array_X_O[1][0] == 'X') { //4 5 6 
			if (Array_X_O[1][1] == 'X' && Array_X_O[1][2] == 'X')
				return en_Player_Winner::Computer_X;
		}

		if (Array_X_O[0][1] == 'X' && Array_X_O[1][1] == 'X' && Array_X_O[2][1] == 'X') {  // 2 5 8 
			return en_Player_Winner::Computer_X;
		}
	}

	return en_Player_Winner::No_Winner;

}

void Play_X_O() {
	Draw_Main_Menu();
	short Choice_Number;


	for (short i = 1; i <= 9; i++) {
		if (i % 2 != 0) {
			Choice_Number = Read_Choice_O();
			system("cls");
			Draw_Menu_After_Turn(Choice_Number, 'O');

			if (Check_Winner() == en_Player_Winner::Player_O_1) {
				cout << "\n\033[36m\t    The Winner Is\033[0m \033[35mPlayer <\033[32mO\033[35m> , \033[33mCongratulations :-)\033[0m ";
				Tone_Win();
				return;
			}
		}
		else if (i % 2 == 0) {
			if (Who_Is_Player == 1) {
				Choice_Number = Read_Choice_X();
				system("cls");
				Draw_Menu_After_Turn(Choice_Number, 'X');

				if (Check_Winner() == en_Player_Winner::Player_X_2) {
					cout << "\n\033[36m\t    The Winner Is\033[0m \033[35mPlayer <\033[31mX\033[35m> , \033[33mCongratulations :-)\033[0m ";
					Tone_Win();
					return;
				}
			}
			else if (Who_Is_Player == 2) {
				Choice_Number = Read_Choice_computer_X();
				system("cls");
				Draw_Menu_After_Turn(Choice_Number, 'X');

				if (Check_Winner() == en_Player_Winner::Computer_X) {
					cout << "\n\033[36m\t    The Winner Is\033[0m \033[35mComputer <\033[31mX\033[35m> , \033[33mCongratulations :-)\033[0m ";
					Tone_Win();
					return;
				}
			}
		}
	}

	cout << "\n\t\t\033[32m\t No Winner \033[31m:-( \033[0m";
	Tone_Error();
}

void Reset_Game() {
	for (short i = 0; i < 3; i++) {
		for (short j = 0; j < 3; j++) {
			Array_X_O[i][j] = 'a';
		}
	}
}

void Start_Game() {

	char Play_Again = 'Y';

	while (Play_Again == 'Y') {
		system("cls");
		Reset_Game();
		Play_X_O();
		cout << "\n\n\033[33m\t     Do You Want To Play Again (Y/N) : \033[34m";
		cin >> Play_Again;
		Tone_Move();
		Play_Again = toupper(Play_Again);
	}
}

void Go_Back_To_Main_Menu() {
	cout << "\n\n\t\033[36m   Press Any Key To Go Back To Main Menu...\033[0m";
	system("pause>0");
	Tone_Move();
	Main_Menu();
}

void Perform_Main_Menu(en_Choice_Player Choice_Player) {
	switch (Choice_Player) {
	case en_Choice_Player::Player:
		Who_Is_Player = Player;
		Start_Game();
		Go_Back_To_Main_Menu();
		break;
	case en_Choice_Player::Computer:
		Who_Is_Player = Computer;
		Start_Game();
		Go_Back_To_Main_Menu();
		break;
	}
}

void Main_Menu() {
	system("cls");
	cout << "\n\n\n\n\t\t\t\t\t\t\033[31m+++++++++++++++++++++++++\033[0m\n";
	cout << "\t\t\t\t\t\t\033[31m| \033[32mChoose The Player You \033[31m|\n\t\t\t\t\t\t\033[31m| \033[32mWant To Play With     \033[31m|\n";
	cout << "\t\t\t\t\t\t\033[31m+++++++++++++++++++++++++\033[0m\n";
	cout << "\t\t\t\t\t\t\033[31m|   \033[35m1) \033[36mPlayer           \033[31m|\n";
	cout << "\t\t\t\t\t\t\033[31m|   \033[35m2) \033[36mComputer         \033[31m|\n";
	cout << "\t\t\t\t\t\t\033[31m+++++++++++++++++++++++++\033[0m\n";
	Perform_Main_Menu((en_Choice_Player)Read_Choice_Another_Player());
}

int main() {

	Main_Menu();

	system("pause>0");
	return 0;
}