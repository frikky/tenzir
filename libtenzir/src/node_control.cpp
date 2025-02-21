//    _   _____   __________
//   | | / / _ | / __/_  __/     Visibility
//   | |/ / __ |_\ \  / /          Across
//   |___/_/ |_/___/ /_/       Space and Time
//
// SPDX-FileCopyrightText: (c) 2021 The Tenzir Contributors
// SPDX-License-Identifier: BSD-3-Clause

#include "tenzir/node_control.hpp"

#include "tenzir/concept/parseable/tenzir/time.hpp"
#include "tenzir/concept/parseable/to.hpp"
#include "tenzir/configuration.hpp"
#include "tenzir/detail/overload.hpp"

#include <caf/scoped_actor.hpp>
#include <caf/settings.hpp>
#include <caf/typed_event_based_actor.hpp>
#include <caf/variant.hpp>

namespace tenzir {

auto node_connection_timeout(const caf::settings& options) -> caf::timespan {
  auto timeout_value = get_or_duration(options, "tenzir.connection-timeout",
                                       defaults::node_connection_timeout);
  if (!timeout_value) {
    TENZIR_ERROR("client failed to read connection-timeout: {}",
                 timeout_value.error());
    return caf::timespan{defaults::node_connection_timeout};
  }
  auto timeout = caf::timespan{*timeout_value};
  if (timeout == timeout.zero())
    return caf::infinite;
  return timeout;
}

caf::expected<caf::actor>
spawn_at_node(caf::scoped_actor& self, const node_actor& node, invocation inv) {
  const auto timeout = node_connection_timeout(self->config().content);
  caf::expected<caf::actor> result = caf::error{};
  self->request(node, timeout, atom::spawn_v, inv)
    .receive(
      [&](caf::actor& actor) {
        result = std::move(actor);
      },
      [&](caf::error& err) {
        result = caf::make_error(ec::unspecified,
                                 fmt::format("failed to spawn '{}' at node: {}",
                                             inv.full_name, err));
      });
  return result;
}

} // namespace tenzir
