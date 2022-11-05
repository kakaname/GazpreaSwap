//
// Created by dhanrajbir on 28/10/22.
//

#ifndef GAZPREABASE_ASTNODES_H
#define GAZPREABASE_ASTNODES_H


class ASTNode {
public:
    enum ASTNodeKind {
        N_Identifier,
        N_Declaration
    };

    ASTNodeKind getKind() const {
        return Kind;
    }
private:
    ASTNodeKind Kind;
};


class Program: ASTNode {

};


class Identifier: public ASTNode {

};


class Assignment: public ASTNode {

};


class Declaration: public ASTNode {

};


class Block: public ASTNode {

};


class LogicalOp: public ASTNode {

};


class ArithmeticOp: public ASTNode {

};


class Index: public ASTNode {

};


class Loop: public ASTNode {

};


class IntLiteral: public ASTNode {

};


class NullLiteral: public ASTNode {

};


class IdentityLiteral: public ASTNode {

};


class RealLiteral: public ASTNode {

};


class BoolLiteral: public ASTNode {

};


class CharLiteral: public ASTNode {

};


class Tuple: public ASTNode {

};


class TupleAccess: public ASTNode {

};


class TupleDecl: public ASTNode {

};


class Conditional: public ASTNode {

};


class Cast: public ASTNode {

};


class BitwiseOp: public ASTNode {

};


class UnaryOp: public ASTNode {

};


class FunctionDecl: public ASTNode {

};


class FunctionCall: public ASTNode {

};


class ProcedureDecl: public ASTNode {

};


class ProcedureCall: public ASTNode {

};


class Return: public ASTNode {

};


class Break: public ASTNode {

};


class Continue: public ASTNode {
    
};

#endif //GAZPREABASE_ASTNODES_H
