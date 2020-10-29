//This upload to GitHub omits the std_lib_facilities.h"

//This program will read in digits (as strings, in fact)
//and compose them into integers.
//For example, 263 is read as the characters 2, 6, and 3.
//The program should output:
//"263: that would be 2 hundreds, 6 tens, and 3 ones."
//This will handle values of up to 4 digits!
//It adds the choice to "try again" to a program cribbed from l-paz91
//First time for me to use the .clear() function to clear the vector and restart the game!
//29th October 2020

vector<int>digits;
int number = 0;

int main() {
	cout << "Please enter up to four digits: \n";
	string digit;
	cin >> digit;
	if (digits.size() > 4)
		error("Too many numbers.");

	for (int i = 0; i < digit.size(); ++i)
		digits.push_back(digit[i] - '0');

	int mult = 1;
	for (int i = digits.size() - 1; i >= 0; --i)
	{
		number += digits[i] * mult;
		mult *= 10;
	}
	cout << number << ": ";
	switch (digits.size()) {
	case 1:
		cout << "that would be " << digits[0] << " ones." << endl;
		break;
	case 2:
		cout << "that would be " << digits[0] << " tens, and " << digits[1] << " ones." << endl;
		break;
	case 3:
		cout << "that would be " << digits[0] << " hundreds, " << digits[1] << " tens, and " << digits[2] << " ones." << endl;
		break;
	case 4:
		cout << "that would be " << digits[0] << " thousands, " << digits[1] << " hundreds " << digits[2] << " tens, and " << digits[3] << " ones." << endl;
		break;
	}
	cout << "Try again?  (y/n)\n";
	char again = ' ';
	cin >> again;
	if (again == 'y')
	{
		digits.clear();
		mult = 1;
		number = 0;
		main();
	}
	else
	keep_window_open();
	return 0;
}