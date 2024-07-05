#include "Table.h"

const vector<vector<vector<wstring>>> Table::_styles = {
	{{L"┌", L"┬", L"┐"}, {L"├", L"┼", L"┤"}, {L"└", L"┴", L"┘"}, {L"─", L"│"}},
	{{L"╔", L"╦", L"╗"}, {L"╠", L"╬", L"╣"}, {L"╚", L"╩", L"╝"}, {L"═", L"║"}},
	{{L"┏", L"┳", L"┓"}, {L"┣", L"╋", L"┫"}, {L"┗", L"┻", L"┛"}, {L"━", L"┃"}},
	{{L"╭", L"┬", L"╮"}, {L"├", L"┼", L"┤"}, {L"╰", L"┴", L"╯"}, {L"─", L"│"}},
	{{L"╔", L"╦", L"╗"}, {L"╠", L"╬", L"╣"}, {L"╚", L"╩", L"╝"}, {L"─", L"│"}},
	{{L"┏", L"┳", L"┓"}, {L"┣", L"╋", L"┫"}, {L"┗", L"┻", L"┛"}, {L"─", L"│"}},
};

Table::Table() {}

Table::Table(const vector<string>& headers, const vector<vector<string>>& data) : _headers(headers), _data(data) {
	_calculate_widths();
}

Table::Table(const vector<vector<string>>& data, const bool with_header) {
	if (with_header) {
		_headers = data[0];
		for (int i = 1; i < data.size(); i++)
			_data.push_back(data[i]);
	}
	else {
		_headers = {};
		_data = data;
	}
	_calculate_widths();
}

void Table::_display_column_separator(int position, int style) {
	_setmode(_fileno(stdout), _O_U16TEXT);
	wcout << _styles[style][position][0];
	for (int i = 0; i < _column_widths.size(); i++) {
		wcout << wstring(_column_widths[i], _styles[style][3][0][0]);
		if (i < _column_widths.size() - 1)
			wcout << _styles[style][position][1];
	}
	wcout << _styles[style][position][2] << endl;
	_setmode(_fileno(stdout), _O_TEXT);
}

void Table::_display_column(const vector<string>& column, const bool& heading, const bool& centered, int style) {
	_setmode(_fileno(stdout), _O_U16TEXT);
	wcout << _styles[style][3][1];
	for (int i = 0; i < column.size(); i++) {
		_setmode(_fileno(stdout), _O_TEXT);
		Console::print(column[i], TextFormatter::RESET, _column_widths[i], centered, false);
		_setmode(_fileno(stdout), _O_U16TEXT);
		if (i != column.size() - 1)
			wcout << _styles[style][3][1];
	}
	wcout << _styles[style][3][1];
	_setmode(_fileno(stdout), _O_TEXT);
	cout << endl;
}

void Table::_c_display_column_separator() {
	Console::print(" ", Colors::TABLE_BORDER, 0, false, false);
	for (int i = 0; i < _column_widths.size(); i++) {
		Console::print(" ", Colors::TABLE_BORDER, 0, false, false);
		Console::print(string(_column_widths[i], ' '), Colors::TABLE_BORDER, 0, false, false);
	}
	Console::print("  ", Colors::TABLE_BORDER);
}

void Table::_c_display_column(const vector<string>& column, const bool& heading, const bool& centered) {
	Console::print("  ", Colors::TABLE_BORDER, 0, false, false);
	for (int i = 0; i < column.size(); i++) {
		Console::print(column[i], (heading) ? Colors::TABLE_HEADER : Colors::UNSELECTED, _column_widths[i], centered, false);
		Console::print(" ", Colors::TABLE_BORDER, 0, false, false);
	}
	Console::print(" ", Colors::TABLE_BORDER, 0, false);
}

void Table::_calculate_widths() {
	int max_width;
	for (int i = 0; i < _data[0].size(); i++) {
		if (_headers.size() != 0 && _headers[i].length() > _data[0][i].length())
			max_width = _headers[i].length();
		else
			max_width = _data[0][i].length();
		for (int j = 0; j < _data.size(); j++) {
			if (_data[j][i].length() > max_width)
				max_width = _data[j][i].length();
		}
		_column_widths.push_back(max_width + 2);
		_total_width += max_width + 2;
	}
}

void Table::display(const int style, const vector<bool>& mask) {
	Table* table;
	if (mask.size() == 0)
		table = this;
	else {
		vector<string> headers;
		vector<vector<string>> data;
		for (int i = 0; i < _headers.size(); i++)
			if (mask[i])
				headers.push_back(_headers[i]);
		for (int i = 0; i < _data.size(); i++) {
			vector<string> row;
			for (int j = 0; j < _data[i].size(); j++)
				if (mask[j])
					row.push_back(_data[i][j]);
			data.push_back(row);
		}
		table = new Table(headers, data);
	}
	table->_display_column_separator(0, style);
	if (table->_headers.size() != 0) {
		table->_display_column(table->_headers, true, true, style);
		table->_display_column_separator(1, style);
	}
	for (int i = 0; i < table->_data.size(); i++)
		table->_display_column(table->_data[i], false, true, style);
	table->_display_column_separator(2, style);
}

