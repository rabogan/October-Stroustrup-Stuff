/*
std_lib_facilities.h
*/

/*
simple "Programming: Principles and Practice using C++ (second edition)" course header to
be used for the first few weeks.
It provides the most common standard headers (in the global namespace)
and minimal exception/error support.

Students: please don't try to understand the details of headers just yet.
All will be explained. This header is primarily used so that you don't have
to understand every concept all at once.

By Chapter 10, you don't need this file and after Chapter 21, you'll understand it

Revised April 25, 2010: simple_error() added

Revised November 25 2013: remove support for pre-C++11 compilers, use C++11: <chrono>
Revised November 28 2013: add a few container algorithms
Revised June 8 2014: added #ifndef to workaround Microsoft C++11 weakness
Revised Febrary 2 2015: randint() can now be seeded (see exercise 5.13).
Revised August 3, 2020: a cleanup removing support for ancient compilers
*/

#ifndef H112
#define H112 080315L


#include<iostream>
#include<iomanip>
#include<fstream>
#include<sstream>
#include<cmath>
#include<cstdlib>
#include<string>
#include<list>
#include <forward_list>
#include<vector>
#include<unordered_map>
#include<algorithm>
#include <array>
#include <regex>
#include<random>
#include<stdexcept>

//------------------------------------------------------------------------------


typedef long Unicode;

//------------------------------------------------------------------------------

using namespace std;

template<class T> string to_string(const T& t)
{
	ostringstream os;
	os << t;
	return os.str();
}

struct Range_error : out_of_range {	// enhanced vector range error reporting
	int index;
	Range_error(int i) :out_of_range("Range error: " + to_string(i)), index(i) { }
};


// trivially range-checked vector (no iterator checking):
template< class T> struct Vector : public std::vector<T> {
	using size_type = typename std::vector<T>::size_type;

	/* #ifdef _MSC_VER
		// microsoft doesn't yet support C++11 inheriting constructors
		Vector() { }
		explicit Vector(size_type n) :std::vector<T>(n) {}
		Vector(size_type n, const T& v) :std::vector<T>(n, v) {}
		template <class I>
		Vector(I first, I last) : std::vector<T>(first, last) {}
		Vector(initializer_list<T> list) : std::vector<T>(list) {}
	*/
	using std::vector<T>::vector;	// inheriting constructor

	T& operator[](unsigned int i) // rather than return at(i);
	{
		if (i < 0 || this->size() <= i) throw Range_error(i);
		return std::vector<T>::operator[](i);
	}
	const T& operator[](unsigned int i) const
	{
		if (i < 0 || this->size() <= i) throw Range_error(i);
		return std::vector<T>::operator[](i);
	}
};

// disgusting macro hack to get a range checked vector:
#define vector Vector

// trivially range-checked string (no iterator checking):
struct String : std::string {
	using size_type = std::string::size_type;
	//	using string::string;

	char& operator[](unsigned int i) // rather than return at(i);
	{
		if (i < 0 || size() <= i) throw Range_error(i);
		return std::string::operator[](i);
	}

	const char& operator[](unsigned int i) const
	{
		if (i < 0 || size() <= i) throw Range_error(i);
		return std::string::operator[](i);
	}
};


namespace std {

	template<> struct hash<String>
	{
		size_t operator()(const String& s) const
		{
			return hash<std::string>()(s);
		}
	};

} // of namespace std


struct Exit : runtime_error {
	Exit() : runtime_error("Exit") {}
};

// error() simply disguises throws:
inline void error(const string& s)
{
	throw runtime_error(s);
}

inline void error(const string& s, const string& s2)
{
	error(s + s2);
}

inline void error(const string& s, int i)
{
	ostringstream os;
	os << s << ": " << i;
	error(os.str());
}


template<class T> char* as_bytes(T& i)	// needed for binary I/O
{
	void* addr = &i;	// get the address of the first byte
	// of memory used to store the object
	return static_cast<char*>(addr); // treat that memory as bytes
}


inline void keep_window_open()
{
	cin.clear();
	cout << "Please enter a character to exit\n";
	char ch;
	cin >> ch;
	return;
}

inline void keep_window_open(string s)
{
	if (s == "") return;
	cin.clear();
	cin.ignore(120, '\n');
	for (;;) {
		cout << "Please enter " << s << " to exit\n";
		string ss;
		while (cin >> ss && ss != s)
			cout << "Please enter " << s << " to exit\n";
		return;
	}
}



