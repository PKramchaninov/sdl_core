/**
 * Copyright (c) 2014, Ford Motor Company
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following
 * disclaimer in the documentation and/or other materials provided with the
 * distribution.
 *
 * Neither the name of the Ford Motor Company nor the names of its contributors
 * may be used to endorse or promote products derived from this software
 * without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include "cppgen/enum_to_json_value_function.h"

#include <ostream>

#include "cppgen/generator_preferences.h"
#include "cppgen/literal_generator.h"
#include "model/composite_type.h"
#include "utils/safeformat.h"

using std::endl;
using typesafe_format::strmfmt;

namespace codegen {

EnumToJsonValueFunction::EnumToJsonValueFunction(const Enum* enm)
    : CppFunction("", "EnumToJsonString", "const char*"),
      enm_(enm) {
  Add(Parameter("val", enm->name()));
}

EnumToJsonValueFunction::~EnumToJsonValueFunction() {
}

void EnumToJsonValueFunction::DefineBody(std::ostream* os) const {
  strmfmt(*os, "switch({0}) {", parameters_[0].name) << endl;
  {
    Indent indent(*os);
    const Enum::ConstantsList& consts = enm_->constants();
    for (Enum::ConstantsList::const_iterator i = consts.begin();
        i != consts.end(); ++i) {
      const Enum::Constant& c = *i;
      strmfmt(*os, "case {0}: return \"{1}\";", LiteralGenerator(c).result(),
              c.name()) << endl;
    }
    *os << "default: return \"\";" << endl;
  }
  *os << "}" << endl;
}

}  // namespace codegen
