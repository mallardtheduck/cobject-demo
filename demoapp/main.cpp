#include <iostream>

#include <meta.hpp>
#include <connection.hpp>

using namespace std;
using namespace meta;
using namespace boost;

int main()
{
    cobject::Connection conn;
    conn.SetNamespace("demoapp");
    MetaClass kv=conn.GetClass("kvdemo", "KeyVal");
    MetaObject mkv=New(kv);
    mkv["load"].Call(make_tuple(string("demofile")));
    mkv["set"].Call(make_tuple(string("foo"), string("bar")));
    string hi=mkv["get"].Call<string>(make_tuple(string("hi")));
    hi+="hi!";
    mkv["set"].Call(make_tuple(string("hi"),hi));
    mkv["save"].Call(make_tuple(string("demofile")));
    return 0;
}
