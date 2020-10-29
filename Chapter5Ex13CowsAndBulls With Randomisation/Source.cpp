#include <iostream>
#include <time.h>
#include <vector>
#include <string>

using namespace std;

string comp_generated() {
	srand(time(0));
	int secret_no = rand() % 9000 + 1000;
	return to_string(secret_no);
}

string user_guess() {
	int guess = 0;
	cin >> guess;
	while (guess < 1000 || guess>9999) {
		cout << "Sorry, pal, you'll have to do better than that!" << endl;
		cin >> guess;
	}
	return to_string(guess);
}

int bull_count(string secret_number, string user_number, bool comp_digit[], bool user_digit[]) {
	int bulls = 0;
	for (int i = 0; i < 4; ++i) {
		if (secret_number[i] == user_number[i]) {
			++bulls;
			comp_digit[i] = true;
			user_digit[i] = true;
		}
	}
	return bulls;
}

int cow_count(string secret_number, string user_number, bool comp_digit[], bool user_digit[]) {
	int cows = 0;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (comp_digit[i] || user_digit[j])
				continue;

			if (secret_number[i] == user_number[j]) {
				++cows;
				comp_digit[i] = true;
				user_digit[j] = true;
			}
		}
	}
	return cows;
}

int main() {
	cout << "Generating secret number: " << endl;
	string secret_number = comp_generated();
	cout << "Successfully generated!  Now...how about your guess?" << endl;

	int nturns = 0;

	while (true) {
		string user_number = user_guess();
		nturns++;
		bool comp_digit[4] = { false, false,false,false };
		bool user_digit[4] = { false, false, false, false };
		int bull = bull_count(secret_number, user_number, comp_digit, user_digit);
		if (bull == 4) {
			cout << "Congratulations, you've solved the puzzle!" << endl;
			break;
		}

		int cow = cow_count(secret_number, user_number, comp_digit, user_digit);
		cout << "So far, there are " << bull << " bulls, and " << cow << " cows, from " << nturns << " attempts." << endl;
	}
}