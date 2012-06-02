// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_IMMUTABLE_H_
#define LIBJ_IMMUTABLE_H_

#include "libj/gc_base.h"
#include "libj/object.h"

namespace libj {

class Immutable
    : public Object
    , public GCBase
    , public ImmutableBase {
 public:
    typedef LIBJ_CPTR(Immutable) CPtr;

    Boolean instanceOf(TypeId id) const {
        return id == Type<Immutable>::id()
            || Object::instanceOf(id);
    }
};

#define LIBJ_IMMUTABLE_DECLS(T, B) public: \
    typedef LIBJ_CPTR(T) CPtr; \
    libj::TypeId type() const { \
        return libj::Type<T>::id(); \
    } \
    Boolean instanceOf(libj::TypeId id) const { \
        return id == libj::Type<T>::id() \
            || B::instanceOf(id); \
    }

#define LIBJ_IMMUTABLE(T) public libj::Immutable { \
    LIBJ_IMMUTABLE_DECLS(T, libj::Immutable)

}  // namespace libj

#endif  // LIBJ_IMMUTABLE_H_
