%{
#include <bits/stdc++.h>
#include <typeinfo>

#include "2005091_SymbolInfo.h"
#include "2005091_SymbolTable.h"
#include "2005091_ScopeTable.h"

using namespace std;

ofstream logout;
ofstream errorout;
ofstream parseout;
ofstream codeout;
ofstream optout;

SymbolTable* symbolTable=new SymbolTable(11);
SymbolInfo* symbolInfoArguments=new SymbolInfo();
int mycnt=0;

extern int line_count;
extern int total_error;
extern FILE *yyin;


string concatName(vector<SymbolInfo*> tem)
{
    string tem_name="";
    for(auto va:tem)
    {
        tem_name+=" ";
        tem_name+=va->getType();
    }
    return tem_name;
}

void errorPrint(string tem)
{
    total_error++;
    errorout<<"Line# "<<line_count<< ": "<<tem<<endl;
}

string changeTypeSpecifier(SymbolInfo* tem_1,SymbolInfo* tem_2)
{
    if((tem_1->getTypeSpecifier()=="error")||(tem_1->getTypeSpecifier()=="VOID"))return "error";
    else if((tem_2->getTypeSpecifier()=="error")||(tem_2->getTypeSpecifier()=="VOID"))return "error";
    else
    {
        if((tem_1->getTypeSpecifier()=="FLOAT"))return "FLOAT";
        else if((tem_2->getTypeSpecifier()=="FLOAT"))return "FLOAT";
        else
        {
            return "INT";
        }
    }
}

bool isVoidTypeSpecifier(SymbolInfo* typeSpecifier){
	if( typeSpecifier->getTypeSpecifier() == "VOID" ){
		return true;
	}
	return false;
}


SymbolInfo* createNewSymbolInfo(vector<SymbolInfo*> listOfName,string type,string TypeSpecifier,SymbolInfo* startTime,SymbolInfo* endTime,vector<SymbolInfo*> expensionList)
{
    return new SymbolInfo(concatName(listOfName),type,TypeSpecifier,startTime->getStart(),endTime->getEnd(),false,logout,expensionList); 
}

void checkParameters(vector<SymbolInfo*> list_1,vector<SymbolInfo*> list_2,SymbolInfo* tem)
{
    int n=list_1.size();
    for(int i=0;i<n;i++)
    {
        if(list_1[i]->getTypeSpecifier()!=list_2[i]->getTypeSpecifier())
        {
            errorPrint("Type mismatch for argument "+to_string(i+1)+" of '"+tem->getName()+"'");
        }
    }
}

string currentFunction;
void functionCheck(SymbolInfo* nameOfFunction,SymbolInfo* typeSpecifier)
{
    nameOfFunction->setIsFunction(true);
	nameOfFunction->setTypeSpecifier(typeSpecifier->getTypeSpecifier());
	nameOfFunction->setParameterList(symbolInfoArguments->getParameterList());
		
    currentFunction = nameOfFunction->getName();  

	SymbolInfo* temFunc=symbolTable->LookUpSymbol(nameOfFunction->getName());

    if(temFunc==NULL)return;

	if(temFunc->getIsDeclared()==false)
    {
        errorPrint("\'"+nameOfFunction->getName()+"\' redeclared as different kind of symbol");
	}
    else
    {
		if(temFunc->getTypeSpecifier()!=nameOfFunction->getTypeSpecifier())
        {
			errorPrint("Conflicting types for\'"+nameOfFunction->getName()+"\'");
		}
        int n=temFunc->getParameterList().size();
        int m=nameOfFunction->getParameterList().size();
		if(n==m)
        {
            checkParameters(temFunc->getParameterList(),nameOfFunction->getParameterList(),nameOfFunction);
		}
        else
        {
            errorPrint("Conflicting types for\'"+nameOfFunction->getName()+"\'");
		}
	}
}





void yyerror(string s)
{
    logout<<"Error at line "<<line_count<<": "<<s<<endl;
}

int yyparse(void);
int yylex(void);




// intermediate code generation

bool hasMain = false;

vector<string> globalVariables;

int LABEL_COUNTER = 0;

int getLabelCounter(){
	
	return LABEL_COUNTER;
}
string newLabel(){
	LABEL_COUNTER++;
	return "label"+to_string(LABEL_COUNTER);
}
string getOpcode(string op){
	string opcode = "";
	if(op == "<") opcode ="JL";
	else if(op == ">") opcode ="JG";
	else if(op == ">=") opcode ="JGE";
	else if(op == "<=") opcode ="JLE";
	else if(op == "==") opcode ="JE";
	else if(op == "!=") opcode ="JNE";
	return opcode;
}

vector<string> get3address(string code){


	string stripped = code;
	while(stripped[stripped.size()-1] == ' ' or stripped[stripped.size()-1] == '\t' ) stripped.pop_back();
	reverse(stripped.begin(),stripped.end());
	while(stripped[stripped.size()-1] == ' ' or stripped[stripped.size()-1] == '\t' ) stripped.pop_back();
	reverse(stripped.begin(),stripped.end());

	vector<string> codes,codes2;
	vector<string> ret;
	stringstream ss(stripped);
 
    while (ss.good()) {
        string substr;
        getline(ss, substr, ' ');
        codes.push_back(substr);
    }
	if( codes.size()>0 ) ret.push_back(codes[0]);
	else ret.push_back("");
	if( codes.size()>1 ){
		stringstream ss(codes[1]);
		while (ss.good()) {
			string substr;
			getline(ss, substr, ',');
			codes2.push_back(substr);
		}	
	}
	if( codes2.size() == 0 ) {
		ret.push_back("");ret.push_back("");
	}else if( codes2.size() == 1 ){
		ret.push_back(codes2[0]);ret.push_back("");
	}else{
		ret.push_back(codes2[0]);
		ret.push_back(codes2[1]);
	}
	ret.push_back(code);
	// cout<<ret[0]<<" | "<<ret[1]<<" | "<<ret[2]<<endl;
	return ret;

}
// void optimizeCode(string code){
// 	// removing redundant move T - T
// 	vector<string> codes;
// 	stringstream ss(code);
// 	vector<vector<string>> optimized;
 
//     while (ss.good()) {
//         string substr;
//         getline(ss, substr, '\n');
//         codes.push_back(substr);
//     }
// 	for(auto code:codes) get3address(code);
// 	int lines = codes.size();
// 	// cout<<"debug line count::"<<lines<<endl;

// 	vector<string> prevthadd = {"","",""};
// 	for(int i=0;i<lines;i++){
// 		if( codes[i][0] == ';' ){
// 			auto thadd = get3address(codes[i]);
// 			optimized.push_back(thadd);
// 			continue;
// 		}

		
// 		vector<string> thadd = get3address(codes[i]);
// 		if( optimized.size() == 0 ){
// 			optimized.push_back(thadd);
// 			continue;
// 		}

// 	//	cout<<thadd[1]<<"="<<prevthadd[1]<<" "<<(thadd[1] == prevthadd[1])<<" || "<<thadd[2]<<"="<<prevthadd[2]<<" "<<(thadd[2] == prevthadd[2])<<endl;
// 		auto prevthadd = optimized.back();
// 		if( thadd[0] == "MOV" and prevthadd[0] == "MOV" ){
// 			if( thadd[1] == prevthadd[1] and thadd[2] == prevthadd[2] ){
// 				cout<<"optimized :) "<<endl;
// 			}else if(thadd[1] == prevthadd[2] and thadd[2] == prevthadd[1]){
// 				cout<<"optimized :) "<<endl;
// 			}else{
// 				optimized.push_back(thadd);
// 			}
// 		}else if( thadd[0] == "POP" ){
// 			if( prevthadd[0] == "PUSH" ){
// 				cout<<"optimized POP :) "<<endl;
// 				optimized.pop_back();
// 			}else{
				
// 				optimized.push_back(thadd);
// 			}
// 		}else{
// 			optimized.push_back(thadd);
		
// 		}

// 	}
// 	for(auto thadd:optimized){
// 		optout<<thadd[3]<<endl;
// 	}
// }




%}



