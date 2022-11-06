//
// Created by dhanrajbir on 01/11/22.
//

#ifndef GAZPREABASE_TYPEREGISTERY_H
#define GAZPREABASE_TYPEREGISTERY_H

#include <map>
#include <memory>
#include <vector>

#include "Types/Type.h"
#include "Types/ScalarTypes.h"
#include "Types/CompositeTypes.h"

using std::unique_ptr;
using std::make_unique;
using std::pair;
using std::vector;

class TypeRegistry {

    using VectorTyContainer = map<int, unique_ptr<VectorTy>>;
    using MatrixTyContainer = map<pair<int, int>, unique_ptr<MatrixTy>>;
    using TupleTyContainer = map<vector<Type*>, unique_ptr<TupleTy>>;
    using FunctionTypeContainer = map<vector<Type*>, unique_ptr<FunctionTy>>;


    NullTy NullType;
    IdentityTy IdentityType;
    BoolTy ConstBoolType;
    BoolTy BoolType;
    CharTy ConstCharType;
    CharTy CharType;
    IntegerTy ConstIntType;
    IntegerTy IntType;
    RealTy ConstRealType;
    RealTy RealType;

    VectorTyContainer VectorTypes;
    MatrixTyContainer MatrixTypes;
    TupleTyContainer TupleTypes;
    FunctionTypeContainer FunctionTypes;

    explicit TypeRegistry() : NullType(), IdentityType(), ConstBoolType(true),
        BoolType(false), ConstCharType(true), CharType(false), ConstIntType(true),
                              IntType(false), ConstRealType(true), RealType(true) {

    }

};

class TupleTypeBuilder {

};

#endif //GAZPREABASE_TYPEREGISTERY_H
