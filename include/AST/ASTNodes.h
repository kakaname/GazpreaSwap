//
// Created by dhanrajbir on 28/10/22.
//

#ifndef GAZPREABASE_ASTNODES_H
#define GAZPREABASE_ASTNODES_H

#include "Common/TreeNode.h"

using ASTNodeT = TreeNode;

class Program: public TreeNode {
    static bool classof(const TreeNode *N) {
        return N->getKind() == TreeNodeKind::N_AST_Program;
    }

public:
    Program() : TreeNode(TreeNodeKind::N_AST_Program) {}
};


class Identifier: public TreeNode {
    static bool classof(const TreeNode *N) {
        return N->getKind() == TreeNodeKind::N_AST_Identifier;
    }

    Identifier() : TreeNode(TreeNodeKind::N_AST_Identifier) {}
};


class Assignment: public TreeNode {
    static bool classof(const TreeNode *N) {
        return N->getKind() == TreeNodeKind::N_AST_Assignment;
    }

public:
    Assignment() : TreeNode(TreeNodeKind::N_AST_Assignment) {};
};


class Declaration: public TreeNode {
    static bool classof(const TreeNode *N) {
        return N->getKind() == TreeNodeKind::N_AST_Declaration;
    }

    Declaration() : TreeNode(TreeNodeKind::N_AST_Declaration) {}
};


class Block: public TreeNode {
    static bool classof(const TreeNode *N) {
        return N->getKind() == TreeNodeKind::N_AST_Block;
    }

    Block() : TreeNode(TreeNodeKind::N_AST_Block) {}
};


class LogicalOp: public TreeNode {
    static bool classof(const TreeNode *N) {
        return N->getKind() == TreeNodeKind::N_AST_LogicalOp;
    }

    LogicalOp() : TreeNode(TreeNodeKind::N_AST_LogicalOp) {}
};


class ArithmeticOp: public TreeNode {
    static bool classof(const TreeNode *N) {
        return N->getKind() == TreeNodeKind::N_AST_ArithmeticOp;
    }

    ArithmeticOp() : TreeNode(TreeNodeKind::N_AST_ArithmeticOp) {}
};


class Index: public TreeNode {
    static bool classof(const TreeNode *N) {
        return N->getKind() == TreeNodeKind::N_AST_Index;
    }

    Index() : TreeNode(TreeNodeKind::N_AST_Index) {};
};


class ConditionalLoop: public TreeNode {
    static bool classof(const TreeNode *N) {
        return N->getKind() == TreeNodeKind::N_AST_ConditionalLoop;
    }

    ConditionalLoop() : TreeNode(TreeNodeKind::N_AST_ConditionalLoop) {}
};


class DomainLoop: public TreeNode {
    static bool classof(const TreeNode *N) {
        return N->getKind() == TreeNodeKind::N_AST_DomainLoop;
    }

    DomainLoop(): TreeNode(TreeNodeKind::N_AST_DomainLoop) {}
};

class IntLiteral: public TreeNode {
    static bool classof(const TreeNode *N) {
        return N->getKind() == TreeNodeKind::N_AST_IntLiteral;
    }

    IntLiteral(): TreeNode(TreeNodeKind::N_AST_IntLiteral) {}
};


class NullLiteral: public TreeNode {
    static bool classof(const TreeNode *N) {
        return N->getKind() == TreeNodeKind::N_AST_NullLiteral;
    }

    NullLiteral(): TreeNode(TreeNodeKind::N_AST_NullLiteral) {}
};


class IdentityLiteral: public TreeNode {
    static bool classof(const TreeNode *N) {
        return N->getKind() == TreeNodeKind::N_AST_IdentityLiteral;
    }

    IdentityLiteral(): TreeNode(TreeNodeKind::N_AST_IdentityLiteral) {}
};


class RealLiteral: public TreeNode {
    static bool classof(const TreeNode *N) {
        return N->getKind() == TreeNodeKind::N_AST_RealLiteral;
    }

    RealLiteral(): TreeNode(TreeNodeKind::N_AST_RealLiteral) {}
};


class BoolLiteral: public TreeNode {
    static bool classof(const TreeNode *N) {
        return N->getKind() == TreeNodeKind::N_AST_BoolLiteral;
    }

    BoolLiteral(): TreeNode(TreeNodeKind::N_AST_BoolLiteral) {}
};