%union{
    SymbolInfo* symbolInfo; 
}

%token<symbolInfo> IF ELSE LOWER_THAN_ELSE FOR STRUCT WHILE RETURN PRINTLN INCOP DECOP ASSIGNOP NOT LPAREN RPAREN LCURL RCURL LSQUARE RSQUARE COMMA SEMICOLON INT FLOAT VOID CONST_INT CONST_FLOAT ID ADDOP MULOP RELOP LOGICOP 
%type<symbolInfo> lcurl start program  unit var_declaration1 func_declaration func_definition struct_definition parameter_list compound_statement var_declaration type_specifier declaration_list statements statement expression_statement variable expression logic_expression rel_expression simple_expression term unary_expression factor argument_list arguments 


%left RELOP ADDOP
%left ID
%left LPAREN RPAREN 
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%%
start : program                                     {
                                                        $$=createNewSymbolInfo({$1},"start","",$1,$1,{$1});
                                                        $$->printParseTree(parseout,0); 

                                                        if(total_error == 0){
                                                            $$->code = $1->code;
                                                            codeout<<".MODEL SMALL\n.STACK 1000H\n.DATA\n\tFIXED_POINT_MULTIPLIER DW 64H\n\tCR EQU 0Dh\n\tLF EQU 0Ah\n\tNEWLINEM DB CR,LF,'$'\n\tTEN DW 10\n";
                                                            optout<<".MODEL SMALL\n.STACK 1000H\n.DATA\n\tFIXED_POINT_MULTIPLIER DW 64H\n\tCR EQU 0Dh\n\tLF EQU 0Ah\n\tNEWLINEM DB CR,LF,'$'\n\tTEN DW 10\n";
                                                            for(auto variable:globalVariables){
                                                                codeout<<'\t'<<variable<<" DW 0\n";
                                                                optout<<'\t'<<variable<<" DW 0\n";
                                                            }
                                                            codeout<<"\n\n\nNEWLINE PROC \n\t\n\tPUSH AX\n\tPUSH DX\n\t\n\tLEA DX, NEWLINEM\n\tMOV AH,9\n\tINT 21h\n\t\n\tPOP DX\n\tPOP AX \n\tRET\n   \nNEWLINE ENDP\n\nPRINTNUMBER PROC\n\tPUSH CX\n\tMOV CX,0   \n\t\n\tCMP AX,0\t\t\t \n\tJG PRINTNUMBER_START \n\t\n\tCMP AX,0\n\tJNE NOT_ZERO\n\tMOV DX,0\n\tADD DL,'0'\n\tMOV AH, 02H\n\tINT 21H\nCALL NEWLINE \n\tPOP CX  \n\tRET\n\t\n\t\n\tNOT_ZERO:\n\tPUSH AX\n\tMOV DX,'-'\n\tMOV AH, 02H\n\tINT 21H \n\tPOP AX  \n\tNEG AX\n\t\n\tPRINTNUMBER_START:\n\tCMP AX,0\n\tJE PRINTNUMBER_END \n\t\n\tXOR DX, DX\n\tDIV TEN\n\tADD DL, '0'\n\tPUSH DX\n\tINC CX\n\tJMP PRINTNUMBER_START\n\t\n\tPRINTNUMBER_END:\n\t\n\tPRINTNUMBER_LOOP:\n\t\t\n\t\tPOP DX\n\t\tMOV AH, 02H\n\t\tINT 21H\n\t\n\tLOOP PRINTNUMBER_LOOP\nCALL NEWLINE \n\tPOP CX\n\tRET\n\t\nPRINTNUMBER ENDP\n\n";
                                                            optout<<"\n\n\nNEWLINE PROC \n\t\n\tPUSH AX\n\tPUSH DX\n\t\n\tLEA DX, NEWLINEM\n\tMOV AH,9\n\tINT 21h\n\t\n\tPOP DX\n\tPOP AX \n\tRET\n   \nNEWLINE ENDP\n\nPRINTNUMBER PROC\n\tPUSH CX\n\tMOV CX,0   \n\t\n\tCMP AX,0\t\t\t \n\tJG PRINTNUMBER_START \n\t\n\tCMP AX,0\n\tJNE NOT_ZERO\n\tMOV DX,0\n\tADD DL,'0'\n\tMOV AH, 02H\n\tINT 21H\nCALL NEWLINE \n\tPOP CX  \n\tRET\n\t\n\t\n\tNOT_ZERO:\n\tPUSH AX\n\tMOV DX,'-'\n\tMOV AH, 02H\n\tINT 21H \n\tPOP AX  \n\tNEG AX\n\t\n\tPRINTNUMBER_START:\n\tCMP AX,0\n\tJE PRINTNUMBER_END \n\t\n\tXOR DX, DX\n\tDIV TEN\n\tADD DL, '0'\n\tPUSH DX\n\tINC CX\n\tJMP PRINTNUMBER_START\n\t\n\tPRINTNUMBER_END:\n\t\n\tPRINTNUMBER_LOOP:\n\t\t\n\t\tPOP DX\n\t\tMOV AH, 02H\n\t\tINT 21H\n\t\n\tLOOP PRINTNUMBER_LOOP\nCALL NEWLINE \n\tPOP CX\n\tRET\n\t\nPRINTNUMBER ENDP\n\n";
                                                            codeout<<$$->code<<endl;
                                                            // optimizeCode($$->code);
                                                            codeout<<"END main\n";
                                                            optout<<"END main\n";
                                                        }



                                                    }
    ;

