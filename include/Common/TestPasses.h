//
// Created by dhanrajbir on 28/10/22.
//

#ifndef GAZPREABASE_TESTPASSES_H
#define GAZPREABASE_TESTPASSES_H

#include "Passes/PassManager.h"

// These are only test passes and exist to check all the template specializations
// work as intended.
struct HelloWorldPass {
    static void runOnAST(ASTPassManager &PM, ASTNodeT &Root) {
        std::cout << "Hello World\n";
    }
};

struct SetsMessage : ASTPassIDMixin<SetsMessage> {
    using ResultT = std::string;

    // The method does not need to be static.
    static void runOnAST(ASTPassManager &PM, ASTNodeT &Root) {
        // Any object of the type ResultT defined above can be set as a result.
        // Notice that the object you set as a result does not need to derive
        // from any other classes.
        PM.setResult<SetsMessage>(std::string("Message from SetsMessage."));
    }
};

struct SetsInt : ASTPassIDMixin<SetsInt> {
    using ResultT = int;

    static void runOnAST(ASTPassManager &PM, ASTNodeT &Root) {
        PM.setResult<SetsInt>(42);
    }
};

struct CustomResult {
    std::string getMessage() {
        return std::string{"Custom result"};
    }
};

struct SetsCustomResult : ASTPassIDMixin<SetsCustomResult> {
    using ResultT = CustomResult;
    using AnnotationT = int;

    static void runOnAST(ASTPassManager &PM, ASTNodeT &Root) {
        PM.setResult<SetsCustomResult>(CustomResult());
        PM.setAnnotation<SetsCustomResult>(Root, 84);
    }
};

struct PrintsResults {
    static void runOnAST(ASTPassManager &PM, ASTNodeT &Root) {
        // Will return "Message from SetsMessage."
        std::string& Msg = PM.getResult<SetsMessage>();

        // Will return 42.
        int Msg2 = PM.getResult<SetsInt>();

        // Will return a reference to the CustomResult object that
        // was set bu the SetsCustomResult pass.
        CustomResult &CustomResult = PM.getResult<SetsCustomResult>();

        // Will return the annotation that was set by the SetsCustomResult for
        // the root of the AST i.e. 84.
        int RootAnnotation = PM.getAnnotation<SetsCustomResult>(Root);

        std::cout << Msg2 << std::endl;
        std::cout << Msg << std::endl;
        std::cout << CustomResult.getMessage() << std::endl;
        std::cout << RootAnnotation << std::endl;
    }
};

struct GetsResultInvalidated : ASTPassIDMixin<GetsResultInvalidated> {
    int Count;
    GetsResultInvalidated() : Count(0) {}

    using ResultT = int;

    void runOnAST(ASTPassManager &PM, ASTNodeT) {
        std::cout << "Ran the pass setting the result with"
                     " count " << Count++ << std::endl;
        PM.setResult<GetsResultInvalidated>(Count);
    }
};

struct InvalidatesResults {
    void runOnAST(ASTPassManager &PM, ASTNodeT) {
        int Res =  PM.getResult<GetsResultInvalidated>();
        std::cout << "Got result " << Res << std::endl;
        PM.invalidateResult<GetsResultInvalidated>();
        Res =  PM.getResult<GetsResultInvalidated>();
        std::cout << "Got result " << Res << std::endl;
    }
};

#endif //GAZPREABASE_TESTPASSES_H
