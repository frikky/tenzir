//    _   _____   __________
//   | | / / _ | / __/_  __/     Visibility
//   | |/ / __ |_\ \  / /          Across
//   |___/_/ |_/___/ /_/       Space and Time
//
// SPDX-FileCopyrightText: (c) 2020 The Tenzir Contributors
// SPDX-License-Identifier: BSD-3-Clause

#pragma once

#include "tenzir/concept/parseable/core/action.hpp"
#include "tenzir/concept/parseable/core/choice.hpp"
#include "tenzir/concept/parseable/core/literal.hpp"
#include "tenzir/concept/parseable/core/operators.hpp"
#include "tenzir/concept/parseable/core/parser.hpp"
#include "tenzir/detail/posix.hpp"

namespace tenzir {

struct socket_type_parser : parser_base<socket_type_parser> {
  using attribute = detail::socket_type;

  template <class Iterator, class Attribute>
  bool parse(Iterator& f, const Iterator& l, Attribute& x) const {
    using namespace parser_literals;
    // clang-format off
    auto p
      = ( "datagram"_p ->* [] { return detail::socket_type::datagram; }
        | "stream"_p ->* [] { return detail::socket_type::stream; }
        | "fd"_p ->* [] { return detail::socket_type::fd; }
        );
    // clang-format on
    return p(f, l, x);
  }
};

template <>
struct parser_registry<detail::socket_type> {
  using type = socket_type_parser;
};

namespace parsers {

auto const socket_type = socket_type_parser{};

} // namespace parsers

} // namespace tenzir