program : program unit                              {
                                                        $$=createNewSymbolInfo({$1,$2},"program","",$1,$2,{$1,$2});
                                                        $$->code = $1->code+$2->code;
                                                    }
    | unit                                          {
                                                        $$=createNewSymbolInfo({$1},"program","",$1,$1,{$1});
                                                        $$->code = $1->code;
                                                    }
    ;
    
unit : var_declaration                              {
                                                        $$=createNewSymbolInfo({$1},"unit","",$1,$1,{$1});
                                                        $$->code = $1->code;
                                                    }
    | func_declaration                              {
                                                        $$=createNewSymbolInfo({$1},"unit","",$1,$1,{$1});
                                                        $$->code = $1->code;
                                                    }
    | func_definition                               {
                                                        $$=createNewSymbolInfo({$1},"unit","",$1,$1,{$1});
                                                        $$->code = $1->code;
                                                    }
    | struct_definition                               {
                                                        $$=createNewSymbolInfo({$1},"unit","",$1,$1,{$1});
                                                    }
    
    ;
struct_definition : STRUCT ID LCURL var_declaration1 RCURL SEMICOLON {
                                                        $$=createNewSymbolInfo({$1,$2,$3,$4,$5,$6},"struct_definition","",$1,$6,{$1,$2,$3,$4,$5,$6});
                                                    }
    ;



var_declaration1 : var_declaration {
        $$=createNewSymbolInfo({$1},"var_declaration1","",$1,$1,{$1});
}

    | var_declaration1 var_declaration {
        $$=createNewSymbolInfo({$1,$2},"var_declaration1","",$1,$2,{$1,$2});
    }
    ;
func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON    {
                                                        $$=createNewSymbolInfo({$1,$2,$3,$4,$5,$6},"func_declaration","",$1,$6,{$1,$2,$3,$4,$5,$6}); 
                                                        $2->setTypeSpecifier($1->getTypeSpecifier()); 
                                                        $2->setParameterList($4->getParameterList()); 
                                                        $2->setIsFunction(true);
                                                        $2->setIsDeclared(true);
                                                        symbolInfoArguments->setParameterList({}); 
                                                        if(!symbolTable->InsertNewSymbolInfo($2))
                                                        {
                                                            errorPrint("Redeclaring function");
                                                        }
                                                    }
        |   type_specifier ID LPAREN RPAREN SEMICOLON { 
                                                        $$=createNewSymbolInfo({$1,$2,$3,$4,$5},"func_declaration","",$1,$5,{$1,$2,$3,$4,$5}); 
                                                        $2->setTypeSpecifier($1->getTypeSpecifier()); 
                                                        $2->setIsFunction(true);
                                                        $2->setIsDeclared(true);
                                                        symbolInfoArguments->setParameterList({});
                                                        if(!symbolTable->InsertNewSymbolInfo($2))
                                                        {
                                                            errorPrint("Redeclaring function");
                                                        }
                                                    }
        ;
func_definition  : type_specifier ID LPAREN parameter_list RPAREN {functionCheck($2,$1);} compound_statement {
    
                                                        $$=createNewSymbolInfo({$1,$2,$3,$4,$5,$7},"func_definition","",$1,$7,{$1,$2,$3,$4,$5,$7});
                                                        $2->setTypeSpecifier($1->getTypeSpecifier()); 
                                                        $2->setParameterList($4->getParameterList()); 
                                                        $2->setIsFunction(true);
                                                        $2->setIsDeclared(true); 
                                                        symbolInfoArguments->setParameterList({}); 
                                                        symbolTable->InsertNewSymbolInfo($2);
                                                        
                                                        //ICG
                                                        $$->code = "\n\n"+$2->getName() + " PROC\n";
                                                        $$->code += "\tPUSH BP\n\tMOV BP,SP\n";

                                                        if($2->getName()=="main"){
                                                            hasMain = true;
                                                            $$->code += "\tMOV AX, @DATA\n\tMOV DS, AX\n\n";
                                                        }
                                                        $$->code += $4->code+"\n";
                                                        $$->code += $7->code+"\n";
                                                        $$->code+=$2->getName()+"_exit:\n";
                                                        $$->code +="\tADD SP,"+to_string(-$7->stackOffset)+"\n";
                                                        $$->code += "\tPOP BP\n";
                                                        
                                                        if($2->getName()=="main"){
                                                            $$->code+="\tMOV AH,4ch\nINT 21h\n\n";
                                                        }else{
                                                            $$->code += "\tRET\n";
                                                        }
                                                        $$->code += "\t"+$2->getName()+" ENDP\n";


                                                    }
        |   type_specifier ID LPAREN RPAREN {functionCheck($2,$1);} compound_statement {
                                                        $$=createNewSymbolInfo({$1,$2,$3,$4,$6},"func_definition","",$1,$6,{$1,$2,$3,$4,$6});
                                                        $2->setTypeSpecifier($1->getTypeSpecifier()); 
                                                        $2->setIsFunction(true);
                                                        $2->setIsDeclared(true); 
                                                        symbolInfoArguments->setParameterList({}); 
                                                        symbolTable->InsertNewSymbolInfo($2);

                                                        //ICG
                                                        $$->code = "\n\n"+$2->getName()+" PROC\n";
                                                        $$->code += "\tPUSH BP\n\tMOV BP,SP\n";
                                                        if($2->getName()=="main"){
                                                            hasMain = true;
                                                            $$->code += "\tMOV AX,@DATA\n\tMOV DS,AX\n\n";
                                                        }

                                                        $$->code += $6->code+"\n";
                                                        $$->code+=$2->getName()+"_exit:\n";
                                                        $$->code +="\tADD SP,"+to_string(-$6->stackOffset)+"\n";
                                                        $$->code += "\tPOP BP\n";
                                                        if( $2->getName() == "main" )
                                                            $$->code+="\tMOV AH,4ch\nINT 21h\n\n";
                                                        else 
                                                            $$->code += "RET\n";
                                                        
                                                        $$->code += $2->getName()+" ENDP\n";

                                                    }
        ;