class CharLiteral: public TreeNode {
    static bool classof(const TreeNode *N) {
        return N->getKind() == TreeNodeKind::N_AST_CharLiteral;
    }

    CharLiteral(): TreeNode(TreeNodeKind::N_AST_CharLiteral) {}
};


class TupleLiteral: public TreeNode {
    static bool classof(const TreeNode *N) {
        return N->getKind() == TreeNodeKind::N_AST_TupleLiteral;
    }

    TupleLiteral(): TreeNode(TreeNodeKind::N_AST_TupleLiteral) {};
};


class MemberAccess: public TreeNode {
    static bool classof(const TreeNode *N) {
        return N->getKind() == TreeNodeKind::N_AST_MemberAccess;
    }

    MemberAccess(): TreeNode(TreeNodeKind::N_AST_MemberAccess) {}
};


class TupleTypeDecl: public TreeNode {
    static bool classof(const TreeNode *N) {
        return N->getKind() == TreeNodeKind::N_AST_TupleTypeDecl;
    }

    TupleTypeDecl(): TreeNode(TreeNodeKind::N_AST_TupleTypeDecl) {}
};


class Conditional: public TreeNode {
    static bool classof(const TreeNode *N) {
        return N->getKind() == TreeNodeKind::N_AST_Conditional;
    }

    Conditional(): TreeNode(TreeNodeKind::N_AST_Conditional) {}
};

class ConditionalElse: public TreeNode {
    static bool classof(const TreeNode *N) {
        return N->getKind() == TreeNodeKind::N_AST_ConditionalElse;
    }

    ConditionalElse(): TreeNode(TreeNodeKind::N_AST_ConditionalElse) {}
};


class TypeCast: public TreeNode {
    static bool classof(const TreeNode *N) {
        return N->getKind() == TreeNodeKind::N_AST_TypeCast;
    }

    TypeCast(): TreeNode(TreeNodeKind::N_AST_TypeCast) {}
};


class BitwiseOp: public TreeNode {
    static bool classof(const TreeNode *N) {
        return N->getKind() == TreeNodeKind::N_AST_BitwiseOp;
    }

    BitwiseOp(): TreeNode(TreeNodeKind::N_AST_BitwiseOp) {}
};


class UnaryOp: public TreeNode {
    static bool classof(const TreeNode *N) {
        return N->getKind() == TreeNodeKind::N_AST_UnaryOp;
    }

    UnaryOp(): TreeNode(TreeNodeKind::N_AST_UnaryOp) {}
};


class FunctionDecl: public TreeNode {
    static bool classof(const TreeNode *N) {
        return N->getKind() == TreeNodeKind::N_AST_FunctionDecl;
    }

    FunctionDecl(): TreeNode(TreeNodeKind::N_AST_FunctionDecl) {};
};


class FunctionCall: public TreeNode {
    static bool classof(const TreeNode *N) {
        return N->getKind() == TreeNodeKind::N_AST_FunctionCall;
    }

    FunctionCall(): TreeNode(TreeNodeKind::N_AST_FunctionCall) {}
};


class ProcedureDecl: public TreeNode {
    static bool classof(const TreeNode *N) {
        return N->getKind() == TreeNodeKind::N_AST_ProcedureDecl;
    }

    ProcedureDecl(): TreeNode(TreeNodeKind::N_AST_ProcedureDecl) {}
};


class ProcedureCall: public TreeNode {
    static bool classof(const TreeNode *N) {
        return N->getKind() == TreeNodeKind::N_AST_ProcedureCall;
    }

    ProcedureCall(): TreeNode(TreeNodeKind::N_AST_ProcedureCall) {}
};


class Return: public TreeNode {
    static bool classof(const TreeNode *N) {
        return N->getKind() == TreeNodeKind::N_AST_Return;
    }

    Return(): TreeNode(TreeNodeKind::N_AST_Return) {}
};


class Break: public TreeNode {
    static bool classof(const TreeNode *N) {
        return N->getKind() == TreeNodeKind::N_AST_Break;
    }

    Break(): TreeNode(TreeNodeKind::N_AST_Break) {}
};


class Continue: public TreeNode {
    static bool classof(const TreeNode *N) {
        return N->getKind() == TreeNodeKind::N_AST_Continue;
    }

    Continue(): TreeNode(TreeNodeKind::N_AST_Continue) {}
};

#endif //GAZPREABASE_ASTNODES_H
