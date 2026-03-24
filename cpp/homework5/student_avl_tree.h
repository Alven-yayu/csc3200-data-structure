#ifndef STUDENT_AVL_TREE_H
#define STUDENT_AVL_TREE_H

#include <algorithm>
#include <cstddef>
#include <functional>

namespace student_std {

template <typename Key, typename Comp = std::less<Key>>
class avl_tree {
public:
    class avl_node {
    public:
        using size_type = std::size_t;

        Key const& value() const { return m_key; }
        avl_node const* parent() const { return m_parent; }
        avl_node const* left() const { return m_left; }
        avl_node const* right() const { return m_right; }
        size_type size() const { return m_size; }
        int height() const { return m_height; }

    private:
        friend class avl_tree;
        Key m_key;
        avl_node* m_parent;
        avl_node* m_left;
        avl_node* m_right;
        size_type m_size;
        int m_height;

        explicit avl_node(Key const& key)
            : m_key(key), m_parent(nullptr), m_left(nullptr), m_right(nullptr), m_size(1), m_height(0) {}
    };

    class avl_iterator {
    public:
        using value_type = avl_node;
        using reference = value_type const&;
        using pointer = value_type const*;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::bidirectional_iterator_tag;

        avl_iterator(pointer node = nullptr) : m_node(node) {}

        avl_iterator& operator++() {
            m_node = successor(m_node);
            return *this;
        }
        avl_iterator operator++(int) { avl_iterator tmp = *this; ++(*this); return tmp; }

        avl_iterator& operator--() {
            m_node = predecessor(m_node);
            return *this;
        }
        avl_iterator operator--(int) { avl_iterator tmp = *this; --(*this); return tmp; }

        bool operator==(avl_iterator const& other) const { return m_node == other.m_node; }
        bool operator!=(avl_iterator const& other) const { return m_node != other.m_node; }

        reference operator*() const { return *m_node; }
        pointer operator->() const { return m_node; }

    private:
        friend class avl_tree;
        pointer m_node;

        static avl_node const* successor(avl_node const* node) {
            if (!node) return nullptr;
            if (node->m_right) {
                node = node->m_right;
                while (node->m_left) node = node->m_left;
                return node;
            }
            avl_node const* p = node->m_parent;
            while (p && node == p->m_right) {
                node = p;
                p = p->m_parent;
            }
            return p;
        }

        static avl_node const* predecessor(avl_node const* node) {
            if (!node) return nullptr;
            if (node->m_left) {
                node = node->m_left;
                while (node->m_right) node = node->m_right;
                return node;
            }
            avl_node const* p = node->m_parent;
            while (p && node == p->m_left) {
                node = p;
                p = p->m_parent;
            }
            return p;
        }
    };

    using key_type = Key;
    using node_type = avl_node;
    using size_type = std::size_t;
    using comparison = Comp;
    using const_iterator = avl_iterator;
    using iterator = avl_iterator;

    avl_tree() : m_root(nullptr), m_comp(Comp()) {}
    ~avl_tree() { destroy_subtree(m_root); }

    iterator insert(Key const& key) {
        avl_node* inserted = insert_recursive(m_root, nullptr, key);
        return iterator(inserted);
    }

    iterator erase(Key const& key) {
        avl_node const* to_erase = find_node(m_root, key);
        if (!to_erase) return end();

        bool has_successor = false;
        Key succ_key = key;
        avl_node const* cur = m_root;
        while (cur) {
            if (m_comp(key, cur->m_key)) {
                has_successor = true;
                succ_key = cur->m_key;
                cur = cur->m_left;
            } else {
                cur = cur->m_right;
            }
        }

        m_root = erase_recursive(m_root, key);

        if (has_successor) {
            avl_node const* succ_node = find_node(m_root, succ_key);
            return iterator(succ_node);
        }
        return end();
    }

    iterator find(Key const& key) const {
        avl_node const* n = find_node(m_root, key);
        return n ? iterator(n) : end();
    }

    bool contains(Key const& key) const { return find_node(m_root, key) != nullptr; }

    size_type size() const { return m_root ? m_root->m_size : 0; }

    int height() const { return m_root ? m_root->m_height : -1; }

    iterator begin() const { return iterator(find_min(m_root)); }
    iterator end() const { return iterator(nullptr); }
    iterator root() const { return m_root ? iterator(m_root) : end(); }

private:
    avl_node* m_root;
    Comp m_comp;

