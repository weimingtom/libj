// Copyright (c) 2013 Plenluno All rights reserved.

#include <libj/string_builder.h>
#include <libj/detail/string_builder.h>

namespace libj {

StringBuilder::Ptr StringBuilder::create() {
    return Ptr(new detail::StringBuilder<StringBuilder>());
}

StringBuilder::Ptr StringBuilder::create(Size capacity) {
    detail::StringBuilder<StringBuilder>* s =
        new detail::StringBuilder<StringBuilder>();
    s->ensureCapacity(capacity);
    return Ptr(s);
}

StringBuilder::Ptr StringBuilder::create(String::CPtr str) {
    if (str) {
        return Ptr(new detail::StringBuilder<StringBuilder>(str));
    } else {
        return StringBuilder::null();
    }
}

}  // namespace libj
