#include <iostream>
#include <memory>
#include <string>
using namespace std;
int main()
{
    shared_ptr<string>p(new string("linux c++"));
 //   p = make_shared<string>(new string("linux c++"));
    if (p)
    {
        cout<<*p<<endl;
    }
    return 0;
}
