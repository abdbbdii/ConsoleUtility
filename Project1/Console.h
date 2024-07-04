#pragma once

#include "Colors.h"
#include "Cursor.h"
#include "TextFormatter.h"
#include "Utils.h"
#include "Trie.h"
#include <conio.h>
#include <fcntl.h>
#include <io.h>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

inline string to_string(const string& _Val) {
	return _Val;
}

class Console {
public:
	static void clear();
	static void pause();
	static int list_selector(const vector<string>& arr, string heading = "");
	static int list_selector_alt(const vector<string>& arr, string heading = "");
	static string get_input(const string& message, const bool& suggestions = true, const bool& password = false);
	static void print_matrix(const vector<vector<int>>& matrix, bool determinent = false);

	template <typename T>
	static T map_selector(const unordered_map<T, string>& options, const string& heading) {
		int selected = list_selector(Utils::get_values<T, string>(options), heading);
		if (selected == -1)
			return T();
		return next(options.begin(), selected)->first;
	}

	template <typename T>
	static void print(const T& text, const string& format = TextFormatter::RESET, const int& set_width = 0, const bool& centered = false, bool endline = true) {
		string str = to_string(text);
		string pre_text = "";
		if (format == Colors::ERROR)
			pre_text = "[ERROR] ";
		else if (format == Colors::SUCCESS)
			pre_text = "[SUCCESS] ";
		else if (format == Colors::WARNING)
			pre_text = "[WARNING] ";
		else if (format == Colors::INFO)
			pre_text = "[INFO] ";
		if (centered && set_width)
			pre_text = string((set_width - str.length() - pre_text.length()) / 2, ' ') + pre_text;

		cout << format;
		if (set_width)
			cout << left << setw(set_width);
		cout << pre_text + str << TextFormatter::RESET << ((endline) ? "\n" : "");
	}
};