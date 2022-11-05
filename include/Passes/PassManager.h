//
// Created by dhanrajbir on 28/10/22.
//

#ifndef GAZPREABASE_PASSMANAGER_H
#define GAZPREABASE_PASSMANAGER_H

#include <vector>
#include <map>
#include <set>
#include <stdexcept>
#include <type_traits>

#include "Common/TreeNode.h"
#include "Common/TreeNodeBuilder.h"
#include "Passes/Pass.h"
#include "AST/ASTNodes.h"
#include "PassManagerResource.h"

using std::vector;
using std::map;
using std::pair;
using std::set;


// The ASTPassManager provides the supporting infrastructure for passes that
// operate on the AST. Apart from running the passes, the pass manager has
// support for setting and accessing results of different passes.
//
// The passes themselves do not need to inherit from any superclass instead,
// any object that has a `runOnAST(PassManager&, ASTNodeT&)` and has a move
// constructor can be registered as a pass.
//
// Passes can set results that can later be used by other passes. This is
// completely optional. The requirements to be able to store results in
// pass manager are:
// 1) A public static method named ID() that should return a pointer to a
// PassId object that uniquely identifies that pass. Note that this ID must be
// the same for all objects of a given pass but should instead uniquely
// identify a pass's class. To simplify this, passes can inherit from the
// ASTPassIDMixin CRTP that automatically provides this ID method that
// uniquely identifies your pass.
// 2) A public member type named ResultT that should be set to the type that
// the pass wishes to set as a result. There are no restriction on what types
// could be used as results. The result types do not need to inherit from any
// super classes.
// Results are set by calling the
//                          `setResult<PassThatIsSettingTheResult>(Result)`
// on the pass manager that was passed in the runOnAST method.
// Results of another pass are accessed by calling
//                          `getResult<PassWhoseResultYouWant>()`
//
// Note that if a pass only accesses the results of other passes but never sets
// its own, it can omit the ResultT member type and the ID method entirely.
//
// Apart from the ability to set results, the pass manager also has some
// convenience methods around annotating the AST.
// The requirements for a pass being able to annotate the AST are similar to
// the requirements for being able to set a result except instead of a ResultT
// member type, annotations require a public AnnotationT member that should
// represent the type with which the pass wishes to annotate the nodes of the
// AST. Any type that can be used as a result of a pass can be used as an
// annotation. That is to say, there are no restrictions on what a annotation
// could be. Note that a pass may define both an annotation type and result
// type.
// Annotations are set and accessed in a similar way to results, by calling
// `setAnnotation<PassThatIsSettingTheAnnotation>(NodeToAnnotate, Annotation)`
// and `getAnnotation<PassThatAnnotated>(Node)`
//
// Check the AST/TestPasses.h file for some example on how passes can access
// this infrastructure.
class ASTPassManager {

    using NodeIdPassIdPair = pair<unsigned, const PassId*>;
    using AnnotationMapT = map<NodeIdPassIdPair , unique_ptr<ResultObject>>;
    using PassIDToIdxMapT = map<const PassId*, size_t>;
    using ResultMapT = map<const PassId*, unique_ptr<ResultObject>>;
    using ResourceMapT = map<const ResourceId*, unique_ptr<ResultObject>>;

    shared_ptr<ASTNodeT> Root;
    AnnotationMapT Annotations;
    ResultMapT Results;
    ResourceMapT Resources;
    PassIDToIdxMapT IdToIdxMap;
    set<const PassId *> ValidResults;

    vector<PassObject> Passes;

public:
    TreeNodeBuilder Builder;
    ASTPassManager() : Builder() {
        Root = Builder.build<ASTNodeT>();
    };

    // NOTE: The following three methods need to be in the header file for the
    // program to compile, this is because the compiler should be able to see
    // the implementation in order to specialize them when calling from other
    // files.
    template<typename PassT>
    typename PassT::ResultT &getResult() {
        auto Res = Results.find(PassT::ID());
        assert(Res != Results.end() && "Attempt to access result from the "
                                       "PassManager before it is set.");

        // If the result has been invalidated, we run the pass again.
        if (!ValidResults.count(PassT::ID()))
            runPass<PassT>();

        // We just ran the pass, therefore the result should be here.
        ResultObject *PassResult = Results.find(PassT::ID())->second.get();
        return PassResult->template getConcreteResult<typename PassT::ResultT>();
    };

    template<typename PassT>
    void invalidateResult() {
        // We just remove it from the set of valid results.
        ValidResults.erase(PassT::ID());
    }

    template<typename PassT>
    void setResult(typename PassT::ResultT Result) {
        // Ensure we are not setting a reference as a result.
        static_assert(!std::is_reference_v<decltype(Result)>);

        // If a result is set explicitly then it must be valid.
        ValidResults.insert(PassT::ID());
        Results.insert({PassT::ID(),
                        make_unique<ResultObject>(std::move(Result))});
    }

    template<class PassT>
    typename PassT::AnnotationT &getAnnotation(ASTNodeT &Node) {
        std::pair<unsigned, const PassId*> Key(Node.getID(), PassT::ID());
        auto Res = Annotations.find(Key);

        assert(Res != Annotations.end() && "Attempt to access annotations from"
                                           " the PassManager before it is set.");

        ResultObject *Annotation = Res->second.get();
        return Annotation->template getConcreteResult<typename PassT::AnnotationT>();
    }

    template<typename PassT>
    void setAnnotation(ASTNodeT &Node, typename PassT::AnnotationT Annotation) {
        // Ensure we are not setting a reference as an annotation.
        static_assert(!std::is_reference_v<decltype(Annotation)>);
        std::pair Key(Node.getID(), PassT::ID());
        Annotations[Key] = make_unique<ResultObject>(
                std::forward<typename PassT::AnnotationT>(Annotation));
    }

    // SFNAE template for passes that have an id and hence may store a result.
    template<typename PassT>
    void registerPass(PassT Pass) {
        // Ensure that we are not passing in a reference type to be registered
        // as a pass.
        static_assert(!std::is_reference_v<decltype(Pass)>);
        IdToIdxMap[PassT::ID()] = Passes.size();
        Passes.push_back(std::forward<PassT>(Pass));
    }

    template<typename PassT>
    void registerAnonymousPass(PassT Pass) {
        static_assert(!std::is_reference_v<decltype(Pass)>);
        Passes.push_back(std::forward<PassT>(Pass));
    }

    template<typename ResourceT>
    void setResource(ResourceT Resource) {
        static_assert(!std::is_reference_v<decltype(Resource)>);
        Resources.insert({typename ResourceT::ID(),
                          make_unique<ResultObject>(std::move(Resource))});
    }

    template<typename ResourceT>
    ResourceT &getResource() {
        auto Res = Results.find(ResourceT::ID());
        assert(Res != Results.end() && "Attempt to access a resource from the "
                                       "PassManager before it is set.");

        // We just ran the pass, therefore the result should be here.
        ResultObject *ResourceResult = Results.find(ResourceT::ID())->second.get();
        return ResourceResult->template getConcreteResult<ResourceT>();
    };


    template<typename PassT>
    void runPass() {
        auto Res = IdToIdxMap.find(PassT::ID());
        assert(Res != IdToIdxMap.end() && "Passes must be registered before "
                                          "being run.");
        Passes[Res->second].runOnAST(*this, *Root);
    }

    void runAllPasses() {
        for (auto &Pass : Passes)
            Pass.runOnAST(*this, *Root);
    }

    ASTNodeT *getRoot() {
        return Root.get();
    }
};


#endif //GAZPREABASE_PASSMANAGER_H
