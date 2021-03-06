#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <ctime>
#include <string>
#include <fstream>

using namespace std;

fstream statistics, records, about_game;
string name;
int moves, difficult, n, user_number;
int **m = nullptr;
long int final_time, sec, minn, hour;

struct Records {
	string name;
	int level,
		time,
		moves;
};

enum Keys {
	UP = 72,
	LEFT = 75,
	RIGHT = 77,
	DOWN = 80,
	ENTER = 13
};

enum ConsoleColor {
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};

void setColor(int background, int text);
void gotoxy(int x, int y);
void game(int **m, int n);
void show_frame(int **m, int n);
void show_cells(int **m, int n);
void show_about_game();
void inp_statistics(int time, int moves);
void out_statistics();
void inp_records(string name, int level, int time, int moves);
void out_records();
void move(int **m, int n, int &moves);
void sec_to_min(long int &sec, long int &min, long int &hour);
void start_game();
int menu();
int difficulty_level();
bool win(int **m, int n);
string enter_name();

int main() {
	setColor(Black, White);
	system("cls");
	user_number = menu();
	switch (user_number) {
	case 1: //newGame
		start_game();
		break;
	case 2: //records
		out_records();
		break;
	case 3: //statistic 
		out_statistics();
		break;
	case 4: //about game
		show_about_game();
		break;
	case 5: //exit
		return 0;
	}
	return 0;
}

int difficulty_level() {
	int key, i = 1;
	gotoxy(12, 1);
	setColor(Black, White);
	cout << "Choose level of difficulty";
	gotoxy(22, 5);
	setColor(White, Black);
	cout << "EASY";
	gotoxy(21, 7);
	setColor(Black, White);
	cout << "MEDIUM";
	gotoxy(22, 9);
	cout << "HARD";
	while (true) {
		key = _getch();
		switch (key) {
		case UP:
			if (i == 2) {
				gotoxy(22, 5);
				setColor(White, Black);
				cout << "EASY";
				gotoxy(21, 7);
				setColor(Black, White);
				cout << "MEDIUM";
				i--;
			}
			else if (i == 3) {
				gotoxy(21, 7);
				setColor(White, Black);
				cout << "MEDIUM";
				gotoxy(22, 9);
				setColor(Black, White);
				cout << "HARD";
				i--;
			}
			break;
		case DOWN:
			if (i == 1) {
				gotoxy(22, 5);
				setColor(Black, White);
				cout << "EASY";
				gotoxy(21, 7);
				setColor(White, Black);
				cout << "MEDIUM";
				i++;
			}
			else if (i == 2) {
				gotoxy(21, 7);
				setColor(Black, White);
				cout << "MEDIUM";
				gotoxy(22, 9);
				setColor(White, Black);
				cout << "HARD";
				setColor(Black, White);
				i++;
			}
			break;
		case ENTER:
			setColor(Black, White);
			system("cls");
			return i;
		}
	}
}

int menu() {
	int key, i = 1;
	gotoxy(22, 8);
	setColor(White, Black);
	cout << "NEW GAME";
	setColor(Black, White);
	gotoxy(23, 10);
	cout << "RECORDS";
	gotoxy(22, 12);
	cout << "STATISTIC";
	gotoxy(21, 14);
	cout << "ABOUT GAME";
	gotoxy(24, 16);
	cout << "EXIT";
	while (true) {
		key = _getch();
		switch (key) {
		case UP:
			if (i == 2) {
				gotoxy(22, 8);
				setColor(White, Black);
				cout << "NEW GAME";
				gotoxy(23, 10);
				setColor(Black, White);
				cout << "RECORDS";
				i--;
			}
			else if (i == 3) {
				gotoxy(23, 10);
				setColor(White, Black);
				cout << "RECORDS";
				gotoxy(22, 12);
				setColor(Black, White);
				cout << "STATISTIC";
				i--;
			}
			else if (i == 4) {
				gotoxy(22, 12);
				setColor(White, Black);
				cout << "STATISTIC";
				gotoxy(21, 14);
				setColor(Black, White);
				cout << "ABOUT GAME";
				i--;
			}
			else if (i == 5) {
				gotoxy(21, 14);
				setColor(White, Black);
				cout << "ABOUT GAME";
				gotoxy(24, 16);
				setColor(Black, White);
				cout << "EXIT";
				i--;
			}
			break;
		case DOWN:
			if (i == 1) {
				gotoxy(22, 8);
				setColor(Black, White);
				cout << "NEW GAME";
				gotoxy(23, 10);
				setColor(White, Black);
				cout << "RECORDS";
				i++;
			}
			else if (i == 2) {
				gotoxy(23, 10);
				setColor(Black, White);
				cout << "RECORDS";
				gotoxy(22, 12);
				setColor(White, Black);
				cout << "STATISTIC";
				i++;
			}
			else if (i == 3) {
				gotoxy(22, 12);
				setColor(Black, White);
				cout << "STATISTIC";
				gotoxy(21, 14);
				setColor(White, Black);
				cout << "ABOUT GAME";
				i++;
			}
			else if (i == 4) {
				gotoxy(21, 14);
				setColor(Black, White);
				cout << "ABOUT GAME";
				gotoxy(24, 16);
				setColor(White, Black);
				cout << "EXIT";
				i++;
			}
			break;
		case ENTER:
			setColor(Black, White);
			system("cls");
			return i;
		}
	}
}