// error function to be used (only) until error() is introduced in Chapter 5:
inline void simple_error(string s)	// write ``error: s and exit program
{
	cerr << "error: " << s << '\n';
	keep_window_open();		// for some Windows environments
	exit(1);
}

// make std::min() and std::max() accessible on systems with antisocial macros:
#undef min
#undef max


// run-time checked narrowing cast (type conversion). See ???.
template<class R, class A> R narrow_cast(const A& a)
{
	R r = R(a);
	if (A(r) != a) error(string("info loss"));
	return r;
}

// random number generators. See 24.7.

inline default_random_engine& get_rand()
{
	static default_random_engine ran;	// note: not thread_local
	return ran;
};

inline void seed_randint(int s) { get_rand().seed(s); }

inline int randint(int min, int max) { return uniform_int_distribution<>{min, max}(get_rand()); }

inline int randint(int max) { return randint(0, max); }

//inline double sqrt(int x) { return sqrt(double(x)); }	// to match C++0x

// container algorithms. See 21.9.   // C++ has better versions of this:

template<typename C>
using Value_type = typename C::value_type;

template<typename C>
using Iterator = typename C::iterator;

template<typename C>
// requires Container<C>()
void sort(C& c)
{
	std::sort(c.begin(), c.end());
}

template<typename C, typename Pred>
// requires Container<C>() && Binary_Predicate<Value_type<C>>()
void sort(C& c, Pred p)
{
	std::sort(c.begin(), c.end(), p);
}

template<typename C, typename Val>
// requires Container<C>() && Equality_comparable<C,Val>()
Iterator<C> find(C& c, Val v)
{
	return std::find(c.begin(), c.end(), v);
}

template<typename C, typename Pred>
// requires Container<C>() && Predicate<Pred,Value_type<C>>()
Iterator<C> find_if(C& c, Pred p)
{
	return std::find_if(c.begin(), c.end(), p);
}

#endif //H112

// Remember the principles of naming a program!  I have removed the std library for clarity
//This calculator differs from the original, because it includes {}!
//It was also rewritten from scratch, so as to practice concepts introduced in Chapter 6

class Token {
public:
	char kind;
	double value;
	Token (char ch) //A Token can define variables and hold values.
		:kind(ch), value(0) { }  //This member function is of a special kind called a constructor.
	//The line above means "Initialize kind to ch and set value to 0".
	Token (char ch, double val) 
		:kind (ch), value (val){}  //Constructors are used to intialize and construct Token objects
	//So, for the line above, '45' would be stored as a character of value 45.
//Note that the body of the function {} is empty.  Nothing else needs done to construct the token here.
};

//Once you write a gramar for the program, you realise that it needs functions including:
//get_token(), expression() for + and -, term() for * and /, primary() for numbers and ( ) and { }
//expression calls get() (originally get_token()) and term(); term() calls primary() and get_token;
//primary() calls expression() and get_token()
//The grammar reads:
//Expression:
//  Term
//  Expression "+" term
//  Expression "-" term
//Term:
//  Primary
//  Term "*" Primary
//  Term "/" Primary
//Primary:
//  Number
//  "(" Expression ")"
//Number:
//  floating-point-integer

//We need a stream that produces a token when we ask for one using get() and put one back using putback(),
//this part is written after the expression()/term()/primary() in the book!

class Token_stream { //We initialze class members in the member initialization list, shown in 40-48
public:
	Token_stream();  //make a Token_stream that reads from cin
	Token get();  //get a Token (get() is defined elsewhere in this program)
	void putback(Token t);  //Put a token back
private:
	bool full;  //Is there a token in the buffer?
	Token buffer;  //Here we keep a Token put back using putback()
};
//On page 7 on my explanations for this chapter, I wrote:
//We need to represent a Token_stream.   e..g What data do we need to store in a Token_stream for it to do its job?
//We need space for any token we put back in the stream.
//To simplify, let's say we put back one token at a time.
//We need space for one token   (Token buffer; is where we keep a Token put back using putback())
//We need an indicator of whether that space is full or empty (bool full; is used to check if there's a token in the buffer)


