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
    MetaClass gfx=conn.GetClass("gdemo", "gfx");
    MetaObject mgfx=New(gfx);
    mgfx["line"].Call(make_tuple(0,0,640,480,0xFFFF));
    mgfx["line"].Call(make_tuple(640,0,0,480,0xFFFF));
    while(true){sleep(1);}
    return 0;
}
