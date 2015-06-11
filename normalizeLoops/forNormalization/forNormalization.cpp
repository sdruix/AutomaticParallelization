#include "forNormalization.hpp"
#include "FunctionDefinitionPred.hpp"
#include "FunctionCallsPred.hpp"
#include <stdlib.h>
#include "hlt/hlt-common.hpp"
#include "tl-omp.hpp"
#include <iostream>
#include <fstream>


#include <bits/basic_string.h>
#include <regex.h>

using namespace TL;
using namespace TL::HLT;
using namespace std;

ForNormalizationPhase::ForNormalizationPhase() {
    
    OpenMP::OpenMPPhase ompP;
    ompP.register_directive("parallel");
    ompP.register_directive("for");
    ompP.register_directive("hmpp");
    ompP.register_directive("fixed");
    ompP.register_directive("check");
    ompP.register_directive("for check");
    ompP.register_directive("for fixed");
    
    
}
void ForNormalizationPhase::normalizeNestedLevel(ObjectList<AST_t> expr_listFor, ScopeLink scope_link){
    for (int lF = 0;lF < expr_listFor.size(); lF++) {

        Statement s(expr_listFor[lF],scope_link);
        ForStatement fS(s);
        int check = normalizeFor(fS);
        TraverseASTFunctor4LocateFor expr_traverseFor(scope_link);
        if(fS.get_loop_body().get_ast().depth_subtrees(expr_traverseFor).size()>0) {
            normalizeNestedLevel(fS.get_loop_body().get_ast().depth_subtrees(expr_traverseFor), fS.get_scope_link());
        }
    }
}
void ForNormalizationPhase::run(DTO& dto) {
    
    AST_t translation_unit = dto["translation_unit"];
    ScopeLink scope_link = dto["scope_link"];
    TraverseASTFunctor4LocateFor expr_traverseFor(scope_link);
    normalizeNestedLevel(translation_unit.depth_subtrees(expr_traverseFor), scope_link);
//    int lF=0;
    
    
//    cout<<translation_unit.prettyprint()<<endl;
//    cin.get();
}
string ForNormalizationPhase::getSimplifiedMathExpression(Expression iterating, string name, int doInverse) {
    
    string iteratingExpression = iterating.prettyprint();
    string opS;
    switch(iteratingExpression[iteratingExpression.find_first_of("=")-1]) {
        case '+':
        case '-':
        case '/':
        case '*':
            opS = iteratingExpression[iteratingExpression.find_first_of("=")-1];
            return (opS+iteratingExpression.substr(iteratingExpression.find_first_of("=")+1, iteratingExpression.length()));
            break;
    }
    string mathExpr = "ERROR";
    regex_t expEqualPlusPrev, expEqualPlusPost, expEqualSubPrev, expEqualSubPost, expEqualMath, expEqualMathWithComma; //Our compiled expression
    stringstream equalPlusPrev, equalPlusPost, equalSubPrev, equalSubPost, equalMath, equalMathWithComma;
    equalPlusPrev << "\\s*"<<name<<"\\+\\+\\s*";
    equalPlusPost << "\\s*\\+\\+"<<name<<"\\s*";
    equalSubPrev << "\\s*"<<name<<"\\-\\-\\s*";
    equalSubPost << "\\s*\\-\\-"<<name<<"\\s*";
    equalMath << "\\s*"<<name<<"\\s*=\\s*";
    equalMathWithComma << ",\\s*"<<name<<"\\s*=\\s*";
    if (regcomp(&expEqualPlusPrev, equalPlusPrev.str().c_str(), 0) != 0) {
        exit(EXIT_FAILURE);
    }
    if (regcomp(&expEqualSubPrev, equalSubPrev.str().c_str(), 0) != 0) {
        exit(EXIT_FAILURE);
    }
    if (regcomp(&expEqualMath, equalMath.str().c_str(), 0) != 0) {
        exit(EXIT_FAILURE);
    }
    if (regcomp(&expEqualPlusPost, equalPlusPost.str().c_str(), 0) != 0) {
        exit(EXIT_FAILURE);
    }
    if (regcomp(&expEqualSubPost, equalSubPost.str().c_str(), 0) != 0) {
        exit(EXIT_FAILURE);
    }
    if (regcomp(&expEqualMathWithComma, equalMathWithComma.str().c_str(), 0) != 0) {
        exit(EXIT_FAILURE);
    }
    int math = 0;
    size_t     nmatch = 2;
    regmatch_t matchesEqual[2]; //A list of the matches in the string (a list of 1)
    //cout<<"Condition: "<<condition<<endl;
    if (regexec(&expEqualPlusPrev, iteratingExpression.c_str(), nmatch, matchesEqual, 0) == 0 ||
            regexec(&expEqualPlusPost, iteratingExpression.c_str(), nmatch, matchesEqual, 0) == 0){
//        cout<<"expEqualPlusPost"<<endl;
        if(doInverse == 1) {
//            cout<<"inverted"<<endl;
            mathExpr = "- 1";
        } else { 
            mathExpr = "+ 1";
        }
    }

    if (regexec(&expEqualSubPrev, iteratingExpression.c_str(), nmatch, matchesEqual, 0) == 0 ||
            regexec(&expEqualSubPost, iteratingExpression.c_str(), nmatch, matchesEqual, 0) == 0){
//        cout<<"expEqualSubPost"<<endl;
        if(doInverse == 1 || doInverse == 2) {
//            cout<<"inverted"<<endl;
            mathExpr = "+ 1";
        } else { 
            mathExpr = "- 1";
        }
    }
    if (regexec(&expEqualMath, iteratingExpression.c_str(), nmatch, matchesEqual, 0) == 0){
        mathExpr = iteratingExpression.substr(matchesEqual[0].rm_so, iteratingExpression.length());
        mathExpr = mathExpr.substr(mathExpr.find_first_of("=")+1,mathExpr.length());
        if(mathExpr.find_first_of(",") > 0 && mathExpr.find_first_of(",")<mathExpr.length())
            mathExpr =  mathExpr.substr(0,mathExpr.find_first_of(","));
        math =1;
    }
    else if (regexec(&expEqualMathWithComma, iteratingExpression.c_str(), nmatch, matchesEqual, 0) == 0){
        mathExpr = iteratingExpression.substr(matchesEqual[0].rm_so+1, iteratingExpression.length());
        mathExpr = mathExpr.substr(mathExpr.find_first_of("=")+1,mathExpr.length());
        if(mathExpr.find_first_of(",") > 0 && mathExpr.find_first_of(",")<mathExpr.length())
            mathExpr =  mathExpr.substr(0,mathExpr.find_first_of(","));
        math =1;
    }
    if(math) {
        regex_t exprEqualMathExpressionBeforeName, exprEqualMathExpressionAfterName;
        stringstream equalMathExpressionBeforeName, equalMathExpressionAfterName;
        equalMathExpressionBeforeName << "\\s*[-|\\+|\\/|\\*]\\s*"<<name<<"\\s*";
        equalMathExpressionAfterName << "\\s*"<<name<<"\\s*[-|\\+|\\/|\\*]\\s*";
        if (regcomp(&exprEqualMathExpressionBeforeName, equalMathExpressionBeforeName.str().c_str(), 0) != 0) {
            exit(EXIT_FAILURE);
        }
        if (regcomp(&exprEqualMathExpressionAfterName, equalMathExpressionAfterName.str().c_str(), 0) != 0) {
            exit(EXIT_FAILURE);
        }
        
        if (regexec(&exprEqualMathExpressionBeforeName, mathExpr.c_str(), nmatch, matchesEqual, 0) == 0){
            stringstream operation; 
//            cout<<"Before name in: "<<mathExpr<<endl;
            if(doInverse == 1) {
                operation<<" -"<<"("<<mathExpr.substr(0,matchesEqual[0].rm_so)<<")";
                
            } else {
                 operation<<mathExpr.substr(0,matchesEqual[0].rm_so);
            }
            mathExpr = operation.str();
        }
        if (regexec(&exprEqualMathExpressionAfterName, mathExpr.c_str(), nmatch, matchesEqual, 0) == 0){
            stringstream operation; 
//            cout<<"After Name in: "<<mathExpr<<endl;
            if(doInverse == 1) {
                operation<<mathExpr.substr(0,matchesEqual[0].rm_so)<<"-("<<mathExpr.substr(mathExpr.find_first_of(name)+1, mathExpr.length())<<")";
                
            } else {
                operation<<mathExpr.substr(0,matchesEqual[0].rm_so)<<mathExpr.substr(mathExpr.find_first_of(name)+1, mathExpr.length());
            }
            mathExpr = operation.str();
             
        }
        
    }
    
    return mathExpr;
}

