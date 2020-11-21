#include <iostream>
using namespace std;
#include <Windows.h>
#include <iomanip>

void gotoxy(int, int);

class Calendar
{
private:
	int year;
	static char const* MONTH_NAME[13];

	void printMonth(int month, int x, int y, bool dayWrapUp)
	{
		int prevY = y;
		gotoxy(x, y);
		cout << "         ***" << MONTH_NAME[month] << "***";
		y += 2;
		
		gotoxy(x, y);
		cout << "  Su  Mo  Tu  We  Th  Fr  Sa";
		gotoxy(x, ++y);
		
		int currentDay = getDayOfWeek(1, month, year);
		int totalDays = getNoOfDaysOfMonth(month, year);
		int currentMonthLineCounter = 1;

		for (int i = 1; i <= totalDays; i++)
		{
			if (i == 1)
			{
				int width = 4 * (currentDay + 1);
				cout << setw(width) << i;
			}
			else
				cout << setw(4) << i;
	
			currentDay = ((currentDay + 1) % 7);
			//if (currentDay == 0)
			//	currentDay = 7; //sunday. This line is not required here

			if (currentDay == 0)
			{
				y++;
				currentMonthLineCounter++;
				if (dayWrapUp == true && currentMonthLineCounter == 6)
					y = prevY + 3;
				gotoxy(x, y);
			}


		}


	}

	int getNoOfDaysOfMonth(int const month, int const year)
	{
		//Feburary
		if (month == 2)
		{
			if ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0))
				return 29;
			else
				return 28;
		}

		//months which have 31 days
		else if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
			return 31;
		else
			return 30;
	}


	//https://cs.uwaterloo.ca/~alopez-o/math-faq/node73.html
	int getDayOfWeek(int day, int month, int year)
	{
		year -= month < 3;
		int dayNo = (year + year / 4 - year / 100 + year / 400 + "-bed=pen+mad."[month] + day) % 7;

		//if (dayNo == 0) //sunday
		//	dayNo = 7;

		return dayNo;
	}

public:
	Calendar()
	{
		year = 0;
	}

	Calendar(int year)
	{
		this->year = year;
	}

	void setYear(int year)
	{
		this->year = year;
	}

	void printCalendar(bool const dayWrapUp = true)
	{
		int month = 1;
		int x = 0;
		int y = 3;
		gotoxy(x, y);
		cout << "                              **********Calendar " << year << "**********";
		y += 3;
		for (int i = 1; i <= 4; i++)
		{
			for (int j = 1; j <= 3; j++)
			{
				printMonth(month, x, y, dayWrapUp);
				x += 31;
				month++;
			
			}
			x = 0;
			y += 11;
		}
		gotoxy(0, 47); //it is necessary if the
					   //day wraps up in december,
	}

};

char const* Calendar::MONTH_NAME[13] =
{ "",
	"January",
	"Feburary",
	"March",
	"April",
	"May",
	"June",
	"July",
	"August",
	"September",
	"October",
	"November",
	"December"
};

void gotoxy(int x, int y)
{
	COORD coordinates;     // coordinates is declared as COORD
	coordinates.X = x;     // defining x-axis
	coordinates.Y = y;     //defining  y-axis
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}


int main()
{
	Calendar c;

	int year;
	cout << "Please enter the year: ";
	cin >> year;
	c.setYear(year);
	c.printCalendar(true);
	
}