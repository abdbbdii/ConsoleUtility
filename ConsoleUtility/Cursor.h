#pragma once

#include <conio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Cursor {
public:
    static void move_up(const int& n);
    static void move_down(const int& n);
    static void move_right(const int& n);
    static void move_left(const int& n);
    static void move_to(const int& row, const int& col);
    static void move_to_start_of_line();
    static void show();
    static void hide();
    static void clear_line_to_cursor();
    static void clear_line_from_cursor();
    static void clear_line();
    static void remove_n_lines(const int& n);
    static void clear_screen_to_cursor();
    static void clear_screen_from_cursor();
    static void clear_screen();
    static void save_position();
    static void restore_position();
    static void save_screen();
    static void restore_screen();
    static void save_screen_alt();
    static void restore_screen_alt();
    static vector<int> get_position();
    static vector<int> get_screen_size();
};