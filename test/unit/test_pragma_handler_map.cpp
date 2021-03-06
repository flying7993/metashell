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

#include <metashell/iface/pragma_handler.hpp>
#include <metashell/null_displayer.hpp>
#include <metashell/pragma_handler_map.hpp>

#include <gtest/gtest.h>

using namespace metashell;

namespace
{
  class test_handler : public iface::pragma_handler
  {
  public:
    explicit test_handler(bool& run_flag_) : _run_flag(run_flag_) {}

    virtual iface::pragma_handler* clone() const override
    {
      return new test_handler(_run_flag);
    }

    virtual std::string arguments() const override { return "a|b|c"; }
    virtual std::string description() const override { return "Foo bar"; }

    virtual void run(const data::command::iterator&,
                     const data::command::iterator&,
                     const data::command::iterator&,
                     const data::command::iterator&,
                     iface::displayer&) const override
    {
      _run_flag = true;
    }

  private:
    bool& _run_flag;
  };
}

TEST(pragma_handler_map, handler_sets_run_flag)
{
  null_displayer d;
  bool flag = false;
  run(test_handler(flag), "foo", d);

  ASSERT_TRUE(flag);
}

TEST(pragma_handler_map, processing_non_existing_handler)
{
  pragma_handler_map m;
  const data::command cmd(/* #pragma metashell */ "foo");

  null_displayer d;
  ASSERT_ANY_THROW(m.process(cmd.begin(), cmd.end(), d));
}

TEST(pragma_handler_map, processing_existing_handler)
{
  bool foo_run = false;
  pragma_handler_map m;
  m.add("foo", test_handler(foo_run));
  const data::command cmd(/* #pragma metashell */ "foo");

  null_displayer d;
  m.process(cmd.begin(), cmd.end(), d);

  ASSERT_TRUE(foo_run);
}

TEST(pragma_handler_map, pragma_with_two_token_name_is_called)
{
  bool foo_bar_run = false;
  pragma_handler_map m;
  m.add("foo", "bar", test_handler(foo_bar_run));
  const data::command cmd(/* #pragma metashell */ "foo bar");

  null_displayer d;
  m.process(cmd.begin(), cmd.end(), d);

  ASSERT_TRUE(foo_bar_run);
}

TEST(pragma_handler_map,
     pragma_with_two_token_name_is_called_when_prefix_is_available)
{
  bool foo_bar_run = false;
  bool foo_run = false;
  pragma_handler_map m;
  m.add("foo", test_handler(foo_run));
  m.add("foo", "bar", test_handler(foo_bar_run));
  const data::command cmd(/* #pragma metashell */ "foo bar");

  null_displayer d;
  m.process(cmd.begin(), cmd.end(), d);

  ASSERT_FALSE(foo_run);
  ASSERT_TRUE(foo_bar_run);
}

TEST(pragma_handler_map,
     pragma_prefix_is_selected_when_longer_version_is_available)
{
  bool foo_bar_run = false;
  bool foo_run = false;
  pragma_handler_map m;
  m.add("foo", test_handler(foo_run));
  m.add("foo", "bar", test_handler(foo_bar_run));
  const data::command cmd(/* #pragma metashell */ "foo x");

  null_displayer d;
  m.process(cmd.begin(), cmd.end(), d);

  ASSERT_TRUE(foo_run);
  ASSERT_FALSE(foo_bar_run);
}
