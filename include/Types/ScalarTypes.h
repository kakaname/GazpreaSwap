//
// Created by dhanrajbir on 01/11/22.
//

#ifndef GAZPREABASE_SCALARTYPES_H
#define GAZPREABASE_SCALARTYPES_H

#include "Type.h"

struct NullTy : public Type {
    static bool classof(const Type *T) {
        return T->getKind() == TypeKind::T_Null;
    }

    NullTy() : Type(TypeKind::T_Null, true) {}
};

struct IdentityTy : public Type {
    static bool classof(const Type *T) {
        return T->getKind() == TypeKind::T_Identity;
    }

    IdentityTy() : Type(TypeKind::T_Identity, true) {}
};

struct IntegerTy : public Type {
    static bool classof(const Type *T) {
        return T->getKind() == TypeKind::T_Int;
    }

    IntegerTy() = delete;

    explicit IntegerTy(bool IsConst) : Type(TypeKind::T_Int, IsConst) {}
};

struct RealTy : public Type {
    static bool classof(const Type *T) {
        return T->getKind() == TypeKind::T_Real;
    }

    RealTy() = delete;

    explicit RealTy(bool IsConst) : Type(TypeKind::T_Real, IsConst) {}
};

struct CharTy : public Type {
    static bool classof(const Type *T) {
        return T->getKind() == TypeKind::T_Real;
    }

    CharTy() = delete;

    explicit CharTy(bool IsConst) : Type(TypeKind::T_Char, IsConst) {}
};


struct BoolTy : public Type {
    static bool classof(const Type *T) {
        return T->getKind() == TypeKind::T_Bool;
    }

    BoolTy() = delete;

    explicit BoolTy(bool IsConst) : Type(TypeKind::T_Bool, IsConst) {}
};

#endif //GAZPREABASE_SCALARTYPES_H
