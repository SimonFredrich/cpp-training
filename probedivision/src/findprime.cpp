bool findprime(int number)
{
	int null_mod_count = 0;
	for (int i = 1; i<=number; i++)
	{
		if (number%i==0) null_mod_count++;
	}
	if (null_mod_count == 2)
	{
		return true;
	} else {
		return false;
	}
}