parameter_list   : parameter_list COMMA type_specifier ID {
                                                        $$=createNewSymbolInfo({$1,$2,$3,$4},"parameter_list","",$1,$4,{$1,$2,$3,$4}); 
                                                        $4->setTypeSpecifier($3->getTypeSpecifier());
                                                        $$->setParameterList($1->getParameterList()); 
                                                        $$->addParameter($4); 
                                                        symbolInfoArguments->setParameterList($$->getParameterList()); 
                                                    }
        |   parameter_list COMMA type_specifier     {
                                                        $$=createNewSymbolInfo({$1,$2,$3},"parameter_list","",$1,$3,{$1,$2,$3}); 
                                                        
                                                        SymbolInfo* tem=new SymbolInfo("","ID",$3->getTypeSpecifier(),10000,10000,false,logout,{});
                                                        $$->setParameterList($1->getParameterList()); 
                                                        $$->addParameter(tem);
                                                        symbolInfoArguments->setParameterList($$->getParameterList()); 
                                                    }
        |   type_specifier ID                       {
                                                        $$=createNewSymbolInfo({$1,$2},"parameter_list","",$1,$2,{$1,$2}); 
                                                        $2->setTypeSpecifier($1->getTypeSpecifier());
                                                        $$->addParameter($2);
                                                        symbolInfoArguments->setParameterList($$->getParameterList());
                                                    }
        |   type_specifier                          {
                                                        $$=createNewSymbolInfo({$1},"parameter_list","",$1,$1,{$1}); 
                                                        SymbolInfo* tem=new SymbolInfo("","ID",$1->getTypeSpecifier(),10000,10000,false,logout,{});
                                                        $$->addParameter(tem); 
                                                        symbolInfoArguments->setParameterList($$->getParameterList()); 
                                                    }
        ;
compound_statement  :   lcurl statements RCURL      {
                                                        $$=createNewSymbolInfo({$1,$2,$3},"compound_statement","",$1,$3,{$1,$2,$3});
                                                        
                                                        //ICG
                                                        $$->code = $2->code;
                                                        $$->code += $3->code;
                                                        $$->stackOffset = symbolTable->getCurrentScopeTable()->stackOffset; 
		
                                                        //ICG
                                                        symbolTable->PrintAllScopeTable(logout);
                                                        symbolTable->ExitScope();
                                                    }
        |   lcurl RCURL                             {
                                                        $$=createNewSymbolInfo({$1,$2},"compound_statement","",$1,$2,{$1,$2});
                                                        symbolTable->PrintAllScopeTable(logout);
                                                        symbolTable->ExitScope();
                                                    }
        ;
var_declaration  : type_specifier declaration_list SEMICOLON {
                                                    $$=createNewSymbolInfo({$1,$2,$3},"var_declaration","",$1,$3,{$1,$2,$3});
                                                    for(auto va:$2->getDeclarationList())
                                                    {
                                                        va->setTypeSpecifier($1->getTypeSpecifier());
                                                    }
                                                    for(auto va:$2->getDeclarationList())
                                                    {
                                                        if(va->getTypeSpecifier()=="VOID") {
                                                            errorPrint("Variable or field '"+ va->getName()+"' declared void");
                                                        }
                                                        else if(!symbolTable->InsertNewSymbolInfo(va)) {
                                                            errorPrint("Conflicting types for\'"+va->getName()+"\'");
                                                        }	
                                                    }

                                                    //ICG
                                                    string comment = $$->getName();
                                                    std::replace( comment.begin(), comment.end(), '\n', ' '); // replace all 'x' to 'y'
                                                    $$->code += "; "+comment+"\n";

                                                    if( !isVoidTypeSpecifier($1) ){
                                                        for(auto symbolInfo:$2->getDeclarationList()){
                                                            symbolInfo->setTypeSpecifier($1->getTypeSpecifier());
                                                            
                                                            bool inserted = symbolTable->InsertNewSymbolInfo(symbolInfo);
                                                            if( !inserted ){
                                                                // print("Multiple declaration of",symbolInfo->getName());
                                                            }else if(symbolTable->getCurrentScopeTable()->getScopeId() == "1"){
                                                                symbolInfo->stackOffset = 0;
                                                                globalVariables.push_back(symbolInfo->getName());
                                                            }else{
                                                                if( symbolInfo->getIsArray() )
                                                                    $$->code+="\tSUB SP,"+to_string(2*symbolInfo->getSize())+"\n";
                                                                else
                                                                    $$->code+="\tSUB SP,2\n";
                                                            }
                                                        }
                                                    }
}
        ;
type_specifier   : INT                              {
                                                        $$=createNewSymbolInfo({$1},"type_specifier",$1->getTypeSpecifier(),$1,$1,{$1});
                                                    }
        |   FLOAT                                   {
                                                        $$=createNewSymbolInfo({$1},"type_specifier",$1->getTypeSpecifier(),$1,$1,{$1});
                                                    }
        |   VOID                                    {
                                                        $$=createNewSymbolInfo({$1},"type_specifier",$1->getTypeSpecifier(),$1,$1,{$1});
                                                    }
        ;
declaration_list : declaration_list COMMA ID        {
                                                        $$=createNewSymbolInfo({$1,$2,$3},"declaration_list","",$1,$3,{$1,$2,$3}); 
                                                        $$->setDeclarationList($1->getDeclarationList()); 
                                                        $$->addDeclaration($3);
                                                    }
        |   declaration_list COMMA ID LSQUARE CONST_INT RSQUARE {
                                                        $$=createNewSymbolInfo({$1,$2,$3,$4,$5,$6},"declaration_list","",$1,$6,{$1,$2,$3,$4,$5,$6}); 
                                                        $3->setIsArray(true);
                                                        $$->setDeclarationList($1->getDeclarationList()); 
                                                        $$->addDeclaration($3); 
                                                    }
        |   ID                                      {
                                                        $$=createNewSymbolInfo({$1},"declaration_list","",$1,$1,{$1});
                                                        $$->addDeclaration($1);
                                                    }
        |   ID LSQUARE CONST_INT RSQUARE              {
                                                        $$=createNewSymbolInfo({$1,$2,$3,$4},"declaration_list","",$1,$4,{$1,$2,$3,$4}); 
                                                        $1->setIsArray(true);
                                                        $$->addDeclaration($1);  
                                                    }
        ;
