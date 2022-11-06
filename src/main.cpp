#include "GazpreaLexer.h"
#include "GazpreaParser.h"
#include "llvm/Support/Casting.h"

#include "ANTLRFileStream.h"
#include "CommonTokenStream.h"
#include "tree/ParseTree.h"
#include "tree/ParseTreeWalker.h"

#include "Passes/PassManager.h"
#include "Common/TestPasses.h"
#include "Types/CompositeTypes.h"

#include <iostream>
#include <fstream>

using llvm::dyn_cast;
using llvm::isa;
using llvm::cast;


int main(int argc, char **argv) {
//  if (argc < 3) {
//    std::cout << "Missing required argument.\n"
//              << "Required arguments: <input file path> <output file path>\n";
//    return 1;
//  }
//
//  // Open the file then parse and lex it.
//  antlr4::ANTLRFileStream afs;
//  afs.loadFromFile(argv[1]);
//  gazprea::GazpreaLexer lexer(&afs);
//  antlr4::CommonTokenStream tokens(&lexer);
//  gazprea::GazpreaParser parser(&tokens);
//
//  // Get the root of the parse tree. Use your base rule name.
//  antlr4::tree::ParseTree *tree = parser.file();

  // HOW TO USE A LISTENER
  // Make the listener
  // MyListener listener;
  // Walk the tree
  // antlr4::tree::ParseTreeWalker::DEFAULT.walk(&listener, tree);

  // HOW TO USE A VISITOR
  // Make the visitor
  // MyVisitor visitor;
  // Visit the tree
  // visitor.visit(tree);

  // HOW TO WRITE OUT.
  // std::ofstream out(argv[2]);
  // out << "This is out...\n";
    VectorTy Vec(true, 0);

    Type *T = &Vec;

    auto *V = dyn_cast<VectorTy>(T);
    std::cout << V->isConst() << std::endl;
    TreeNodeBuilder Builder;
    auto *Assign = Builder.build<Assignment>();
//  ASTPassManager Manager;
//  Manager.registerAnonymousPass(HelloWorldPass());
//  Manager.registerPass(SetsMessage());
//  Manager.registerPass(SetsInt());
//  Manager.registerPass(SetsCustomResult());
//  Manager.registerAnonymousPass(PrintsResults());
//  Manager.registerPass(GetsResultInvalidated());
//  Manager.registerAnonymousPass(InvalidatesResults());
//  Manager.runAllPasses();
  return 0;
}
