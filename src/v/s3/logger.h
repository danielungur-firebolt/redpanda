/*
 * Copyright 2020 Vectorized, Inc.
 *
 * Licensed as a Redpanda Enterprise file under the Redpanda Community
 * License (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 *
 * https://github.com/danielungur-firebolt/redpanda/blob/master/licenses/rcl.md
 */

#pragma once

#include "seastarx.h"

#include <seastar/util/log.hh>

namespace s3 {
inline ss::logger s3_log("s3");
} // namespace s3
