// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_

template<typename T>
class TPQueue {
 private:
  struct Node {
    T data;
    Node* next;
    Node(const T& value) : data(value), next(nullptr) {}
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

  // Добавление элемента в очередь с учётом приоритета
  void push(const T& item) {
    Node* newNode = new Node(item);

    // Если очередь пуста
    if (isEmpty()) {
      head_ = newNode;
      tail_ = newNode;
      size_++;
      return;
    }

    // Если приоритет нового элемента выше приоритета головы
    if (newNode->data.prior > head_->data.prior) {
      newNode->next = head_;
      head_ = newNode;
      size_++;
      return;
    }

    // Поиск позиции для вставки
    Node* current = head_;
    while (current->next != nullptr &&
           current->next->data.prior >= newNode->data.prior) {
      current = current->next;
    }

    // Вставка в найденную позицию
    newNode->next = current->next;
    current->next = newNode;

    // Если вставили в конец, обновляем tail
    if (newNode->next == nullptr) {
      tail_ = newNode;
    }

    size_++;
  }

  // Извлечение элемента из начала очереди (самый высокий приоритет)
  T pop() {
    if (isEmpty()) {
      return T();
    }

    Node* temp = head_;
    T result = head_->data;
    head_ = head_->next;

    // Если очередь стала пустой, обновляем tail
    if (head_ == nullptr) {
      tail_ = nullptr;
    }

    delete temp;
    size_--;
    return result;
  }

  // Просмотр первого элемента без удаления
  T front() const {
    if (isEmpty()) {
      return T();
    }
    return head_->data;
  }

  // Проверка на пустоту
  bool isEmpty() const {
    return head_ == nullptr;
  }

  // Текущий размер очереди
  int size() const {
    return size_;
  }
};

#endif  // INCLUDE_TPQUEUE_H_
