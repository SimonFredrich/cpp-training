#include <iostream>
using namespace std;

/***
 * Eine Variable nimmt einen bestimmten Platz im RAM ein.
 ***/
void variables()
{
	char a = 'A';
	int max_int = 2147483647;
	uint double_max_int = 2*max_int;
	float float_var = 5.5f; // ohne das f wäre es ein double
	double double_var = 5.2;
	bool boolean_var_1 = true;
	bool boolean_var_2 = false;

	// Werte ausgeben
	cout << a << endl 
		<< max_int << endl
		<< double_max_int << endl
		<< boolean_var_1 << endl
		<< boolean_var_2 << endl;

	// finde Größen:
	// int
	cout << sizeof(int) << endl
	// double
		<< sizeof(double) << endl
	// boolean
		<< sizeof(bool) << endl;
}