string ForNormalizationPhase::getExpressionOnLoop(Statement loopBody, ScopeLink sL, string name, int doInverse){
//    cout<<"Looking for the step expression"<<endl;
//    cin.get();
    string mathOp = "ERROR";
    TraverseASTFunctor4LocateAssigmentUse expr_traverseUse(sL);
    ObjectList<AST_t> expr_listUse = loopBody.get_ast().depth_subtrees(expr_traverseUse);
    
//    int lF=0;
    int numChanges = 0;
    for (int l = 0;l < expr_listUse.size(); l++) {
        Expression expr(expr_listUse[l], sL);
        
        string ppExpr = expr.prettyprint();
//        cout<<ppExpr<<endl;
//        cin.get();
        string check2Change = mathOp;
        if(expr.is_assignment()) {
            if(expr.get_first_operand().prettyprint().compare(name)==0) {
                
                mathOp = getSimplifiedMathExpression(expr, name, doInverse);
            }
        } else if(expr.is_operation_assignment()){
            //mathOp = mathOp + ppExpr[ppExpr.find_first_of("=")-1] + "(" + getSimplifiedMathExpression(expr, name, doInverse) + ")";
            mathOp = getSimplifiedMathExpression(expr, name, doInverse);
        } else if((ppExpr.find_first_of("++")>= 0 && ppExpr.find_first_of("++")<ppExpr.length()) 
                    || (ppExpr.find_first_of("--")>= 0 && ppExpr.find_first_of("--")<ppExpr.length())) {      
                mathOp = getSimplifiedMathExpression(expr, name, doInverse);
        }
        if(check2Change.compare(mathOp)!=0){
            expr_listUse[l].remove_in_list();
            numChanges++;
        }
//        cout <<mathOp<<endl;
        
    }
    if(numChanges!=1) {
        cerr<<"Complex step found on loop, please keep loops simpler as possible"<<endl;
        exit(-1);
    }
    return mathOp;
}

