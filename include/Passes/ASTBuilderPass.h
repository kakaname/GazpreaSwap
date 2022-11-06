//
// Created by dhanrajbir on 05/11/22.
//

#ifndef GAZPREABASE_ASTBUILDERPASS_H
#define GAZPREABASE_ASTBUILDERPASS_H

#include "GazpreaBaseVisitor.h"
#include "AST/ASTNodes.h"
#include "PassManager.h"

class ASTBuilderPass: public gazprea::GazpreaBaseVisitor {
    ASTPassManager *PM{};

    Program *Prog;

    std::any visitFile(GazpreaParser::FileContext *ctx) override;

    std::any visitIdentDecl(gazprea::GazpreaParser::IdentDeclContext *ctx) override;

    std::any visitAssignment(gazprea::GazpreaParser::AssignmentContext *ctx) override;

    std::any visitIdentifier(gazprea::GazpreaParser::IdentifierContext *ctx) override;

    antlr4::tree::ParseTree *File;

    ASTNodeT *castToNodeVisit(antlr4::tree::ParseTree *Tree) {
        return std::any_cast<ASTNodeT *>(visit(Tree));
    }

public:

    explicit ASTBuilderPass(antlr4::tree::ParseTree *F): File(F) {};

    void runOnAST(ASTPassManager &Manager, ASTNodeT *Root);
};


#endif //GAZPREABASE_ASTBUILDERPASS_H
