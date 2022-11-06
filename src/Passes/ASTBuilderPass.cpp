//
// Created by dhanrajbir on 05/11/22.
//

#include "Passes/ASTBuilderPass.h"
#include "llvm/Support/Casting.h"

using llvm::cast;
using llvm::isa;
using llvm::dyn_cast;

std::any ASTBuilderPass::visitFile(gazprea::GazpreaParser::FileContext *ctx) {
    for (auto Child : ctx->global())
        Prog->addChild(castToNodeVisit(Child));
    return nullptr;
}

void ASTBuilderPass::runOnAST(ASTPassManager &Manager, ASTNodeT *Root) {
    PM = &Manager;
    assert((Prog = dyn_cast<Program>(Root)) && "The Root must be a program");
    visit(File);
}

std::any ASTBuilderPass::visitAssignment(gazprea::GazpreaParser::AssignmentContext *ctx) {
    auto Assign = PM->Builder.build<Assignment>();
    auto Ident = PM->Builder.build<Identifier>();
    Ident->setName(ctx->ID()->getText());
    Assign->setIdentifier(Ident);
    Assign->setExpr(castToNodeVisit(ctx->expr()));
    return Assign;
}

std::any ASTBuilderPass::visitIdentifier(gazprea::GazpreaParser::IdentifierContext *ctx) {
    auto Ident = PM->Builder.build<Identifier>();
    Ident->setName(ctx->getText());
    return Ident;
}

std::any ASTBuilderPass::visitIdentDecl(gazprea::GazpreaParser::IdentDeclContext *ctx) {
    auto Decl = PM->Builder.build<Declaration>();

    // Mark the decl as const if we see a const type qualifier.
    if (ctx->typeQualifier()->CONST())
        Decl->setConst();

    // Set the type node to null if it is not specified. In this case, it will
    // be inferred by the type inference pass later.
    if (!ctx->type())
        Decl->setIdentTypeNode(nullptr);
    else
        Decl->setIdentTypeNode(castToNodeVisit(ctx->type()));
    // Build the identifier that is being assigned to.
    auto Ident = PM->Builder.build<Identifier>(Decl);
    Ident->setName(ctx->ID()->getText());

    // Set the expression to null if it is omitted, the default initializer
    // pass will make sure to set the init value to null for that type.
    if (!ctx->expr())
        Decl->setInitExpr(nullptr);
    else
        Decl->setInitExpr(castToNodeVisit(ctx->expr()));

    return Decl;
}
