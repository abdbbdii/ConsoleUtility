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

	static string rgb_to_ansi(int r, int g, int b, const bool fg = true);
	static string rgb_to_ansi(const vector<int>& rgb, const bool fg = true);
	static string hsl_to_ansi(int h, int s, int l, const bool fg = true);
	static string hsl_to_ansi(const vector<int>& hsl, const bool fg = true);
	static string hex_to_ansi(const string& hex, const bool fg = true);

	static vector<int> hsl_to_rgb(int h, int s, int l);
	static vector<int> hsl_to_rgb(const vector<int>& hsl);
	static vector<int> hex_to_rgb(const string& hex);
	
	static vector<int> rgb_to_hsl(int r, int g, int b);
	static vector<int> rgb_to_hsl(const vector<int>& rgb);
	static vector<int> hex_to_hsl(const string& hex);

	static string rgb_to_hex(int r, int g, int b);
	static string rgb_to_hex(const vector<int>& rgb);
	static string hsl_to_hex(int h, int s, int l);
	static string hsl_to_hex(const vector<int>& hsl);
};
