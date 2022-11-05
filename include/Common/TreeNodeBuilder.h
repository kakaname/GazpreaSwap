//
// Created by dhanrajbir on 28/10/22.
//

#ifndef GAZPREABASE_TREENODEBUILDER_H
#define GAZPREABASE_TREENODEBUILDER_H

#include <memory>

#include "Common/TreeNode.h"

using std::make_shared;
using std::shared_ptr;

class TreeNodeBuilder {
    unsigned CurrentId;

public:
    template<typename NodeT>
    shared_ptr<NodeT> build() {
        return make_shared<NodeT>(std::forward<NodeT>(NodeT(++CurrentId)));
    }

    template<typename NodeT>
    shared_ptr<NodeT> build(TreeNode<typename NodeT::InnerT> *Parent) {
        return make_shared<NodeT>(std::forward<NodeT>(NodeT(++CurrentId, Parent)));
    }


    template<typename NodeT>
    shared_ptr<NodeT> build(typename NodeT::InnerT Inner) {
        return make_shared<NodeT>(std::forward<NodeT>(NodeT(++CurrentId, Inner)));
    }

    template<typename NodeT>
    shared_ptr<NodeT> build(TreeNode<typename NodeT::InnerT> *Parent, typename NodeT::InnerT Inner) {
        return make_shared<NodeT>(std::forward<NodeT>(NodeT(++CurrentId, Parent, Inner)));
    }

    template<typename NodeT>
    NodeT buildAsValue() {
        return NodeT(++CurrentId);
    }
};


#endif //GAZPREABASE_TREENODEBUILDER_H
