template<typename T, typename T2, typename T3>
void iter(T &addr, T2 lent, T3 &func){
    for(T2 i=0;i!=lent;i++)
        func(addr[i]);
}