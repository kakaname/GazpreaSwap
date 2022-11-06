#pragma clang diagnostic push
#pragma ide diagnostic ignored "google-explicit-constructor"
//
// Created by dhanrajbir on 28/10/22.
//

#ifndef GAZPREABASE_PASS_H
#define GAZPREABASE_PASS_H

#include <algorithm>
#include <memory>
#include <iostream>

#include "Common/TreeNode.h"
#include "AST/ASTNodes.h"

using std::move;
using std::make_unique;
using std::unique_ptr;

class ASTPassManager;

struct alignas(8) PassId {};

class PassObject {
    friend class ASTPassManager;

    struct PassConceptT {
        virtual ~PassConceptT() = default;
        PassConceptT() = default;
        PassConceptT(PassConceptT &&) = default;
        virtual void runOnAST(ASTPassManager &PM, ASTNodeT &Root) = 0;
    };

    template<typename PassT>
    struct PassModelT : PassConceptT {
        PassModelT(PassT P) : Self(std::move(P)) {}
        PassModelT(PassModelT &&)  noexcept = default;
        PassT Self;

        void runOnAST(ASTPassManager &PM, ASTNodeT &Root) override {
            Self.runOnAST(PM, Root);
        }
    };

    unique_ptr<PassConceptT> Pass;

public:
    template<typename T>
    PassObject(T &&P) : Pass(make_unique<PassModelT<T>>(PassModelT<T>(P))) {};

    void runOnAST(ASTPassManager &PM, ASTNodeT &Root)  {
        Pass->runOnAST(PM, Root);
    }
};


class ResultObject {
    struct ResultConceptT {
        virtual ~ResultConceptT() = default;
        ResultConceptT() = default;
        ResultConceptT(ResultConceptT &&) = default;
    };

    template<typename R>
    struct ResultModelT : ResultConceptT {
        ResultModelT(R Res) : Self(std::forward<R>(Res)) {}
        ResultModelT() = delete;
        ResultModelT(ResultModelT &&)  noexcept = default;
        R &getSelf() {
            return Self;
        }

        R Self;
    };

    unique_ptr<ResultConceptT> Self;

public:
    template<typename R, typename = std::enable_if_t<!std::is_reference_v<R>>>
    ResultObject(R Res) : Self(make_unique<ResultModelT<R>>(ResultModelT<R>(Res))) {};

    ResultObject() = delete;

    template<typename R>
    R &getConcreteResult() {
        // Get the pointer behind the unique_ptr and get cast it to the given type.
        ResultConceptT *Res = Self.get();
        auto *Model = dynamic_cast<ResultModelT<R>*>(Res);
        return Model->getSelf();
    }
};


// A simple CRTP mixin that provides an ID to a pass so each pass does not
// have to define and set its own ID method. If you want your pass to be
// able to set results and annotations in the pass manager, derive from
// ASTPassIDMixin<YourPass>.
template<typename Derived>
struct ASTPassIDMixin {
    static PassId *ID() {
        return &Id;
    }
private:
    inline static PassId Id;
};

#endif //GAZPREABASE_PASS_H

#pragma clang diagnostic pop