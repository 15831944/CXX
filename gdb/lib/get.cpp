#include <iostream>
#include "get.h"
using namespace std;


static int x = 0;
int get()
{
    cout<<"get x= "<<x<<endl;
    return x;
}

int set(int a)
{
    cout<<"set a= "<<a<<endl;
    x = a;
    return x;
}
