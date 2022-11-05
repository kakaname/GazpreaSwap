//
// Created by dhanrajbir on 01/11/22.
//

#ifndef GAZPREABASE_COMPOSITETYPES_H
#define GAZPREABASE_COMPOSITETYPES_H

#include <vector>
#include <map>
#include <string>

#include "Type.h"

using std::vector;
using std::map;
using std::string;

struct IntervalTy : public Type {
    static bool classof(const Type *T) {
        return T->getKind() == TypeKind::T_Interval;
    }

    IntervalTy() = delete;

    explicit IntervalTy(bool IsConst, int StepSize) : Type(TypeKind::T_Interval, IsConst), StepSize(1) {
        StepSizeKnown = (StepSize > 0);
    }

    int getStepSize() const {
        return StepSize;
    }

    bool isStepSizeKnown() const {
        return StepSizeKnown;
    }

private:
    bool StepSizeKnown;
    int StepSize;
};

struct VectorTy : public Type {
    static bool classof(const Type *T) {
        return T->getKind() == TypeKind::T_Vector;
    }

    VectorTy() = delete;

    VectorTy(bool IsConst, int Size) : Type(TypeKind::T_Vector, IsConst), Size(Size) {
        IsSizeKnown = (Size > 0);
    }

    bool isSizeKnown() const {
        return IsSizeKnown;
    }

    int getSize() const {
        return Size;
    }

private:
    int Size;
    bool IsSizeKnown;
};

struct MatrixTy : public Type {
    static bool classof(const Type *T) {
        return T->getKind() == TypeKind::T_Matrix;
    }

    MatrixTy() = delete;
    
    MatrixTy(bool IsConst, int Rows, int Columns) :
        Type(TypeKind::T_Matrix, IsConst), Rows(Rows), Columns(Columns) {
        RowsIsKnown = (Rows > 0);
        ColumnsIsKnown = (Columns > 0);
    }

    int getNumOfRows() const {
        return Rows;
    };

    int getNumOfColumns() const {
        return Columns;
    };

    bool isNumOfRowsIsKnown() const {
        return RowsIsKnown;
    };

    bool isNumOfColumnsIsKnown() const {
        return ColumnsIsKnown;
    };

private:
    int Rows;
    int Columns;
    bool RowsIsKnown;
    bool ColumnsIsKnown;
};

struct TupleTy : public Type {

    using MemberTyContainer = vector<Type*>;
    using IdentMappingTy = map<string, size_t>;

    static bool classof(const Type *T) {
        return T->getKind() == TypeKind::T_Tuple;
    }

    TupleTy() = delete;

    const Type *getMemberTypeAt(size_t Pos) const {
        if (Pos >= ContainedTypes.size())
            return nullptr;
        return ContainedTypes.at(Pos);
    }

    size_t getNumOfMembers() const {
        return ContainedTypes.size();
    }

    TupleTy(bool IsConst, MemberTyContainer &&ContainedTypes) :
        Type(TypeKind::T_Tuple, IsConst), ContainedTypes(ContainedTypes) {}

private:
    MemberTyContainer ContainedTypes;
};


struct FunctionTy : public Type {
    static bool classof(const Type *T) {
        return T->getKind() == TypeKind::T_Function;
    }

    using ArgsTypeContainer = vector<Type*>;

    const Type *getArgTypeAt(size_t Pos) {
        if (Pos >= Args.size())
            return nullptr;
        return Args.at(Pos);
    }

    FunctionTy() = delete;

    explicit FunctionTy(ArgsTypeContainer &&Args) :
        Type(TypeKind::T_Function, true), Args(Args) {}

private:
    ArgsTypeContainer Args;
};

#endif //GAZPREABASE_COMPOSITETYPES_H
