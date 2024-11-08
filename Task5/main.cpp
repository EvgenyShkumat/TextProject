#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <map>
using namespace std;

void combination(string str, int& alternation_count, int& total_count);
void str_tolower(string& str);
map<string, int> count_words(string str);
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
	
	int immutability_count = 0, total_count = 0;

	str_tolower(result);
	combination(result, immutability_count, total_count);

	cout << immutability_count << endl;
	cout << total_count << endl;

	map<string, int> words = count_words(result);
	string word = find_max_count(words);

	cout << "Самое частое слово: " << word;

	return 0;
}

//cheking if the symbol is vowel
bool is_vowel(char symbol) {
	bool vowel = false; 
	if (symbol == 'у' || symbol == 'е' || symbol == 'ы' 
		|| symbol == 'а' || symbol == 'о' || symbol == 'э' 
		|| symbol == 'я' || symbol == 'и') { 
		vowel = true; 
	}

	return vowel;
}

//cheking if the symbol is letter
bool is_letter(char symbol) {
	if (symbol <= -1 && symbol >= -32) {
		return true; 
	} 
	return false; 
}

//converting the string to lower case
void str_tolower(string& str) {
	for (int i = 0; i < str.length(); i++)
	{
		str[i] = tolower(str[i]);
	}
}

//counting the combinations: total_count - amount of all combinations
//immutability_count: amount of combinations, where the first and
//second letter are both vowels or consonants
void combination(string str, int& immutability_count, int& total_count) {
	for (int i = 0; i < str.length() - 1; i++) {
		if (is_letter(str[i]) && is_letter(str[i + 1])) {
			if (is_vowel(str[i]) == is_vowel(str[i + 1])) {
				immutability_count++;
			}
			total_count++;
		}
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

