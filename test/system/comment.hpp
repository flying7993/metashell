#ifndef METASHELL_SYSTEM_TEST_COMMENT_HPP
#define METASHELL_SYSTEM_TEST_COMMENT_HPP

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

#include "paragraph.hpp"
#include "json_string.hpp"
#include "placeholder.hpp"

#include <iosfwd>
#include <vector>

namespace metashell_system_test
{
  class comment
  {
  public:
    explicit comment(std::vector<paragraph> paragraphs_);
    explicit comment(placeholder);

    bool paragraphs_specified() const;
    const std::vector<paragraph>& paragraphs() const;
  private:
    bool _paragraphs_specified;
    std::vector<paragraph> _paragraphs;
  };
  
  std::ostream& operator<<(std::ostream& out_, const comment& comment_);

  json_string to_json_string(const comment& comment_);

  bool operator==(const comment& comment_, const json_string& s_);
}

#endif

