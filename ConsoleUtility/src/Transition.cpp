#include "Transition.h"

void Transition::rgb(const string& s, const int duration, const int speed, bool reverse) {
	Cursor::hide();
	vector<int> v = Cursor::get_position();
	for (int i = 0; i < duration / speed; i++) {
		Cursor::move_to(v[0], v[1]);
		for (int j = 0; j < s.length(); j++)
			Console::print(string(1, s[j]), TextFormatter::hsl_to_ansi((360 / s.length()) * (reverse ? i + j : i - j) % 360, 100, 50), 0, false, false);
		Sleep(speed);
	}
	Cursor::move_to(v[0], v[1]);
	cout << s;
	Cursor::show();
}

void Transition::fade(const string& s, const int speed, const int start, const int end) {
	Cursor::hide();
	vector<int> v = Cursor::get_position();
	if (start < end) {
		for (int i = start; i < end; i++) {
			Cursor::move_to(v[0], v[1]);
			for (int j = 0; j < s.length(); j++)
				Console::print(string(1, s[j]), TextFormatter::rgb_to_ansi(i, i, i), 0, false, false);
			Sleep(speed);
		}
	}
	else {
		for (int i = start; i > end; i--) {
			Cursor::move_to(v[0], v[1]);
			for (int j = 0; j < s.length(); j++)
				Console::print(string(1, s[j]), TextFormatter::rgb_to_ansi(i, i, i), 0, false, false);
			Sleep(speed);
		}
	}
	Cursor::move_to(v[0], v[1]);
	cout << s;
	Cursor::show();
}

void Transition::glitch_color(const string& s, const int duration, const int speed) {
	Cursor::hide();
	vector<int> v = Cursor::get_position();
	for (int i = 0; i < duration / speed; i++) {
		Cursor::move_to(v[0], v[1]);
		for (int j = 0; j < s.length(); j++)
			Console::print(string(1, s[j]), TextFormatter::rgb_to_ansi(rand() % 256, rand() % 256, rand() % 256), 0, false, false);
		Sleep(speed);
	}
	Cursor::move_to(v[0], v[1]);
	cout << s;
	Cursor::show();
}

void Transition::glitch_text(const string& s, const int duration, const int speed) {
	Cursor::hide();
	vector<int> v = Cursor::get_position();
	for (int i = 0; i < duration / speed; i++) {
		for (int j = 0; j < s.length(); j++)
			Console::print(string(1, (char)(rand() % 93 + 33) % 127), "", 0, false, false);
		Sleep(speed);
		Cursor::move_to(v[0], v[1]);
	}
	string temp = "";
	for (int i = 0; i < s.length(); i++) {
		temp = s;
		for (int j = 0; j < s.length(); j++)
			if (i + j < s.length() - 1)
				temp[i + j] = (char)(rand() % 93 + 33) % 127;

		Cursor::move_to(v[0], v[1]);
		Console::print(temp, "", 0, false, false);
		Sleep(speed);
	}
	Cursor::show();
}