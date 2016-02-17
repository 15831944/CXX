#include <iostream>
#include <algorithm>
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
    vector<int>vec={-2,1,4,32,45,6,67};
    for_each(vec.begin(),vec.end(),[](int i){cout<<i<<" ";});
    return 0;
}