void Table::c_display(const vector<bool>& mask) {
	_c_display_column_separator();
	if (_headers.size() != 0)
		_c_display_column(_headers, true, true);
	for (int i = 0; i < _data.size(); i++)
		_c_display_column(_data[i]);
	_c_display_column_separator();
}

vector<int> Table::selector() {
	Cursor::hide();

	// Printing the table
	for (int i = 0; i < _headers.size(); i++)
		Console::print(_headers[i], Colors::TABLE_HEADER, _column_widths[i], true, false);
	cout << endl;
	for (vector<string> row : _data) {
		for (int i = 0; i < row.size(); i++)
			Console::print(row[i], Colors::UNSELECTED, _column_widths[i], true, false);
		cout << endl;
	}
	Console::print("Back", Colors::UNSELECTED, _total_width, true, false);

	// Selecting the element
	vector<int> pos = Cursor::get_position();
	int selectedr = 0, selectedc = 0;
	int r, c;
	char key;
	do {
		r = pos[0] - _data.size() + selectedr;
		c = Utils::accumulate(_column_widths, 0, selectedc) + 1;
		Cursor::move_to(r, c);

		// Printing the selected element
		if (selectedr == _data.size())
			Console::print("Back", Colors::SELECTED, _total_width, true, false);
		else
			Console::print(_data[selectedr][selectedc], Colors::SELECTED, _column_widths[selectedc], true, false);

		Cursor::move_to(r, c);

		// Getting the key pressed
		while (true) {
			key = _getch();
			if (key == 72 || key == 80 || key == 75 || key == 77 || key == 13 || key == 27)
				break;
		}

		// Printing the unselected element
		if (selectedr == _data.size())
			Console::print("Back", Colors::UNSELECTED, _total_width, true, false);
		else
			Console::print(_data[selectedr][selectedc], Colors::UNSELECTED, _column_widths[selectedc], true, false);

		if ((key == 75 || key == 77) && selectedc == 0 && selectedr == _data.size())
			continue;
		// up_arrow_key
		else if (key == 72) {
			if (selectedr > 0)
				selectedr--;
			else if (selectedr == 0) {
				selectedr = _data.size();
				selectedc = 0;
			}
		}
		// down_arrow_key
		else if (key == 80) {
			if (selectedr < _data.size()) {
				selectedr++;
				if (selectedr == _data.size())
					selectedc = 0;
			}
			else if (selectedr == _data.size())
				selectedr = 0;
		}
		// left_arrow_key
		else if (key == 75) {
			if (selectedc > 0)
				selectedc--;
			else if (selectedc == 0)
				selectedc = _data[0].size() - 1;
		}
		// right_arrow_key
		else if (key == 77) {
			if (selectedc < _data[0].size() - 1)
				selectedc++;
			else if (selectedc == _data[0].size() - 1)
				selectedc = 0;
		}
		// enter_key
		else if (key == 13)
			break;

	} while (true);

	Cursor::move_to(pos[0] - _data.size() - 1, 1);
	Cursor::clear_screen_from_cursor();
	Cursor::show();

	if (selectedr == _data.size())
		return { -1, -1 };
	return { selectedr, selectedc };
}

vector<int> Table::selector_alt() {
	vector<string> options = { "Select", "Exit" };

	int selectedr = 0, selectedc = 0;
	for (int i = 0; i < _headers.size(); i++)
		Console::print(_headers[i], Colors::TABLE_HEADER, _column_widths[i], true, false);
	cout << endl
		<< endl;

	char key;
	do {
		for (int x = 0; x < _data.size(); x++) {
			for (int y = 0; y < _data[x].size(); y++) {
				string str = _data[x][y];
				if (selectedr == x && selectedc == y)
					Console::print(' ' + str, Colors::SELECTED, _column_widths[y], true, false);
				else
					Console::print(' ' + str, Colors::UNSELECTED, _column_widths[y], true, false);
			}
			cout << endl;
		}
		cout << endl;
		if (selectedr == _data.size())
			Console::print("Back", Colors::SELECTED, _total_width, true);
		else
			Console::print("Back", Colors::UNSELECTED, _total_width, true);

		while (true) {
			key = _getch();
			if (key == 72 || key == 80 || key == 13 || key == 27 || key == 75 || key == 77)
				break;
		}
		Cursor::remove_n_lines(_data.size() + 2); // Extra lines are for back option

		if (selectedr > 0 && key == 72) // up_arrow_key
			selectedr--;
		else if (selectedr < _data.size() && key == 80) // down_arrow_key
			selectedr++;
		else if (selectedr == 0 && key == 72) // up_arrow_key
			selectedr = _data.size();
		else if (selectedr == _data.size() && key == 80) // down_arrow_key
			selectedr = 0;
		else if (selectedc > 0 && key == 75) // left_arrow_key
			selectedc--;
		else if (selectedc < _data[0].size() - 1 && key == 77) // right_arrow_key
			selectedc++;
		else if (selectedc == 0 && key == 75) // left_arrow_key
			selectedc = _data[0].size() - 1;
		else if (selectedc == _data[0].size() - 1 && key == 77) // right_arrow_key
			selectedc = 0;
		else if (key == 13) // enter_key
			break;

	} while (true);

	Cursor::remove_n_lines(2); // Extra lines are for Header
	if (selectedr == _data.size())
		return { -1, -1 };
	return { selectedr, selectedc };
}