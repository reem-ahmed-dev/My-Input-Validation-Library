#pragma once
#pragma warning(disable:4996)
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
using namespace std;
class clsDate
{
private:

	short _Day = 1;
	short _Month = 1;
	short _Year = 2026;
public:

	clsDate()
	{
		time_t t = time(0);
		tm* now = localtime(&t);
		_Year = now->tm_year + 1900;
		_Month = now->tm_mon + 1;
		_Day = now->tm_mday;
	}
	
	clsDate(string Date)
	{
		vector <string> vDate;
		vDate = SplitString(Date, "/");
		_Day = stoi(vDate[0]);
		_Month = stoi(vDate[1]);
		_Year = stoi(vDate[2]);
	}

	clsDate(int Day, int Month, int Year)
	{
		_Day = Day;
		_Month = Month;
		_Year = Year;
	}

	clsDate(int Period, int Year)
	{
		clsDate Date1=GetDateFromDayOrderInYear(Period,Year);
		_Day = Date1.Day;
		_Month = Date1.Month;
		_Year=Date1.Year;
	}

	void SetDay(short Day) {
		_Day = Day;
	}
	short GetDay() {
		return _Day;
	}
	__declspec(property(get = GetDay, put = SetDay)) short Day;
	
	void SetMonth(short Month) {
		_Month = Month;
	}
	short GetMonth() {
		return _Month;
	}
	__declspec(property(get = GetMonth, put = SetMonth)) short Month;
	
	void SetYear(short Year) {
		_Year = Year;
	}
	short GetYear() {
		return _Year;
	}
	__declspec(property(get = GetYear, put = SetYear)) short Year;

	// Print Date
	void Print()
	{
		cout << DateToString() << endl;
	}

	// Is Leap Year
	static bool isLeapYear(short Year)
	{
		return (Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0);
	}
	bool isLeapYear()
	{
		return isLeapYear(_Year);
	}

	// Number Of Days In Year
	static short NumberOfDaysInAYear(short Year)
	{
		return isLeapYear(Year) ? 366 : 365;
	}
	short NumberOfDaysInAYear()
	{
		return NumberOfDaysInAYear(_Year);
	}
	
	// Number Of Hours In Year
	static short NumberOfHoursInAYear(short Year)
	{
		return NumberOfDaysInAYear(Year) * 24;
	}
	short NumberOfHoursInAYear()
	{
		return NumberOfHoursInAYear(_Year);
	}
	
	// Number Of Minutes In Year
	static int NumberOfMinutesInAYear(short Year)
	{
		return NumberOfHoursInAYear(Year) * 60;
	}
	int NumberOfMinutesInAYear()
	{
		return NumberOfMinutesInAYear(_Year);
	}
	
	// Number Of Seconds In Year
	static int NumberOfSecondsInAYear(short Year)
	{
		return NumberOfMinutesInAYear(Year) * 60;
	}
	int NumberOfSecondsInAYear()
	{
		return NumberOfSecondsInAYear(_Year);
	}
	
