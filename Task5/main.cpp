#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
using namespace std;

void combination(string str, int& alternation_count, int& total_count);
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

	str_tolower(result);
	combination(result, immutability_count, total_count);

	cout << immutability_count << endl;
	cout << total_count;

	return 0;
}

//cheking if the symbol is vowel
bool is_vowel(char symbol) {
	bool vowel = false; 
	if (symbol == 'ó' || symbol == 'å' || symbol == 'û' 
		|| symbol == 'à' || symbol == 'î' || symbol == 'ý' 
		|| symbol == 'ÿ' || symbol == 'è') { 
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

