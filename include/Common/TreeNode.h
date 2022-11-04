//
// Created by dhanrajbir on 28/10/22.
//

#pragma clang diagnostic push
#pragma ide diagnostic ignored "LoopDoesntUseConditionVariableInspection"
#ifndef GAZPREABASE_TREENODE_H
#define GAZPREABASE_TREENODE_H

#include <list>
#include <memory>
#include <cassert>

using std::shared_ptr;
using std::make_shared;
using std::list;

using UnitT = struct{};

// Common tree node interface that can be used to build any kind of trees. Each
// node has a member of the parameterized type called Inner. The tree should ideally
// own all of its children, but it is possible to get shared references to the
// children nodes. Each node also has a unique ID that can be used to identify a
// given node. The children of any given node are ordered and hence can be accessed
// based on their index.
//
// The TreeNode can be used the Unit type which is an empty type and can be used to
// represent Tree Nodes that do not need to hold an Inner type. TreeNode instances
// should only be created through the TreeNodeBuilder to ensure that the node ID
// is unique.
template<typename T>
struct TreeNode {
    friend class TreeNodeBuilder;

public:
    using InnerT = T;
    using ChildrenContainerT = list<shared_ptr<TreeNode<T>>>;
    size_t addChild(TreeNode<T> &Child) {
        Children.template emplace_back(make_shared<TreeNode<T>>(Child));
        return Children.size();
    };

    size_t addChild(shared_ptr<TreeNode<T>> Child) {
        Children.push_back(std::move(Child));
        return Children.size();
    };

    size_t addChildAt(shared_ptr<TreeNode<T>> Child, size_t Pos) {
        // Ensure there are enough elements in the list.
        while (Pos + 1 > Children.size())
            Children.push_back(shared_ptr<TreeNode<T>>());
        auto It = Children.begin();
        std::advance(It, Pos);
        Children.insert(It, Child);
        return Children.size();
    };

    size_t replaceChildAt(shared_ptr<TreeNode<T>> Child, size_t Pos) {
        while (Pos + 1 > Children.size())
            Children.push_back(shared_ptr<TreeNode<T>>());
        auto It = Children.begin();
        std::advance(It, Pos);
        *It = std::move(Child);
        return Children.size();
    };

    size_t removeChildAt(int Pos) {
        if (Pos + 1 > Children.size())
            return Children.size();
        auto It = Children.begin();
        std::advance(It, Pos);
        Children.erase(It);
        return Children.size();
    };

    size_t numOfChildren() {
        return Children.size();
    }

    bool replaceChildWithId(unsigned Id, shared_ptr<TreeNode<T>> NewChild) {
        auto It = Children.begin();
        while(Children.end() != It) {
            shared_ptr<TreeNode<T>> Child = *It;
            if (Child->getID() == Id) {
                *It = NewChild;
                return true;
            }
            It++;
        }
        return false;
    }

    // Use only when you need to have the subtree stick around after being
    // replaced from the parent. For most cases, getChildAt is more appropriate.
    shared_ptr<TreeNode<T>> getChildAtStrong(size_t Pos) {
        if (Pos + 1 > Children.size())
            return shared_ptr<TreeNode<T>>();
        auto It = Children.begin();
        std::advance(It, Pos);
        shared_ptr<TreeNode<T>> NewShared = *It;
        return NewShared;
    };

    TreeNode<T> *getChildAt(size_t Pos) {
        assert(Pos + 1 > Children.size() && "Attempt to access out of bounds "
                                            "element from TreeNode");
        auto It = Children.begin();
        std::advance(It, Pos);
        return It->get();
    };

    template<typename RetT>
    RetT *getChildAtAs(int Pos) {
        return dynamic_cast<RetT*>(getChildAt(Pos));
    }

    [[nodiscard]] unsigned getID() const {
        return NodeId;
    }

    TreeNode<T> *getParent() {
        return Parent;
    }

    void setParent(TreeNode<T> *P) {
        Parent = P;
    }

    T &getInner() {
        return Inner;
    }

    virtual ~TreeNode() = default;

    // Restrict constructing nodes without IDs. Constructors are private so
    // that Nodes can only be constructed using the Node builder.
    TreeNode() = delete;


private:

    const unsigned NodeId;
    TreeNode<T> *Parent = nullptr;

protected:
    TreeNode(unsigned NodeId, T Inner) : Inner(Inner), NodeId(NodeId), Parent() {};

    TreeNode(unsigned NodeId, TreeNode<T> *Parent) : NodeId(NodeId), Parent(Parent) {}

    TreeNode(unsigned NodeId, TreeNode<T> *Parent, T Inner) : NodeId(NodeId), Parent(Parent), Inner(Inner) {}

    explicit TreeNode(unsigned NodeId) : NodeId(NodeId) {};

    ChildrenContainerT Children;
    T Inner;
};


#endif //GAZPREABASE_TREENODE_H

#pragma clang diagnostic pop