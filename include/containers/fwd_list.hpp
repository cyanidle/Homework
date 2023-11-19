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
    using iterator_type = std::forward_iterator_tag;
    using value_type = T;
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
    bool operator==(const iter& other) const noexcept {
        return current == other.current;
    }
    bool operator!=(const iter& other) const noexcept {
        return current != other.current;
    }
    iter(Node* head) : current(head) {}
    iter(const iter&) = default;
    iter(iter&&) = default;
    iter& operator=(const iter&) = default;
    iter& operator=(iter&&) = default;
private:
    Node* current;
    friend fwd_list<T>;
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
        return {*last()};
    }
    const_iterator end() const {
        return cend();
    }
    const_iterator cend() const {
        return {*last()};
    }
    const_iterator erase(size_t index) {
        return erase(begin()+=index);
    }
    const_iterator erase(const_iterator iter) {
        return erase(iter, iter+1);
    }
    size_t size() const {
        return std::distance(begin(), end());
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
    Node** last() {
        auto last = &head;
        while(*last) {
            last = &(*last)->next;
        }
        return last;
    }
    Node** last() const {
        auto last = &head;
        while(*last) {
            last = &last->next;
        }
        return last;
    }

    Node* head = nullptr;
};
