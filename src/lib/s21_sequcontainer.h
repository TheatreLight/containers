#ifndef SRC_LIB_S21_SEQUCONTAINER_H_
#define SRC_LIB_S21_SEQUCONTAINER_H_

#include "container.h"

namespace s21 {
template <typename T>
class SequContainer : public Container<T> {
 public:
    using value_type = T;
    using reference = T &;
    using const_reference = const T &;
    using iterator = T *;
    using const_iterator = const T *;
    using size_type = size_t;

 private:
    size_type cont_size_;
    T *arr_;

 protected:
    void move_content(SequContainer *s) {
        const_iterator pointer = s->get_pointer();
        assign_array(pointer);
        s->assign_array(nullptr);
        set_size(s->size());
        s->set_size(0);
    }

    void set_size(const size_type &size) { cont_size_ = size; }

    void assign_array(const_iterator newArr) {
        if (newArr) {
            if (arr_ != nullptr) delete[] arr_;
            arr_ = iterator(newArr);
        } else {
            arr_ = nullptr;
        }
    }

    void set_pointer(T *pointer) { arr_ = pointer; }

    reference get_value(size_type pos) {
            return arr_[pos];
    }

    iterator get_pointer() { return arr_; }

 public:
    SequContainer() {
        cont_size_ = 0;
        arr_ = nullptr;
    }

    explicit SequContainer(size_type n) {
        cont_size_ = n;
        if (n > 0) {
            arr_ = new T[n + 1]();
        } else {
            arr_ = nullptr;
        }
    }

    explicit SequContainer(std::initializer_list<value_type> const &items) {
        cont_size_ = items.size();
        arr_ = new T[cont_size_ + 1]();
        std::copy(items.begin(), items.end(), arr_);
    }

    SequContainer(const SequContainer &s) {
        cont_size_ = s.cont_size_;
        arr_ = new T[cont_size_ + 1];
        std::copy(s.arr_, s.arr_ + cont_size_, arr_);
    }

    ~SequContainer() { delete[] arr_; }

    virtual const_reference front() const {  // Element access
        return arr_[0];
    }

    virtual const_reference back() const { return arr_[cont_size_ - 1]; }

    virtual iterator begin() {  // Iterators
        return &arr_[0];
    }

    virtual iterator end() { return arr_ + cont_size_; }

    virtual reference at(size_type pos) { return get_value(pos); }

    virtual reference operator[](size_type pos) { return get_value(pos); }

    virtual iterator data() { return iterator(get_pointer()); }

  bool empty() {
    if (cont_size_ == 0)
      return true;
    else
      return false;
  }

    size_type size() const { return cont_size_; }

    virtual size_type max_size() {
        return std::allocator<value_type>().max_size();
    }

    virtual void clear() {
        if (arr_) {
            delete[] arr_;
            arr_ = nullptr;
            cont_size_ = 0;
        }
    }

    void erase(iterator pos) {
        for (; pos != end() - 1; pos++) {
            *pos = *(pos + 1);
        }
        arr_[cont_size_ - 1] = 0;
        --cont_size_;
    }

    virtual void pop_back() {
        arr_[cont_size_] = value_type();
        --cont_size_;
    }

    virtual SequContainer<T> operator=(SequContainer<T> &&s) {
        move_content(&s);
        cont_size_ = s.size();
        arr_ = s.get_pointer();
        return *this;
    }
};
}  // namespace s21

#endif  // SRC_LIB_S21_SEQUCONTAINER_H_
