#pragma once

#include <regex>
#include <string>
#include <vector>

using namespace std;

class TextFormatter {
public:
    static string BOLD;
    static string UNDERLINE;
    static string ITALIC;
    static string STRIKETHROUGH;
    static string RESET;

private:
    static string _make_format(const string& fg, const string& bg, const bool& bold, const bool& underline, const bool& italic, const bool& strikethrough);
    static vector<int> _parse_rgb(const string& rgb);

public:
    static string get_format(const string& fg = "", const string& bg = "", const bool& bold = false, const bool& underline = false, const bool& italic = false, const bool& strikethrough = false);
    static string make_color_code(const vector<int>& rgb, const bool& fg = true);
};
