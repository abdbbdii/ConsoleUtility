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

string TextFormatter::get_format(const string& fg, const string& bg, const bool bold, const bool underline, const bool italic, const bool strikethrough, const bool blink, const bool dim) {
	string format = "";
	if (fg != "")
		format += rgb_to_ansi(_parse_rgb(fg), true);
	if (bg != "")
		format += rgb_to_ansi(_parse_rgb(bg), false);
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

string TextFormatter::rgb_to_ansi(int r, int g, int b, const bool fg) {
	return "\033[" + to_string(fg ? 38 : 48) + ";2;" + to_string(r) + ";" + to_string(g) + ";" + to_string(b) + "m";
}

string TextFormatter::rgb_to_ansi(const vector<int>& rgb, const bool fg) {
	return rgb_to_ansi(rgb[0], rgb[1], rgb[2], fg);
}

string TextFormatter::hsl_to_ansi(int h, int s, int l, const bool fg) {
	return rgb_to_ansi(hsl_to_rgb(h, s, l), fg);
}

string TextFormatter::hsl_to_ansi(const vector<int>& hsl, const bool fg) {
	return hsl_to_ansi(hsl[0], hsl[1], hsl[2], fg);
}

string TextFormatter::hex_to_ansi(const string& hex, const bool fg) {
	return rgb_to_ansi(hex_to_rgb(hex), fg);
}

vector<int> TextFormatter::hsl_to_rgb(int h, int s, int l) {
	double H = h / 60.0;
	double S = s / 100.0;
	double L = l / 100.0;
	double C = (1 - abs(2 * L - 1)) * S;
	double X = C * (1 - abs(fmod(H, 2) - 1));
	double m = L - C / 2;
	double R, G, B;
	if (H >= 0 && H < 1) {
		R = C;
		G = X;
		B = 0;
	}
	else if (H >= 1 && H < 2) {
		R = X;
		G = C;
		B = 0;
	}
	else if (H >= 2 && H < 3) {
		R = 0;
		G = C;
		B = X;
	}
	else if (H >= 3 && H < 4) {
		R = 0;
		G = X;
		B = C;
	}
	else if (H >= 4 && H < 5) {
		R = X;
		G = 0;
		B = C;
	}
	else {
		R = C;
		G = 0;
		B = X;
	}
	return { (int)((R + m) * 255), (int)((G + m) * 255), (int)((B + m) * 255) };

}


vector<int> TextFormatter::hsl_to_rgb(const vector<int>& hsl) {
	return hsl_to_rgb(hsl[0], hsl[1], hsl[2]);
}

vector<int> TextFormatter::hex_to_rgb(const string& hex) {
	vector<int> rgb;
	for (int i = 1; i < 7; i += 2) {
		string s = hex.substr(i, 2);
		rgb.push_back(stoi(s, nullptr, 16));
	}
	return rgb;
}

vector<int> TextFormatter::rgb_to_hsl(int r, int g, int b) {
	double R = r / 255.0;
	double G = g / 255.0;
	double B = b / 255.0;
	double M = max({ R, G, B });
	double m = min({ R, G, B });
	double C = M - m;
	double H, S, L;
	if (C == 0)
		H = 0;
	else if (M == R)
		H = fmod((G - B) / C, 6);
	else if (M == G)
		H = (B - R) / C + 2;
	else
		H = (R - G) / C + 4;
	H *= 60;
	if (H < 0)
		H += 360;
	L = (M + m) / 2;
	S = C == 0 ? 0 : C / (1 - abs(2 * L - 1));
	return { (int)H, (int)(S * 100), (int)(L * 100) };
}

vector<int> TextFormatter::rgb_to_hsl(const vector<int>& rgb) {
	return rgb_to_hsl(rgb[0], rgb[1], rgb[2]);
}

vector<int> TextFormatter::hex_to_hsl(const string& hex) {
	return rgb_to_hsl(hex_to_rgb(hex));
}

string TextFormatter::rgb_to_hex(int r, int g, int b) {
	char hexColor[8];
	sprintf_s(hexColor, "#%02x%02x%02x", r, g, b);
	return string(hexColor);
}

string TextFormatter::rgb_to_hex(const vector<int>& rgb) {
	return rgb_to_hex(rgb[0], rgb[1], rgb[2]);
}

string TextFormatter::hsl_to_hex(int h, int s, int l) {
	return rgb_to_hex(hsl_to_rgb(h, s, l));
}

string TextFormatter::hsl_to_hex(const vector<int>& hsl) {
	return hsl_to_hex(hsl[0], hsl[1], hsl[2]);
}