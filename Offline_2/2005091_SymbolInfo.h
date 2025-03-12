#ifndef SYMBOLINFO_HEADER
#define SYMBOLINFO_HEADER


#include<bits/stdc++.h>
using namespace std;
class SymbolInfo
{
    private:
        SymbolInfo* PointerOfNextSymbollInfo;
        string Name;
        string Type;
    public:
        SymbolInfo(string name,string type)
        {
            PointerOfNextSymbollInfo=nullptr;
            Name=name;
            Type=type;
        }
        ~SymbolInfo()
        {
            ;
        }

        void setName(string name)
        {
            Name=name;
        }
        string getName()
        {
            return Name;
        }
        void setType(string type)
        {
            Type=type;
        }
        string getType()
        {
            return Type;
        }
        void setPointerOfNextSymbollInfo(SymbolInfo* symbolInfo)
        {
            PointerOfNextSymbollInfo=symbolInfo;
        }
        SymbolInfo* getPointerOfNextSymbollInfo()
        {
            return PointerOfNextSymbollInfo;
        }
};
#endif //SYMBOLINFO_HEADER