statements       : statement                        {
                                                        $$=createNewSymbolInfo({$1},"statements","",$1,$1,{$1});
                                                        $$->code = $1->code;
                                                    }
        |   statements statement                    {
                                                        $$=createNewSymbolInfo({$1,$2},"statements","",$1,$2,{$1,$2});
                                                        $$->code = $1->code + '\n' + $2->code;
                                                    }
        ;
statement        : var_declaration                  {
                                                        $$=createNewSymbolInfo({$1},"statement","",$1,$1,{$1});
                                    $$->code = $1->code;
                                                    }
        |   expression_statement                    {
                                                        $$=createNewSymbolInfo({$1},"statement","",$1,$1,{$1});
                                                        string comment = $$->getName();
                                                        std::replace( comment.begin(), comment.end(), '\n', ' '); // replace all 'x' to 'y'
                                                        $$->code += "; "+comment+"\n";
                                                        $$->code += $1->code;                           
                                                    }
        |   compound_statement                      {
                                                        $$=createNewSymbolInfo({$1},"statement","",$1,$1,{$1});
                                                        $$->code = $1->code;                            
                                                    }
        |   FOR LPAREN expression_statement expression_statement expression RPAREN statement {
                                                        $$=createNewSymbolInfo({$1,$2,$3,$4,$5,$6,$7},"statement","",$1,$7,{$1,$2,$3,$4,$5,$6,$7});
                                                        string comment = $$->getName();
                                                        std::replace( comment.begin(), comment.end(), '\n', ' '); // replace all 'x' to 'y'
                                                        $$->code += "; "+comment+"\n";

                                                        //string label = to_string( getLabelCounter() );
                                                        string label_loop = newLabel();//"for_loop"+label;
                                                        string label_end = newLabel();//"for_end"+label;

                                                        $$->code+=$3->code;
                                                        $$->code+=label_loop+":\n";
                                                        $$->code+=$4->code;
                                                        $$->code+="\tJCXZ "+label_end+"\n";
                                                        $$->code+=$7->code;
                                                        $$->code+=$5->code;
                                                        $$->code+="\tJMP "+label_loop+"\n";
                                                        $$->code+=label_end+":\n";                            
                                                    
                                                    
                                                    }
        |   IF LPAREN expression RPAREN statement   {
                                                        $$=createNewSymbolInfo({$1,$2,$3,$4,$5},"statement","",$1,$5,{$1,$2,$3,$4,$5});
                                                    
                                                        string comment = $$->getName();
                                                        std::replace( comment.begin(), comment.end(), '\n', ' '); // replace all 'x' to 'y'
                                                        $$->code += "; "+comment+"\n";

                                                    //	string label = to_string(getLabelCounter());
                                                        string label_false = newLabel();//"if_false" +label;
                                                        string label_true = newLabel();//"if_true" +label;

                                                        $$->code += $3->code+"\n";
                                                        $$->code += "\tJCXZ "+label_false+"\n"; //l1
                                                        $$->code += $5->code+"\n";
                                                        $$->code += "\tJMP "+label_true+"\n"; //l2
                                                        $$->code += label_false+":\n"; //
                                                        $$->code += label_true+":\n";                            
                                                    
                                                    }
        |   IF LPAREN expression RPAREN statement ELSE statement {
                                                        $$=createNewSymbolInfo({$1,$2,$3,$4,$5,$6,$7},"statement","",$1,$7,{$1,$2,$3,$4,$5,$6,$7});
                                                    
                                                        string comment = $$->getName();
                                                        std::replace( comment.begin(), comment.end(), '\n', ' '); // replace all 'x' to 'y'
                                                        $$->code += "; "+comment+"\n";

                                                        //string label = to_string(getLabelCounter());
                                                        string label_false = newLabel();//"if_false" +label;
                                                        string label_true = newLabel();//"if_true" +label;

                                                        $$->code += $3->code+"\n";
                                                        $$->code += "\tJCXZ "+label_false+"\n"; //l1
                                                        $$->code += $5->code+"\n";
                                                        $$->code += "\tJMP "+label_true+"\n"; //l2
                                                        $$->code += label_false+":\n"; // xxx
                                                        $$->code += $7->code+"\n";
                                                        $$->code += label_true+":\n";                            
                                                    
                                                    }
        |   WHILE LPAREN expression RPAREN statement {
                                                        $$=createNewSymbolInfo({$1,$2,$3,$4,$5},"statement","",$1,$5,{$1,$2,$3,$4,$5});
                                                        string comment = $$->getName();
                                                        std::replace( comment.begin(), comment.end(), '\n', ' '); // replace all 'x' to 'y'
                                                        $$->code += "; "+comment+"\n";

                                                        
                                                        string label_loop =newLabel();
                                                        string label_end = newLabel();

                                                        $$->code+=label_loop+":\n";
                                                        $$->code+=$3->code;
                                                        $$->code+="\tJCXZ "+label_end+"\n";
                                                        $$->code+=$5->code;
                                                        $$->code+="\tJMP "+label_loop+"\n";
                                                        $$->code+=label_end+":\n";                            
                                                    
                                                    }
        |   PRINTLN LPAREN ID RPAREN SEMICOLON      {
                                                        $$=createNewSymbolInfo({$1,$2,$3,$4,$5},"statement","",$1,$5,{$1,$2,$3,$4,$5});
                                                        string comment = $$->getName();
                                                        std::replace( comment.begin(), comment.end(), '\n', ' '); // replace all 'x' to 'y'
                                                        $$->code += "; "+comment+"\n";

                                                        if( !symbolTable->LookUpSymbol($3->getName()) ){
                                                            // error_output("Undeclared variable",$3->getName());
                                                        }else{
                                                            ////////////
                                                            auto searchedSymbol = symbolTable->LookUpSymbol($3->getName());
                                                        
                                                            if( !searchedSymbol ){
                                                                // error_output("Undeclared variable",$3->getName());
                                                                
                                                            }else if(searchedSymbol->getIsArray()){
                                                                // error_output("Type mismatch,",$3->getName()+" is an array");
                                                                $$->setTypeSpecifier("error");
                                                            }else {
                                                                $$->stackOffset =  searchedSymbol->stackOffset;
                                                                if( $$->stackOffset != 0 ) $$->varName = to_string($$->stackOffset)+"[BP]"; // actual variable
                                                                else $$->varName = $3->getName(); // global variable

                                                            //	$$->code += "\tMOV AX,"+$$->varName+"\n";
                                                                $$->code += "\tMOV AX,"+$$->varName+"\n\tCALL PRINTNUMBER\n";

                                                            }
                                                            ///////////	
                                                        }                            
                                                    
                                                    }
        |   RETURN expression SEMICOLON             {
                                                        $$=createNewSymbolInfo({$1,$2,$3},"statement","",$1,$3,{$1,$2,$3});
                                                        string comment = $$->getName();
                                                        std::replace( comment.begin(), comment.end(), '\n', ' '); // replace all 'x' to 'y'
                                                        $$->code += "; "+comment+"\n";

                                                        $$->code += $2->code;
                                                        $$->code +="\tMOV DX,CX\n\tJMP "+currentFunction+"_exit\n";                            
                                                    }
        ;