bool go_to_menu();

void game(int **m, int n) {
	int k = 1, x1, y1, x2, y2;
	for (int i = 0; i < n; i++) {
		m[i] = new int[n];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++, k++) {
			m[j][i] = k;
		}
	}
	m[n - 1][n - 1] = 0;
	k = 0;
	while (k < n*n + n * n) {
		x1 = rand() % n;
		y1 = rand() % n;
		x2 = rand() % n;
		y2 = rand() % n;
		swap(m[x1][y1], m[x2][y2]);
		k++;
	}
}

void gotoxy(int x, int y) {
	COORD p = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

void setColor(int background, int text) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)((background << 4) | text));
}

void show_frame(int **m, int n) {
	setColor(White, White);
	int jump = 2;
	for (int k = 1; k <= n + 1; k++, jump += 4) {
		gotoxy(5, jump);
		for (int i = 1; i <= (n * 4 + 1) * 2; i++) {
			cout << " ";
		}
	}
	jump = 5;
	for (int k = 1; k <= n + 1; k++, jump += 8) {
		for (int i = 2; i <= n * 4 + 1; i++) {
			gotoxy(jump, i);
			cout << "  ";
		}
	}
	setColor(Black, White);
}

void show_cells(int **m, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int color = 0;
			if (m[i][j] <= n && m[i][j] != 0) {
				color = Red;
			}
			else if (m[i][j] > n && m[i][j] <= 2 * n) {
				color = Blue;
			}
			else if (m[i][j] > 2 * n && m[i][j] <= 3 * n) {
				color = Brown;
			}
			else if (m[i][j] > 3 * n && m[i][j] <= 4 * n) {
				color = Cyan;
			}
			else if (m[i][j] > 4 * n && m[i][j] <= 5 * n) {
				color = Magenta;
			}
			setColor(color, color);
			for (int r = 1; r <= 3; r++) {
				gotoxy((i * 8) + 7, (j * 4) + 2 + r);
				cout << "      ";
				setColor(color, White);
			}
			gotoxy((i * 8) + 9, (j * 4) + 4);
			if (m[i][j] != 0) {
				cout << m[i][j];
			}
		}
	}
	setColor(Black, White);
}

void show_about_game() {
	int count = 1;
	about_game.open("about_game.txt");
	setColor(Black, White);
	system("cls");
	while (!about_game.eof()) {
		string s;
		getline(about_game, s);
		gotoxy(2, count);
		cout << s << endl;
		count++;
	}
	about_game.close();
	if (go_to_menu() == true) {
		main();
	}
	else {
		return;
	}
}

void inp_statistics(int time, int moves) {
	int games = 0, total_time = 0, total_moves = 0, avg_moves = 0, avg_time = 0;
	statistics.open("statistics.txt");
	statistics >> games;
	statistics >> total_time;
	statistics >> total_moves;
	statistics >> avg_time;
	statistics >> avg_moves;
	games++;
	total_time += time;
	total_moves += moves;
	avg_time = total_time / games;
	avg_moves = total_moves / games;
	statistics.close();
	statistics.open("statistics.txt", ios_base::out | ios_base::trunc);
	statistics << games << endl;
	statistics << total_time << endl;
	statistics << total_moves << endl;
	statistics << avg_time << endl;
	statistics << avg_moves;
	statistics.close();
}

void out_statistics() {
	int games = 0, total_time = 0, total_moves = 0, avg_moves = 0, avg_time = 0;
	statistics.open("statistics.txt");
	statistics >> games;
	statistics >> total_time;
	statistics >> total_moves;
	statistics >> avg_time;
	statistics >> avg_moves;
	if (games == 0) {
		gotoxy(2, 1);
		cout << "You didn't play anyone game";
	}
	else {
		gotoxy(2, 1);
		cout << "Games: " << games;
		sec = total_time;
		minn = 0;
		hour = 0;
		sec_to_min(sec, minn, hour);
		gotoxy(2, 2);
		if (minn == 0 && hour == 0) {
			cout << "Total time: " << sec << " sec";
		}
		else if (hour == 0) {
			cout << "Total time: " << minn << " min " << sec << " sec";
		}
		else {
			cout << "Total time: " << hour << "hour" << minn << " min " << sec << " sec ";
		}
		gotoxy(2, 3);
		cout << "Total moves in game: " << total_moves;
		sec = avg_time;
		minn = 0;
		hour = 0;
		sec_to_min(sec, minn, hour);
		gotoxy(2, 4);
		if (minn == 0 && hour == 0) {
			cout << "Avarage time in one game: " << sec << " sec";
		}
		else if (hour == 0) {
			cout << "Avarage time in one game: " << minn << " min " << sec << " sec";
		}
		else {
			cout << "Avarage time in one game: " << hour << "hour" << minn << " min " << sec << " sec";
		}
		gotoxy(2, 5);
		cout << "Avarage moves in one game: " << avg_moves;
		statistics.close();
	}
	if (go_to_menu() == true) {
		main();
	}
	else {
		return;
	}
}

