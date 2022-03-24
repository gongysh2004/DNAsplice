#ifndef DNA_STRAND_HPP
#define DNA_STRAND_HPP

#include "node.hpp"

class DNAstrand {
public:
  DNAstrand() = default;
  DNAstrand(const DNAstrand& rhs) = delete;
  DNAstrand& operator=(const DNAstrand& rhs) = delete;
  ~DNAstrand();

  DNAstrand(const char*);
  const char* toCstr() const;
  void SpliceIn(const char* pattern, DNAstrand& to_splice_in);
  
  int MatchTailCLosest(const char* pattern) const;
  int Replace(Node* pos);
  int StrLen(const char* c_str) const;
private:
  Node* head_ = nullptr;
  Node* tail_ = nullptr;
  int size() const;

};

#endif