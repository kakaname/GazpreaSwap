//
// Created by dhanrajbir on 04/11/22.
//

#ifndef GAZPREABASE_PASSMANAGERRESOURCE_H
#define GAZPREABASE_PASSMANAGERRESOURCE_H

struct alignas(8) ResourceId {};


template<typename Derived>
struct ResourceIdMixin {
    static ResourceId *ID() {
        return &Id;
    }
private:
    inline static ResourceId Id;
};

#endif //GAZPREABASE_PASSMANAGERRESOURCE_H