void inp_records(string name, int level, int time, int moves) {
	string res_name = "";
	int arr_size = 0, res_level = 0, res_time = 0, res_moves = 0;
	records.open("records.txt");
	Records *records_list = nullptr;
	while (!records.eof()) {
		res_name = "";
		res_level = 0;
		res_time = 0;
		res_moves = 0;
		records >> res_name;
		records >> res_level;
		records >> res_time;
		records >> res_moves;
		if (res_name != "" && res_level != 0 && res_time != 0 && res_moves != 0) {
			if (arr_size == 0) {
				records_list = new Records[1];
			}
			else {
				Records *new_list = new Records[arr_size + 1];
				for (int i = 0; i < arr_size; i++) {
					new_list[i] = records_list[i];
				}
				delete[] records_list;
				records_list = new_list;
			}
			records_list[arr_size].name = res_name;
			records_list[arr_size].level = res_level;
			records_list[arr_size].time = res_time;
			records_list[arr_size].moves = res_moves;
			arr_size++;
		}

	}
	records.close();
	if (arr_size == 0) {
		records_list = new Records[1];
	}
	else {
		Records *new_list = new Records[arr_size + 1];
		for (int i = 0; i < arr_size; i++) {
			new_list[i] = records_list[i];
		}
		delete[] records_list;
		records_list = new_list;
	}
	records_list[arr_size].name = name;
	records_list[arr_size].level = level;
	records_list[arr_size].time = time;
	records_list[arr_size].moves = moves;
	arr_size++;
	if (arr_size != 1) {
		bool exit = false;
		while (!exit) {
			exit = true;
			for (int i = 0; i < arr_size - 1; i++) {
				if (records_list[i].moves > records_list[i + 1].moves) {
					swap(records_list[i].name, records_list[i + 1].name);
					swap(records_list[i].level, records_list[i + 1].level);
					swap(records_list[i].time, records_list[i + 1].time);
					swap(records_list[i].moves, records_list[i + 1].moves);
					exit = false;
				}
				else if (records_list[i].moves == records_list[i + 1].moves && records_list[i].time > records_list[i + 1].time) {
					swap(records_list[i].name, records_list[i + 1].name);
					swap(records_list[i].level, records_list[i + 1].level);
					swap(records_list[i].time, records_list[i + 1].time);
					swap(records_list[i].moves, records_list[i + 1].moves);
					exit = false;
				}
			}
		}
		exit = false;
		while (!exit) {
			exit = true;
			for (int i = 0; i < arr_size - 1; i++) {
				if (records_list[i].level > records_list[i + 1].level) {
					swap(records_list[i].name, records_list[i + 1].name);
					swap(records_list[i].level, records_list[i + 1].level);
					swap(records_list[i].time, records_list[i + 1].time);
					swap(records_list[i].moves, records_list[i + 1].moves);
					exit = false;
				}
			}
		}
	}
	records.open("records.txt", ios_base::out | ios_base::trunc);
	for (int i = 0; i < arr_size; i++) {
		records << records_list[i].name << endl;
		records << records_list[i].level << endl;
		records << records_list[i].time << endl;
		records << records_list[i].moves << endl;
	}
	records.close();
}

