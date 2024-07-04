# Console Utility Library

This library provides a variety of utilities for working with the console, including ANSI escape sequences for text formatting, cursor movement, and custom text and table formatting. Below is an overview of the features and how to use them.

## Features

- **ANSI Escape Sequences**: For colors, cursor movement, and text formatting.
- **Utility Functions**: General-purpose functions like splitting and joining strings, and getting keys/values from maps.
- **TextFormatter**: For applying various text styles and colors.
- **Cursor**: For moving the cursor and manipulating the console screen.
- **Console**: For printing formatted text and handling user input.
- **Table**: For displaying data in tabular format.

## Getting Started

### Prerequisites

- A C++ compiler that supports C++11 or later.
- Windows console (since the `_getch()` function is used).

### Installation

Simply include the provided header file in your C++ project:

```cpp
#include "ConsoleUtility.h"
```

### Usage

#### 1. Text Formatting

You can format text using ANSI escape sequences with the `TextFormatter` class:

```cpp
#include "ConsoleUtility.h"

int main() {
    std::cout << TextFormatter::BOLD << "Bold Text" << TextFormatter::RESET << std::endl;
    std::cout << TextFormatter::get_format("rgb(255, 0, 0)") << "Red Text" << TextFormatter::RESET << std::endl;
    return 0;
}
```

#### 2. Cursor Movement

Use the `Cursor` class to move the cursor around the console:

```cpp
#include "ConsoleUtility.h"

int main() {
    Cursor::move_to(10, 10);
    std::cout << "Text at (10, 10)" << std::endl;
    Cursor::move_up(5);
    std::cout << "Text 5 lines up" << std::endl;
    return 0;
}
```

#### 3. Console Printing

Print formatted text and handle user input with the `Console` class:

```cpp
#include "ConsoleUtility.h"

int main() {
    Console::print("Hello, World!", Colors::INFO);
    std::string input = Console::get_input("Enter your name: ");
    Console::print("Hello, " + input + "!", Colors::SUCCESS);
    return 0;
}
```

#### 4. Displaying Tables

Display data in tabular format using the `Table` class:

```cpp
#include "ConsoleUtility.h"

int main() {
    std::vector<std::string> headers = {"Name", "Age", "Country"};
    std::vector<std::vector<std::string>> data = {
        {"Alice", "30", "USA"},
        {"Bob", "25", "UK"},
        {"Charlie", "35", "Canada"}
    };

    Table table(headers, data);
    table.display();
    return 0;
}
```

#### 5. Utility Functions

Use utility functions for common tasks:

```cpp
#include "ConsoleUtility.h"

int main() {
    std::string text = "one,two,three";
    std::vector<std::string> tokens = Utils::split(text, ',');
    Utils::print_vector(tokens);
    return 0;
}
```

## Classes and Methods

### Utils

- `static std::vector<K> get_keys(const std::map<K, V>& m)`
- `static std::vector<V> get_values(const std::map<K, V>& m)`
- `static std::vector<std::string> split(const std::string& str, const char& delimiter)`
- `static std::string join(const std::vector<std::string>& arr, const std::string& delimiter)`
- `static int accumulate(std::vector<int>& arr, int start, int end)`

### TextFormatter

- `static const std::string BOLD`
- `static const std::string UNDERLINE`
- `static const std::string ITALIC`
- `static const std::string STRIKETHROUGH`
- `static const std::string RESET`
- `static std::string get_format(...)`
- `static std::string make_color_code(...)`

### Cursor

- `static void move_up(const int& n)`
- `static void move_down(const int& n)`
- `static void move_right(const int& n)`
- `static void move_left(const int& n)`
- `static void move_to(const int& row, const int& col)`
- `static void move_to_start_of_line()`
- `static void show()`
- `static void hide()`
- `static void clear_line()`
- `static void clear_screen_from_cursor()`
- `static void remove_n_lines(const int& n)`
- `static std::vector<int> get_position()`

### Console

- `static void clear()`
- `static void pause()`
- `static void print(...)`
- `static int list_selector(const std::vector<std::string>& arr, std::string heading = "")`
- `static int list_selector_alt(const std::vector<std::string>& arr, std::string heading = "")`
- `static T map_selector(const std::map<T, std::string>& options, const std::string& heading)`
- `static std::string get_input(const std::string& message, const bool& password = false)`
- `static void print_matrix(const std::vector<std::vector<int>>& matrix, bool determinant = false)`

### Table

- `Table(const std::vector<std::string>& headers, const std::vector<std::vector<std::string>>& data)`
- `Table(std::vector<std::vector<std::string>>& data)`
- `void display(int style = 0)`
- `void c_display()`
- `std::vector<int> selector()`

## License

This project is licensed under the MIT License.

## Acknowledgments

ANSI escape sequences were referenced from [fnky's gist](https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797).