expression_statement :  SEMICOLON                   {
                                                        $$=createNewSymbolInfo({$1},"expression_statement","",$1,$1,{$1});
                                                        $$->code+=$1->code;                            
                                                    }
        |   expression SEMICOLON                    {
                                                        $$=createNewSymbolInfo({$1,$2},"expression_statement",$1->getTypeSpecifier(),$1,$2,{$1,$2});
                                                        $$->code = $1->code;                            
                                                    }
        ;
variable :  ID                                      {
                                                        $$=createNewSymbolInfo({$1},"variable","",$1,$1,{$1}); 
                                                        SymbolInfo* va=symbolTable->LookUpSymbol($1->getName());
                                                        if(va!=NULL)
                                                        {
                                                            $$->setTypeSpecifier(va->getTypeSpecifier());
                                                            $$->setIsArray(va->getIsArray());
                                                        }
                                                        else
                                                        {
                                                            $$->setTypeSpecifier("error");
                                                            errorPrint("Undeclared variable '"+$1->getName()+"'"); 
                                                        }
                                                    }
        |   ID LSQUARE expression RSQUARE           {
                                                        $$=createNewSymbolInfo({$1,$2,$3,$4},"variable","",$1,$4,{$1,$2,$3,$4});
                                                        SymbolInfo* va=symbolTable->LookUpSymbol($1->getName());
                                                        if(va!=NULL)
                                                        {
                                                            if(va->getIsArray()==false)
                                                            {
                                                                $$->setTypeSpecifier("error");
                                                                errorPrint("\'"+$1->getName()+"\' is not an array"); 
                                                            } 
                                                            if($3->getTypeSpecifier()!="INT")
                                                            {
                                                                $$->setTypeSpecifier("error");
                                                                errorPrint("Array subscript is not an integer");
                                                            }
                                                            else 
                                                            {
                                                                $$->setIsArray(false); 
                                                                $$->setTypeSpecifier(va->getTypeSpecifier());
                                                            }
                                                        }
                                                        else
                                                        {
                                                            errorPrint("Undeclared variable '"+$1->getName()+"'"); 
                                                            $$->setTypeSpecifier("error");                                                            
                                                        }
                                                        if( $3->getTypeSpecifier()!= "CONST_INT" and $3->getTypeSpecifier()!= "INT" ){
                                                            // error_output("Expression inside third brackets not an integer","");	
                                                        }else{
                                                            // use bx for index
                                                            $$->code+=$3->code;
                                                            $$->code+="\tMOV BX,CX\n";
                                                            $$->code+="\tSHL BX,1\n";
                                                            $$->code+="\tNEG BX\n";
                                                            $$->code+="\tADD BX,"+to_string(va->stackOffset)+"\n";
                                                            $$->code+="\tADD BX,BP\n";
                                                            $$->varName = "[BX]";
                                                        }
                                                    }
        ;
expression       : logic_expression                     {
                                                            $$=createNewSymbolInfo({$1},"expression",$1->getTypeSpecifier(),$1,$1,{$1});
                                                            $$->setIsArray($1->getIsArray());
                                                            $$->code = $1->code;                            
                                                        }
        |   variable ASSIGNOP logic_expression          {

                                                            $$=createNewSymbolInfo({$1,$2,$3},"expression","",$1,$3,{$1,$2,$3});
                                                            $$->setIsArray($1->getIsArray());

                                                            if($3->getTypeSpecifier()=="VOID")
                                                            {
                                                                errorPrint("Void cannot be used in expression ");
                                                            }
                                                            else if(($1->getTypeSpecifier()=="INT")&&($3->getTypeSpecifier()=="FLOAT"))
                                                            {
                                                                errorPrint("Warning: possible loss of data in assignment of FLOAT to INT");
                                                            }else{
                                                                $$->code += $1->code;
                                                                $$->code += $3->code;
                                                                $$->code += "\tMOV "+$1->varName+",CX\n";
                                                            }
                                                        } 
        ;
logic_expression : rel_expression                       {
                                                            $$=createNewSymbolInfo({$1},"logic_expression",$1->getTypeSpecifier(),$1,$1,{$1});  
                                                            bool tem=$1->getIsArray();
                                                            $$->setIsArray(tem);
                                                            $$->code = $1->code;
                                                        }
        |   rel_expression LOGICOP rel_expression       {

                                                            $$=createNewSymbolInfo({$1,$2,$3},"logic_expression","INT",$1,$3,{$1,$2,$3}); 
                                                            if(($1->getTypeSpecifier()=="VOID")||($3->getTypeSpecifier()=="VOID"))
                                                            {
                                                                errorPrint("Void cannot be used in expression ");
                                                            }

                                                            string labelEnd = newLabel();
                                                            $$->code += $1->code;
                                                            $$->code += "\tCMP CX,0\n";
                                                            if( $2->getName() == "&&" )
                                                                $$->code += "\tJCXZ "+labelEnd+"\n";
                                                            else
                                                                $$->code += "\tJNZ "+labelEnd+"\n";
                                                            $$->code += $3->code;
                                                            $$->code += labelEnd+":\n";
                                                        }
        ;
