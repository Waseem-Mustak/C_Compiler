#ifndef SCOPETABLE_HEADER
#define SCOPETABLE_HEADER
#include "2005091_SymbolInfo.h"



class ScopeTable
{
    private:
        SymbolInfo** HashTable;
        int HashTableSize;
        ScopeTable* parentScope;
        string ScopeId;
        int DeletedScope;
    public:
        ScopeTable(int size)
        {
            HashTable=new SymbolInfo* [size];
            HashTableSize=size;
            for(int i=0;i<HashTableSize;i++)
            {
                HashTable[i]=nullptr;
            }
            parentScope=nullptr;
            ScopeId="1";
            DeletedScope=0;
        }
        
        ~ScopeTable()
        {
            // for(int i=0;i<HashTableSize;i++)
            // {
            //     SymbolInfo* Curr=HashTable[i];
            //     while ((Curr!=nullptr))
            //     {
            //         SymbolInfo* tem=Curr;
            //         Curr=(Curr->getPointerOfNextSymbollInfo());
            //         delete tem;
            //     }
                
            //     // if(HashTable[i]==nullptr)continue;
            //     // else delete HashTable[i];
            // }
            // if(HashTableSize!=0)delete[] HashTable;
        }

        unsigned long long getHashValue(string input)
        {
            unsigned long long value=0;
            int len=input.size();
            unsigned long long tem;
            for(int i=0;i<len;i++)
            {
                tem=input[i];
                value=tem+(value<<6)+(value<<16)-value;
            }
            value=(value%HashTableSize);
            return value;
        }

        ScopeTable* getParentScope()
        {
            return parentScope;
        }
        void setParentScope(ScopeTable* parentscope)
        {
            parentScope=parentscope;
        }

        string getScopeId()
        {
            return ScopeId;
        }

        void setScopeId(string scopeid)
        {
            ScopeId=scopeid;
        }
        int getDeletedScope()
        {
            return DeletedScope;
        }

        void setDeletedScope(int deletedscope)
        {
            DeletedScope=deletedscope;
        }

        bool InsertSymbolInHashtable(string name,string type)
        {

            int hashValue=getHashValue(name);
            SymbolInfo* CurrentSymbolInfo=HashTable[hashValue];

            while (1)
            {
                if(CurrentSymbolInfo==nullptr)break;
                string tem=CurrentSymbolInfo->getName();
                if(tem==name)break;
                CurrentSymbolInfo=CurrentSymbolInfo->getPointerOfNextSymbollInfo();
            }

            if(CurrentSymbolInfo!=nullptr)           //already exist
            {
                // cout<<"\t'"<<name<<"' already exists in the current ScopeTable# "<<ScopeId<<endl;
                return false;
            }
            else                                     //insert
            {
                SymbolInfo* symbolInfo=new SymbolInfo(name,type);
                if(HashTable[hashValue]==nullptr)
                {
                    HashTable[hashValue]=symbolInfo;
                    // cout<<"\tInserted  at position <"<<hashValue+1<<", "<<1<<"> of ScopeTable# "<<ScopeId<<endl;
                    return true;
                }

                SymbolInfo* CurrentSymbolInfo=HashTable[hashValue];
                int pos=2;
                while(CurrentSymbolInfo->getPointerOfNextSymbollInfo()!=nullptr)
                {
                    CurrentSymbolInfo=CurrentSymbolInfo->getPointerOfNextSymbollInfo();
                    pos++;
                }
                CurrentSymbolInfo->setPointerOfNextSymbollInfo(symbolInfo);
                // cout<<"\tInserted  at position <"<<hashValue+1<<", "<<pos<<"> of ScopeTable# "<<ScopeId<<endl;
                return true;
            }
        }



        bool InsertSymbolInHashtable(SymbolInfo* sym)
        {
            string name=sym->getName();
            string type=sym->getType();
            int hashValue=getHashValue(sym->getName());
            SymbolInfo* CurrentSymbolInfo=HashTable[hashValue];

            while (1)
            {
                if(CurrentSymbolInfo==nullptr)break;
                string tem=CurrentSymbolInfo->getName();
                if(tem==name)break;
                CurrentSymbolInfo=CurrentSymbolInfo->getPointerOfNextSymbollInfo();
            }

            if(CurrentSymbolInfo!=nullptr)           //already exist
            {
                // cout<<"\t'"<<name<<"' already exists in the current ScopeTable# "<<ScopeId<<endl;
                return false;
            }
            else                                     //insert
            {
                SymbolInfo* symbolInfo=sym;
                if(HashTable[hashValue]==nullptr)
                {
                    HashTable[hashValue]=symbolInfo;
                    // cout<<"\tInserted  at position <"<<hashValue+1<<", "<<1<<"> of ScopeTable# "<<ScopeId<<endl;
                    return true;
                }

                SymbolInfo* CurrentSymbolInfo=HashTable[hashValue];
                int pos=2;
                while(CurrentSymbolInfo->getPointerOfNextSymbollInfo()!=nullptr)
                {
                    CurrentSymbolInfo=CurrentSymbolInfo->getPointerOfNextSymbollInfo();
                    pos++;
                }
                CurrentSymbolInfo->setPointerOfNextSymbollInfo(symbolInfo);
                // cout<<"\tInserted  at position <"<<hashValue+1<<", "<<pos<<"> of ScopeTable# "<<ScopeId<<endl;
                return true;
            }
        }