int ForNormalizationPhase::normalizeFor(ForStatement fS){
    
    Expression iterating = fS.get_iterating_expression();
    Expression condition = fS.get_iterating_condition();
    AST_t init = fS.get_iterating_init();
    
    Expression exprInit(init, fS.get_scope_link());
    Source initVar, initValue,initType, initS;
    initS << exprInit.prettyprint();
    initVar << fS.get_induction_variable().prettyprint();
   
    string tempValue = std::string(initS).substr(std::string(initS).find_first_of("=")+1,std::string(initS).length());
    if(tempValue.find_first_of(";")>=0 && tempValue.find_first_of(";")<tempValue.length())
        tempValue = tempValue.substr(0,tempValue.find_first_of(";"));
    initValue << tempValue;
    
    string type = std::string(initS).substr(0, std::string(initS).find_first_of(std::string(initVar)));
    
    int varDefinedInFor = 1;
    
    
    initType << type;
    string conditionToWork = condition.prettyprint();
    string varToWork;
    
    string logicOperation = findLogicalOperation(condition.prettyprint(), std::string(initVar));
    //logicOperation = ">";
    //                cout<<conditionToWork<<endl;
    int hasEqual = 0;
    if(conditionToWork.find_first_of("=")>=0 && conditionToWork.find_first_of("=")<conditionToWork.length()){
        varToWork = conditionToWork.substr(0, conditionToWork.find_first_of("="));
        conditionToWork = conditionToWork.substr(conditionToWork.find_first_of("=")+1,conditionToWork.length());
        hasEqual = 1;
        
    }
    if(conditionToWork.find_first_of("<")>=0 && conditionToWork.find_first_of("<")<conditionToWork.length()){
        varToWork = conditionToWork.substr(0, conditionToWork.find_first_of("<"));
        conditionToWork =conditionToWork.substr(conditionToWork.find_first_of("<")+1,conditionToWork.length());
        
    }
    if(conditionToWork.find_first_of(">")>=0 && conditionToWork.find_first_of(">")<conditionToWork.length()){
        varToWork = conditionToWork.substr(0, conditionToWork.find_first_of("<"));
        conditionToWork =conditionToWork.substr(conditionToWork.find_first_of(">")+1,conditionToWork.length());
        
    }
    
    
    cout<<"Prev: for("<<std::string(initType)<<" "<<std::string(initVar)<<" = " <<std::string(initValue)<<" ; " 
             << std::string(initVar) << logicOperation <<conditionToWork << " ; "
             << iterating.prettyprint()<<")"<<endl;
     string mathExpressiononIteratingVariable;
     int hasChanges = 0;
     if(logicOperation.find_first_of(">")>=0 && logicOperation.find_first_of(">")<logicOperation.length()) {
         cout<<"Finded > on ("<<logicOperation<<")"<<endl;
         hasChanges = 1;
//         cout<<"Inverse iterator"<<endl;
        mathExpressiononIteratingVariable= getSimplifiedMathExpression(iterating, std::string(initVar),1);
        if(mathExpressiononIteratingVariable.compare("ERROR") == 0) {
            mathExpressiononIteratingVariable= getExpressionOnLoop(fS.get_loop_body(), fS.get_scope_link(), std::string(initVar), 1);
        }
        if(logicOperation.find_first_of("=")>=0 && logicOperation.find_first_of("=")<logicOperation.length()) {
           initValue << "+("<<mathExpressiononIteratingVariable<<")";
        } else {
           //conditionToWork =conditionToWork + "+ ("+mathExpressiononIteratingVariable+")";
        }
        string tempCondition = conditionToWork;
        conditionToWork = std::string(initValue);
        Source nullS;
        initValue = nullS;
        initValue << tempCondition;
     } else if(logicOperation.find_first_of("!")>=0 && logicOperation.find_first_of("!")<logicOperation.length()) {
         hasChanges = 1;
         cout<<"Finded ! on ("<<logicOperation<<")"<<endl;
         //cout<<"Uncertainty on iterator"<<endl;
         mathExpressiononIteratingVariable= getSimplifiedMathExpression(iterating, std::string(initVar),2); 
          if(mathExpressiononIteratingVariable.compare("ERROR") == 0) {
            mathExpressiononIteratingVariable= getExpressionOnLoop(fS.get_loop_body(), fS.get_scope_link(), std::string(initVar), 2);
        }
     } else if (hasEqual){
         hasChanges = 1;
         cout<<"Finded == or <= on ("<<logicOperation<<")"<<endl;
         //cout<<"Keep iterator"<<endl;
        mathExpressiononIteratingVariable= getSimplifiedMathExpression(iterating, std::string(initVar),0);  
         if(mathExpressiononIteratingVariable.compare("ERROR") == 0) {
            mathExpressiononIteratingVariable= getExpressionOnLoop(fS.get_loop_body(), fS.get_scope_link(), std::string(initVar), 0);
        }
        if(logicOperation.find_first_of("=")>=0 && logicOperation.find_first_of("=")<logicOperation.length()) {
            conditionToWork= conditionToWork +mathExpressiononIteratingVariable;
        }
     }
     
     if(hasChanges) {
        Source newForLoop;
        newForLoop<<"for("<<std::string(initType)<<" "<<std::string(initVar)<<" = " <<std::string(initValue)<<" ; " 
                << std::string(initVar) << " < " <<conditionToWork << " ; "
                << std::string(initVar) << " = " << std::string(initVar) << mathExpressiononIteratingVariable<<")";
        cout<<"Post: "<<std::string(newForLoop)<<endl;
        newForLoop << "{" <<fS.get_loop_body()<<"}";
        AST_t newForAST = newForLoop.parse_statement(fS.get_enclosing_statement().get_ast(),fS.get_scope_link());
        cout<<"---------------------------------"<<endl;
        fS.get_ast().replace(newForAST);
     }
//     cin.get();
//    cout<<std::string(initType)
//            <<" "<<std::string(initVar)
//            <<" ("<<std::string(initValue)
//            <<" "<<logicOperation<<" "
//            <<conditionToWork<<")"
//            <<" [ "<<iterating.prettyprint()<<" => "
//            <<mathExpressiononIteratingVariable<<"]"<<endl;
    return 1;
}

