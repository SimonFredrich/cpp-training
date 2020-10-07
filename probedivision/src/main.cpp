#include <iostream>
#include "findprime.h"
using namespace std;

int main()
{

	int prime_count = 0;
	for (int i = 1; i < 542; i++) 
	{
		if (findprime(i)) prime_count++;
	}
	cout << prime_count << endl;
	return 0;
}