	// Number Of Days In Month
	static short NumberOfDaysInAMonth(short Month, short Year)
	{
		if (Month < 1 || Month>12)
			return 0;
		int NumberOfDays[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
		return (Month == 2) ? (isLeapYear(Year) ? 29 : 28) : NumberOfDays[Month - 1];
	}
	short NumberOfDaysInAMonth()
	{
		return NumberOfDaysInAMonth(_Month, _Year);
	}

	// Day Of Week Order
	static short DayOfWeekOrder(short Day, short Month, short Year)
	{
		short a, y, m;
		a = (14 - Month) / 12;
		y = Year - a;
		m = Month + (12 * a) - 2;
		// Gregorian:
		//0:sun, 1:Mon, 2:Tue...etc
		return (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
	}
	short DayOfWeekOrder()
	{
		return DayOfWeekOrder(_Day, _Month, _Year);
	}

	// Day Short Name
	static string DayShortName(short Day, short Month, short Year)
	{
		string arrDayNames[] = {
		"Sun","Mon","Tue","Wed","Thu","Fri","Sat" };
		return arrDayNames[DayOfWeekOrder(Day, Month, Year)];
	}
	static string DayShortName(short DayOfWeekOrder)
	{
		string arrDayNames[] = {
		"Sun","Mon","Tue","Wed","Thu","Fri","Sat" };
		return arrDayNames[DayOfWeekOrder];
	}
	string DayShortName()
	{
		return DayShortName(DayOfWeekOrder(_Day,_Month,_Year));
	}

	// Month Short Name
	static string MonthShortName(short MonthNumber)
	{
		string Months[12] = { "Jan", "Feb", "Mar",
		"Apr", "May", "Jun",
		"Jul", "Aug", "Sep",
		"Oct", "Nov", "Dec"
		};
		return (Months[MonthNumber - 1]);
	}
	string MonthShortName()
	{
		return MonthShortName(_Month);
	}

	// Print Month Calendar
	static void PrintMonthCalendar(short Month, short Year)
	{
		int NumberOfDays;
		// Index of the day from 0 to 6
		int current = DayOfWeekOrder(1, Month, Year);
		NumberOfDays = NumberOfDaysInAMonth(Month, Year);
		// Print the current month name
		printf("\n _______________%s_______________\n\n", MonthShortName(Month).c_str());
		// Print the columns
		printf(" Sun Mon Tue Wed Thu Fri Sat\n");
		// Print appropriate spaces
		int i;
		for (i = 0; i < current; i++)
			printf(" ");
		for (int j = 1; j <= NumberOfDays; j++)
		{
			printf("%5d", j);
			if (++i == 7)
			{
				i = 0;
				printf("\n");
			}
		}
		printf("\n _________________________________\n");
	}
	void PrintMonthCalendar()
	{
		PrintMonthCalendar(_Month, _Year);
	}

	// Print Year Calendar
	static void PrintYearCalendar(int Year)
	{
		printf("\n _________________________________\n\n");
		printf(" Calendar - %d\n", Year);
		printf(" _________________________________\n");
		for (int i = 1; i <= 12; i++)
		{
			PrintMonthCalendar(i, Year);
		}
		return;
	}
	void PrintYearCalendar()
	{
		PrintYearCalendar(_Year);
	}

	// Number Of Days From The Begining Of The Year
	static short NumberOfDaysFromTheBeginingOfTheYear(short Day, short Month, short Year)
	{
		short TotalDays = 0;
		for (int i = 1; i <= Month - 1; i++)
		{
			TotalDays += NumberOfDaysInAMonth(i, Year);
		}
		TotalDays += Day;
		return TotalDays;
	}
	short NumberOfDaysFromTheBeginingOfTheYear()
	{
		return NumberOfDaysFromTheBeginingOfTheYear(_Day, _Month,_Year);
	}

	// Get Date From Day Order In Year
	static clsDate GetDateFromDayOrderInYear(short DateOrderInYear, short Year)
	{
		clsDate Date;
		short RemainingDays = DateOrderInYear;
		short MonthDays = 0;
		Date.Year = Year;
		Date.Month = 1;
		while (true)
		{
			MonthDays = NumberOfDaysInAMonth(Date.Month, Year);
			if (RemainingDays > MonthDays)
			{
				RemainingDays -= MonthDays;
				Date.Month++;
			}
			else
			{
				Date.Day = RemainingDays;
				break;
			}
		}
		return Date;
	}
	clsDate GetDateFromDayOrderInYear(short DateOrderInYear)
	{
		return GetDateFromDayOrderInYear(DateOrderInYear,_Year);
	}

	// Date Add Days
	static void DateAddDays(short Days, clsDate &Date)
	{
		short RemainingDays = Days +NumberOfDaysFromTheBeginingOfTheYear(Date._Day, Date._Month,Date._Year);
		short MonthDays = 0;
		Date._Month = 1;
		while (true)
		{
			MonthDays = NumberOfDaysInAMonth(Date._Month, Date._Year);
			if (RemainingDays > MonthDays)
			{
				RemainingDays -= MonthDays;
				Date._Month++;
				if (Date._Month > 12)
				{
					Date._Month = 1;
					Date._Year++;
				}
			}
			else
			{
				Date._Day = RemainingDays;
				break;
			}
		}
	}
	void DateAddDays(short Days)
	{
		DateAddDays(Days, *this);
	}

	// Is Date1 Before Date2
	static bool IsDate1BeforeDate2(clsDate Date1, clsDate Date2)
	{
		return (Date1._Year < Date2._Year) ? true : ((Date1._Year ==
			Date2._Year) ? (Date1._Month < Date2._Month ? true : (Date1._Month ==
				Date2._Month ? Date1._Day < Date2._Day : false)) : false);
	}
	bool IsDate1BeforeDate2(clsDate Date2)
	{
		return IsDate1BeforeDate2(*this, Date2);
	}

	// Is Date1 Equal Date2
	static bool IsDate1EqualDate2(clsDate Date1,clsDate Date2)
	{
		return (Date1._Year == Date2._Year) ? ((Date1._Month ==
			Date2._Month) ? ((Date1._Day == Date2._Day) ? true : false)
			: false) : false;
	}
	bool IsDate1EqualDate2(clsDate Date2)
	{
		return IsDate1EqualDate2(*this, Date2);
	}

	// Is Last Day In Month
	static bool IsLastDayInMonth(clsDate Date)
	{
		return (Date._Day == NumberOfDaysInAMonth(Date._Month,
			Date._Year));
	}
	bool IsLastDayInMonth()
	{
		return IsLastDayInMonth(*this);
	}

	// Is Last Month In Year
	static bool IsLastMonthInYear(short Month)
	{
		return (Month == 12);
	}
	bool IsLastMonthInYear()
	{
		return IsLastMonthInYear(_Month);
	}

	// Increase Date By One Day
	static void IncreaseDateByOneDay(clsDate &Date)
	{
		if (IsLastDayInMonth(Date))
		{
			if (IsLastMonthInYear(Date._Month))
			{
				Date._Month = 1;
				Date._Day = 1;
				Date._Year++;
			}
			else
			{
				Date._Day = 1;
				Date._Month++;
			}
		}
		else
		{
			Date._Day++;
		}
	}
	void IncreaseDateByOneDay()
	{
		IncreaseDateByOneDay(*this);
	}

	// Get Difference In Days
	static int GetDifferenceInDays(clsDate Date1, clsDate Date2, bool IncludeEndDay = false)
	{
		int Days = 0;
		short SawpFlagValue = 1;
		if (!IsDate1BeforeDate2(Date1, Date2))
		{
			//Swap Dates
			SwapDates(Date1, Date2);
			SawpFlagValue = -1;
		}
		while (IsDate1BeforeDate2(Date1, Date2))
		{
			Days++;
			IncreaseDateByOneDay(Date1);
		}
		return IncludeEndDay ? ++Days * SawpFlagValue : Days *SawpFlagValue;
	}
	int GetDifferenceInDays(clsDate Date2,bool IncludeEndDay = false)
	{
		return GetDifferenceInDays(*this, Date2, IncludeEndDay);
	}

	// Get System Date
	static clsDate GetSystemDate()
	{
		time_t t = time(0);
		tm* now = localtime(&t);
		short Day, Month, Year;
		Year = now->tm_year + 1900;
		Month = now->tm_mon + 1;
		Day = now->tm_mday;

		return clsDate(Day, Month, Year);
	}

	// Swap Dates
	static void SwapDates(clsDate& Date1, clsDate& Date2)
	{
		clsDate TempDate;
		TempDate = Date1;
		Date1 = Date2;
		Date2 = TempDate;
	}
	void SwapDates(clsDate &Date2)
	{
		SwapDates(*this, Date2);
	}

	// Increase Date By One Week
	static void IncreaseDateByOneWeek(clsDate &Date)
	{
		for (int i = 1; i <= 7; i++)
		{
			IncreaseDateByOneDay(Date);
		}
	}
	void IncreaseDateByOneWeek()
	{
		IncreaseDateByOneWeek(*this);
	}

	// Increase Date By X Weeks
	static void IncreaseDateByXWeeks(short Weeks, clsDate &Date)
	{
		for (short i = 1; i <= Weeks; i++)
		{
			IncreaseDateByOneWeek(Date);
		}
	}
	void IncreaseDateByXWeeks(short Weeks)
	{
		IncreaseDateByXWeeks(Weeks, *this);
	}

	// Increase Date By One Month
	static void IncreaseDateByOneMonth(clsDate &Date)
	{
		if (Date._Month == 12)
		{
			Date._Month = 1;
			Date._Year++;
		}
		else
		{
			Date._Month++;
		}
		short NumberOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date._Month, Date._Year);
		if (Date._Day > NumberOfDaysInCurrentMonth)
		{
			Date._Day = NumberOfDaysInCurrentMonth;
		}
	}
	void IncreaseDateByOneMonth()
	{
		IncreaseDateByOneMonth(*this);
	}

	// Increase Date By X Days
	static void IncreaseDateByXDays(short Days, clsDate &Date)
	{
		for (short i = 1; i <= Days; i++)
		{
			IncreaseDateByOneDay(Date);
		}
	}
	void IncreaseDateByXDays(short Days)
	{
		IncreaseDateByXDays(Days, *this);
	}

	// Increase Date By X Months
	static void IncreaseDateByXMonths(short Months, clsDate &Date)
	{
		for (short i = 1; i <= Months; i++)
		{
			IncreaseDateByOneMonth(Date);
		}
	}
	void IncreaseDateByXMonths(short Months)
	{
		IncreaseDateByXMonths(Months, *this);
	}

	// Increase Date By One Year
	static void IncreaseDateByOneYear(clsDate &Date)
	{
		Date._Year++;
	}
	void IncreaseDateByOneYear()
	{
		IncreaseDateByOneYear(*this);
	}

	//Increase Date By X Years
	static void IncreaseDateByXYears(short Years, clsDate &Date)
	{
		Date._Year += Years;
	}
	void IncreaseDateByXYears(short Days)
	{
		IncreaseDateByXYears(Days, *this);
	}

	//Increase Date By One Decade
	static void IncreaseDateByOneDecade(clsDate &Date)
	{
		Date._Year += 10;
	}
	void IncreaseDateByOneDecade()
	{
		IncreaseDateByOneDecade(*this);
	}

	//Increase Date By X Decade
	static void IncreaseDateByXDecades(short Decade, clsDate &Date)
	{
		Date._Year += Decade * 10;
	}
	void IncreaseDateByXDecades(short Decade)
	{
		IncreaseDateByXDecades(Decade, *this);
	}

	//Increase Date By One Century
	static void IncreaseDateByOneCentury(clsDate &Date)
	{
		Date._Year += 100;
	}
	void IncreaseDateByOneCentury()
	{
		IncreaseDateByOneCentury(*this);
	}

	//Increase Date By One Millennium
	static void IncreaseDateByOneMillennium(clsDate &Date)
	{
		Date._Year += 1000;
	}
	void IncreaseDateByOneMillennium()
	{
		IncreaseDateByOneMillennium(*this);
	}

	//Decrease Date By One Day
	static void DecreaseDateByOneDay(clsDate &Date)
	{
		if (Date._Day == 1)
		{
			if (Date._Month == 1)
			{
				Date._Month = 12;
				Date._Day = 31;
				Date._Year--;
			}
			else
			{
				Date._Month--;
				Date._Day = NumberOfDaysInAMonth(Date._Month,Date._Year);
			}
		}
		else
		{
			Date._Day--;
		}
	}
	void DecreaseDateByOneDay()
	{
		 DecreaseDateByOneDay(*this);
	}

	//Decrease Date By One Week
	static void DecreaseDateByOneWeek(clsDate &Date)
	{
		for (int i = 1; i <= 7; i++)
		{
			DecreaseDateByOneDay(Date);
		}
	}
	void DecreaseDateByOneWeek()
	{
		DecreaseDateByOneWeek(*this);
	}

	//Decrease Date By X Weeks
	static void DecreaseDateByXWeeks(short Weeks, clsDate &Date)
	{
		for (short i = 1; i <= Weeks; i++)
		{
			DecreaseDateByOneWeek(Date);
		}
	}
	void DecreaseDateByXWeeks(short Weeks)
	{
		DecreaseDateByXWeeks(Weeks, *this);
	}

	//Decrease Date By One Month
	static void DecreaseDateByOneMonth(clsDate &Date)
	{
		if (Date._Month == 1)
		{
			Date._Month = 12;
			Date._Year--;
		}
		else
			Date._Month--;
		short NumberOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date._Month, Date._Year);
		if (Date._Day > NumberOfDaysInCurrentMonth)
		{
			Date._Day = NumberOfDaysInCurrentMonth;
		}
	}
	void DecreaseDateByOneMonth()
	{
		DecreaseDateByOneMonth(*this);
	}

