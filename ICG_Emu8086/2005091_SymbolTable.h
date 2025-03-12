#ifndef SYMBOLTABLE_HEADER
#define SYMBOLTABLE_HEADER

#include "2005091_ScopeTable.h"
class SymbolTable
{
    private:
        int Size;
        ScopeTable* CurrentScopeTable;
        int total_scope=1;
    public:
        SymbolTable(int size)
        {
            Size=size;
            CurrentScopeTable=new ScopeTable(size);
            // cout<<"\tScopeTable# "<<CurrentScopeTable->getScopeId()<<" created"<<endl;
        }
        ~SymbolTable()
        {
            while(1)
            {
                if(CurrentScopeTable==nullptr)break;
                ScopeTable* tem=CurrentScopeTable->getParentScope();
                // cout<<"\tScopeTable# "<<CurrentScopeTable->getScopeId()<<" deleted"<<endl;
                delete CurrentScopeTable;
                CurrentScopeTable = tem;
            }
        }

        void EnterNewScope()
        {
            total_scope++;
            ScopeTable* newScope=new ScopeTable(Size);
            newScope->setParentScope(CurrentScopeTable);
            CurrentScopeTable=newScope;
            string tem=CurrentScopeTable->getParentScope()->getScopeId();
            int deletedScopeOfThisLevel=CurrentScopeTable->getParentScope()->getDeletedScope();
            tem=(tem+"."+to_string(deletedScopeOfThisLevel+1));
            // CurrentScopeTable->setScopeId(tem);
            CurrentScopeTable->setScopeId(to_string(total_scope));

            // cout<<"\tScopeTable# "<<CurrentScopeTable->getScopeId()<<" created"<<endl;
        }

        void ExitScope()
        {
            if(CurrentScopeTable->getParentScope()==nullptr)
            {
                // cout<<"\tScopeTable# "<<CurrentScopeTable->getScopeId()<<" cannot be deleted"<<endl;
            }
            else
            {
                int tem=CurrentScopeTable->getParentScope()->getDeletedScope();
                CurrentScopeTable->getParentScope()->setDeletedScope(tem+1);// setDeletedScope()
                ScopeTable* forDelete=CurrentScopeTable;
                // cout<<"\tScopeTable# "<<CurrentScopeTable->getScopeId()<<" deleted"<<endl;
                CurrentScopeTable=CurrentScopeTable->getParentScope();
                delete forDelete;
            }
        }
        bool InsertNewSymbolInfo(string name,string type)
        {
            return CurrentScopeTable->InsertSymbolInHashtable(name,type);
        }

        bool InsertNewSymbolInfo(SymbolInfo* sym)
        {
            return CurrentScopeTable->InsertSymbolInHashtable(sym);
        }

        bool DeleteSymbol(string name)
        {
            return CurrentScopeTable->DeleteSymbolFromHashtable(name);
        }

        SymbolInfo* LookUpSymbol(string name)
        {
            ScopeTable* tem=CurrentScopeTable;
            while (1)
            {
                if(tem==nullptr)break;
                SymbolInfo* symbol=tem->LookUpSymbolInHashtable(name);
                if(symbol!=nullptr)
                {
                    return symbol;
                }
                tem=tem->getParentScope();
            }
            // cout<<"\t'"<<name<<"' not found in any of the ScopeTables"<<endl;
            return nullptr;
        }

        void PrintCurrentScopeTable(ofstream &out) 
        {
            CurrentScopeTable->printScopeTable(out);
        }

        void PrintAllScopeTable(ofstream &out)
        {
            ScopeTable* tem=CurrentScopeTable;
            while(1)
            {
                if(tem==nullptr)break;
                tem->printScopeTable(out);
                tem=tem->getParentScope();
            }
        }
        ScopeTable* getCurrentScopeTable() const {
            return CurrentScopeTable;
        }
        // ScopeTable *getCurrentScopeTable() const;
};
#endif //SYMBOLTABLE_HEADER