Revised attempt!

class Name_value {
public:
	string name;
	int value;
	Name_value (string str, int val)
		:name(str),value(val){}
};

int main() 

try{
	cout << "Please enter name-and-value pairs such as Joe 90; terminating with 'NoName 0':\n";

	vector<Name_value>new_concept;  //Note how this Token thingy is stored in the vector now :)

	string name = " ";
	int score = 0;

	while (cin >> name >> score && !(name == "NoName" && score == 0)) {
		for (int i = 0; i < new_concept.size(); ++i)
			if (name == new_concept[i].name) error("name occurs twice: ", name);
		new_concept.push_back(Name_value(name, score));
	}


	//to print the list of name/value pairs...

	for (int i = 0; i < new_concept.size(); ++i)
	{
		cout << "(" << new_concept[i].name << ',' << new_concept[i].value << ")" << endl;
	}

}
catch (exception& e) {
	cerr << "error: " << e.what() << '\n';
	keep_window_open();
	return 1;
}
catch (...) {
	cerr << "Oops: unknown exception!\n";
	keep_window_open();
	return 2;
}