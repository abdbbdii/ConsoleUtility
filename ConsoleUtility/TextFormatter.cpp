#include "TextFormatter.h"

const string TextFormatter::RESET = "\033[0m";
const string TextFormatter::BOLD = "\033[1m";
const string TextFormatter::UNDERLINE = "\033[4m";
const string TextFormatter::ITALIC = "\033[3m";
const string TextFormatter::STRIKETHROUGH = "\033[9m";
const string TextFormatter::INVERSE = "\033[7m";
const string TextFormatter::HIDE = "\033[8m";
const string TextFormatter::SHOW = "\033[28m";
const string TextFormatter::DIM = "\033[2m";
const string TextFormatter::BLINK = "\033[5m";

string TextFormatter::get_format(const string& fg, const string& bg, const bool bold, const bool underline, const bool italic, const bool strikethrough, const bool blink, const bool dim) {
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
	if (blink)
		format += "\033[5m";
	if (dim)
		format += "\033[2m";
	return format;
}

string TextFormatter::make_color_code(const vector<int>& rgb, const bool fg) {
	return "\033[" + to_string(fg ? 38 : 48) + ";2;" + to_string(rgb[0]) + ";" + to_string(rgb[1]) + ";" + to_string(rgb[2]) + "m";
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
