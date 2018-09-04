#include <iostream>
using namespace std;
class Date
{
public:
    Date()
    {
        cout<<"Date()"<<endl;
        _year = 0;
        _month = 0;
        _day = 0;
        ++scount;
    }
    void Display()
    {
        cout<<"year:"<<_year<<endl;
        cout<<"month:"<<_month<<endl;
        cout<<"day:"<<_day<<endl;
        cout<<"scount:"<<scount<<endl;
    }
    static void printcount()
    {
        cout<<"Date count:"<<scount<<endl;
    }
private:
    int _year;
    int _month;
    int _day;
private:
    static int scount;
};
int Date::scount = 0;
void test()
{
    Date d1;
    Date::printcount();
    d1.Display();
}
int main()
{
    test();
    return 0;
}



//#define ADD(a,b) a+b
//void test()
//{
//    int a = 1;
//    int b = 2;
//    int c = 3;
//    int ret = ADD(a,b);
//    cout<<"a+b:"<<ret<<endl;
//    ret = ADD(a,b)*c;
//    cout<<"(a+b)*c:"<<ret<<endl;
//}
//int main()
//{
//    test();
//    return 0;
//}