        SymbolInfo* LookUpSymbolInHashtable(string input)
        {
            int hashValue=getHashValue(input);
            SymbolInfo* CurrentSymbolInfo=HashTable[hashValue];

            int pos=0;
            while (1)
            {
                if(CurrentSymbolInfo==nullptr)break;
                string tem=CurrentSymbolInfo->getName();
                if(tem==input)break;
                CurrentSymbolInfo=CurrentSymbolInfo->getPointerOfNextSymbollInfo();
                pos++;
            }

            if(CurrentSymbolInfo!=nullptr)           //found
            {
                // cout<<"\t'"<<input<<"' found at position <"<<hashValue+1<<", "<<pos+1<<"> of ScopeTable# "<<ScopeId<<endl;
            }
            else                                     //dont exist
            {
                // do nothing
            }
            return CurrentSymbolInfo;
        }


        bool DeleteSymbolFromHashtable(string input)
        {
            int hashValue=getHashValue(input);
            SymbolInfo* CurrentSymbolInfo=HashTable[hashValue];

            int pos=0;
            while (1)
            {
                if(CurrentSymbolInfo==nullptr)break;
                string tem=CurrentSymbolInfo->getName();
                if(tem==input)break;
                CurrentSymbolInfo=CurrentSymbolInfo->getPointerOfNextSymbollInfo();
                pos++;
            }

            if(CurrentSymbolInfo!=nullptr)           //found
            {

                if(HashTable[hashValue]==CurrentSymbolInfo)
                {
                    HashTable[hashValue]=CurrentSymbolInfo->getPointerOfNextSymbollInfo();
                    delete CurrentSymbolInfo;
                    cout<<"\tDeleted '"<<input<<"' from position <"<<hashValue+1<<", "<<pos+1<<"> of ScopeTable# "<<ScopeId<<endl;
                    return true;
                }
                else
                {
                    SymbolInfo* prevSymbolInfo=HashTable[hashValue];
                    while ((prevSymbolInfo->getPointerOfNextSymbollInfo()!=CurrentSymbolInfo))
                    {
                        prevSymbolInfo=prevSymbolInfo->getPointerOfNextSymbollInfo();
                    }

                    prevSymbolInfo->setPointerOfNextSymbollInfo(CurrentSymbolInfo->getPointerOfNextSymbollInfo());
                    delete CurrentSymbolInfo;
                    cout<<"\tDeleted '"<<input<<"' from position <"<<hashValue+1<<", "<<pos+1<<"> of ScopeTable# "<<ScopeId<<endl;
                    return true;
                }
            }
            else                                     //dont exist
            {
                cout<<"\tNot found in the current ScopeTable# "<<ScopeId<<endl;
                return false;
            }
        }
        void printScopeTable(ofstream &out)
        {
            out<<"\tScopeTable# "<<ScopeId<<endl;
            for(int i=0;i<HashTableSize;i++)
            {
                // out<<"\t"<<i+1;
                SymbolInfo* currentSymbol=HashTable[i];
                if(currentSymbol==nullptr)continue;
                out<<"\t"<<i+1<<"-->";
                while(1)
                {
                    if(currentSymbol==nullptr)break;
                    if(currentSymbol->getIsFunction())
                    {
                        out<<" <"<<currentSymbol->getName()<<","<<"FUNCTION,"<<currentSymbol->getTypeSpecifier()<<">";
                    }
                    else if(currentSymbol->getIsArray())
                    {
                        out<<" <"<<currentSymbol->getName()<<","<<"ARRAY"<<">";
                    }
                    else out<<" <"<<currentSymbol->getName()<<","<<currentSymbol->getTypeSpecifier()<<">";
                    currentSymbol=(currentSymbol->getPointerOfNextSymbollInfo());
                }
                out<<endl;
            }
        }
};
#endif //SCOPETABLE_HEADER



// SymbolInfo** getHashTable()
        // {
        //     return HashTable;
        // }

        // void setHashTable(SymbolInfo** hashtable)
        // {
        //     HashTable=hashtable;
        // }

        // int getHashTableSize()
        // {
        //     return HashTableSize;
        // }

        // void setHashTableSize(int hashTableSize)
        // {
        //     HashTableSize=hashTableSize;
        // }
