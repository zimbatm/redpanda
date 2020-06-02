#include "raft/rpc_client_protocol.h"

#include "outcome_future_utils.h"
#include "raft/raftgen_service.h"
#include "rpc/connection_cache.h"
#include "rpc/exceptions.h"
#include "rpc/transport.h"
#include "rpc/types.h"

namespace raft {

ss::future<result<vote_reply>> rpc_client_protocol::vote(
  model::node_id n, vote_request&& r, rpc::client_opts opts) {
    return _connection_cache.local().with_node_client<raftgen_client_protocol>(
      n,
      [r = std::move(r),
       opts = std::move(opts)](raftgen_client_protocol client) mutable {
          return client.vote(std::move(r), std::move(opts))
            .then(&rpc::get_ctx_data<vote_reply>);
      });
}

ss::future<result<append_entries_reply>> rpc_client_protocol::append_entries(
  model::node_id n, append_entries_request&& r, rpc::client_opts opts) {
    return _connection_cache.local().with_node_client<raftgen_client_protocol>(
      n,
      [r = std::move(r),
       opts = std::move(opts)](raftgen_client_protocol client) mutable {
          return client.append_entries(std::move(r), std::move(opts))
            .then(&rpc::get_ctx_data<append_entries_reply>);
      });
}

ss::future<result<heartbeat_reply>> rpc_client_protocol::heartbeat(
  model::node_id n, heartbeat_request&& r, rpc::client_opts opts) {
    return _connection_cache.local().with_node_client<raftgen_client_protocol>(
      n,
      [r = std::move(r),
       opts = std::move(opts)](raftgen_client_protocol client) mutable {
          return client.heartbeat(std::move(r), std::move(opts))
            .then(&rpc::get_ctx_data<heartbeat_reply>);
      });
}

} // namespace raft
