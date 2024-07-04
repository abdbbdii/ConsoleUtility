#include "Cursor.h"

void Cursor::move_up(const int& n) {
    cout << "\033[" << n << "A";
}
void Cursor::move_down(const int& n) {
    cout << "\033[" << n << "B";
}
void Cursor::move_right(const int& n) {
    cout << "\033[" << n << "C";
}
void Cursor::move_left(const int& n) {
    cout << "\033[" << n << "D";
}
void Cursor::move_to(const int& row, const int& col) {
    cout << "\033[" << row << ";" << col << "H";
}
void Cursor::move_to_start_of_line() {
    cout << "\r";
}
void Cursor::show() {
    cout << "\033[?25h";
}
void Cursor::hide() {
    cout << "\033[?25l";
}
void Cursor::clear_line() {
    cout << "\033[2K";
}
void Cursor::clear_screen_from_cursor() {
    cout << "\033[0J";
}
void Cursor::remove_n_lines(const int& n) {
    if (n == 0)
        return;
    move_to_start_of_line();
    clear_line();
    for (int i = 0; i < n; i++) {
        move_up(1);
        clear_line();
    }
}
vector<int> Cursor::get_position() {
    cout << "\033[6n";
    char buf;
    string response;
    while (true) {
        buf = _getch();
        if (buf == 'R') {
            break;
        }
        response += buf;
    }

    int row = stoi(response.substr(2, response.find(';') - 2));
    int col = stoi(response.substr(response.find(';') + 1));
    return {row, col};
}
