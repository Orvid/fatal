/*
 *  Copyright (c) 2015, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  LICENSE file in the root directory of this source tree. An additional grant
 *  of patent rights can be found in the PATENTS file in the same directory.
 */

#include <fatal/type/benchmark/prefix_tree.h>

#include <fatal/benchmark/driver.h>

namespace fatal {

CREATE_BENCHMARK(n30_len20,
  s20_00, s20_01, s20_02, s20_03, s20_04,
  s20_05, s20_06, s20_07, s20_08, s20_09,
  s20_10, s20_11, s20_12, s20_13, s20_14,
  s20_15, s20_16, s20_17, s20_18, s20_19,
  s20_20, s20_21, s20_22, s20_23, s20_24,
  s20_25, s20_26, s20_27, s20_28, s20_29
);

} // namespace fatal {
