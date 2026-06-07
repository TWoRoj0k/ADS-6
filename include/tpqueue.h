// Copyright 2025 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_

// Структура SYM для использования в main.cpp
struct SYM {
    char ch;
    int prior;
};

template<typename T>
class TPQueue {
 private:
  struct Node {
    T data;
    Node* next;
    explicit Node(const T& value) : data(value), next(nullptr) {}
  };

  Node* head_;
  Node* tail_;
  int size_;

 public:
  TPQueue() : head_(nullptr), tail_(nullptr), size_(0) {}

  ~TPQueue() {
    while (!isEmpty()) {
      pop();
    }
  }

  void push(const T& item) {
    Node* newNode = new Node(item);

    if (isEmpty()) {
      head_ = newNode;
      tail_ = newNode;
      size_++;
      return;
    }

    if (newNode->data.prior > head_->data.prior) {
      newNode->next = head_;
      head_ = newNode;
      size_++;
      return;
    }

    Node* current = head_;
    while (current->next != nullptr &&
           current->next->data.prior >= newNode->data.prior) {
      current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;

    if (newNode->next == nullptr) {
      tail_ = newNode;
    }

    size_++;
  }

  T pop() {
    if (isEmpty()) {
      return T();
    }

    Node* temp = head_;
    T result = head_->data;
    head_ = head_->next;

    if (head_ == nullptr) {
      tail_ = nullptr;
    }

    delete temp;
    size_--;
    return result;
  }

  T front() const {
    if (isEmpty()) {
      return T();
    }
    return head_->data;
  }

  bool isEmpty() const {
    return head_ == nullptr;
  }

  int size() const {
    return size_;
  }
};

#endif  // INCLUDE_TPQUEUE_H_
