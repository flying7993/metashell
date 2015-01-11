#ifndef METASHELL_CONSOLE_DISPLAYER_HPP
#define METASHELL_CONSOLE_DISPLAYER_HPP

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

#include <metashell/iface/displayer.hpp>
#include <metashell/iface/console.hpp>

namespace metashell
{
  class console_displayer : public iface::displayer
  {
  public:
    console_displayer(
      iface::console& console_,
      bool indent_,
      bool syntax_highlight_
    );

    virtual void show_raw_text(const std::string& text_) override;
    virtual void show_error(const std::string& msg_) override;
    virtual void show_type(const type& type_) override;
    virtual void show_comment(const text& msg_) override;
    virtual void show_cpp_code(const std::string& code_) override;

    virtual void show_frame(const frame& frame_) override;
    virtual void show_backtrace(const backtrace& trace_) override;
    virtual void show_call_graph(const iface::call_graph& cg_) override;
  private:
    iface::console* _console;
    bool _indent;
    bool _syntax_highlight;

    void display_code(const std::string& c_);
  };
}

#endif
