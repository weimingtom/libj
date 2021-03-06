// Copyright (c) 2012-2014 Plenluno All rights reserved.

#ifndef LIBJ_JS_OBJECT_H_
#define LIBJ_JS_OBJECT_H_

#include <libj/map.h>

namespace libj {

class JsObject : LIBJ_MAP(JsObject)
 public:
    static Ptr create();

    virtual Boolean containsKey(const Value& key) const = 0;

    virtual Boolean containsKey(String::CPtr key) const = 0;

    virtual Value get(const Value& key) const = 0;

    virtual Value get(String::CPtr key) const = 0;

    virtual Value put(const Value& key, const Value& val) = 0;

    virtual Value put(String::CPtr key, const Value& val) = 0;

    virtual Value remove(const Value& key) = 0;

    virtual Value remove(String::CPtr key) = 0;

 public:
    virtual Boolean hasProperty(const Value& name) const = 0;

    virtual Boolean hasProperty(String::CPtr name) const = 0;

    virtual Value getProperty(const Value& name) const = 0;

    virtual Value getProperty(String::CPtr name) const = 0;

    virtual Value setProperty(const Value& name, const Value& val) = 0;

    virtual Value setProperty(String::CPtr name, const Value& val) = 0;

    virtual Value deleteProperty(const Value& name) = 0;

    virtual Value deleteProperty(String::CPtr name) = 0;

    template<typename T>
    typename Type<T>::Ptr getPtr(const Value& name) const;

    template<typename T>
    typename Type<T>::Ptr getPtr(String::CPtr name) const;

    template<typename T>
    typename Type<T>::CPtr getCPtr(const Value& name) const;

    template<typename T>
    typename Type<T>::CPtr getCPtr(String::CPtr name) const;
};

}  // namespace libj

#include <libj/impl/js_object.h>

#define LIBJ_JS_OBJECT(T) public libj::JsObject { \
    LIBJ_MUTABLE_DEFS(T, LIBJ_JS_OBJECT)

#endif  // LIBJ_JS_OBJECT_H_
