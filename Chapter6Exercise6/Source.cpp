//****I have removed the standard library here, for clarity
//If anyone understands how to:
//  a)  Incorporate articles...so that "The fish swim but the birds fly . "
// and "fish swim but the birds fly . " would be accepted as grammatically correct
//  b)  Include a smooth means of exiting
//  I would be very grateful!

//  1)  Set up some vectors, which will contain the words you will check the grammar of!
vector<string>nouns;
vector<string>verbs;
vector<string>conjunctions;

//  2) Initialize the vectors - being sure to include articles in front of the nouns
//  2b)  This function will be called by main()
void init()
{
	nouns.push_back("birds");
	nouns.push_back("fish");
	nouns.push_back("Birds");
	nouns.push_back("Fish");

	verbs.push_back("swim");
	verbs.push_back("fly");
	verbs.push_back("soar");

	conjunctions.push_back("and");
	conjunctions.push_back("but");
	conjunctions.push_back("although");
}
//   ....)  It's better to delay this step until after completing sentence() and main()

//   8)  Create an "is_noun" function.   Set up "is_verb" and "is_conjunction" at the same time.
//   8b) They should follow roughly the same thing :)
//   I create these last of all... 

bool is_noun(string input) {
	for (int i = 0; i < nouns.size(); ++i)
		if (input == nouns[i])  return true;
	//  9)  You must add a "return false", as otherwise 'not all control paths return a value' ;)
	return false;
}

bool is_verb(string input) {
	for (int i = 0; i < verbs.size(); ++i)
		if (input == verbs[i]) return true;
	return false;
}

bool is_conjunction(string input) {
	for (int i = 0; i < conjunctions.size(); ++i)
		if (input == conjunctions[i]) return true;
	return false;
}

//   5)  This function is called upon by main(), and will call on functions (created later, listed earlier)
//   to see if the sentence is viable.  Essentially, it will take the string input, and call functions
//   using that string.   The sentence must start with something from the noun vector, or this function
//   will return as false.   It must be followed by a verb, then by a conjunction...
bool sentence() {
	string w;
	cin >> w;
	if (!is_noun(w)) return false;   //5b)  Essentially, if the first word input isn't a noun,
	//the sentence will fail!

	string w2;
	cin >> w2;
	if (!is_verb(w2)) return false;   //The same logic described in 5) and 5b) applies here!

	string w3;
	cin >> w3;
	//6)   You need to incorporate a " . " before checking for that conjunction!
	
	if (w3 == ".") return true;  //Take care with this.  No space necessary.

	//7)  Next, check for a conjunction (assuming no . was entered beforehand)
	if (!is_conjunction(w3)) return false;  //This means if no conjunction is found, it's
	//neither the end of the sentence, nor was a conjunction found...

	return sentence();
}

//Note the jump!  3)  Enter your initial main().
//Prompt the user for the sentence, and write some code indicating if a sentence will be accepted or not.
int main()
try {
	cout << "Please enter your sentence, using '!' to terminate: \n";
	init();  //See 2a/2b!  This initializes the word tables.

	while (cin) {  //  4) Open up your while loop, which will INTAKE cin.
		bool b = sentence();   // It will call this function! (Which is it better to write first?  sentence() or main()?)
		if (b)
			//In other words, if sentence() returns as true...the sentence is okay.
			cout << "This sentence is grammatically correct!\n";
		else
			cout << "I'm afraid a mistake has been made\n";


	}
		//If sentence() returns as false, the sentence is incorrect!
	keep_window_open("~");
}

catch (runtime_error e) {
	cout << e.what() << '\n';
	keep_window_open("~");
}