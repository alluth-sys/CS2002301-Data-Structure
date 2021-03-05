#include <iostream>
#include <vector>


using namespace std;


vector<string>symmetric(int n);

int main() {
	int input;
	vector<string> result;


	while (cin >> input) {
		result = symmetric(input);

		for (int i = 0; i < result.size(); i++) {
			if(result[i][0]!='0'){
				cout << result[i] << endl;
			}
		}
	}
}

vector<string>symmetric(int n) {
	vector<string>middle;

	vector<string>sym1{ "0","1","8" };
	vector<string>sym2{ "00","11","88","69","96" };

	if (n == 1) {
		return sym1;
	}
	else if (n == 2) {
		return sym2;
	}
	else {

		middle = symmetric(n - 2);
		vector<string> result;
		
		for (int i = 0; i < middle.size(); i++) {
			result.push_back("0" + middle[i] + "0");
			result.push_back("1" + middle[i] + "1");
			result.push_back("8" + middle[i] + "8");
			result.push_back("6" + middle[i] + "9");
			result.push_back("9" + middle[i] + "6");

		}
		return result;	
	}
}
