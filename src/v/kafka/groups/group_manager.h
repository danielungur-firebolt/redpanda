#pragma once
#include "config/configuration.h"
#include "kafka/errors.h"
#include "kafka/groups/group.h"
#include "kafka/requests/heartbeat_request.h"
#include "kafka/requests/join_group_request.h"
#include "kafka/requests/leave_group_request.h"
#include "kafka/requests/sync_group_request.h"
#include "seastarx.h"

#include <seastar/core/future.hh>
#include <seastar/core/sharded.hh>

#include <cluster/partition_manager.h>

namespace kafka {

/// \brief Manages the Kafka group lifecycle.
class group_manager {
public:
    group_manager(
      sharded<cluster::partition_manager>& partitions,
      config::configuration& conf)
      : _partitions(partitions.local())
      , _conf(conf) {}

    future<> start() {
        // TODO setup partition manager hooks when this shard becomes a
        // partition leader for the group membership topic then group state will
        // need to be recovered. this will happen for instance at startup, and
        // in response to failovers.
        return make_ready_future<>();
    }

    future<> stop() {
        // TODO clean up groups and members and timers. in flight requests may
        // be holding references to groups/members--so here we mark groups as
        // being cleaned up. we can also use semaphore / guards here, but this
        // integration is evolving.
        return make_ready_future<>();
    }

public:
    /// \brief Handle a JoinGroup request
    future<join_group_response> join_group(join_group_request&& request);

    /// \brief Handle a SyncGroup request
    future<sync_group_response> sync_group(sync_group_request&& request);

    /// \brief Handle a Heartbeat request
    future<heartbeat_response> heartbeat(heartbeat_request&& request) {
        using reply = heartbeat_response;
        return make_ready_future<reply>(reply(error_code::unsupported_version));
    }

    /// \brief Handle a LeaveGroup request
    future<leave_group_response> leave_group(leave_group_request&& request) {
        using reply = leave_group_response;
        return make_ready_future<reply>(reply(error_code::unsupported_version));
    }

public:
    static error_code validate_group_status(group_id group, api_key api);
    static bool valid_group_id(group_id group, api_key api);

private:
    group_ptr get_group(group_id group) {
        if (auto it = _groups.find(group); it != _groups.end()) {
            return it->second;
        }
        return nullptr;
    }

    cluster::partition_manager& _partitions;
    config::configuration& _conf;
    std::unordered_map<group_id, group_ptr> _groups;
};

} // namespace kafka
