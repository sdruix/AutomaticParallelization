#ifndef FUNCTIONCALLSPRED_HPP
#define	FUNCTIONCALLSPRED_HPP

#include "tl-scopelink.hpp"
#include "tl-langconstruct.hpp"

class FunctionCallsPred : public TL::TraverseASTFunctor
{
private:
    TL::ScopeLink _sl;
public:

    FunctionCallsPred(TL::ScopeLink sl) : _sl(sl)
    {
    }

    TL::ASTTraversalResult do_(const TL::AST_t& a) const
    {
        if (TL::Expression::predicate(a))
        {
            TL::Expression expr(a, _sl);
            bool match = expr.is_function_call() && (expr.original_tree() == expr.get_ast());
            return TL::ast_traversal_result_helper(match, true);
        }
        else
        {
            return TL::ast_traversal_result_helper(false, true);
        }
    }
};

#endif	/* FUNCTIONCALLSPRED_HPP */

