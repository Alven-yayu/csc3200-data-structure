#include <algorithm>
#include <iostream>
#include <iomanip>
#include <set>
#include <random>

#include "student_avl_tree.h"
#include "student_avl_tree.h"

template<typename NodePtr>
bool is_bst(NodePtr n) {
    if(n == nullptr) return true;
    if(n->left() != nullptr && n->left()->parent() != n)
        return false;
    if(n->right() != nullptr && n->right()->parent() != n)
        return false;
    if(n->left() == n->right() && n->left() != nullptr)
        return false;
    if(n->left() != nullptr && !(n->left()->value() < n->value()))
        return false;
    if(n->right() != nullptr && !(n->value() < n->right()->value()))
        return false;
    return is_bst(n->left()) && is_bst(n->right());
}

template<typename NodePtr>
bool size_valid(NodePtr n) {
    if(n == nullptr) return true;
    return n->size() == 1 + (n->left() ? n->left()->size() : 0) + (n->right() ? n->right()->size() : 0)
        && size_valid(n->left()) && size_valid(n->right());
}

template<typename NodePtr>
std::ptrdiff_t height(NodePtr n) {
    if(n == nullptr) return -1;
    return n->height();
}

template<typename NodePtr>
bool height_valid(NodePtr n) {
    if(n == nullptr) return true;
    return n->height() == 1 + std::max(height(n->left()), height(n->right()))
        && std::abs(height(n->left()) - height(n->right())) < 2
        && height_valid(n->left()) && height_valid(n->right());
}

struct allocation_counter {
    allocation_counter(int val) : m_val(val) { allocations()++; }
    allocation_counter(allocation_counter const& other) : m_val(other.m_val) { allocations()++; }
    ~allocation_counter() { allocations()--; }
    static int& allocations() {
        static int allocation_singleton = 0;
        return allocation_singleton;
    }
    bool operator<(allocation_counter const& other) const {
        return m_val < other.m_val;
    }
    bool operator==(allocation_counter const& other) const {
        return m_val == other.m_val;
    }
    bool operator!=(allocation_counter const& other) const {
        return m_val != other.m_val;
    }
    int value() const { return m_val; }
private:
    int m_val;
};


int main() {
    int before = allocation_counter::allocations();
    bool bst_validity = true; //#
    bool avl_validity = true; //#
    bool tree_root_consistency = true; //#
    bool memory_correctness = true;
    bool tree_set_size_consistency = true; //#
    bool insert_iterator_correctness = true; //#
    bool erase_iterator_correctness = true; //#
    bool forward_iteration_correctness = true;
    bool backward_iteration_correctness = true;
    bool contains_correctness = true; //#
    bool find_correctness = true; //#
    {
        std::mt19937 rng{0};
        std::uniform_int_distribution<> dist(0, 100);
        using ac_tree = student_std::avl_tree<allocation_counter>;
        using acn = ac_tree::node_type;
        std::cout << "Testing default construction." << std::endl;
        ac_tree t;
        std::set<int> s;
        auto validities = [&]() {
            if(s.size() == 0) return;
            bst_validity = bst_validity && is_bst(t.root().operator->()) && size_valid(t.root().operator->());
            avl_validity = avl_validity && height_valid(t.root().operator->());
            tree_root_consistency = tree_root_consistency && (t.size() == t.root()->size() && t.height() == t.root()->height());
            tree_set_size_consistency = tree_set_size_consistency && (s.size() == t.size());
        };
        std::cout << "Testing random insertions." << std::endl;
        for(int i = 0; i < 100; ++i) {
            validities();
            int val = dist(rng);
            bool contains = s.find(val) != s.end();
            s.insert(val);
            if(!contains) {
                auto it = t.insert(allocation_counter(val));
                insert_iterator_correctness = insert_iterator_correctness &&
                    it->value().value() == val;
            }
        }
        std::cout << "Testing random erasures." << std::endl;
        for(int i = 0; i < 50; ++i) {
            validities();
            int val = dist(rng);
            auto acval = allocation_counter(val);
            bool contained = s.find(val) != s.end();
            contains_correctness = contains_correctness && contained == t.contains(acval);
            if(contained) {
                auto it = t.find(acval);
                find_correctness = find_correctness && it->value().value() == val;
                auto succ_s = s.erase(s.find(val));
                auto succ_t = t.erase(allocation_counter(val));
                if(succ_s != s.end()) {
                    erase_iterator_correctness = erase_iterator_correctness &&
                        *succ_s == succ_t->value().value();
                }
            }
        }
        std::cout << "Testing forward traversal." << std::endl;
        auto it_t1 = t.begin();
        auto it_t2 = t.begin();
        auto it_s1 = s.begin();
        auto it_s2 = s.begin();
        while(std::next(it_s1) != s.end()) {
            forward_iteration_correctness = forward_iteration_correctness &&
                (++it_t1)->value().value() == *(++it_s1) &&
                (it_t2++)->value().value() == *(it_s2++);
        }
        auto it_t3 = t.begin();
        auto it_s3 = s.begin();
        auto it_t4 = t.begin();
        auto it_s4 = s.begin();
        while(it_s3 != std::prev(s.end())) {
            ++it_s3; ++it_t3; ++it_s4; ++it_t4;
        }
        std::cout << "Testing backward traversal." << std::endl;
        while(it_s3 != s.begin()) {
            int val_t3 = (--it_t3)->value().value();
            int val_t4 = (it_t4--)->value().value();
            int val_s3 = *(--it_s3);
            int val_s4 = *(it_s4--);
            backward_iteration_correctness = backward_iteration_correctness &&
                 val_t3 == val_s3 && val_t4 == val_s4;
        }
    }
    double score = 1.0; // For compiling;
    auto widen = [](const char* str) {
        std::string s(str);
        s += ":";
        while(s.size() < 74) s+= " ";
        return s;
    };
    auto check = [&](bool criterion, const char* label, double criterion_score) {
        if(criterion) score += criterion_score;
            std::cout << widen(label)
                      << (criterion ? criterion_score : 0.0)
                      << " / " << criterion_score << "\n";
        };
    int after = allocation_counter::allocations();
    memory_correctness = before == after;
    if(before > after) {
        std::cerr << "More node values deleted than created --> double deletion error.\n";
    }
    else if(before < after) {
        std::cerr << "Fewer node values deleted than created --> memory leak.\n";
    }
    std::cout << std::setprecision(1) << std::fixed;
    check(bst_validity, "Valid BST through all operations", 0.5);
    check(avl_validity, "AVL Balance through all operations", 0.5);
    check(tree_root_consistency, "Tree and root have same height/size through all operations", 0.5);
    check(tree_set_size_consistency, "avl_tree has correct size after all insertions/erasures", 0.5);
    check(insert_iterator_correctness, "insert(Key const&) returns correct iterator for new values", 0.5);
    check(erase_iterator_correctness, "erase(Key const&) returns correct iterator when erasing existing values", 0.5);
    check(forward_iteration_correctness, "iterator increments return values in sorted order", 0.5);
    check(backward_iteration_correctness, "iterator decrements return values in reverse order", 0.5);
    check(contains_correctness, "contains(Key const&) produces expected values", 0.5);
    check(find_correctness, "find(Key const&) produces expected values", 0.5);
    check(memory_correctness, "No memory leaks/double deletions", 1.0);
    std::cout << widen("Total score") << score << " / 7.0\n";
    return 0;
}