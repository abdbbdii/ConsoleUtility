#pragma once

#include <regex>
#include <string>
#include <vector>

using namespace std;

class TextFormatter {
public:
    static const string BOLD;
    static const string UNDERLINE;
    static const string ITALIC;
    static const string STRIKETHROUGH;
    static const string INVERSE;
    static const string HIDE;
    static const string SHOW;
    static const string DIM;
    static const string BLINK;
    static const string RESET;

private:
    static vector<int> _parse_rgb(const string& rgb);

public:
    static string get_format(const string& fg = "", const string& bg = "", const bool bold = false, const bool underline = false, const bool italic = false, const bool strikethrough = false, const bool blink = false, const bool dim = false);
    static string make_color_code(const vector<int>& rgb, const bool fg = true);
};