	//Decrease Date By X Days
	static void DecreaseDateByXDays(short Days, clsDate &Date)
	{
		for (short i = 1; i <= Days; i++)
		{
			DecreaseDateByOneDay(Date);
		}
	}
	void DecreaseDateByXDays(short Days)
	{
		DecreaseDateByXDays(Days, *this);
	}

	//Decrease Date By X Months
	static void DecreaseDateByXMonths(short Months, clsDate &Date)
	{
		for (short i = 1; i <= Months; i++)
		{
			DecreaseDateByOneMonth(Date);
		}
	}
	void DecreaseDateByXMonths(short Months)
	{
		DecreaseDateByXMonths(Months, *this);
	}

	//Decrease Date By One Year
	static void DecreaseDateByOneYear(clsDate &Date)
	{
		Date._Year--;
	}
	void DecreaseDateByOneYear()
	{
		DecreaseDateByOneYear(*this);
	}

	//Decrease Date By X Years
	static void DecreaseDateByXYears(short Years, clsDate &Date)
	{
		Date._Year -= Years;
	}
	void DecreaseDateByXYears(short Years)
	{
		DecreaseDateByXYears(Years, *this);
	}

	//Decrease Date By One Decade
	static void DecreaseDateByOneDecade(clsDate &Date)
	{
		Date._Year -= 10;
	}
	void DecreaseDateByOneDecade()
	{
		DecreaseDateByOneDecade(*this);
	}

