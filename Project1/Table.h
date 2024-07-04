#pragma once

#include "Colors.h"
#include "Console.h"
#include "Cursor.h"
#include "Utils.h"
#include <conio.h>
#include <fcntl.h>
#include <io.h>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Table {
private:
    vector<string> _headers = {};
    vector<vector<string>> _data = { {} };
    vector<int> _column_widths = {};
    int _total_width = 0;
    static const vector<vector<vector<wstring>>> _styles;

private:
    void _display_column_separator(int position, int style = 0);
    void _display_column(const vector<string>& column, const bool& heading = false, const bool& centered = true, int style = 0);
    void _c_display_column_separator();
    void _c_display_column(const vector<string>& column, const bool& heading = false, const bool& centered = true);
    void _calculate_widths();

public:
    Table();
    Table(const vector<string>& headers, const vector<vector<string>>& data);
    Table(vector<vector<string>>& data);
    void display(int style = 0);
    void c_display();
    vector<int> selector();
    vector<int> selector_alt();
};