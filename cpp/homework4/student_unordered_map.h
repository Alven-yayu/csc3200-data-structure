#ifndef STUDENT_UNORDERED_MAP_H
#define STUDENT_UNORDERED_MAP_H

#include <vector>
#include <list>
#include <functional>

namespace student_std {

template <typename Key, typename T, typename Hash = std::hash<Key>>
class unordered_map {
public:
    using key_type = Key;
    using mapped_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using value_type = std::pair<Key, T>;
    using hasher = Hash;
    using reference = value_type&;
    using const_reference = const value_type&;

private:
    std::vector<std::list<value_type>> b;
    size_type s = 0;
    hasher h;

    size_type idx(const key_type& k) const {
        return h(k) % b.size();
    }

    void rh(size_type nb) {
        std::vector<std::list<value_type>> nbuckets(nb);
        for (auto& bucket : b) {
            for (auto& entry : bucket) {
                size_type i = h(entry.first) % nb;
                nbuckets[i].push_back(std::move(entry));
            }
        }
        b = std::move(nbuckets);
    }

public:
    unordered_map() : b(1) {}

    unordered_map(const unordered_map& o) : b(o.b), s(o.s), h(o.h) {}

    unordered_map& operator=(const unordered_map& o) {
        if (this != &o) {
            b = o.b;
            s = o.s;
            h = o.h;
        }
        return *this;
    }

    size_type size() const { return s; }

    bool empty() const { return s == 0; }

    size_type bucket_count() const { return b.size(); }

    bool contains(const key_type& k) const {
        size_type i = idx(k);
        for (const auto& entry : b[i]) {
            if (entry.first == k) return true;
        }
        return false;
    }

    size_type erase(const key_type& k) {
        size_type i = idx(k);
        auto& bucket = b[i];
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->first == k) {
                bucket.erase(it);
                --s;
                return 1;
            }
        }
        return 0;
    }

    void clear() {
        for (auto& bucket : b) bucket.clear();
        s = 0;
    }

    mapped_type& operator[](const key_type& k) {
        if (s >= 2 * b.size()) {
            rh(2 * b.size());
        }

        size_type i = idx(k);
        auto& bucket = b[i];
        for (auto& entry : bucket) {
            if (entry.first == k) return entry.second;
        }

        bucket.emplace_back(k, mapped_type{});
        ++s;
        return bucket.back().second;
    }
};

} 

#endif