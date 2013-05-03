// Copyright (c) 2013 Plenluno All rights reserved.

#ifndef LIBJ_TRACE_H_
#define LIBJ_TRACE_H_

#include <libj/config.h>

#ifdef LIBJ_DEBUG

namespace libj {
namespace trace {

void on();

void off();

bool include(const char* pattern);

bool exclude(const char* pattern);

}  // namespace trace
}  // namespace libj

#define LIBJ_DEBUG_TRACE_ON         libj::trace::on()
#define LIBJ_DEBUG_TRACE_OFF        libj::trace::off()
#define LIBJ_DEBUG_TRACE_INCLUDE(P) libj::trace::include(P)
#define LIBJ_DEBUG_TRACE_EXCLUDE(P) libj::trace::exclude(P)

#else

#define LIBJ_DEBUG_TRACE_ON
#define LIBJ_DEBUG_TRACE_OFF
#define LIBJ_DEBUG_TRACE_INCLUDE(P) false
#define LIBJ_DEBUG_TRACE_EXCLUDE(P) false

#endif

#endif  // LIBJ_TRACE_H_