// Metashell - Interactive C++ template metaprogramming shell
// Copyright (C) 2015, Abel Sinkovics (abel@sinkovics.hu)
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

#include <metashell/engine_clang.hpp>

#include <metashell/code_completer_clang.hpp>
#include <metashell/cpp_validator_clang.hpp>
#include <metashell/engine.hpp>
#include <metashell/header_discoverer_clang.hpp>
#include <metashell/macro_discovery_clang.hpp>
#include <metashell/preprocessor_shell_clang.hpp>
#include <metashell/template_tracer_clang.hpp>
#include <metashell/type_shell_clang.hpp>

#include <metashell/clang_binary.hpp>

using namespace metashell;

namespace
{
  template <bool UseInternalTemplight>
  std::unique_ptr<iface::engine>
  create_clang_engine(const data::config& config_,
                      const boost::filesystem::path& internal_dir_,
                      const boost::filesystem::path& temp_dir_,
                      const boost::filesystem::path& env_filename_,
                      iface::environment_detector& env_detector_,
                      iface::displayer& displayer_,
                      logger* logger_)
  {
    const clang_binary cbin(
        UseInternalTemplight,
        find_clang(UseInternalTemplight, config_.extra_clang_args,
                   config_.metashell_binary, config_.engine, env_detector_,
                   displayer_, logger_),
        config_.extra_clang_args, internal_dir_, env_detector_, logger_);

    return make_engine(
        config_.engine,
        type_shell_clang(internal_dir_, env_filename_, cbin, logger_),
        preprocessor_shell_clang(cbin),
        code_completer_clang(
            internal_dir_, temp_dir_, env_filename_, cbin, logger_),
        header_discoverer_clang(cbin),
        template_tracer_clang(internal_dir_, env_filename_, cbin),
        cpp_validator_clang(internal_dir_, env_filename_, cbin, logger_),
        macro_discovery_clang(cbin));
  }
} // anonymous namespace

engine_entry metashell::get_engine_clang_entry()
{
  return engine_entry(
      &create_clang_engine<false>,
      "<Clang binary> -std=<standard to use> [<Clang args>]",
      "Uses the Clang compiler or Templight. <Clang args> are passed to the"
      " compiler as command line-arguments. Note that Metashell requires C++11"
      " or above. If your Clang uses such a standard by default, you can omit"
      " the -std argument.");
}

engine_entry metashell::get_internal_templight_entry()
{
  return engine_entry(
      &create_clang_engine<true>, "[<Clang args>]",
      "Uses the Templight shipped with Metashell. <Clang args> are passed to"
      " the compiler as command line-arguments.");
}
