#include "Console.h"

void Console::clear() {
	system("cls");
}

void Console::pause() {
	system("pause");
}

int Console::list_selector(const vector<string>& arr, string heading) {
	int column_width = Utils::max_column_width(arr);
	if (column_width < heading.length())
		column_width = heading.length();
	column_width += 2;

	Cursor::hide();

	// Printing the list
	print(heading, Colors::TABLE_HEADER, column_width, true);
	cout << endl;
	for (int i = 0; i < arr.size(); i++)
		print(' ' + arr[i], Colors::UNSELECTED, column_width);
	print(" Back", Colors::UNSELECTED, column_width);

	// Selecting the element
	vector<int> pos = Cursor::get_position();
	int selected = 0;
	char key;
	do {
		Cursor::move_to(pos[0] - arr.size() - 1 + selected, 1);

		// Printing the selected element
		if (selected == arr.size())
			print(" Back", Colors::SELECTED, column_width, false, false);
		else
			print(' ' + arr[selected], Colors::SELECTED, column_width, false, false);

		Cursor::move_to_start_of_line();

		// Getting the key pressed
		while (true) {
			key = _getch();
			if (key == 72 || key == 80 || key == 13 || key == 27)
				break;
		}

		// Printing the unselected element
		if (selected == arr.size())
			print(" Back", Colors::UNSELECTED, column_width, false, false);
		else
			print(' ' + arr[selected], Colors::UNSELECTED, column_width, false, false);

		// up_arrow_key
		if (selected > 0 && key == 72)
			selected--;
		// down_arrow_key
		else if (selected < arr.size() && key == 80)
			selected++;
		// up_arrow_key
		else if (selected == 0 && key == 72)
			selected = arr.size();
		// down_arrow_key
		else if (selected == arr.size() && key == 80)
			selected = 0;
		// enter_key
		else if (key == 13)
			break;

	} while (true);

	Cursor::move_to(pos[0] - arr.size() - 3, 1);
	Cursor::clear_screen_from_cursor();
	Cursor::show();

	return (selected == arr.size()) ? -1 : selected;
}

int Console::list_selector_alt(const vector<string>& arr, string heading) {
	int column_width = Utils::max_column_width(arr);
	if (column_width < heading.length())
		column_width = heading.length();
	column_width += 2;

	print(heading, Colors::TABLE_HEADER, column_width, true);
	cout << endl;

	int selected = 0;
	char key;
	do {
		for (int i = 0; i < arr.size(); i++) {
			if (selected == i)
				print(' ' + arr[i], Colors::SELECTED, column_width);
			else
				print(' ' + arr[i], Colors::UNSELECTED, column_width);
		}
		cout << endl;
		if (selected == arr.size())
			print(" Back", Colors::SELECTED, column_width);
		else
			print(" Back", Colors::UNSELECTED, column_width);

		while (true) {
			key = _getch();
			if (key == 72 || key == 80 || key == 13 || key == 27)
				break;
		}
		Cursor::remove_n_lines(arr.size() + 2);

		if (selected > 0 && key == 72) // up_arrow_key
			selected--;
		else if (selected < arr.size() && key == 80) // down_arrow_key
			selected++;
		else if (selected == 0 && key == 72) // up_arrow_key
			selected = arr.size();
		else if (selected == arr.size() && key == 80) // down_arrow_key
			selected = 0;
		else if (key == 13) { // enter_key
			break;
		}
	} while (true);
	Cursor::remove_n_lines(2);
	return (selected == arr.size()) ? -1 : selected;
}

