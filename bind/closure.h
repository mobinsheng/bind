/*
 *  Copyright 2014 The WebRTC Project Authors. All rights reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#ifndef RTC_BASE_ASYNCINVOKER_INL_H_
#define RTC_BASE_ASYNCINVOKER_INL_H_

#include <memory>
#include <functional>

namespace lazy {


// Helper class for AsyncInvoker. Runs a task and triggers a callback
// on the calling thread if necessary.
class AsyncClosure {
 public:
    explicit AsyncClosure(){}
    virtual ~AsyncClosure(){}
  // Runs the asynchronous task, and triggers a callback to the calling
  // thread if needed. Should be called from the target thread.
  virtual void Execute() = 0;
};

// Simple closure that doesn't trigger a callback for the calling thread.
template <class FunctorT>
class FireAndForgetAsyncClosure : public AsyncClosure {
 public:
  explicit FireAndForgetAsyncClosure(FunctorT&& functor)
      : AsyncClosure(), functor_(std::forward<FunctorT>(functor)) {}
  virtual void Execute() { functor_(); }

 private:
  typename std::decay<FunctorT>::type functor_;
};

}  // namespace rtc

#endif  // RTC_BASE_ASYNCINVOKER_INL_H_
