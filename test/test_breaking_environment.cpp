// Metashell - Interactive C++ template metaprogramming shell
// Copyright (C) 2014, Abel Sinkovics (abel@sinkovics.hu)
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "breaking_environment.hpp"

#include <metashell/config.hpp>

#include <just/test.hpp>

JUST_TEST_CASE(test_breaking_environment_does_not_throw)
{
  breaking_environment e(metashell::config::empty());

  // should not throw

  e.append("foo");
  e.get();
  e.get_appended("bar");
  e.internal_dir();
  e.clang_arguments();
  e.get_headers();
}

JUST_TEST_CASE(test_breaking_environment_throws)
{
  breaking_environment e(metashell::config::empty());
  e.throw_from_now();

  JUST_ASSERT_THROWS_SOMETHING(e.append("foo"));
  JUST_ASSERT_THROWS_SOMETHING(e.get());
  JUST_ASSERT_THROWS_SOMETHING(e.get_appended("bar"));
  JUST_ASSERT_THROWS_SOMETHING(e.internal_dir());
  JUST_ASSERT_THROWS_SOMETHING(e.clang_arguments());
  JUST_ASSERT_THROWS_SOMETHING(e.get_headers());
}


