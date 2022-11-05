//
// Created by dhanrajbir on 28/10/22.
//

#ifndef GAZPREABASE_ASTNODES_H
#define GAZPREABASE_ASTNODES_H


class ASTNode {
public:
    enum ASTNodeKind {
        N_Program,
        N_Identifier,
        N_Assignment,
        N_Declaration,
        N_Block,
        N_LogicalOp,
        N_ArithmeticOp,
        N_Index,
        N_Loop,
        N_IntLiteral,
        N_NullLiteral,
        N_IdentityLiteral,
        N_RealLiteral,
        N_BoolLiteral,
        N_CharLiteral,
        N_Tuple,
        N_TupleAccess,
        N_TupleDecl,
        N_Conditional,
        N_Cast,
        N_BitwiseOp,
        N_UnaryOp,
        N_FunctionDecl,
        N_FunctionCall,
        N_ProcedureDecl,
        N_ProcedureCall,
        N_Return,
        N_Break,
        N_Continue
    };

    ASTNodeKind getKind() const {
        return Kind;
    }
private:
    ASTNodeKind Kind;
};


class Program: ASTNode {
    static bool classof(const ASTNode *N) {
        return N->getKind() == ASTNodeKind::N_Program;
    }
};


class Identifier: public ASTNode {
    static bool classof(const ASTNode *N) {
        return N->getKind() == ASTNodeKind::N_Identifier;
    }
};


class Assignment: public ASTNode {
    static bool classof(const ASTNode *N) {
        return N->getKind() == ASTNodeKind::N_Assignment;
    }
};


class Declaration: public ASTNode {
    static bool classof(const ASTNode *N) {
        return N->getKind() == ASTNodeKind::N_Declaration;
    }
};


class Block: public ASTNode {
    static bool classof(const ASTNode *N) {
        return N->getKind() == ASTNodeKind::N_Block;
    }
};


class LogicalOp: public ASTNode {
    static bool classof(const ASTNode *N) {
        return N->getKind() == ASTNodeKind::N_LogicalOp;
    }
};


class ArithmeticOp: public ASTNode {
    static bool classof(const ASTNode *N) {
        return N->getKind() == ASTNodeKind::N_ArithmeticOp;
    }
};


class Index: public ASTNode {
    static bool classof(const ASTNode *N) {
        return N->getKind() == ASTNodeKind::N_Index;
    }
};


class Loop: public ASTNode {
    static bool classof(const ASTNode *N) {
        return N->getKind() == ASTNodeKind::N_Loop;
    }
};


class IntLiteral: public ASTNode {
    static bool classof(const ASTNode *N) {
        return N->getKind() == ASTNodeKind::N_IntLiteral;
    }
};


class NullLiteral: public ASTNode {
    static bool classof(const ASTNode *N) {
        return N->getKind() == ASTNodeKind::N_NullLiteral;
    }
};


class IdentityLiteral: public ASTNode {
    static bool classof(const ASTNode *N) {
        return N->getKind() == ASTNodeKind::N_IdentityLiteral;
    }
};


class RealLiteral: public ASTNode {
    static bool classof(const ASTNode *N) {
        return N->getKind() == ASTNodeKind::N_RealLiteral;
    }
};


class BoolLiteral: public ASTNode {
    static bool classof(const ASTNode *N) {
        return N->getKind() == ASTNodeKind::N_BoolLiteral;
    }
};


class CharLiteral: public ASTNode {
    static bool classof(const ASTNode *N) {
        return N->getKind() == ASTNodeKind::N_CharLiteral;
    }
};


class Tuple: public ASTNode {
    static bool classof(const ASTNode *N) {
        return N->getKind() == ASTNodeKind::N_Tuple;
    }
};


class TupleAccess: public ASTNode {
    static bool classof(const ASTNode *N) {
        return N->getKind() == ASTNodeKind::N_TupleAccess;
    }
};


class TupleDecl: public ASTNode {
    static bool classof(const ASTNode *N) {
        return N->getKind() == ASTNodeKind::N_TupleDecl;
    }
};


class Conditional: public ASTNode {
    static bool classof(const ASTNode *N) {
        return N->getKind() == ASTNodeKind::N_Conditional;
    }
};


class Cast: public ASTNode {
    static bool classof(const ASTNode *N) {
        return N->getKind() == ASTNodeKind::N_Cast;
    }
};


class BitwiseOp: public ASTNode {
    static bool classof(const ASTNode *N) {
        return N->getKind() == ASTNodeKind::N_BitwiseOp;
    }
};


class UnaryOp: public ASTNode {
    static bool classof(const ASTNode *N) {
        return N->getKind() == ASTNodeKind::N_UnaryOp;
    }
};


class FunctionDecl: public ASTNode {
    static bool classof(const ASTNode *N) {
        return N->getKind() == ASTNodeKind::N_FunctionDecl;
    }
};


class FunctionCall: public ASTNode {
    static bool classof(const ASTNode *N) {
        return N->getKind() == ASTNodeKind::N_FunctionCall;
    }
};


class ProcedureDecl: public ASTNode {
    static bool classof(const ASTNode *N) {
        return N->getKind() == ASTNodeKind::N_ProcedureDecl;
    }
};


class ProcedureCall: public ASTNode {
    static bool classof(const ASTNode *N) {
        return N->getKind() == ASTNodeKind::N_ProcedureCall;
    }
};


class Return: public ASTNode {
    static bool classof(const ASTNode *N) {
        return N->getKind() == ASTNodeKind::N_Return;
    }
};


class Break: public ASTNode {
    static bool classof(const ASTNode *N) {
        return N->getKind() == ASTNodeKind::N_Break;
    }
};


class Continue: public ASTNode {
    static bool classof(const ASTNode *N) {
        return N->getKind() == ASTNodeKind::N_Continue;
    }
};

#endif //GAZPREABASE_ASTNODES_H
