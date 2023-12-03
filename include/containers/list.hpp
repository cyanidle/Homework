#pragma once
#include <cassert>
#include <iterator>

template<typename T>
struct linked_list
{
    struct node
    {
        T* value = {};
        node* next = {};
        node* prev = {};
        ~node() {
            if (value) delete value;
        }
    };

    struct iter {
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = ptrdiff_t;
        using pointer = T*;
        using reference = T&;
        node* current;
        iter& operator++() {
            current = current->next;
            return *this;
        }
        iter& operator--() {
            current = current->prev;
            return *this;
        }
        difference_type operator-(const iter& o) const {
            difference_type res = 0;
            node* node = o.current;
            while (node != current) {
                node = node->next;
                res++;
            }
            return res;
        }
        iter& operator+=(difference_type count) {
            while(count--) {
                ++*this;
            }
            return *this;
        }
        iter operator+(difference_type count) const {
            iter temp = *this;
            return temp += count;
        }
        iter operator-(difference_type count) const {
            iter temp = *this;
            while(count--) {
                --temp;
            }
            return temp;
        }
        bool operator==(const iter& o) const noexcept {
            return current == o.current;
        }
        bool operator!=(const iter& o) const noexcept {
            return current != o.current;
        }
        T& operator*() {
            assert(current->value);
            return *current->value;
        }
    };

    linked_list(std::initializer_list<T> init = {}) {
        head = tail = new node{};
        head->next = head->prev = tail;
        tail->next = tail->prev = head;
        for (auto& v: init) {
            append(std::move(v));
        }
    }
    linked_list& append(T value) {
        insert(end(), std::move(value));
        return *this;
    }
    iter insert(iter pos, T val) {
        node* target = pos.current;
        node* prev = pos.current->prev;
        node* n = new node{new T{std::move(val)}};
        if (prev == tail) {
            head = n;
        }
        target->prev = n;
        n->next = target;
        prev->next = n;
        n->prev = prev;
        return {n};
    }
    iter erase(iter it) {
        assert(it != end());
        node* trg = it.current;
        auto inplace = trg->next;
        trg->prev->next = inplace;
        inplace->prev = trg->prev;
        delete trg;
        return {inplace};
    }
    iter begin() {
        return iter{head};
    }
    iter end() {
        return iter{tail};
    }
    T& operator[](size_t ind) {
        return *(begin() + ind);
    }
    template<typename Comp = std::less<T>>
    void bubble_sort(Comp cmp = {}) {
        auto size = end() - begin();
        for (auto i = 0u; i < size; ++i) {
            for (auto j = 0u; j < size - i - 1; ++j) {
                auto& l = operator[](j);
                auto& r = operator[](j + 1);
                if (!cmp(l, r)){
                    std::swap(l, r);
                }
            }
        }
    }
    ~linked_list() {
        auto next = head;
        while(next != tail) {
            auto tmp = next->next;
            delete next;
            next = tmp;
        }
    }
    node* head;
    node* tail;
};
