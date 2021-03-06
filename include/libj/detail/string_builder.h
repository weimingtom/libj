// Copyright (c) 2013-2014 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_STRING_BUILDER_H_
#define LIBJ_DETAIL_STRING_BUILDER_H_

#include <libj/this.h>
#include <libj/symbol.h>
#include <libj/detail/string.h>
#include <libj/detail/to_string.h>

#include <assert.h>

namespace libj {
namespace detail {

template<typename I>
class StringBuilder : public I {
 public:
    typedef typename I::Ptr Ptr;
    typedef typename I::CPtr CPtr;

    StringBuilder() {}

    StringBuilder(String::CPtr str) : buf_(str->data(), str->length()) {}

    virtual Size length() const {
        return buf_.length();
    }

    virtual Size capacity() const {
        return buf_.capacity();
    }

    virtual void ensureCapacity(Size capacity) {
        buf_.reserve(capacity);
    }

    virtual Ptr append(const Value& val) {
        LIBJ_STATIC_SYMBOL_DEF(symNull,      "null");
        LIBJ_STATIC_SYMBOL_DEF(symUndefined, "undefined");
        LIBJ_STATIC_SYMBOL_DEF(symTrue,      "true");
        LIBJ_STATIC_SYMBOL_DEF(symFalse,     "false");

        if (val.isObject()) {
            String::CPtr s = toCPtr<Object>(val)->toString();
            assert(s);
            buf_.append(s->data(), s->length());
        } else if (val.isPrimitive()) {
            if (val.is<Boolean>()) {
                if (to<Boolean>(val)) {
                    buf_.append(symTrue->data(), symTrue->length());
                } else {
                    buf_.append(symFalse->data(), symFalse->length());
                }
            } else if (val.is<Double>()) {
                const Size kLen = 64;
                char buf[kLen];
                doubleToString(val, buf, kLen);
                return StringBuilder::appendStr(buf);
            } else if (val.is<Float>()) {
                const Size kLen = 64;
                char buf[kLen];
                floatToString(val, buf, kLen);
                return StringBuilder::appendStr(buf);
            } else {
                const Size kLen = 64;
                Char buf[kLen];
                const Char* s = integerToString(val, buf, kLen);
                assert(s);
                buf_.append(s);
            }
        } else if (val.isNull()) {
            buf_.append(symNull->data(), symNull->length());
        } else {
            assert(val.isUndefined());
            buf_.append(symUndefined->data(), symUndefined->length());
        }
        return LIBJ_THIS_PTR(I);
    }

    virtual Ptr appendChar(Char c) {
        buf_.push_back(c);
        return LIBJ_THIS_PTR(I);
    }

    virtual Ptr appendStr(const char* str) {
        LIBJ_STATIC_SYMBOL_DEF(symNull, "null");

        if (str) {
            while (Char c = static_cast<Char>(*str++)) {
                buf_.push_back(c);
            }
        } else {
            buf_.append(symNull->data(), symNull->length());
        }
        return LIBJ_THIS_PTR(I);
    }

    virtual Ptr appendStr(const Char* str) {
        LIBJ_STATIC_SYMBOL_DEF(symNull, "null");

        if (str) {
            buf_.append(str);
        } else {
            buf_.append(symNull->data(), symNull->length());
        }
        return LIBJ_THIS_PTR(I);
    }

    virtual Ptr appendStr(String::CPtr str) {
        LIBJ_STATIC_SYMBOL_DEF(symNull, "null");

        if (str) {
            buf_.append(str->data(), str->length());
        } else {
            buf_.append(symNull->data(), symNull->length());
        }
        return LIBJ_THIS_PTR(I);
    }

    virtual Char charAt(Size index) const {
        if (index >= buf_.length()) {
            return NO_CHAR;
        } else {
            return buf_[index];
        }
    }

    virtual Boolean setCharAt(Size index, Char c) {
        if (index >= buf_.length()) {
            return false;
        } else {
            buf_[index] = c;
            return true;
        }
    }

    virtual void clear() {
        buf_.clear();
    }

    virtual String::CPtr toString() const {
        return String::create(buf_);
    }

    virtual const Char* data() const {
        return buf_.data();
    }

    virtual std::string toStdString(libj::String::Encoding enc) const {
#ifdef LIBJ_USE_UTF16
        return glue::fromUtf16(buf_, convertStrEncoding(enc));
#else
        return glue::fromUtf32(buf_, convertStrEncoding(enc));
#endif
    }

 private:
#ifdef LIBJ_USE_UTF16
    std::u16string buf_;
#else
    std::u32string buf_;
#endif
};

}  // namespace detail
}  // namespace libj

#endif  // LIBJ_DETAIL_STRING_BUILDER_H_
