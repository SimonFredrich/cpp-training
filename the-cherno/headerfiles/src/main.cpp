#include <iostream>
#include "Log.h"
using namespace std;

void Log(const char* message)
{
	cout << message << endl;
}

int main()
{
	Log("Hello World!");
	cin.get();
}