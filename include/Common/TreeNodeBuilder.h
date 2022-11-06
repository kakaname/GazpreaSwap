#pragma clang diagnostic push
#pragma ide diagnostic ignored "google-explicit-constructor"
//
// Created by dhanrajbir on 28/10/22.
//

#ifndef GAZPREABASE_TREENODEBUILDER_H
#define GAZPREABASE_TREENODEBUILDER_H

#include <map>
#include <memory>

#include "Common/TreeNode.h"
#include "AST/ASTNodes.h"

using std::map;
using std::unique_ptr;

class TreeNodeBuilder {
    unsigned CurrentId;

    struct TreeNodeObject {

        struct TreeNodeConcept {
            virtual ~TreeNodeConcept() = default;
        };

        template<typename NodeT, typename = std::enable_if_t<!std::is_reference_v<NodeT>>>
        struct TreeNodeModel : TreeNodeConcept {
            TreeNodeModel(NodeT N) : Node(N) {
                static_assert(!std::is_reference_v<decltype(N)>);
            }

            NodeT Node;

            NodeT *getPointerToNode() {
                return &Node;
            }
        };

        unique_ptr<TreeNodeConcept> Self;

        TreeNodeObject() = delete;
        TreeNodeObject(TreeNodeObject &&) = default;

        template<typename NodeT>
        TreeNodeObject(NodeT Node): Self(std::make_unique<TreeNodeModel<NodeT>>(Node)) {}

        TreeNodeConcept *getInner() {
            return Self.get();
        }
    };

    using NodesContainerT = map<unsigned, TreeNodeObject>;
    NodesContainerT Nodes;

public:

    TreeNodeBuilder(): CurrentId(0) {}

    template<typename NodeT,
            typename = std::enable_if_t<std::is_base_of_v<TreeNode, NodeT>>>
    NodeT *build() {
        std::pair Key{++CurrentId, TreeNodeObject(NodeT())};
        auto I = Nodes.insert(std::move(Key));
        auto *Res = dynamic_cast<TreeNodeObject::TreeNodeModel<NodeT>*>(
                I.first->second.getInner());
        assert(Res && "Somehow dynamic cast failed?");
        return Res->getPointerToNode();
    }

};


#endif //GAZPREABASE_TREENODEBUILDER_H

#pragma clang diagnostic pop