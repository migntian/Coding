#include <iostream>
using namespace std;
class Array
{
public:
    Array(size_t size = 10)
        :_size(size)
        ,_a(0)
    {
        cout<<"Array(size_t size)"<<endl;
        if(_size > 0)
        {
            _a = new int[size];
        }
    }
    ~Array()
    {
        cout<<"Array()"<<endl;
        if(_a)
        {
            delete[]_a;
            _a = 0;
            _size = 0;
        }
    }
private:
    int * _a;
    size_t _size;
};
void Test()
{
    //int *p1 = new int;
    //delete p1;
    //Array *p2 = new Array;
    //delete p2;
    int *p3 = new int[10];
    delete p3;
    //Array *p4 = new Array[10];
    //delete[] p4;
}
int main()
{
    Test();
    return 0;
}
