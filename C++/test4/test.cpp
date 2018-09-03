#include <iostream>
using namespace std;

class Date
{
public:
    void Func()
    {}
    void Display();
private:
    int _year;
    int _month;
    int _day;
};
inline void Date::Display()
{
    cout<<"year:"<<_year<<endl;
    cout<<"month:"<<_month<<endl;
    cout<<"day:"<<_day<<endl;
}
inline void Test()
{
}
int main()
{
    Date a;

    return 0;
}
