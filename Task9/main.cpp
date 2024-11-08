#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <map>
using namespace std;

map<string, int> count_words(string str);
void str_tolower(string& str);
string find_max_count(map<string, int> words);

int main() {
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(ANSI_CHARSET);

	ifstream fin("input.txt");
	string buf = "";
	string result = "";

	while (!fin.eof()) {
		getline(fin, buf);
		result += buf;
	}
	fin.close();

	str_tolower(result);
	
	map<string, int> words = count_words(result);
	string word = find_max_count(words);

	cout << "Самое частое слово: " << word;
	cin;
	return 0;
}

bool is_letter(char symbol) {
	if (symbol <= -1 && symbol >= -32) {
		return true;
	}
	return false;
}

void str_tolower(string& str) {
	for (int i = 0; i < str.length(); i++)
	{
		str[i] = tolower(str[i]);
	}
}

map<string, int> count_words(string str) {
	map<string, int> words;
	int start_index = 0;
	for (int i = 1; i < str.length(); i++)
	{
		
		if (!is_letter(str[i]) && is_letter(str[i - 1]) && start_index < i) {
			string word = str.substr(start_index, i - start_index);
			
			start_index = i + 1;
			
			if (words.count(word) == 0) {
				words[word] = 1;
			}
			else {
				words[word]++;
			}
		}
	}

	return words;
}

string find_max_count(map<string, int> words) {
	string max_word;
	int max_count = 0;

	for (const auto& pair : words) {
		if (pair.second > max_count) {
			max_count = pair.second;
			max_word = pair.first;
		}
	}

	return max_word;
}