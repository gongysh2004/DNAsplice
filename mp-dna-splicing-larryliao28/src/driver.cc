#include <iostream>

#include "dna_strand.hpp"
#include "node.hpp"
#include <cassert>
#include <cstring>

void testMatchCase(const char * src, const char * pattern, int expect_pos){
  DNAstrand* sequence1=new DNAstrand(src);
  assert(expect_pos == sequence1->MatchTailCLosest(pattern));
}

void testSpliceSelf(const char * src){
  DNAstrand* sequence1=new DNAstrand(src);
  sequence1->SpliceIn("pattern", *sequence1);
  const char* dnsstr = sequence1->toCstr();
  assert(strcmp( dnsstr, src)==0);
  delete dnsstr;
  delete sequence1;
}

void testNoMatchEmptyCase(const char * src, const char * pattern, const char* sub){
  DNAstrand* sequence1=new DNAstrand(src);
  DNAstrand to_splice_in(sub);
  sequence1->SpliceIn(pattern, to_splice_in);
  const char* dnsstr = sequence1->toCstr();
  assert(strcmp( dnsstr, src)==0);
  delete dnsstr;
  delete sequence1;
}
void testNoMatchSpliceExceptionCase(const char * src, const char * pattern, const char* sub){
  DNAstrand* sequence1=new DNAstrand(src);
  DNAstrand to_splice_in(sub);
  try{
    sequence1->SpliceIn(pattern, to_splice_in);
  } catch(...){
    delete sequence1;
    return;
  }
  assert(1==2);

}

void testSpliceInCase(const char * src, const char * pattern, const char* sub, const char* target_str){
  DNAstrand* sequence1=new DNAstrand(src);
  DNAstrand to_splice_in(sub);
  sequence1->SpliceIn(pattern, to_splice_in);
  const char* dnsstr = sequence1->toCstr();
  assert(strcmp( dnsstr, target_str)==0);
  delete sequence1;
  delete dnsstr;
}

int main() {
  testMatchCase("ctgaattcg", "gaattc", 2);
  //Match middle
  testSpliceInCase("ctgaattcg","gaattc","tgatc", "cttgatcg" );
  testMatchCase("ctata","ta",3 );
  //Match tail
  testSpliceInCase("ctata","ta","tga", "ctatga" );
  //Match tail
  testSpliceInCase("cta2ta","ta","tga", "cta2tga" );
  //Match head
  testSpliceInCase("cta1ct2ta","cta","tga", "tga1ct2ta" );
  //No match exception
  testNoMatchSpliceExceptionCase("cta1ct2ta","xxxxxx","tga");
  //Empty pattern
  testNoMatchEmptyCase("ctata","","tga");
  //splice self
  testSpliceSelf("spliceself");

}