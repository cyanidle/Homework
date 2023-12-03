#pragma once

#include <iterator>
#include <type_traits>
#include <utility>

template<typename T>
struct fwd_list;

namespace fwd_impl
{

template<typename T>
struct node
{
    T value;
    node* next = nullptr;
};

template<typename T>
struct iter
{
    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using Node = std::conditional_t<std::is_const<T>::value, const node<T>, node<T>>;
    operator iter<const T>() const {
        return {current};
    }
    const T& operator*() const {
        return current->value;
    }
    T& operator*() {
        return current->value;
    }
    const T* operator->() const {
        return &current->value;
    }
    T* operator->() {
        return &current->value;
    }
    iter operator++() {
        auto temp = *this;
        ++*this;
        return temp;
    }
    iter operator+(size_t steps) {
        auto temp = *this;
        return temp+=steps;
    }
    template<typename U>
    void swap(iter<U>& other) {
        std::swap(current->value, other.current->value);
    }
    template<typename U>
    std::ptrdiff_t operator-(const iter<U>& other) {
        auto o = other.current;
        auto c = current;
        std::ptrdiff_t res = 0;
        return res;
    }
    iter& operator+=(size_t steps) {
        while(--steps) {
            ++*this;
        }
        return *this;
    }
    iter& operator++(int) {
        current = current->next;
        return *this;
    }
    template<typename U>
    bool operator==(const iter<U>& other) const noexcept {
        return current == other.current;
    }
    template<typename U>
    bool operator!=(const iter<U>& other) const noexcept {
        return current != other.current;
    }
    using non_const = std::remove_const_t<T>;
    iter(node<non_const>* head) : current(head) {}
    iter(const iter&) = default;
    iter(iter&&) = default;
    iter& operator=(const iter&) = default;
    iter& operator=(iter&&) = default;
private:
    mutable node<non_const>* current;
    friend iter<const T>;
    friend iter<non_const>;
    friend struct fwd_list<T>;
    friend struct fwd_list<const T>;
    friend struct fwd_list<non_const>;
};

}

template<typename T>
struct fwd_list
{
    using Node = fwd_impl::node<T>;
    using value_type = T;
    using iterator = fwd_impl::iter<T>;
    using const_iterator = fwd_impl::iter<const T>;
    iterator begin() {
        return {head};
    }
    const_iterator begin() const {
        return {head};
    }
    const_iterator cbegin() const {
        return {head};
    }
    iterator end() {
        return {nullptr};
    }
    const_iterator end() const {
        return cend();
    }
    const_iterator cend() const {
        return {nullptr};
    }
    iterator erase(size_t index) {
        return erase(begin()+=index);
    }
    iterator erase(const_iterator iter) {
        return erase(iter, iter+1);
    }
    size_t size() const {
        size_t res = 0;
        auto last = &head;
        while(*last) {
            last = &(*last)->next;
            res++;
        }
        return res;
    }
    template<typename Comp = std::less<T>>
    void bubble_sort(Comp comp = {}) {
        auto size = this->size();
        for (auto i = 0u; i < size; ++i) {
            for (auto j = 0u; j < size - i - 1; ++j) {
                auto& l = operator[](j);
                auto& r = operator[](j + 1);
                if (!comp(l, r)){
                    std::swap(l, r);
                }
            }
        }
    }
    iterator erase(const_iterator start, const_iterator end) {
        iterator preStart = begin();
        if (preStart == start) {
            head = end.current;
        } else {
            while (preStart.current->next != start.current) {
                ++preStart;
            }
            preStart.current->next = end.current;
        }
        for(;start != end; ++start) {
            delete start.current;
        }
        return iterator{end.current};
    }
    iterator insert(const_iterator pos, const T& value) {
        return insert(pos, &value, &value + 1);
    }
    template<typename Iter>
    iterator insert(const_iterator pos, Iter start, Iter end) {
        for(;start != end; ++start) {
            auto wasNext = pos.current->next;
            pos.current->next = new Node{*start};
            pos.current->next->next = wasNext;
            ++pos;
        }
        return {pos.current};
    }
    fwd_list& append(const T& value) {
        *last() = new Node{value};
        return *this;
    }
    fwd_list() = default;
    fwd_list(fwd_list&& o) :
        head(std::exchange(o.head, nullptr))
    {}
    fwd_list& operator=(fwd_list&& o) {
        std::swap(head, o.head);
        return *this;
    }
    fwd_list(const fwd_list& o) {
        insert(begin(), o.begin(), o.end());
    }
    fwd_list& operator=(const fwd_list& o) {
        if (this == &o) return *this;
        clear();
        insert(begin(), o.begin(), o.end());
        return *this;
    }
    T& operator[](size_t idx) {
        return (begin() + idx).current->value;
    }
    const T& operator[](size_t idx) const {
        return (begin() + idx).current->value;
    }
    ~fwd_list() {
        clear();
    }
    void clear() {
        for(auto it = begin(); it != end(); ++it) {
            delete it.current;
        }
        head = nullptr;
    }
private:
    Node** last() const {
        auto last = &head;
        while(*last) {
            last = &(*last)->next;
        }
        return last;
    }

    mutable Node* head = nullptr;
};
