#include <iostream>

#include "dna_strand.hpp"
#include "node.hpp"
#include <cassert>
#include <cstring>

int main() {
  DNAstrand* sequence1=new DNAstrand("ctgaattcg");
  const char * pattern1 = "gaattc";
  assert(6 == sequence1->StrLen(pattern1));
  assert(2 == sequence1->MatchTailCLosest(pattern1));
  assert(0 == sequence1->MatchTailCLosest("ctgaa"));
  assert(-1 == sequence1->MatchTailCLosest("ctgxx"));
  DNAstrand *to_splice_in1= new DNAstrand("tgatc");
  sequence1->SpliceIn(pattern1, *to_splice_in1);
  const char* targetStr = sequence1->toCstr();
  assert(strcmp( "cttgatcg", targetStr)==0);
  delete targetStr;
  delete sequence1;
  DNAstrand* sequence2 = new DNAstrand("ctata");
  const char * pattern2 = "ta";
  DNAstrand *to_splice_in2= new DNAstrand("tga");
  sequence2->SpliceIn(pattern2, *to_splice_in2);
  const char* targetStr2 = sequence2->toCstr();
  assert(strcmp( "ctatga", targetStr2)==0);
}