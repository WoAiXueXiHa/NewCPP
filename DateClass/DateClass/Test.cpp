#include <iostream>

using namespace std;

class Date
{
public:
	Date()
	{
		_year = 1;
		_month = 1;
		_day = 1;
	}
	~Date()
	{

	}
private:
	size_t _year;
	size_t _month;
	size_t _day;
};

int main()
{
	return 0;
}