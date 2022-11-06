//
// Created by dhanrajbir on 28/10/22.
//

#pragma clang diagnostic push
#pragma ide diagnostic ignored "LoopDoesntUseConditionVariableInspection"
#ifndef GAZPREABASE_TREENODE_H
#define GAZPREABASE_TREENODE_H

#include "llvm/Support/Casting.h"

#include <vector>


using std::vector;
using llvm::cast;

class TreeNode {
public:
    using ChildrenContainerT = vector<TreeNode*>;

    enum TreeNodeKind {
        N_AST_Program,
        N_AST_Identifier,
        N_AST_Assignment,
        N_AST_Declaration,
        N_AST_Block,
        N_AST_LogicalOp,
        N_AST_ArithmeticOp,
        N_AST_Index,
        N_AST_ConditionalLoop,
        N_AST_DomainLoop,
        N_AST_IntLiteral,
        N_AST_NullLiteral,
        N_AST_IdentityLiteral,
        N_AST_RealLiteral,
        N_AST_BoolLiteral,
        N_AST_CharLiteral,
        N_AST_TupleLiteral,
        N_AST_MemberAccess,
        N_AST_TupleTypeDecl,
        N_AST_Conditional,
        N_AST_ConditionalElse,
        N_AST_TypeCast,
        N_AST_BitwiseOp,
        N_AST_UnaryOp,
        N_AST_FunctionDecl,
        N_AST_FunctionCall,
        N_AST_ProcedureDecl,
        N_AST_ProcedureCall,
        N_AST_Return,
        N_AST_Break,
        N_AST_Continue
    };

    TreeNodeKind getKind() const {
        return Kind;
    }

    TreeNode() = delete;

    explicit TreeNode(TreeNodeKind Kind) : Kind(Kind), Parent(nullptr) {}

    void setParent(TreeNode *P) {
        Parent = P;
    }

    TreeNode *getParent() {
        return Parent;
    }

protected:
    ChildrenContainerT Children;

    TreeNode *getChildAt(size_t Pos) {
        return Children.at(Pos);
    }

    template<typename T>
    T *getChildAtAs(size_t Pos) {
        return cast<T*>(Children.at(Pos));
    }

    void setChildAt(long Pos, TreeNode *Child) {
        Children.insert(Children.begin() + Pos, Child);
    }

private:
    TreeNodeKind Kind;
    TreeNode *Parent;
};



#endif //GAZPREABASE_TREENODE_H

#pragma clang diagnostic pop