#include <algorithm>
#include <string>
#include <set>
#include <iostream>
#include <iterator>
#include <vector>
#include <fstream>
using namespace std;

#define MAX 39397


//Hash function
unsigned int djb2(string& word) {
	unsigned hash = 5381;
	for (int i = 0; i < word.size(); i++) {
		hash = ((hash << 5) + hash) + word[i];
	}
	return (hash % MAX);
}

class Dictionary {
public:
	vector<string> chain[MAX];
	void insert(string data) {
		unsigned int index;
		index = djb2(data);
		chain[index].push_back(data);
	}
	bool search(string data) {
		unsigned int index;
		index = djb2(data);
		vector<string>::iterator it;
		it = find(chain[index].begin(), chain[index].end(), data);
		if (it != chain[index].end()) {
			return true;
		}
		else {
			return false;
		}
	}
};

void makeConfusableSet(Dictionary& dict, set<string>& result, const string& word, bool flag);

void insertStr(Dictionary& dict, set<string>& result, const string& word, bool flag) {
	string possibleWord(word.length() + 1, 'x');

	for (int i = 0; i <= word.length(); ++i) {
		for (int j = 0, Indx = 0; j <= word.length(); ++j) {
			if (i != j) {
				possibleWord[j] = word[Indx];
				Indx++;
			}
		}
		for (char c = 'a'; c <= 'z'; c++) {
			possibleWord[i] = c;
			if (dict.search(possibleWord)) {
				result.insert(possibleWord);
			}

			//because the edit distance can be 2 do again but set flag to false
			if (flag == true) {
				makeConfusableSet(dict, result, possibleWord, false);
			}
		}
	}

}


void deleteStr(Dictionary& dict, set<string>& result, const string& word, bool flag) {
	string possibleWord(word.length() - 1, 'X');
	for (int i = 0; i < word.length(); ++i) {
		for (int j = 0, Indx = 0; j < word.length(); ++j) {
			if (i != j) {
				possibleWord[Indx] = word[j];
				Indx++;

			}
		}
		if (dict.search(possibleWord)) {
			result.insert(possibleWord);
		}

		//because the edit distance can be 2 do again but set flag to false
		if (flag == true) {
			makeConfusableSet(dict, result, possibleWord, false);
		}

	}
}

void subtituteStr(Dictionary& dict, set<string>& result, const string& word, bool flag) {
	string possibleWord = word;
	for (int i = 0; i < word.length(); i++) {
		for (char c = 'a'; c <= 'z'; c++) {
			possibleWord[i] = c;

			if (dict.search(possibleWord)) {
				result.insert(possibleWord);
			}
			//because the edit distance can be 2 do again but set flag to false
			if (flag == true) {
				makeConfusableSet(dict, result, possibleWord, false);
			}
		}
		possibleWord[i] = word[i];
	}
}

void transposeStr(Dictionary& dict, set<string>& result, const string& word, bool flag) {
	string possibleWord = word;
	for (int i = 0; i < word.length() - 1; i++) {

		swap(possibleWord[i], possibleWord[i + 1]);

		if (dict.search(possibleWord)) {
			result.insert(possibleWord);
		}
		if (flag == true) {
			makeConfusableSet(dict, result, possibleWord, false);
		}
		swap(possibleWord[i], possibleWord[i + 1]);
	}
}



void makeConfusableSet(Dictionary& dict, set<string>& result, const string& word, bool flag) {
	insertStr(dict, result, word, flag);
	deleteStr(dict, result, word, flag);
	subtituteStr(dict, result, word, flag);
	transposeStr(dict, result, word, flag);
}


int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	Dictionary dictionary;
	string input;

	ifstream dict;
	dict.open("dictionary.txt");
	while (getline(dict, input)) {
		dictionary.insert(input);
	}
	dict.close();

	//input the test case
	ifstream test_input;
	test_input.open("test.txt");

	//output the result to answer.csv
	ofstream output;
	output.open("answer.csv");

	//write file
	output << "word,answer" << endl;

	while (getline(test_input, input)) {
		output << input << ",";
		if (dictionary.search(input)) {
			output << "OK" << endl;
		}
		else {
			set<string> recommendation;
			makeConfusableSet(dictionary, recommendation, input, true);
			if (recommendation.size() != 0) {
				for (auto i = recommendation.begin(); i != recommendation.end(); i++) {
					if (i == prev(recommendation.end())) {
						output << *i;
					}
					else {
						output << *i << ' ';
					}
				}
			}
			else {
				output << "NONE";
			}
			output << endl;
		}
	}
	test_input.close();
	output.close();
	cout << "Done" << endl;
}

