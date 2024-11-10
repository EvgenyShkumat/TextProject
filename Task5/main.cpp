#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <map>
using namespace std;

void combination(string str, int& alternation_count, int& total_count);// task 5
void count_pairs(string str, int* pairs); //task 6
map<string, int> count_words(string str); //task 9 
string find_max_count(map<string, int> words);//task 9
void str_tolower(string& str);

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
	int* pairs = new int[4];
	pairs[0] = pairs[1] = pairs[2] = pairs[3] = 0;

	str_tolower(result);
	combination(result, immutability_count, total_count);
	map<string, int> words = count_words(result);
	string word = find_max_count(words);
	count_pairs(result, pairs);

	cout << "Чередование гласной и согласной: " << immutability_count << endl;
	cout << "Гласная и гласная или согласная и согласная: " << total_count - immutability_count << endl;
	cout << "Самое частое слово: " << word << endl;
	cout << "Чередования(первые буквы двух слов по парам):\nГласная-гласная: " << pairs[0] << "\nСолгасная-согласная: " 
		<< pairs[1] << "\nГласная-согласная:" << pairs[2] << "\nСогласная-гласная: " << pairs[3];

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
	bool letter = false;
	if (symbol <= -1 && symbol >= -32) {
		letter = true; 
	} 
	return letter; 
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

//counting all words
//in the line 98 cheking if the word is compound (and between two roots is '-')
map<string, int> count_words(string str) {
	map<string, int> words;
	int start_index = 0;
	for (int i = 1; i < str.length(); i++)
	{
		if ((!is_letter(str[i]) && is_letter(str[i - 1]) && start_index < i) && 
			!(str[i] == '-' && is_letter(str[i - 1]) && is_letter(str[i + 1]))) { 
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

//finding the most frequent word
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

//coutning pairs: 0 - vowel vowel; 1 - consonant consonant;
//				  2 - vowel consonant; 3 - consonant vowel
//in the line 140 cheking if the word is compound (and between two roots is '-')
void count_pairs(string str, int* pairs) {

	bool first_letter = is_vowel(str[0]); //if vowel - true; if consonant - false 
	bool second_letter;
	for (int i = 1; i < str.length(); i++)
	{
		if (is_letter(str[i]) && !is_letter(str[i - 1]) && 
			!(str[i] == '-' && is_letter(str[i - 1]) && is_letter(str[i + 1]))) {
			second_letter = is_vowel(str[i]);

			if (first_letter && second_letter) {
				pairs[0]++;
			}
			else if (!first_letter && !second_letter) {
				pairs[1]++;
			}
			else if (first_letter && !second_letter) {
				pairs[2]++;
			}
			else {
				pairs[3]++;
			}

			first_letter = second_letter;
		}
	}
}