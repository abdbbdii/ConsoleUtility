#include "Trie.h"

TrieNode::TrieNode() : is_end(false) {}

Trie Trie::words = _get_words();

Trie Trie::_get_words() {
	Trie trie;
	ifstream file("words.txt");
	string word;
	while (file >> word)
		trie._insert(word);
	file.close();
	return trie;
}

void Trie::_collect_words(TrieNode* node, string currentWord, vector<string>& words, int limit) {
	if (node->is_end)
		words.push_back(currentWord);
	for (auto& pair : node->children) {
		if (words.size() >= limit)
			return;
		_collect_words(pair.second, currentWord + pair.first, words, limit);
	}
}

void Trie::_insert(const string& word) {
	TrieNode* current = _root;
	for (char c : word) {
		if (current->children.find(c) == current->children.end())
			current->children[c] = new TrieNode();
		current = current->children[c];
	}
	current->is_end = true;
}

Trie::Trie() : _root(new TrieNode()) {}


vector<string> Trie::get_suggestions(const string& prefix, int limit) {
	TrieNode* current = _root;
	vector<string> suggestions;
	for (char c : prefix) {
		if (current->children.find(c) == current->children.end())
			return suggestions;
		current = current->children[c];
	}
	_collect_words(current, prefix, suggestions, limit);
	return suggestions;
}