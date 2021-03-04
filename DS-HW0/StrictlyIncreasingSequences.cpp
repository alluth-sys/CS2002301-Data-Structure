#include <iostream>
using namespace std;

int main() {

	std::ios::sync_with_stdio(false);
	cin.tie(0);

	int N, T;
	int* database;

	while (cin >> N >> T) {
		int current = 0;
		int count = 0;

		database = new int[N];
		cin >> database[current]; // insert the first one
		current++;

		for (int i = 1; i < N; i++) {
			//Check after T number
			if (i >= T-1) {
				cin >> database[current];
				current++;
				
				for (int k = 0; k < T-1; k++) {
					if (database[current-1]-(k+1) == database[current-2-k]) {
						count++;
					}
					else {
						count = 0;
						break;
					}
				}
				if(count==T-1){
					current -= T ;
					count = 0;
				}
			}
			else {
				cin >> database[current];
				current++;
			}

		}

		//print
		for (int j = 0; j < current; j++) {
			cout << database[j] << " ";
		}
		cout << endl;

	}
}
