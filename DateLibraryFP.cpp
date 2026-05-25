#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>
#include <algorithm>
#include <vector>
using namespace std;

// -------------------- struct --------------------

struct stDate {
    short day;
    short month;
    short year;
};

// -------------------- (1) helper functions --------------------

// -------------------- year --------------------

short getYear() {
    short year = 0;
    cout << "Enter a year: ";
    cin >> year;
    return year;
}

bool isLeapYear(short year) {
    return (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0));
}

short numberOfDaysInYear(short year) {
    return isLeapYear(year) ? 366 : 365;
}

int numberOfHoursInYear(short year) {
    return numberOfDaysInYear(year) * 24;
}

int numberOfMinutesInYear(short year) {
    return numberOfHoursInYear(year) * 60;
}

int numberOfSecondsInYear(short year) {
    return numberOfMinutesInYear(year) * 60;
}


// -------------------- month --------------------

short getMonth() {
    short month = 0;
    cout << "Enter a number of a month (1 for January): ";
    cin >> month;
    return month;
}

bool isLastMonthInYear(int month) {
    return month == 12;
}

short numberOfDaysInMonth(short month, short year) {
    if (month < 1 || month > 12)
        return 0;

    int days[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

    if (month == 2 && isLeapYear(year))
        return 29;

    return days[month - 1];
}

int numberOfHoursInMonth(short month, short year) {
    return numberOfDaysInMonth(month, year) * 24;
}

int numberOfMinutesInMonth(short month, short year) {
    return numberOfHoursInMonth(month, year) * 60;
}

int numberOfSecondsInMonth(short month, short year) {
    return numberOfMinutesInMonth(month, year) * 60;
}

string getMonthName(int month) {
    if (month < 1 || month > 12)
        return "Invalid Month";

    string months[12] = {
        "January","February","March","April","May","June",
        "July","August","September","October","November","December"
    };

    return months[month - 1];
}


// -------------------- day(s) --------------------

short getDay() {
    short day = 0;
    cout << "Enter a day: ";
    cin >> day;
    return day;
}

int numberOfPassedDays(stDate date) {
    int daysBeforeMonth[] = {
        0,31,59,90,120,151,181,212,243,273,304,334
    };

    int total = daysBeforeMonth[date.month - 1] + date.day - 1;

    if (date.month > 2 && isLeapYear(date.year))
        total++;

    return total;
}

int numberOfRemainingDays(stDate date) {
    return numberOfDaysInYear(date.year) - numberOfPassedDays(date);
}

bool isLastDayInMonth(stDate date)
{
    return date.day == numberOfDaysInMonth(date.month, date.year);
}

// Zeller Formula
int getDayIndex(stDate date) {
    int d = date.day;
    int m = date.month;
    int y = date.year;

    if (m < 3) {
        m += 12;
        y--;
    }

    int K = y % 100;
    int J = y / 100;

    return (d + 13 * (m + 1) / 5 + K + K / 4 + J / 4 + 5 * J) % 7;
}

// Saturday = 1 ... Friday = 7
short getDayOrder(stDate date) {
    int h = getDayIndex(date);
    return (h == 0) ? 7 : h;
}

bool isEndOfWeek(stDate date)
{
    short dayIndex = getDayOrder(date);

    return dayIndex == 7;
}

bool isWeekEnd(stDate date)
{
    short dayIndex = getDayOrder(date);

    return dayIndex == 1 || dayIndex == 2;
}

bool isBusinessDay(stDate date)
{
    return !isWeekEnd(date);
}

short daysUntilTheEndOfWeek(stDate date) {
    short dayIndex = getDayOrder(date);

    return 7 - dayIndex;

}

short daysUntilTheEndOfMonth(stDate date) {
    short daysInMonth = numberOfDaysInMonth(date.month, date.year);


    return daysInMonth - date.day;

}

short daysUntilTheEndOfYear(stDate date)
{
    return numberOfDaysInYear(date.year)
        - numberOfPassedDays(date)
        - 1;
}


// -------------------- (2) Validation functions --------------------

bool isValidDate(stDate date) {
    if (date.year < 1)
        return false;

    if (date.month < 1 || date.month > 12)
        return false;

    if (date.day < 1 || date.day > numberOfDaysInMonth(date.month, date.year))
        return false;

    return true;
}


// -------------------- (3) Date functions --------------------

// ------- Create date -------

stDate readFullDate()
{
    stDate date;

    do
    {
        cout << "\nEnter Day: ";
        cin >> date.day;

        cout << "Enter Month: ";
        cin >> date.month;

        cout << "Enter Year: ";
        cin >> date.year;

        if (!isValidDate(date))
            cout << "\nInvalid Date, Enter Again:\n";

    } while (!isValidDate(date));

    return date;
}


// ------- Read date -------

void printDate(stDate date, string separator = "/") {
    cout << "Date is : "
        << date.day << separator
        << date.month << separator
        << date.year << endl;
}

stDate getDateByPassedDays(int passedDays, int year) {

    if (passedDays >= numberOfDaysInYear(year))
        passedDays = numberOfDaysInYear(year) - 1;

    stDate date;
    date.month = 1;
    date.year = year;

    while (true)
    {
        short daysInMonth = numberOfDaysInMonth(date.month, date.year);

        if (passedDays < daysInMonth)
            break;

        passedDays -= daysInMonth;
        date.month++;
    }

    date.day = passedDays + 1;
    return date;
}


// ------- Add operations date -------

stDate getDateByAddingOneDay(stDate date) {
    if (isLastDayInMonth(date)) {
        if (isLastMonthInYear(date.month)) {
            date.day = 1;
            date.month = 1;
            date.year++;
        }
        else {
            date.day = 1;
            date.month++;
        }
    }
    else {
        date.day++;
    }

    return date;
}

stDate getDateByAddingDays(stDate date, int daysToAdd) {
    date.day += daysToAdd;

    while (date.day > numberOfDaysInMonth(date.month, date.year)) {
        date.day -= numberOfDaysInMonth(date.month, date.year);
        date.month++;

        if (date.month > 12) {
            date.month = 1;
            date.year++;
        }
    }

    return date;
}

stDate getDateByAddingOneWeek(stDate date) {
    return getDateByAddingDays(date, 7);
}

stDate getDateByAddingWeeks(stDate date, int weeks) {
    return getDateByAddingDays(date, weeks * 7);
}

stDate getDateByAddingOneMonth(stDate date) {
    date.month++;
    if (date.month > 12) {
        date.month = 1;
        date.year++;
    }

    short daysInNewMonth = numberOfDaysInMonth(date.month, date.year);

    if (date.day > daysInNewMonth) {
        date.day = daysInNewMonth;
    }

    return date;
}

stDate getDateByAddingMonths(stDate date, int months) {
    for (int i = 0; i < months; i++) {
        date = getDateByAddingOneMonth(date);
    }

    return date;
}

stDate getDateByAddingYears(stDate date, int years) {
    date.year += years;

    if (date.month == 2 && date.day == 29 && !isLeapYear(date.year)) {
        date.day = 28;
    }

    return date;
}

stDate getDateByAddingOneYear(stDate date) {
    return getDateByAddingYears(date, 1);
}

stDate getDateByAddingOneDecade(stDate date) {
    return getDateByAddingYears(date, 10);
}

stDate getDateByAddingDecades(stDate date, int decades) {
    return getDateByAddingYears(date, decades * 10);
}

stDate getDateByAddingOneCentury(stDate date) {
    return getDateByAddingYears(date, 100);
}

stDate getDateByAddingMillennium(stDate date) {
    return getDateByAddingYears(date, 1000);
}

// Adds vacation business days, skipping weekends in counting.
stDate getDateByAddingBusinessDays(stDate dateFrom, int vacationDays)
{
    while (vacationDays > 0)
    {
        dateFrom = getDateByAddingOneDay(dateFrom);

        if (isBusinessDay(dateFrom))
        {
            vacationDays--;
        }
    }

    return dateFrom;
}

// ------- Compare operations date -------

bool isDatesEqual(stDate date1, stDate date2) {
    return (
        date1.day == date2.day &&
        date1.month == date2.month &&
        date1.year == date2.year
        );
}

bool isDate1BeforeDate2(stDate date1, stDate date2) {
    if (date1.year < date2.year)
        return true;

    if (date1.year == date2.year && date1.month < date2.month)
        return true;

    if (date1.year == date2.year &&
        date1.month == date2.month &&
        date1.day < date2.day)
        return true;

    return false;
}

bool isDate1AfterDate2(stDate date1, stDate date2) {
    return !isDate1BeforeDate2(date1, date2) && !isDatesEqual(date1, date2);
}

enum class enDateCompare { Before = -1, Equal = 0, After = 1 };
enDateCompare CompareDates(stDate Date1, stDate Date2)
{
    if (isDate1BeforeDate2(Date1, Date2))
        return enDateCompare::Before;

    if (isDatesEqual(Date1, Date2))
        return enDateCompare::Equal;

    return enDateCompare::After;
}

short CalculateVacationDays(stDate dateFrom, stDate dateTo)
{
    short vacationInDays = 0;

    while (isDate1BeforeDate2(dateFrom, dateTo))
    {
        if (!isBusinessDay(dateFrom))
            vacationInDays++;

        dateFrom = getDateByAddingOneDay(dateFrom);
    }

    return vacationInDays;
}

// ------- Subtract operations date -------

int differenceBetweenDates(stDate date1, stDate date2, bool isIncludingEndDay = false) {
    if (isDate1AfterDate2(date1, date2)) {
        swap(date1, date2);
    }

    int days = 0;

    if (date1.year == date2.year) {
        days = numberOfPassedDays(date2) - numberOfPassedDays(date1);
    }
    else {
        // remaining days in first year
        days += numberOfRemainingDays(date1);

        // full years in between
        for (int year = date1.year + 1; year < date2.year; year++) {
            days += numberOfDaysInYear(year);
        }

        // passed days in last year
        days += numberOfPassedDays(date2);
    }

    if (isIncludingEndDay)
        days++;

    return days;
}
stDate getSystemDate() {
    time_t t = time(0);

    tm now;
    localtime_s(&now, &t);

    stDate today;

    today.year = now.tm_year + 1900;
    today.month = now.tm_mon + 1;
    today.day = now.tm_mday;

    return today;
}

int differenceBetweenDateAndToday(stDate userDate, bool isIncludingEndDay = false) {
    stDate today = getSystemDate();

    return differenceBetweenDates(userDate, today, isIncludingEndDay);
}

stDate getDateBySubtractingOneDay(stDate date)
{
    if (date.day > 1)
    {
        --date.day;
        return date;
    }

    if (date.month == 1)
    {
        --date.year;
        date.month = 12;
    }
    else
    {
        --date.month;
    }

    date.day = numberOfDaysInMonth(date.month, date.year);

    return date;
}

stDate getDateBySubtractingDays(stDate date, int days)
{
    date.day -= days;

    while (date.day <= 0)
    {
        date.month--;

        if (date.month < 1)
        {
            date.month = 12;
            date.year--;
        }

        date.day += numberOfDaysInMonth(date.month, date.year);
    }

    return date;
}

stDate getDateBySubtractingOneWeek(stDate date) {
    return getDateBySubtractingDays(date, 7);
}

stDate getDateBySubtractingWeeks(stDate date, int weeks) {
    return getDateBySubtractingDays(date, 7*weeks);
}
stDate getDateBySubtractingOneMonth(stDate date)
{
    date.month--;

    if (date.month < 1)
    {
        date.month = 12;
        date.year--;
    }

    short daysInNewMonth = numberOfDaysInMonth(date.month, date.year);

    if (date.day > daysInNewMonth)
        date.day = daysInNewMonth;

    return date;
}
//stDate getDateBySubtractingMonths(stDate date, int months)
//{
//    for (int i = 0; i < months; i++)
//    {
//        date = getDateBySubtractingOneMonth(date);
//    }
//
//    return date;
//}
stDate getDateBySubtractingMonths(stDate date, int months)
{
    int totalMonths = date.year * 12 + (date.month - 1);

    totalMonths -= months;

    date.year = totalMonths / 12;
    date.month = (totalMonths % 12) + 1;

    short daysInNewMonth = numberOfDaysInMonth(date.month, date.year);

    if (date.day > daysInNewMonth)
        date.day = daysInNewMonth;

    return date;
}
stDate getDateBySubtractingYears(stDate date, int years)
{
    date.year -= years;

    if (date.month == 2 && date.day == 29 && !isLeapYear(date.year))
        date.day = 28;

    return date;
}

stDate getDateBySubtractingOneYear(stDate date) {
    return getDateBySubtractingYears(date, 1);
}

stDate getDateBySubtractingOneDecade(stDate date) {
    return getDateBySubtractingYears(date, 10);
}

stDate getDateBySubtractingDecades(stDate date, int decades) {
    return getDateBySubtractingYears(date, 10*decades);
}

stDate getDateBySubtractingOneCentury(stDate date) {
    return getDateBySubtractingYears(date, 100);
}

stDate getDateBySubtractingMillennium(stDate date) {
    return getDateBySubtractingYears(date, 1000);
}


// -------------------- (4) Calendar functions --------------------

void printMonthCalendar(int month, int year) {
    int daysInMonth = numberOfDaysInMonth(month, year);

    stDate firstDayDate;
    firstDayDate.day = 1;
    firstDayDate.month = month;
    firstDayDate.year = year;

    int firstDayOrder = getDayOrder(firstDayDate);

    cout << "\n__________ "
        << getMonthName(month)
        << " __________\n\n";

    cout << "  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n";

    for (int i = 1; i < firstDayOrder; i++)
        cout << "     ";

    for (int day = 1; day <= daysInMonth; day++) {
        cout << setw(5) << day;

        if ((day + firstDayOrder - 1) % 7 == 0)
            cout << endl;
    }

    cout << "\n\n";
}

void printYearCalendar(int year) {
    cout << "\n=========== "
        << year
        << " ===========\n";

    for (int i = 1; i <= 12; i++)
        printMonthCalendar(i, year);
}

// -------------------- (5) Periods --------------------

struct stPeriod {
    stDate StartDate;
    stDate EndDate;
};

stPeriod readPeriod() {
    stPeriod period;

    cout << "Enter period start date : " << endl;
    period.StartDate = readFullDate();
    cout << "Enter period end date : " << endl;
    period.EndDate = readFullDate();

    return period;
}

bool IsOverlapPeriods(stPeriod period1, stPeriod period2)
{
    return !(isDate1BeforeDate2(period1.EndDate, period2.StartDate) || isDate1BeforeDate2(period2.EndDate, period1.StartDate));
}

int PeriodLengthInDays(stPeriod Period, bool IncludeEndDate = false)
{
    return differenceBetweenDates(Period.StartDate, Period.EndDate, IncludeEndDate);
}

bool isDateInPeriod(stDate Date, stPeriod Period)
{
    return !(CompareDates(Date, Period.StartDate) == enDateCompare::Before 
        || CompareDates(Date, Period.EndDate) == enDateCompare::After);
}

int CountOverlapDays(stPeriod Period1, stPeriod Period2)
{
    int Period1Length = PeriodLengthInDays(Period1, true);
    int Period2Length = PeriodLengthInDays(Period2, true);
    int OverlapDays = 0;
    if (!IsOverlapPeriods(Period1, Period2))
        return 0;
    if (Period1Length < Period2Length)
    {
        while (isDate1BeforeDate2(Period1.StartDate, Period1.EndDate))
        {
            if (isDateInPeriod(Period1.StartDate, Period2))
                OverlapDays++;
            Period1.StartDate = getDateByAddingOneDay(Period1.StartDate);
        }
    }
    else
    {
        while (isDate1BeforeDate2(Period2.StartDate, Period2.EndDate))
        {
            if (isDateInPeriod(Period2.StartDate, Period1))
                OverlapDays++;
            Period2.StartDate = getDateByAddingOneDay(Period2.StartDate);
        }
    }
    return OverlapDays;
}

// -------------------- (6) Formatting --------------------

vector<string> SplitString(string text, string delimiter)
{
    vector<string> vString;

    short pos = 0;
    string word;

    while ((pos = text.find(delimiter)) != string::npos)
    {
        word = text.substr(0, pos);

        if (word != "")
        {
            vString.push_back(word);
        }

        text.erase(0, pos + delimiter.length());
    }

    if (text != "")
    {
        vString.push_back(text);
    }

    return vString;
}

string DateToString(stDate date)
{
    return to_string(date.day) + "/" +
        to_string(date.month) + "/" +
        to_string(date.year);
}

stDate StringToDate(string dateString)
{
    stDate date;

    vector<string> vDate = SplitString(dateString, "/");

    date.day = stoi(vDate[0]);
    date.month = stoi(vDate[1]);
    date.year = stoi(vDate[2]);

    return date;
}

string ReadStringDate(string message)
{
    string dateString;

    cout << message;

    getline(cin >> ws, dateString);

    return dateString;
}

// -------------------- Main --------------------

int main() {
    stDate date1 = readFullDate();
    stDate date2 = readFullDate();

    if (!isValidDate(date1) && !isValidDate(date2)) {
        cout << "Please enter a validate dates";
    }

    enDateCompare result = CompareDates(date1, date2);

    if (result == enDateCompare::Before)
        cout << "date1 is before d2\n";
    else if (result == enDateCompare::Equal)
        cout << "date1 is equal to d2\n";
    else
        cout << "date1 is after d2\n";

    return 0;
}