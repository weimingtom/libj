// Copyright (c) 2013-2014 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/atomic_integer.h>
#include <libj/js_function.h>
#include <libj/status.h>
#include <libj/thread.h>

namespace libj {

TEST(GTestAtomicInteger, TestCreate) {
    AtomicInteger::Ptr a1 = AtomicInteger::create();
    AtomicInteger::Ptr a2 = AtomicInteger::create(5);
    ASSERT_TRUE(!!a1);
    ASSERT_TRUE(!!a2);
}

TEST(GTestAtomicInteger, TestInstanceOf) {
    AtomicInteger::Ptr a = AtomicInteger::create();
    ASSERT_TRUE(a->instanceof(Type<AtomicInteger>::id()));
    ASSERT_TRUE(a->instanceof(Type<Mutable>::id()));
    ASSERT_TRUE(a->instanceof(Type<Object>::id()));

    ASSERT_FALSE(a->instanceof(Type<Immutable>::id()));
}

TEST(GTestAtomicInteger, TestGet) {
    AtomicInteger::Ptr a1 = AtomicInteger::create();
    AtomicInteger::Ptr a2 = AtomicInteger::create(5);
    ASSERT_EQ(0, a1->get());
    ASSERT_EQ(5, a2->get());
}

TEST(GTestAtomicInteger, TestSet) {
    AtomicInteger::Ptr a = AtomicInteger::create(5);
    a->set(11);
    ASSERT_EQ(11, a->get());
}

TEST(GTestAtomicInteger, TestAddAndGet) {
    AtomicInteger::Ptr a = AtomicInteger::create(5);
    ASSERT_EQ(13, a->addAndGet(8));
}

TEST(GTestAtomicInteger, TestIncrementAndGet) {
    AtomicInteger::Ptr a = AtomicInteger::create(5);
    ASSERT_EQ(6, a->incrementAndGet());
}

TEST(GTestAtomicInteger, TestDecrementAndGet) {
    AtomicInteger::Ptr a = AtomicInteger::create(5);
    ASSERT_EQ(4, a->decrementAndGet());
}

class GTestAtomicIntegerInc : LIBJ_JS_FUNCTION(GTestAtomicIntegerInc)
 public:
    GTestAtomicIntegerInc(
        AtomicInteger::Ptr a,
        Size max)
        : max_(max)
        , a_(a) {}

    virtual Value operator()(JsArray::Ptr args) {
        for (Size i = 0; i < max_; i++) {
            a_->incrementAndGet();
        }
        return Status::OK;
    }

 private:
    Size max_;
    AtomicInteger::Ptr a_;
};

TEST(GTestAtomicInteger, TestIncrementAndGet2) {
    AtomicInteger::Ptr a = AtomicInteger::create();

    Thread::Ptr t1 = Thread::create(
        Function::Ptr(new GTestAtomicIntegerInc(a, 1000)));
    Thread::Ptr t2 = Thread::create(
        Function::Ptr(new GTestAtomicIntegerInc(a, 1000)));
    Thread::Ptr t3 = Thread::create(
        Function::Ptr(new GTestAtomicIntegerInc(a, 1333)));

    t1->start();
    t2->start();
    t3->start();

    t1->join();
    t2->join();
    t3->join();

    ASSERT_EQ(3333, a->get());
}

}  // namespace libj
