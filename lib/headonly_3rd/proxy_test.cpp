#include <iostream>

#include "proxy.h"
#include "ykm_proxy.h"

YKM_PROXY_I_DEF(Serable,                      //
                YKM_PROXY_FUNCS(Ser),         //
                YKM_PROXY_MEMBER(Ser, void()) //
);

struct MySer
{
    void Ser() const { std::cout << i; }
    int i;
};

int main()
{
    MySer ser;
    ser.i = 5;
    //Proxy_Serable serable = pro::make_proxy<Facade_Serable>(ser);
    Serable_Proxy serable = Serable::MakeProxy(ser);
    ser.i = 6;
    serable.invoke<Serable::Ser>();
    return 0;
}
