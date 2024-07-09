#pragma once

#include <string>
#include "Console.h"
#include "Cursor.h"

using namespace std;

class Transition {
public:
	static void rgb(const string& s, const int duration = 1000, const int speed = 50, bool reverse = false);
	static void fade(const string& s, const int speed = 1, const int start = 0, const int end = 256);
	static void glitch_color(const string& s, const int duration = 1000, const int speed = 50);
	static void glitch_text(const string& s, const int duration = 1000, const int speed = 50);
};