rel_expression   : simple_expression                    {
                                                            $$=createNewSymbolInfo({$1},"rel_expression",$1->getTypeSpecifier(),$1,$1,{$1});
                                                            bool tem=$1->getIsArray();
                                                            $$->setIsArray(tem);
                                                            $$->code = $1->code;
                                                        }
        |   simple_expression RELOP simple_expression   {
                                                            $$=createNewSymbolInfo({$1,$2,$3},"rel_expression","INT",$1,$3,{$1,$2,$3}); 
                                                            if(($1->getTypeSpecifier()=="VOID")||($3->getTypeSpecifier()=="VOID"))
                                                            {
                                                                errorPrint("Void cannot be used in expression ");
                                                            }else{
                                                                $$->setTypeSpecifier("INT");

                                                                string opcode = getOpcode($2->getName());

                                                                string labelTrue = newLabel();
                                                                string labelFalse = newLabel();
                                                                $$->code+=$1->code ;
                                                                $$->code+="\tPUSH CX\n"; 
                                                                $$->code+=$3->code;
                                                                $$->code+="\tPOP AX\n";
                                                                $$->code+="\tCMP AX,CX\n";
                                                                $$->code+="\t"+opcode+" "+labelTrue+"\n";
                                                                $$->code+="\tMOV CX,0\n";
                                                                $$->code+="\tJMP "+labelFalse+"\n";
                                                                $$->code+=labelTrue+":\n";
                                                                $$->code+="\tMOV CX,1\n";
                                                                $$->code+=labelFalse+":\n";
                                                            }
                                                        }
        ;
simple_expression   :   term                            {
                                                            $$=createNewSymbolInfo({$1},"simple_expression",$1->getTypeSpecifier(),$1,$1,{$1});
                                                            bool tem=$1->getIsArray();
                                                            $$->setIsArray(tem);
                                                            $$->code = $1->code;
                                                        }
        |   simple_expression ADDOP term                {
                                                            $$=createNewSymbolInfo({$1,$2,$3},"simple_expression",changeTypeSpecifier($1,$3),$1,$3,{$1,$2,$3});
                                                            if($3->getTypeSpecifier()=="VOID")
                                                            {
                                                                errorPrint("Void cannot be used in expression ");
                                                            }else{
                                                                $$->code = $1->code+$3->code;
                                                                if( $2->getName() == "+" )
                                                                    $$->code += "\tPOP AX\n\tADD AX,CX\n\tMOV CX,AX\n";
                                                                else
                                                                    $$->code += "\tPOP AX\n\tSUB AX,CX\n\tMOV CX,AX\n";
                                                            }


                                                        }
        ;
term : unary_expression                                 {
                                                            $$=createNewSymbolInfo({$1},"term",$1->getTypeSpecifier(),$1,$1,{$1});
                                                            bool tem=$1->getIsArray();
                                                            $$->setIsArray(tem);
                                                            $$->code = $1->code;
                                                        }
        |   term MULOP unary_expression                 {
                                                            $$=createNewSymbolInfo({$1,$2,$3},"term",changeTypeSpecifier($1,$3),$1,$3,{$1,$2,$3});
                                                            if($3->getTypeSpecifier()=="VOID")
                                                            {
                                                                errorPrint("Void cannot be used in expression ");
                                                            }
                                                            else if(($2->getName()=="/")&&($3->getStatement()=="0"))
                                                            { 
                                                                $$->setTypeSpecifier("error");
                                                                errorPrint("Warning: division by zero");
                                                            }
                                                            else if(($2->getName()=="%")&&($3->getStatement()=="0"))
                                                            { 
                                                                $$->setTypeSpecifier("error"); 
                                                                errorPrint("Warning: division by zero"); 
                                                            }
                                                            else if($2->getName()=="%")
                                                            {
                                                                if(!(($1->getTypeSpecifier()=="INT")&&($3->getTypeSpecifier()=="INT")))
                                                                {
                                                                    $$->setTypeSpecifier("error");
                                                                    errorPrint("Operands of modulus must be integers "); 
                                                                }
                                                            }else{
                                                                $$->code += $1->code+$3->code;
                                                                if( $2->getName() == "*" )
                                                                    $$->code+="\tPOP AX\nIMUL CX\n\tMOV CX,AX\n";
                                                                else if( $2->getName() == "/" )
                                                                    $$->code+="\tPOP AX\nCWD\nIDIV CX\n\tMOV CX,AX\n";
                                                                else if( $2->getName() == "%" )
                                                                    $$->code+="\tPOP AX\nCWD\nIDIV CX\n\tMOV CX,DX\n";
                                                            }
                                                        }
        ;
unary_expression : ADDOP unary_expression               {
                                                            $$=createNewSymbolInfo({$1,$2},"unary_expression",$2->getTypeSpecifier(),$1,$2,{$1,$2}); 
                                                            if($2->getTypeSpecifier()=="VOID")
                                                            {
                                                                errorPrint("Void cannot be used in expression ");
                                                            }else{
                                                                $$->setTypeSpecifier($2->getTypeSpecifier());
                                                                $$->code+=$2->code;
                                                                if($1->getName() == "-")
                                                                    $$->code+="NEG CX\n";
                                                            }
                                                        }
        |   NOT unary_expression                        {
                                                            $$=createNewSymbolInfo({$1,$2},"unary_expression","INT",$1,$2,{$1,$2}); 
                                                            if($2->getTypeSpecifier()=="VOID")
                                                            {
                                                                errorPrint("Void cannot be used in expression ");
                                                            }else{
                                                            $$->setTypeSpecifier("INT");
                                                            $$->code+=$2->code;
                                                            //string label = to_string( getLabelCounter() );
                                                            string labelEnd =newLabel();// "not_end"+label;
                                                            string labelOne = newLabel();//"not_one"+label;
                                                            $$->code+=$2->code;
                                                            $$->code+="\tJCXZ "+labelOne+"\n";
                                                            $$->code+="\tMOV CX,0\n";
                                                            $$->code+=labelOne+":\n";
                                                            $$->code+="\tMOV CX,1\n";
                                                            $$->code+=labelEnd+":\n";
		}
                                                        }
        |   factor                                      {
                                                            $$=createNewSymbolInfo({$1},"unary_expression",$1->getTypeSpecifier(),$1,$1,{$1}); 
                                                            bool tem=$1->getIsArray();
                                                            $$->setIsArray(tem);
                                                            $$->code = $1->code;
                                                        }
        ;
