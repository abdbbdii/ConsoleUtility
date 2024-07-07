#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <unordered_map>
#include <fstream>

using namespace std;

class Utils {
public:
	static string strip(const string& str);
	static vector<string> split(const string& str, const char& delimiter);
	static string join(const vector<string> arr, const string& delemeter);
	static int accumulate(vector<int>& arr, int start, int end);
	static int max_column_width(const vector<string>& arr);
	static void save_csv(const string& filename, const vector<vector<string>>& data, const vector<string>& headers = {}, const string& delimiter = ",");
	static vector<vector<string>> load_csv(const string& filename, const bool include_first_row = true, const string& delimiter = ",");

	template <typename K, typename V>
	static vector<K> get_keys(const unordered_map<K, V>& m) {
		vector<K> keys;
		for (const auto& pair : m) {
			keys.push_back(pair.first);
		}
		return keys;
	}

	template <typename K, typename V>
	static vector<V> get_values(const unordered_map<K, V>& m) {
		vector<V> values;
		for (const auto& pair : m) {
			values.push_back(pair.second);
		}
		return values;
	}

	template <typename T>
	static void print_vector(const vector<T>& arr) {
		cout << "{ ";
		for (int i = 0; i < arr.size(); i++) {
			cout << arr[i] << ((i < arr.size() - 1) ? ", " : "");
		}
		cout << " }" << endl;
	}
};
