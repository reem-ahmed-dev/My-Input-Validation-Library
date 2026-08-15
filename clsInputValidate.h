#pragma once
#include<iostream>
#include "clsDate.h";
using namespace std;

class clsInputValidate
{
public:

	//Is Number Between (short)
	static bool IsNumberBetween(short Number, short From, short To)
	{
		return (Number >= From && Number <= To) ? true : false;
	}

	//Is Number Between (int)
	static bool IsNumberBetween(int Number, int From, int To)
	{
		return (Number >= From && Number <= To) ? true : false;
	}

	//Is Number Between (double)
	static bool IsNumberBetween(double Number, double From, double To)
	{
		return (Number >= From && Number <= To) ? true : false;
	}

	//Is Number Between (float)
	static bool IsNumberBetween(double Number, double From, double To)
	{
		return (Number >= From && Number <= To) ? true : false;
	}

	//Is Date Between
	static bool IsDateBetween(clsDate Date, clsDate From, clsDate To)
	{
		if ((clsDate::IsDate1AfterDate2(Date, From) || clsDate::IsDate1EqualDate2(Date, From))
			&&
			(clsDate::IsDate1BeforeDate2(Date, To) || clsDate::IsDate1EqualDate2(Date, To))
			)
		{
			return true;
		}
		if ((clsDate::IsDate1AfterDate2(Date, To) || clsDate::IsDate1EqualDate2(Date, To))
			&&
			(clsDate::IsDate1BeforeDate2(Date, From) || clsDate::IsDate1EqualDate2(Date, From))
			)
		{
			return true;
		}

		return false;
	}

	//Read int Number
	static int ReadIntNumber(string ErrorMessage = "Invalid Number, Enter again")
	{
		int Number;
		cin >> Number;
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			cout << ErrorMessage << endl;
			cin >> Number;
		}
		return Number;
	}

	//Read int Number Between
	static int ReadIntNumberBetween(int From, int To, string ErrorMessage)
	{
		int Number = ReadIntNumber();
		while (!IsNumberBetween(Number, From, To))
		{
			cout << ErrorMessage;
			Number = ReadIntNumber();
		}
		return Number;
	}

	//Read Double Number
	static double ReadDblNumber(string ErrorMessage= "Invalid Number, Enter again")
	{
		double Number;
		cin >> Number;
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			cout << ErrorMessage << endl;
			cin >> Number;
		}
		return Number;
	}

	//Read double Number Between
	static double ReadDblNumberBetween(double From, double To, string ErrorMessage= "Invalid Number, Enter again")
	{
		double Number = ReadDblNumber();

		while (!IsNumberBetween(Number, From, To)) {
			cout << ErrorMessage;
			Number = ReadDblNumber();
		}
		return Number;
	}

	//Is Valid Date
	static bool IsValideDate(clsDate Date)
	{
		return clsDate::IsValidDate(Date);
	}


};