factor  :   variable                                    {
                                                            $$=createNewSymbolInfo({$1},"factor",$1->getTypeSpecifier(),$1,$1,{$1});
                                                            bool tem=$1->getIsArray();
                                                            $$->setIsArray(tem);
                                                            $$->code+=$1->code;
		                                                    $$->code += "\tMOV CX,"+$1->varName+"\n";
                                                        }
        |   ID LPAREN argument_list RPAREN              {
                                                            $$=createNewSymbolInfo({$1,$2,$3,$4},"factor","error",$1,$4,{$1,$2,$3,$4}); 
                                                            SymbolInfo* va=symbolTable->LookUpSymbol($1->getName());
                                                            if(va!=NULL) 
                                                            {
                                                                $$->setTypeSpecifier(va->getTypeSpecifier());
                                                                vector<SymbolInfo*> tem_1=$3->getParameterList();
                                                                vector<SymbolInfo*> tem_2=va->getParameterList();
                                                                int n=tem_1.size();
                                                                int m=tem_2.size();
                                                                if(n<m)
                                                                {
                                                                    errorPrint("Too few arguments to function '"+$1->getName()+"'");
                                                                }
                                                                else if(n>m) 
                                                                {
                                                                    errorPrint("Too many arguments to function '"+$1->getName()+"'");
                                                                }
                                                                else
                                                                {                                                                    
                                                                    checkParameters(tem_1,tem_2,$1);
                                                                    $$->code +=$3->code+"\tCALL "+$1->getName()+"\n\tMOV CX,DX\n"+"\tADD SP,"+to_string($3->stackOffset)+"\n";
                                                                }
                                                            }
                                                            else
                                                            {
                                                                errorPrint("Undeclared function '"+$1->getName()+"'");
                                                            }
                                                        }
        |   LPAREN expression RPAREN                    {
                                                            $$=createNewSymbolInfo({$1,$2,$3},"factor",$1->getTypeSpecifier(),$1,$3,{$1,$2,$3});
                                                            $$->code = $2->code;
                                                        }
        |   CONST_INT                                   {
                                                            $$=createNewSymbolInfo({$1},"factor","INT",$1,$1,{$1});
                                                            $$->code = "\tMOV CX,"+$1->getName()+"\n";
                                                        }
        |   CONST_FLOAT                                 {
                                                            $$=createNewSymbolInfo({$1},"factor","FLOAT",$1,$1,{$1});
                                                            $$->code = "\tMOV CX,"+$1->getName()+"\n";
                                                        }
        |   variable INCOP                              {
                                                            $$=createNewSymbolInfo({$1,$2},"factor",$1->getTypeSpecifier(),$1,$2,{$1,$2}); 
                                                            if($1->getTypeSpecifier()=="VOID" )
                                                            {
                                                                $$->setTypeSpecifier("error");
                                                                errorPrint("Variable or field '"+$1->getName()+"' declared void");
                                                            }else{
                                                                $$->setTypeSpecifier($1->getTypeSpecifier());
                                                                $$->code += $1->code;
                                                                $$->code += "\tMOV CX,"+$1->varName+"\n";
                                                                $$->code += "\tINC "+$1->varName+"\n";
                                                                
                                                            }
                                                        }
        |   variable DECOP                              {
                                                            $$=createNewSymbolInfo({$1,$2},"factor",$1->getTypeSpecifier(),$1,$2,{$1,$2}); 
                                                            if($1->getTypeSpecifier()=="VOID" )
                                                            {
                                                                $$->setTypeSpecifier("error");
                                                                errorPrint("Variable or field '"+$1->getName()+"' declared void");
                                                            }else{
                                                                $$->setTypeSpecifier($1->getTypeSpecifier());
                                                                $$->code += "\tMOV CX,"+$1->varName+"\n";
                                                                $$->code += "\t MOV AX,CX\n\tSUB AX,1\n\tMOV "+$1->varName+",AX\n";
                                                            }
                                                        }
        ;
argument_list    : arguments                            {
                                                            $$=createNewSymbolInfo({$1},"argument_list","",$1,$1,{$1}); 
                                                            $$->setParameterList($1->getParameterList());
                                                            $$->code+=$1->code;
		                                                    $$->stackOffset = $1->stackOffset;
                                                        }
        |                                               {
                                                            $$=new SymbolInfo(concatName({}),"argument_list","",line_count,line_count,false,logout,{});
                                                        }
        ;
arguments        : arguments COMMA logic_expression     {
                                                            $$=createNewSymbolInfo({$1,$2,$3},"arguments","",$1,$3,{$1,$2,$3}); 
                                                            $$->setParameterList($1->getParameterList()); 
                                                            $$->addParameter($3);
                                                            $$->code+=$1->code+$3->code;
                                                            $$->code+="\tPUSH CX\n";
                                                            $$->stackOffset = $1->stackOffset + 2;
                                                        }
        |   logic_expression                            {
                                                            $$=createNewSymbolInfo({$1},"arguments","",$1,$1,{$1}); 
                                                            $$->addParameter($1);
                                                            $$->code+=$1->code;
                                                            $$->code+="\tPUSH CX\n";
                                                            $$->stackOffset = 2;
                                                        }
        ;
lcurl : LCURL                                           {
                                                            $$=$1;
                                                            symbolTable->EnterNewScope(); 
                                                            for(auto va:symbolInfoArguments->getParameterList())
                                                            {
                                                                if(symbolTable->InsertNewSymbolInfo(va)==false)
                                                                {
                                                                    errorPrint("Redefinition of parameter \'"+va->getName()+"\'");
                                                                    break;
                                                                }
                                                            }
                                                            symbolInfoArguments->setParameterList({});	
                                                        }	
		;
    


%%
int main(int argc,char *argv[]){
    // ki vongchong korsilam mone nai 
    FILE *fp;

    if((fp=fopen(argv[1],"r"))==NULL){
        printf("Cannot Open Input File.\n");
        exit(1);
    }

    logout.open("log.txt");
    errorout.open("error.txt");
    parseout.open("paesetree.txt");
    codeout.open("emu8086.txt");
    /* optout.open("optcode.txt"); */

    yyin=fp;
    yyparse();
    
    logout<<"Total Lines: "<<line_count<<endl;
    logout<<"Total Errors: "<<total_error<<endl;
    cout<<"All done"<<endl;

    fclose(yyin);
    logout.close();
    errorout.close();
    parseout.close();
    codeout.close();
    /* optout.close(); */
    return 0;
}