	//Decrease Date By X Decades
	static void DecreaseDateByXDecades(short Decade, clsDate &Date)
	{
		Date._Year -= Decade * 10;
	}
	void DecreaseDateByXDecades(short Decade)
	{
		DecreaseDateByXDecades(Decade, *this);
	}

	//Decrease Date By One Century
	static void DecreaseDateByOneCentury(clsDate &Date)
	{
		Date._Year -= 100;
	}
	void DecreaseDateByOneCentury()
	{
		DecreaseDateByOneCentury(*this);
	}

	//Decrease Date By One Millennium
	static void DecreaseDateByOneMillennium(clsDate &Date)
	{
		Date._Year -= 1000;
	}
	void DecreaseDateByOneMillennium()
	{
		DecreaseDateByOneMillennium(*this);
	}

	//Is End Of Week
	static short IsEndOfWeek(clsDate Date)
	{
		return DayOfWeekOrder(Date._Day, Date._Month, Date._Year) == 6;
	}
	short IsEndOfWeek()
	{
		return IsEndOfWeek(*this);
	}

	//Is WeekEnd
	static bool IsWeekEnd(clsDate Date)
	{
		//Weekends are Fri and Sat
		short DayIndex = DayOfWeekOrder(Date._Day, Date._Month, Date._Year);
		return (DayIndex == 5 || DayIndex == 6);
	}
	bool IsWeekEnd()
	{
		return IsWeekEnd(*this);
	}

