#include "Utils.h"

string Utils::strip(const string& str) {
	if (str == "")
		return str;
	string stripped = "";
	int start = 0;
	while (str[start] == ' ' || str[start] == '\t' || str[start] == '\n')
		start++;
	int end = str.length() - 1;
	while (str[end] == ' ' || str[end] == '\t' || str[end] == '\n')
		end--;
	for (int i = start; i <= end; i++)
		stripped += str[i];
	return stripped;
}

vector<string> Utils::split(const string& str, const char& delimiter) {
	vector<string> tokens;
	string token = "";
	for (char c : str) {
		if (c == delimiter) {
			tokens.push_back(token);
			token = "";
		}
		else
			token += c;
	}
	tokens.push_back(token);
	return tokens;
}

string Utils::join(const vector<string> arr, const string& delemeter) {
	string str = "";
	for (int i = 0; i < arr.size(); i++) {
		str += arr[i];
		if (i != arr.size() - 1)
			str += delemeter;
	}
	return str;
}

int Utils::accumulate(vector<int>& arr, int start, int end) {
	int sum = 0;
	for (int i = start; i < end; i++)
		sum += arr[i];
	return sum;
}

int Utils::max_column_width(const vector<string>& arr) {
	int column_width = 0;
	for (string str : arr)
		if (str.length() > column_width)
			column_width = str.length();
	return column_width;
}