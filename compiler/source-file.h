// vim: set ts=8 sts=4 sw=4 tw=99 et:
//
//  Copyright (c) AlliedModders LLC 2021
//
//  This software is provided "as-is", without any express or implied warranty.
//  In no event will the authors be held liable for any damages arising from
//  the use of this software.
//
//  Permission is granted to anyone to use this software for any purpose,
//  including commercial applications, and to alter it and redistribute it
//  freely, subject to the following restrictions:
//
//  1.  The origin of this software must not be misrepresented; you must not
//      claim that you wrote the original software. If you use this software in
//      a product, an acknowledgment in the product documentation would be
//      appreciated but is not required.
//  2.  Altered source versions must be plainly marked as such, and must not be
//      misrepresented as being the original software.
//  3.  This notice may not be removed or altered from any source distribution.
#pragma once

#include <stdio.h>

#include <memory>
#include <string>

#include <amtl/am-maybe.h>
#include "stl/stl-string.h"

class SourceFile
{
    friend class SourceManager;

  public:
    SourceFile();
    SourceFile(const SourceFile&) = delete;
    SourceFile(SourceFile&&) = delete;

    bool Read(unsigned char* target, int maxchars);
    int64_t Pos();
    void Reset(int64_t pos);
    int Eof();

    const char* name() const { return name_.c_str(); }
    const std::string& path() const { return name_; }
    size_t size() const { return data_.size(); }
    uint32_t sources_index() const { return sources_index_.get(); }

    bool is_main_file() const { return is_main_file_; }
    void set_is_main_file() { is_main_file_ = true; }

    void operator =(const SourceFile&) = delete;
    void operator =(SourceFile&&) = delete;
    const unsigned char* data() const {
        return reinterpret_cast<const unsigned char*>(data_.data());
    }

  private:
    bool Open(const std::string& file_name);

    void set_sources_index(uint32_t sources_index) { sources_index_ = ke::Some(sources_index); }
    uint32_t location_index() const { return location_index_.get(); }
    void set_location_index(uint32_t location_index) { location_index_ = ke::Some(location_index); }

  private:
    std::string name_;
    tr::string data_;
    size_t pos_;
    bool is_main_file_ = false;
    ke::Maybe<uint32_t> sources_index_;
    ke::Maybe<uint32_t> location_index_;
};
