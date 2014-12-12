#ifndef FOR_NORMALIZATION_PHASE
#define	FOR_NORMALIZATION_PHASE

#include <tl-compilerphase.hpp>
#include <hlt/hlt-inline.hpp>
#include <hlt/hlt-common.hpp>
#include <tl-ast.hpp>
#include <tl-scopelink.hpp>
#include <tl-langconstruct.hpp>
#include <tl-symbol.hpp>
#include <cxx-utils.h>
#include <uniquestr.h>
#include <tl-source.hpp>
#include <tl-datareference.hpp>
#include <tr1/regex>


using namespace TL;
using namespace TL::HLT;
using namespace std;
class ForNormalizationPhase : public CompilerPhase {
public:
    ForNormalizationPhase();
    virtual void run(DTO &dto);
    string findLogicalOperation(string condition, string name);
    string getSimplifiedMathExpression(Expression iterating, string name, int doInverse);
    
private:
    stringstream _otherExpressions;
    int normalizeFor(ForStatement fS);
    class TraverseASTFunctor4LocateFor : public TraverseASTFunctor {
                private:
                    ScopeLink _slLF;
                public:

                    TraverseASTFunctor4LocateFor(ScopeLink sl) : _slLF(sl) {};
                    virtual ASTTraversalResult do_(const TL::AST_t &a) const
                    {
                        bool retBool = false;
                        //std::cout<<"********************+"<<a.prettyprint()<<std::endl;
                        if(ForStatement::predicate(a)) {
                            //std::cout<<"********************+"<<a.prettyprint()<<std::endl;
                            retBool =true;
                            return ast_traversal_result_helper(retBool,false);
                        }
                        
                        return ast_traversal_result_helper(false, true);
                    };
            };
};

#endif	/* FORNORMALIZATION_H */

