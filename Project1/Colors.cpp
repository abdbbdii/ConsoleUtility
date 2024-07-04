#include "Colors.h"

string Colors::INPUT_FIELD_HEADING = TextFormatter::get_format("rgb(0, 0, 0)", "rgb(255, 255, 215)", true);
string Colors::INPUT_FIELD_TEXT = TextFormatter::get_format("rgb(255, 255, 215)");
string Colors::SELECTED = TextFormatter::get_format("rgb(0, 0, 0)", "rgb(135, 175, 255)");
string Colors::UNSELECTED = TextFormatter::get_format("rgb(255, 255, 255)", "rgb(38, 38, 38)");
string Colors::TABLE_BORDER = TextFormatter::get_format("rgb(255, 255, 255)", "rgb(58, 58, 58)");
string Colors::TABLE_HEADER = TextFormatter::get_format("rgb(255, 255, 255)", "rgb(28, 28, 28)", true);
string Colors::ERROR = TextFormatter::get_format("rgb(255, 100, 100)", "");
string Colors::SUCCESS = TextFormatter::get_format("rgb(100, 255, 100)", "");
string Colors::WARNING = TextFormatter::get_format("rgb(255, 255, 100)", "");
string Colors::INFO = TextFormatter::get_format("rgb(100, 100, 255)", "");