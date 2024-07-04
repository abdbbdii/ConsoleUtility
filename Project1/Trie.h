#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

class TrieNode {
public:
	unordered_map<char, TrieNode*> children;
	bool is_end;

public:
	TrieNode();
};

class Trie {
private:
	TrieNode* _root;

private:
	static Trie _get_words();
	void _collect_words(TrieNode* node, string currentWord, vector<string>& words, int limit);
	void _insert(const string& word);

public:
	static Trie words;

public:
	Trie();
	vector<string> get_suggestions(const string& prefix, int limit);
};