#include "dna_strand.hpp"

#include <stdexcept>

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
  if (&to_splice_in == this) {
    return;
  }
  // step 1: find the pattern
  // loop through the linked list
  // if character matches the first node of pattern,
  // create another loop through the linked list,
  // find match: create an char array of pattern length, see if it matches with
  // pattern
  // terminates if they don't match
  // if mathches, store the position of the current node
  // if reach the end of the list without spotting the pattern(store position is
  // empty), throw an exception
  Node* current = head_;
  Node* pos = nullptr;
  while (current != nullptr) {
    if (current->data == *pattern) {
      Node* trace = current;
      char* check = new char(StrLen(pattern));
      int size = 0;
      while (size < StrLen(pattern) &&
             trace != nullptr) {  // smaller than the size of pattern and not
                                  // null pointer) {add pattern to free store
                                  // char(char*)
        *(check + size) = trace->data;
        trace = trace->next;
        size++;
      }
      // check if pattern matches
      bool result = true;
      int i = 0;
      while (result && i < StrLen(pattern)) {
        if (*(pattern + i) != *(check + i)) {
          result = false;
          break;
        }
        i++;
      }
      if (result) {
        pos = current;
      }
      delete check;
    }
    current = current->next;
  }

  // check if the position is used
  if (pos == nullptr) {
    throw std::runtime_error("no matching pattern");
  }

  // step 2: remove and add splice
  // remove the strand starting from the starting position of pattern
  // add the to_splice_in from the starting position (make the actual
  // to_splice_in empty) and return the function update head and tail(if in
  // the first  update head, if ends in the last sequence, update tail
  // remove
  Node* to_delete = pos;
  int i = 0;
  while (i < StrLen(pattern)) {
    Node* tmp = to_delete->next;
    delete to_delete;
    to_delete = tmp;
  }
  pos->next = to_delete;

  // add and empty the DNA strand
  to_splice_in.tail_->next = pos->next;
  pos->next = to_splice_in.head_;
  while (to_splice_in.head_ != nullptr) {
    Node* next = to_splice_in.head_->next;
    delete to_splice_in.head_;
    to_splice_in.head_ = next;
  }
}

int DNAstrand::StrLen(const char* c_str) {
  int size = 0;
  while (*c_str != '\0') {
    size++;
    c_str++;
  }
  return size;
}