	//Is Business Day
	static bool IsBusinessDay(clsDate Date)
	{
		return !IsWeekEnd(Date);
	}
	bool IsBusinessDay()
	{
		return IsBusinessDay(*this);
	}

	//Days Until The End Of Week
	static short DaysUntilTheEndOfWeek(clsDate Date)
	{
		return 6 - DayOfWeekOrder(Date._Day, Date._Month, Date._Year);
	}
	short DaysUntilTheEndOfWeek()
	{
		return DaysUntilTheEndOfWeek(*this);
	}

	//Days Until The End Of Month 
	static short DaysUntilTheEndOfMonth(clsDate Date1)
	{
		clsDate Date2;
		Date2._Day = NumberOfDaysInAMonth(Date1._Month, Date1._Year);
		Date2._Month = Date1._Month;
		Date2._Year = Date1._Year;
		return GetDifferenceInDays(Date1, Date2, true);
	}
	short DaysUntilTheEndOfMonth()
	{
		return DaysUntilTheEndOfMonth(*this);
	}

	//Days Until The End Of Year
	static short DaysUntilTheEndOfYear(clsDate Date1)
	{
		clsDate EndOfYearDate;
		EndOfYearDate._Day = 31;
		EndOfYearDate._Month = 12;
		EndOfYearDate._Year = Date1._Year;
		return GetDifferenceInDays(Date1, EndOfYearDate, true);
	}
	short DaysUntilTheEndOfYear()
	{
		return DaysUntilTheEndOfYear(*this);
	}

