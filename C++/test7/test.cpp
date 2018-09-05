#include <iostream>
#include <string.h>

using namespace std;
class String
{
public:
    String(const char* str)
        :_str(new char[strlen(str)+1])
    {
        strcpy(_str,str);
    }
    String(const String& str)
        :_str(new char[strlen(str._str) + 1])
    {
        strcpy(_str,str._str);
        cout<<"拷贝构造"<<endl;
    }

    // String & operator=(String str)
    // {
    //     swap(_str, str._str);
    //     str._str = NULL;
    //     cout << "wogan" << endl;
    //     return *this;
    // }

     String& operator=(const String& str) {
         if (_str != str._str) {
             if (_str)
                 delete[] _str;
             _str = new char[strlen(str._str) + 1];
             strcpy(_str,str._str);
         }
         return *this;
     }

    ~String()
    {
        cout << _str << endl;
        cout << "~string()" << endl;
        if(_str)
        {
            delete[]_str;
        }
    }
private:
    char* _str;
};

void test()
{
    String s1("hello world");
    String s2("fjlkdasjflsajflkasjdf");
    //String s3 = s1;
    s2 = s1;
}

int main()
{
    test();
    return 0;
}