void out_records() {
	int level = 0, moves = 0, best_time = 0, count = 1, k_easy = 0, k_middle = 0, k_hard = 0,
		move_x = 2, move_y = 1, m_y_easy = 1, m_y_middle = 1, m_y_hard = 1;
	string name = "", level_str = "";
	records.open("records.txt");
	while (!records.eof()) {
		name = "";
		level - 0;
		best_time = 0;
		moves = 0;
		records >> name;
		records >> level;
		records >> best_time;
		records >> moves;
		if (name != "" && level != 0 && best_time != 0 && moves != 0) {
			if (k_easy < 3 && level == 1) {
				k_easy++;
				level_str = "easy";
				move_x = 2;
				count = m_y_easy;
				m_y_easy += 5;
			}
			else if (k_middle < 3 && level == 2) {
				k_middle++;
				level_str = "middle";
				move_x = 17;
				count = m_y_middle;
				m_y_middle += 5;
			}
			else if (k_hard < 3 && level == 3) {
				k_hard++;
				level_str = "hard";
				move_x = 32;
				count = m_y_hard;
				m_y_hard += 5;
			}
			else {
				continue;
			}
			gotoxy(move_x, count);
			cout << "Name: " << name;
			gotoxy(move_x, count + 1);
			cout << "Level: " << level_str;
			gotoxy(move_x, count + 2);
			cout << "Time: " << best_time << " sec";
			gotoxy(move_x, count + 3);
			cout << "Moves: " << moves;
			count += 5;
		}
		if (k_easy == 0 && k_middle == 0 && k_hard == 0) {
			gotoxy(2, count);
			cout << "Records is empty";
		}
	}
	records.close();
	if (go_to_menu() == true) {
		main();
	}
	else {
		return;
	}
}

void move(int **m, int n, int &moves) {
	int x = 0, y = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (m[i][j] == 0) {
				x = i;
				y = j;
			}
		}
	}
	int key;
	key = _getch();
	switch (key) {
	case DOWN:
		if (y != n - 1) {
			swap(m[x][y], m[x][y + 1]);
			moves++;
		}

		break;
	case LEFT:
		if (x != 0) {
			swap(m[x][y], m[x - 1][y]);
			moves++;
		}
		break;
	case UP:
		if (y != 0) {
			swap(m[x][y], m[x][y - 1]);
			moves++;
		}
		break;
	case RIGHT:
		if (x != n - 1) {
			swap(m[x][y], m[x + 1][y]);
			moves++;
		}
		break;
	}
	return;
}

void sec_to_min(long int &sec, long int &min, long int &hour) {
	if (sec >= 60) {
		min = sec / 60;
		sec %= 60;
		if (min >= 60) {
			hour = min / 60;
			min %= 60;
		}
	}
}

void start_game() {
	long int start_time = 0, end_time = 0;
	final_time = 0;
	moves = 0;
	name = enter_name();
	difficult = difficulty_level();
	n = difficult + 2; //розмірність
	m = new int*[n]; //створення поля
	for (int i = 0; i < n; i++) {
		m[i] = new int[n];
	}
	start_time = time(NULL);//початок таймеру
	game(m, n);//створення поля
	show_frame(m, n);//відрисовка границь
	gotoxy(1, 0);
	cout << "Moves: " << moves;
	while (!win(m, n)) {
		show_cells(m, n);
		move(m, n, moves);
		gotoxy(1, 0);
		cout << "Moves: " << moves;
	}
	end_time = time(NULL);
	final_time = end_time - start_time;
	setColor(Black, White);
	system("cls");
	gotoxy(20, 11);
	cout << "YOU WIN!";
	gotoxy(15, 13);
	sec = final_time, minn = 0, hour = 0;
	sec_to_min(sec, minn, hour);
	if (minn == 0 && hour == 0) {
		cout << "Your time is " << sec << " sec";
	}
	else if (hour == 0) {
		cout << "Your time is " << minn << " min " << sec << " sec ";
	}
	else {
		cout << "Your time is " << hour << " hour " << minn << " min " << sec << " sec ";
	}
	inp_statistics(final_time, moves);
	inp_records(name, difficult, final_time, moves);
	if (go_to_menu() == true) {
		main();
	}
	else {
		return;
	}
}

bool go_to_menu() {
	int i = 1, key = 0;
	setColor(White, Black);
	gotoxy(10, 20);
	cout << "BACK TO MENU";
	setColor(Black, White);
	gotoxy(30, 20);
	cout << "EXIT";
	while (true) {
		key = _getch();
		switch (key) {
		case LEFT:
			if (i == 2) {
				setColor(White, Black);
				gotoxy(10, 20);
				cout << "BACK TO MENU";
				setColor(Black, White);
				gotoxy(30, 20);
				cout << "EXIT";
				i--;
			}
			break;
		case RIGHT:
			if (i == 1) {
				setColor(Black, White);
				gotoxy(10, 20);
				cout << "BACK TO MENU";
				setColor(White, Black);
				gotoxy(30, 20);
				cout << "EXIT";
				i++;
			}
			break;
		case ENTER:
			if (i == 1) { //Back to menu
				return true;
			}
			else {
				return false;
			}
		}
	}
}

bool win(int **m, int n) {
	int k = 1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (k == n * n - 1) {
				return true;
			}
			else if (m[j][i] == k && m[i][j] != 0) {
				k++;
			}
			else {
				return false;
			}
		}
	}
}

string enter_name() {
	string name;
	setColor(Black, White);
	gotoxy(2, 1);
	cout << "Enter your name: ";
	cin >> name;
	system("cls");
	return name;
}