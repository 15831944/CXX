#include <string>
#include <vector>
#include <memory>
using namespace std;
//class Info
//{
//    public:
//        Info(int,std::string);
//        void func();
//        char* func_char();
//    private:
//        int ii;
//        std::string str;
//};
class Strlob
{
    public:
        Strlob();
        Strlob(initializer_list<string>il);
        typedef vector<string>::size_type size_type;
        size_type size()const{return data->size();}
        bool empty()const{return data->empty();}
        void push_back(const string& t)
        {
            data->push_back(t);
        }
        void pop_back();
        string& front();
        string& back();
    private:
        shared_ptr<vector<string>>data;
        void check(size_type i, const string& msg)const;

};
Strlob::Strlob():data(make_shared<vector<string>>()){}
Strlob::Strlob(initializer_list<string>il):
    data(make_shared<vector<string>>(il)){}

void Strlob::check(size_type i , const string& msg)const
{
    if (i>=data->size())
        throw out_of_range(msg);
}
string& Strlob::front()
{
    check(0,"Strlob::front()");
    return data->front();
}
string& Strlob::back()
{
    check(data->size()-1,"Strlob::back()");
    return data->back();
}
void Strlob::pop_back()
{
    data->pop_back();
}
