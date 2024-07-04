#include "TextFormatter.h"

string TextFormatter::RESET = "\033[0m";
string TextFormatter::BOLD = "\033[1m";
string TextFormatter::UNDERLINE = "\033[4m";
string TextFormatter::ITALIC = "\033[3m";
string TextFormatter::STRIKETHROUGH = "\033[9m";

string TextFormatter::get_format(const string& fg, const string& bg, const bool& bold, const bool& underline, const bool& italic, const bool& strikethrough) {
	return _make_format(fg, bg, bold, underline, italic, strikethrough);
}

string TextFormatter::make_color_code(const vector<int>& rgb, const bool& fg) {
	return "\033[" + to_string(fg ? 38 : 48) + ";2;" + to_string(rgb[0]) + ";" + to_string(rgb[1]) + ";" + to_string(rgb[2]) + "m";
}

string TextFormatter::_make_format(const string& fg, const string& bg, const bool& bold, const bool& underline, const bool& italic, const bool& strikethrough) {
	string format = "";
	if (fg != "")
		format += make_color_code(_parse_rgb(fg), true);
	if (bg != "")
		format += make_color_code(_parse_rgb(bg), false);
	if (bold)
		format += "\033[1m";
	if (underline)
		format += "\033[4m";
	if (italic)
		format += "\033[3m";
	if (strikethrough)
		format += "\033[9m";
	return format;
}

vector<int> TextFormatter::_parse_rgb(const string& rgb) {
	vector<int> values;
	regex colorRegex(R"(rgb\((\d+),\s*(\d+),\s*(\d+)\))");
	smatch match;
	if (regex_search(rgb, match, colorRegex)) {
		for (int i = 1; i <= 3; i++)
			values.push_back(stoi(match[i].str()));
	}
	return values;
}