	//Calculate Business Days
	static short CalculateBusinessDays(clsDate DateFrom, clsDate DateTo)
	{
		short Days = 0;
		while (IsDate1BeforeDate2(DateFrom, DateTo))
		{
			if (IsBusinessDay(DateFrom))
				Days++;
			IncreaseDateByOneDay(DateFrom);
		}
		return Days;
	}

	//Calculate Vacation Days
	static short CalculateVacationDays(clsDate &DateFrom, clsDate &DateTo)
	{
		short DaysCount = 0;
		while (IsDate1BeforeDate2(DateFrom, DateTo))
		{
			if (IsBusinessDay(DateFrom))
				DaysCount++;
			IncreaseDateByOneDay(DateFrom);
		}
		return DaysCount;
	}
	short CalculateVacationDays(clsDate DateTo)
	{
		return CalculateVacationDays(*this, DateTo);
	}

	//Calculate Vacation Return Date
	static void CalculateVacationReturnDate(clsDate &DateFrom, short VacationDays)
	{

		short WeekEndCounter = 0;
		while (IsWeekEnd(DateFrom))
		{
			IncreaseDateByOneDay(DateFrom);
		}

		for (short i = 1; i <= VacationDays + WeekEndCounter; i++)
		{

			if (IsWeekEnd(DateFrom))
				WeekEndCounter++;

			IncreaseDateByOneDay(DateFrom);
		}
		while (IsWeekEnd(DateFrom))
		{
			IncreaseDateByOneDay(DateFrom);
		}
	}
	void CalculateVacationReturnDate(short VacationDays)
	{
		CalculateVacationReturnDate(*this, VacationDays);
	}

