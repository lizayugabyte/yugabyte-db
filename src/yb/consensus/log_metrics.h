// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.
//
// The following only applies to changes made to this file as part of YugaByte development.
//
// Portions Copyright (c) YugaByte, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except
// in compliance with the License.  You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software distributed under the License
// is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express
// or implied.  See the License for the specific language governing permissions and limitations
// under the License.
//
#ifndef YB_CONSENSUS_LOG_METRICS_H
#define YB_CONSENSUS_LOG_METRICS_H

#include "yb/gutil/macros.h"
#include "yb/gutil/ref_counted.h"
#include "yb/util/monotime.h"

namespace yb {

class Counter;
class Histogram;
class MetricEntity;

namespace log {

struct LogMetrics {
  explicit LogMetrics(const scoped_refptr<MetricEntity>& metric_entity);

  // Global stats
  scoped_refptr<Counter> bytes_logged;
  scoped_refptr<Counter> wal_size;

  // Per-group group commit stats
  scoped_refptr<Histogram> sync_latency;
  scoped_refptr<Histogram> append_latency;
  scoped_refptr<Histogram> group_commit_latency;
  scoped_refptr<Histogram> roll_latency;
  scoped_refptr<Histogram> entry_batches_per_group;
};

// TODO extract and generalize this for all histogram metrics
#define SCOPED_LATENCY_METRIC(_mtx, _h) \
  ScopedLatencyMetric _h##_metric(_mtx ? _mtx->_h.get() : NULL)

} // namespace log
} // namespace yb

#endif // YB_CONSENSUS_LOG_METRICS_H
