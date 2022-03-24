#include "dna_strand.hpp"
#include "node.hpp"
#include <stdexcept>
#include <cassert>
#include <iostream>

DNAstrand::DNAstrand(const char* c_str) {
  const char* c = c_str;
  while ( *c != '\0'){
    Node * node = new Node(*c);
    if(head_ == nullptr){
       head_ = node;
       tail_ = node;
    }else{
      tail_->next = node;
      tail_ = node;
    }
    c++;
  }
}
int DNAstrand::size() const{
  int size = 0;
  Node * node = this->head_;
  while(node != nullptr){
  size ++;
  node=node->next;
  }
  return size;
}
const char* DNAstrand::toCstr() const {
  int size = this->size();
  if(size==0) return nullptr;
  char * cstr = new char[size+1];
  char * work_ptr = cstr;
  Node * node = this->head_;
  while(node != nullptr){
     *work_ptr = node->data;
     work_ptr++;
     node=node->next;
  }
  *work_ptr = '\0';
  return cstr;
}
DNAstrand::~DNAstrand() {
  while (head_ != nullptr) {
    Node* next = head_->next;
    delete head_;
    head_ = next;
  }
}

void DNAstrand::SpliceIn(const char* pattern, DNAstrand& to_splice_in) {
  if (pattern == nullptr || to_splice_in.head_ == nullptr) {
    return;
  }
  int patternSize = this->StrLen(pattern);
  if(to_splice_in.size()==0 || patternSize==0){
    return;
  }
  if (&to_splice_in == this) {
    return;
  }
  int pos = this->MatchTailCLosest(pattern);
  if(pos<0){
    throw std::runtime_error ("Not found the pattern"); 
  }
  Node* start_reserve = nullptr;
  Node* end_reserve = nullptr;
  int step = -1;
  while(step<pos-1){
    if(start_reserve==nullptr){
      start_reserve= head_;
    }else{
    start_reserve =  start_reserve->next;
    }
    step++;
  }

  end_reserve=head_;
  int step2=0;
  while(step2<pos+patternSize){
    end_reserve=end_reserve->next;
    step2 ++;
  }
  Node* start_delete=head_;
  if(start_reserve!=nullptr){
    start_delete = start_reserve->next;
  }
  while(start_delete!=end_reserve){
    Node* temp = start_delete->next;
    delete start_delete;
    start_delete = temp;
  }
  if(start_reserve==nullptr){
    head_ = to_splice_in.head_;
  }else{
    start_reserve->next = to_splice_in.head_;
  }
  to_splice_in.tail_->next = end_reserve;
  if(end_reserve==nullptr){
    tail_ = to_splice_in.tail_;
  }

}

int DNAstrand::StrLen(const char* c_str) const {
  int size = 0;
  while (*c_str != '\0') {
    size++;
    c_str++;
  }
  return size;
}
 


int DNAstrand::MatchTailCLosest(const char* pattern) const{
  int size = this->size();

  int patternSize = this->StrLen(pattern);
  int diff = size - patternSize;
  if(diff<0) return -1;
  // if find match return position, if not return -1)
  const char* work_c_str = pattern;
  Node* current_pos = head_;
  for(int pos=diff; pos>=0; pos--){
    work_c_str = pattern;
    current_pos = head_;
    int move_step = 0;
    while(move_step<pos){
      current_pos = current_pos->next;
      move_step ++;
    }
    while (*work_c_str != '\0' && current_pos->data==*work_c_str) {
      current_pos = current_pos->next;
      work_c_str++;
    }
    if(*work_c_str=='\0'){
      return pos;
    }
  }
  return -1;
}

