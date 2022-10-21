#include "s21_stack.h"

namespace s21 {

template <typename T>
typename stack<T>::const_reference stack<T>::top() {
    return BaseQueue<T>::back();
}

template <typename T>
void stack<T>::pop() {
    BaseQueue<T>::pop_back();
}

template <typename T>
template <typename... Args>
void stack<T>::emplace_front(Args &&...args) {
    std::initializer_list<value_type> items({args...});
    for (T t : items) {
        BaseQueue<T>::push(t);
    }
}
}  // namespace s21