    void destroy_subtree(avl_node* n) {
        if (!n) return;
        destroy_subtree(n->m_left);
        destroy_subtree(n->m_right);
        delete n;
    }

    void update_size_and_height(avl_node* n) {
        if (!n) return;
        std::size_t ls = n->m_left ? n->m_left->m_size : 0;
        std::size_t rs = n->m_right ? n->m_right->m_size : 0;
        n->m_size = 1 + ls + rs;
        int lh = n->m_left ? n->m_left->m_height : -1;
        int rh = n->m_right ? n->m_right->m_height : -1;
        n->m_height = 1 + (lh > rh ? lh : rh);
    }

    int get_balance(avl_node* n) const {
        if (!n) return 0;
        int lh = n->m_left ? n->m_left->m_height : -1;
        int rh = n->m_right ? n->m_right->m_height : -1;
        return lh - rh;
    }

    avl_node* rotate_right(avl_node* x) {
        avl_node* y = x->m_left;
        avl_node* T2 = y->m_right;

        y->m_right = x;
        y->m_parent = x->m_parent;
        x->m_parent = y;
        x->m_left = T2;
        if (T2) T2->m_parent = x;

        update_size_and_height(x);
        update_size_and_height(y);
        return y;
    }

    avl_node* rotate_left(avl_node* y) {
        avl_node* x = y->m_right;
        avl_node* T2 = x->m_left;

        x->m_left = y;
        x->m_parent = y->m_parent;
        y->m_parent = x;
        y->m_right = T2;
        if (T2) T2->m_parent = y;

        update_size_and_height(y);
        update_size_and_height(x);
        return x;
    }

    avl_node* rebalance(avl_node* n) {
        update_size_and_height(n);
        int bal = get_balance(n);
        if (bal > 1 && get_balance(n->m_left) >= 0) {
            return rotate_right(n);
        }
        if (bal > 1 && get_balance(n->m_left) < 0) {
            n->m_left = rotate_left(n->m_left);
            return rotate_right(n);
        }
        if (bal < -1 && get_balance(n->m_right) <= 0) {
            return rotate_left(n);
        }
        if (bal < -1 && get_balance(n->m_right) > 0) {
            n->m_right = rotate_right(n->m_right);
            return rotate_left(n);
        }
        return n;
    }

    avl_node* insert_recursive(avl_node*& node, avl_node* parent, Key const& key) {
        if (!node) {
            node = new avl_node(key);
            node->m_parent = parent;
            return node;
        }
        if (m_comp(key, node->m_key)) {
            avl_node* ret = insert_recursive(node->m_left, node, key);
            node = rebalance(node);
            return ret;
        } else if (m_comp(node->m_key, key)) {
            avl_node* ret = insert_recursive(node->m_right, node, key);
            node = rebalance(node);
            return ret;
        }
        return node;
    }

    avl_node* find_min_nc(avl_node* node) const {
        if (!node) return nullptr;
        while (node->m_left) node = node->m_left;
        return node;
    }

    avl_node const* find_min(avl_node const* node) const {
        if (!node) return nullptr;
        while (node->m_left) node = node->m_left;
        return node;
    }

    avl_node const* find_node(avl_node const* node, Key const& key) const {
        while (node) {
            if (m_comp(key, node->m_key)) node = node->m_left;
            else if (m_comp(node->m_key, key)) node = node->m_right;
            else return node;
        }
        return nullptr;
    }

    avl_node* erase_recursive(avl_node*& node, Key const& key) {
        if (!node) return nullptr;
        if (m_comp(key, node->m_key)) {
            node->m_left = erase_recursive(node->m_left, key);
        } else if (m_comp(node->m_key, key)) {
            node->m_right = erase_recursive(node->m_right, key);
        } else {
            if (!node->m_left || !node->m_right) {
                avl_node* tmp = node->m_left ? node->m_left : node->m_right;
                if (tmp) tmp->m_parent = node->m_parent;
                delete node;
                node = tmp;
            } else {
                avl_node* tmp = find_min_nc(node->m_right);
                node->m_key = tmp->m_key;
                node->m_right = erase_recursive(node->m_right, tmp->m_key);
            }
        }
        if (!node) return nullptr;
        return rebalance(node);
    }
};

} 

#endif 