string Console::get_input(const string& message, const bool& suggestions, const bool& password) {
	vector<int> init_pos = Cursor::get_position();
	cout << endl;
	print("[ESC] to cancel. [TAB] to autocomplete. [Enter] to submit.", Colors::INFO);
	print(' ' + message + ' ', Colors::INPUT_FIELD_HEADING);

	string input = "";
	string token = "";
	char key;
	bool arrow_key_pressed = false;
	int selected = 0;
	int prev_selected = 0;
	int column_width = 0;
	vector<string> suggested;
	int n_results = 10;
	int cursor_pos = 1;

	for (int i = 0; i < n_results + 1; i++)
		cout << endl;
	Cursor::move_up(n_results + 1);
	init_pos = { Cursor::get_position()[0] - 3, init_pos[1] };

	do {
		key = _getch();
		if (key == 13) // enter_key
			break;
		else if (key == 9 && !password) { // tab_key
			auto tokens = Utils::split(input, ' ');
			string sub = input.substr(0, input.length() - token.length());
			Cursor::move_left(token.length());

			print(suggested[selected] + ' ', Colors::INPUT_FIELD_TEXT, 0, false, false);
			input = sub + suggested[selected] + ' ';
			cursor_pos += suggested[selected].length() - token.length() + 1;

			token = "";
			selected = 0;
			arrow_key_pressed = false;
		}
		else if (key == 8 && input.length() > 0) { // backspace_key
			input.pop_back();
			cout << "\b \b";
			token = token.substr(0, token.length() - 1);
			cursor_pos--;
		}
		else if (key == 27) { // escape_key
			input = "";
			break;
		}
		else if (key == 72 && arrow_key_pressed) // up_arrow_key
			selected--;
		else if (key == 80 && arrow_key_pressed) // down_arrow_key
			selected++;
		else if (key == -32) { // up_arrow_key or down_arrow_key
			arrow_key_pressed = true;
			continue;
		}
		else if (' ' <= key <= '~') {
			input += key;
			if (key == ' ')
				token = "";
			else
				token += key;
			print(string(1, password ? '*' : key), Colors::INPUT_FIELD_TEXT, 0, false, false);
			cursor_pos++;
			arrow_key_pressed = false;
			selected = 0;
		}

		if (!suggestions || password)
			continue;

		else if (!arrow_key_pressed) {
			if (token.length() == 0)
				suggested.clear();
			else {
				suggested = Trie::words.get_suggestions(token, 10);
				column_width = Utils::max_column_width(suggested) + 2;
			}
			Cursor::move_to(init_pos[0] + 4, 1);
			Cursor::clear_screen_from_cursor();
		}
		else if (arrow_key_pressed) {
			if (selected < 0)
				selected = suggested.size() - 1;
			else if (selected >= suggested.size())
				selected = 0;
		}

		if (suggested.size() != 0) {
			if (!arrow_key_pressed) {
				for (int i = 0; i < suggested.size(); i++)
					print(' ' + suggested[i], Colors::UNSELECTED, column_width);
			}
			else if (arrow_key_pressed) {
				Cursor::move_to(init_pos[0] + 4 + prev_selected, 1);
				print(' ' + suggested[prev_selected], Colors::UNSELECTED, column_width);
			}
			Cursor::move_to(init_pos[0] + 4 + selected, 1);
			print(' ' + suggested[selected], Colors::SELECTED, column_width);
		}

		prev_selected = selected;
		Cursor::move_to(init_pos[0] + 3, cursor_pos);

	} while (true);
	Cursor::move_to(init_pos[0], init_pos[1]);
	Cursor::clear_screen_from_cursor();
	return input;
}

void Console::print_matrix(const vector<vector<int>>& matrix, bool determinent) {
	vector<int> column_widths;
	int max_width = 0;
	for (int i = 0; i < matrix[0].size(); i++) {
		int max = 0;
		for (int j = 0; j < matrix.size(); j++) {
			int width = to_string(matrix[j][i]).length();
			if (width > max)
				max = width;
		}
		column_widths.push_back(max);
		max_width += max;
	}
	max_width += matrix[0].size() - 1;

	_setmode(_fileno(stdout), _O_U16TEXT);

	for (int i = 0; i < matrix.size(); i++) {
		if (i == 0)
			wcout << (determinent ? L"│ " : L"┌ ");
		else if (i == matrix.size() - 1)
			wcout << (determinent ? L"│ " : L"└ ");
		else
			wcout << L"│ ";
		for (int j = 0; j < matrix[i].size(); j++) {
			wcout << left << setw(column_widths[j]) << wstring((column_widths[j] - to_wstring(matrix[i][j]).length()) / 2, L' ') + to_wstring(matrix[i][j]);
			wcout << L" ";
		}
		if (i == 0)
			wcout << (determinent ? L"│" : L"┐");
		else if (i == matrix.size() - 1)
			wcout << (determinent ? L"│" : L"┘");
		else
			wcout << L"│";
		wcout << endl;
	}

	_setmode(_fileno(stdout), _O_TEXT);
}