//This constructor just sets FULL to indicate that the buffer is empty!
Token_stream::Token_stream()  //This is Token_stream's constructor.   It is a member with the same name as its class.
//The dot notation class_name::member_name is used to mention which class we mean the member to be a member of!
	:full(false), buffer(0)  //The single colon here allows initialization.
{
}
// EVERY token must be initialized, so...
void Token_stream::putback(Token t)
{
	if (full) error("putback() into a full buffer");  //This test is used to make sure we don't use putback() twice...
	//...without reading what we put back in between using get()
	buffer = t;  //copy t to buffer
	full = true;  //buffer is now full
}
//In the above, the putback() member function puts its argument back into the Token_stream's buffer.


//If there isn't a Token in Token_stream::buffer, get() must read characters from cin, and compose them into Tokens!
Token Token_stream::get()
{
	if (full) {  //If we already have a token in the buffer, we just (remove?) it!
		full = false;  //Do we already have a token?
		return buffer;   //Remove the token from the buffer
	}
	char ch;  //If there's no token in the buffer, we need to mess with characters!
	cin >> ch;  //Not that >> skips whitespace (space, newline, tab, etc...)
	switch (ch) {
	case '=':  //for print!
	case 'x':  //for quit, in my version
	case '(': case ')': case '+': case '-': case '*': case '/': case '%': case '{': case '}':
		return (ch); //For simplicity, we let the kind of a token be the parentheses and operator themselves.
		//We're looking for parentheses and operators here.  We also need numbers...
	case '.':
	case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
	{  //Inputting a number to the switch converts it to a Token
		cin.putback(ch);
		double val;
		cin >> val;
		return Token('8', val);   //This is how we tell cin to turn C++ literals into values of type double!
	}
	default: //basically, any non-number/non-operator/non-parentheses/non curly-braces (exercise 2)
		//creates an error that terminates the program
		error("Bad token"); 
	}
}

Token_stream ts;  //provides get() and putback()

double expression();   //Forward declaring so that primary() can call expression()

//to deal with the numbers and parentheses:
double primary()
{
	Token t = ts.get();
	switch (t.kind) {
	case '(':
	{
		double d = expression();
		t = ts.get();
		if (t.kind != ')') error("')' expected");
			return d;
	}
	case '{':  //I made this basically the same as the (
	{
		double e = expression();
		t = ts.get();
		if (t.kind != '}') error("'}' expected");
		return e;
	}
	case '8':
		return t.value;
	default:
		error("Primary expected");
	}
}

//To deal with *, /
double term()
{
	double left = primary();
	Token t = ts.get();  //get the next token from Token_stream

	while (true) {
		switch (t.kind) {
		case '*':
			left *= primary();
			t = ts.get();
			break;
		case '/':  //Crucial!  If you want to define or initialize variables in a switch, you must put them in a block!{} 
		{
			double d = primary();
			if (d == 0) error("divide by zero");
			left /= d;
			t = ts.get();
			break;
		}
		default:
			ts.putback(t); //Places t back into the Token_stream
			return left;
		}
	}
}

double expression() {
	double left = term();
	Token t = ts.get(); //get the next token from Token_stream
	while (true) {
		switch (t.kind)
		{
		case '+':
			left += term();  //evaluate Term and add
			t = ts.get();
			break;

		case '-':
			left -= term();  //evaluate Term and subtract 
			t = ts.get();
			break;

		default:  //The token t is gonna be used by some other function reading tokens from the input...
			//...so we put the token back intot the input stream so it can be read by that function
			ts.putback(t);  //Put t back into the Token_stream
			return left;  //When there's no more + or -, return the answer.
		}
	}
}

int main()
try {
	cout << "Welcome to our simple calculator!\n";
	cout << "Please enter operations using floating-point-numbers\n";
	cout << "You can choose from the operators:  +, -, *, /, (), and {}\n";
	cout << "To print the result, use =\n";
	cout << "To quit the program, use x\n";

	while (cin) {
		cout << "> "; //prompts the user for something
		Token t = ts.get();
		while (t.kind == '=')  t = ts.get();
		if (t.kind == 'x') {
			keep_window_open();
			return 0;
		}
		ts.putback(t);
		cout << "= " << expression() << endl;
	}
	keep_window_open();
	return 0;
}

catch (exception& e) {
	cerr << "error: " << e.what() << '\n';
	keep_window_open("~~");
	return 1;
}
catch (...) {
	cerr << "Oops!  Unknown exception!\n";
}