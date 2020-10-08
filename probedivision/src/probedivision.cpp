#include <iostream>
#include "probedivision.h"
#include "findprime.h"

using namespace std;

// TODO: something with sqrt(n)

void probedivision(int n)
{
	for (int i = 2; i <= n; i++)
	{
		if (findprime(i))
		{
			if (n%i==0)
			{
				cout << i << endl;
			}
		}
	}
}