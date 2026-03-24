#ifndef STUDENT_INORDER_ITERATOR_H
#define STUDENT_INORDER_ITERATOR_H

#include <cstddef>
#include <iterator>

namespace student_std {

template <typename BinaryTree>
class inorder_iterator {
public:
    using value_type = typename BinaryTree::value_type;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::forward_iterator_tag;
    using reference = value_type const&;
    using pointer = value_type const*;

private:
    const BinaryTree* now = nullptr;

    const BinaryTree* next_node(const BinaryTree* n) const {
        if (!n) return nullptr;
        if (n->right()) {
            const BinaryTree* x = n->right();
            while (x->left()) x = x->left();
            return x;
        }
        const BinaryTree* p = n->parent();
        const BinaryTree* c = n;
        while (p && p->right() == c) {
            c = p;
            p = p->parent();
        }
        return p;
    }

    const BinaryTree* leftmost(const BinaryTree* n) const {
        if (!n) return nullptr;
        const BinaryTree* cur = n;
        while (cur->left()) cur = cur->left();
        return cur;
    }

public:
    inorder_iterator() {}

    explicit inorder_iterator(const BinaryTree* r) {
        if (r) now = leftmost(r);
    }

    reference operator*() const {
        return now->value();
    }

    pointer operator->() const {
        return &now->value();
    }

    inorder_iterator& operator++() {
        if (now) now = next_node(now);
        return *this;
    }

    inorder_iterator operator++(int) {
        inorder_iterator t = *this;
        ++(*this);
        return t;
    }

    bool operator==(const inorder_iterator& o) const {
        return now == o.now;
    }

    bool operator!=(const inorder_iterator& o) const {
        return now != o.now;
    }
};

} 

#endif