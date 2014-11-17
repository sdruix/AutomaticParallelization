#ifndef FUNCTIONDEFINITIONPRED_HPP
#define	FUNCTIONDEFINITIONPRED_HPP

#include "tl-langconstruct.hpp"

class FunctionDefinitionPred : public TL::TraverseASTFunctor
{
public:
    FunctionDefinitionPred(){}
    
    TL::ASTTraversalResult do_(const TL::AST_t& a) const
    {
        if (TL::FunctionDefinition::predicate(a))
        {
            return TL::ast_traversal_result_helper(true, false);
        }
        else
        {
            return TL::ast_traversal_result_helper(false, true);
        }
    }
};
    
#endif	/* FUNCTIONDEFINITIONPRED_HPP */