	//Is Date1 After Date2
	static bool IsDate1AfterDate2(clsDate Date1, clsDate Date2)
	{
		return (!IsDate1BeforeDate2(Date1, Date2) && !IsDate1EqualDate2(Date1, Date2));
	}
	bool IsDate1AfterDate2(clsDate Date2)
	{
		return IsDate1AfterDate2(*this, Date2);
	}

	// Is Valid Date
	static bool IsValidDate(clsDate Date)
	{
		if (Date._Day < 1 || Date._Day>31)
			return false;
		if (Date._Month < 1 || Date._Month>12)
			return false;
		if (Date._Month == 2)
		{
			if (isLeapYear(Date._Year))
			{
				if (Date._Day > 29)
					return false;
			}
			else
			{
				if (Date._Day > 28)
					return false;
			}
		}
		short DaysInMonth = NumberOfDaysInAMonth(Date._Month, Date._Year);
		if (Date._Day > DaysInMonth)
			return false;
		return true;
	}
	bool IsValid()
	{
		return IsValidDate(*this);
	}

	// Date to string
	static string DateToString(clsDate Date)
	{
		return to_string(Date._Day) + "/" + to_string(Date._Month) + "/" + to_string(Date._Year);
	}
	string DateToString()
	{
		return DateToString(*this);
	}
	
	//Compare Dates
	enum enDateCompare { Before = -1, Equal = 0, After = 1 };
	static enDateCompare CompareDates(clsDate Date1, clsDate Date2)
	{
		if (IsDate1BeforeDate2(Date1, Date2))
			return enDateCompare::Before;
		if (IsDate1EqualDate2(Date1, Date2))
			return enDateCompare::Equal;
		return enDateCompare::After;
	}
	enDateCompare CompareDates(clsDate Date2)
	{
		return CompareDates(*this, Date2);
	}
	
	//Split String
	static vector<string> SplitString(string S1, string Delim)
	{
		vector<string> vString;
		short pos = 0;
		string sWord; // define a string variable
		// use find() function to get the position of the delimiters
		while ((pos = S1.find(Delim)) != std::string::npos)
		{
			sWord = S1.substr(0, pos); // store the word
			if (sWord != "")
			{
				vString.push_back(sWord);
			}
			S1.erase(0, pos + Delim.length());
		}
		if (S1 != "")
		{
			vString.push_back(S1); // it adds last word of the string.
		}
		return vString;
	}

	//String To Date
	static void StringToDate(string DateString,clsDate &Date)
	{
		vector <string> vDate;
		vDate = SplitString(DateString, "/");
		Date._Day = stoi(vDate[0]);
		Date._Month = stoi(vDate[1]);
		Date._Year = stoi(vDate[2]);
	}
	void StringToDate(string DateString)
	{
		StringToDate(DateString, *this);
	}

	//Replace Word In String
	static string ReplaceWordInString(string S1, string StringToReplace, string sRepalceTo)
	{
		short pos = S1.find(StringToReplace);
		while (pos != std::string::npos)
		{
			S1 = S1.replace(pos, StringToReplace.length(),
				sRepalceTo);
			pos = S1.find(StringToReplace);//find next
		}
		return S1;
	}

	//Formate Date
	static string FormateDate(clsDate Date, string DateFormat = "dd/mm/yyyy")
	{
		string FormattedDateString = "";
		FormattedDateString = ReplaceWordInString(DateFormat, "dd", to_string(Date._Day));
		FormattedDateString = ReplaceWordInString(FormattedDateString, "mm", to_string(Date._Month));
		FormattedDateString = ReplaceWordInString(FormattedDateString, "yyyy", to_string(Date._Year));
		return FormattedDateString;
	}
	string FormateDate(string DateFormat = "dd/mm/yyyy")
	{
		return FormateDate(*this, DateFormat);
	}

	//Calculate My Age In Days
	static int CalculateMyAgeInDays(clsDate DateOfBirth)
	{
		clsDate Today = clsDate::GetSystemDate();
		return GetDifferenceInDays(DateOfBirth,Today, true);
	}


};

