#include <iostream>
#include <meta.hpp>
#include <connection.hpp>

#include <boost/serialization/map.hpp>
#include <string>
#include <fstream>

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

using namespace std;
using namespace boost;

typedef map<string, string> mapping_t;

META_METHOD(kv_ctor, NO_RETURN, NO_PARAMS){
    MEM_INIT(mapping_t, mapping);
    return Nothing;
}

META_METHOD(kv_set, NO_RETURN, Q(tuple<string, string>)){
    MEM(mapping_t, mapping);
    mapping[args.get<0>()]=args.get<1>();
    cout << args.get<0>() << " set to " << args.get<1>() << endl;
    return Nothing;
}

META_METHOD(kv_get, string, tuple<string>){
    MEM(mapping_t, mapping);
    return mapping[args.get<0>()];
}

META_METHOD(kv_erase, NO_RETURN, tuple<string>){
    MEM(mapping_t, mapping);
    mapping.erase(args.get<0>());
    return Nothing;
}

META_METHOD(kv_save, NO_RETURN, tuple<string>){
    MEM(mapping_t, mapping);
    ofstream os(args.get<0>().c_str());
    archive::text_oarchive oa(os);
    oa << mapping;
    cout << "Mapping saved as: " << args.get<0>() << endl;
    return Nothing;
}

META_METHOD(kv_load, NO_RETURN, tuple<string>){
    try{
        MEM(mapping_t, mapping);
        ifstream is(args.get<0>().c_str());
        archive::text_iarchive ia(is);
        ia >> mapping;
        cout << "Mapping loaded from: " << args.get<0>() << endl;
        return Nothing;
    }catch(...){
        cout << "Error loading." << endl;
        return Nothing;
    }
}

int main()
{
    MetaClass kv("KeyVal");
    kv.AddMethod("ctor", StdFn(kv_ctor));
    kv.AddMethod("set", StdFn(kv_set));
    kv.AddMethod("get", StdFn(kv_get));
    kv.AddMethod("erase", StdFn(kv_erase));
    kv.AddMethod("save", StdFn(kv_save));
    kv.AddMethod("load", StdFn(kv_load));
    cobject::Connection conn;
    conn.SetNamespace("kvdemo");
    conn.RegisterClass(kv);
    while(true)sleep(10);
}