string ForNormalizationPhase::findLogicalOperation(string condition, string name) {
    
    regex_t expEqual; //Our compiled expression
    stringstream equal;
    string con = "ERROR";
    equal << "\\s*"<<name<<"\\s*[<|>|!]";
    //equal << "\\("<<name<<"\\s*"<<"\\["<<"\\s*"<<"[a-z]*"<<"\\s*"<<"\\]"<<"\\)";
    
    //cout <<varUse.prettyprint() <<endl;
    if (regcomp(&expEqual, equal.str().c_str(), 0) != 0) {
        exit(EXIT_FAILURE);
    }
    size_t     nmatch = 2;
    regmatch_t matchesEqual[2]; //A list of the matches in the string (a list of 1)
    //cout<<"Condition: "<<condition<<endl;
    if (regexec(&expEqual, condition.c_str(), nmatch, matchesEqual, 0) == 0){
        //cout<<"Char: "<<condition[matchesEqual[0].rm_eo]<<endl;
        if(condition[matchesEqual[0].rm_eo]=='=') {
            //cout<<1<<endl;
            con = condition.substr(0,matchesEqual[0].rm_eo+2);
            con = con.substr(con.length()-3,con.length());
        } else {
           // cout<<2<<endl;
            con = condition.substr(0,matchesEqual[0].rm_eo+1);
            con = con.substr(con.length()-2,con.length());
        }
      //  con = con.substr(0,matchesEqual[0].rm_eo-matchesEqual[0].rm_so);
    }

    return con;
}



EXPORT_PHASE(ForNormalizationPhase);


