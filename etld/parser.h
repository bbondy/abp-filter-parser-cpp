/* Copyright (c) 2019 The Brave Software Team. Distributed under the MPL2
 * license. This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ETLD_PARSER_H_
#define ETLD_PARSER_H_

#include <string>
#include <fstream>
#include <vector>
#include "etld/public_suffix_rule.h"
#include "etld/types.h"

namespace brave_etld {

enum PublicSuffixTextLineType {
  PublicSuffixTextLineTypeNone = 0,
  PublicSuffixTextLineTypeWhitespace,
  PublicSuffixTextLineTypeComment,
  PublicSuffixTextLineTypeInvalidRule,
  PublicSuffixTextLineTypeRule,
};

struct PublicSuffixTextLineParseResult {
  PublicSuffixTextLineParseResult() {
    type = PublicSuffixTextLineTypeNone;
  }
  PublicSuffixTextLineType type;
  PublicSuffixRule rule;
};

class PublicSuffixParseResult {
 public:
  PublicSuffixParseResult();
  PublicSuffixParseResult(const PublicSuffixParseResult &results);

  std::vector<PublicSuffixRule> Rules() const;
  void AddParseResult(const PublicSuffixTextLineParseResult &result);

  int NumWhitespaceLines() const {
    return num_whitespace_lines_;
  }

  int NumCommentLines() const {
    return num_comment_lines_;
  }

  int NumInvalidRules() const {
    return num_invalid_rules_;
  }

 private:
  int num_whitespace_lines_ = 0;
  int num_comment_lines_ = 0;
  int num_invalid_rules_ = 0;
  std::vector<PublicSuffixRule> rules_;
};

// This attempts to implement the algorithm described here:
//   https://www.publicsuffix.org/list/
PublicSuffixParseResult parse_rule_file(std::ifstream &rule_file);
PublicSuffixParseResult parse_rule_text(const std::string &rule_text);
PublicSuffixTextLineParseResult parse_rule_line(const std::string &line);

}  // namespace brave_etld

#endif  // ETLD_PARSER_H_