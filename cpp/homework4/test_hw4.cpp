#include <iostream>

#define TEST_P1 __has_include("student_unordered_map.h")
#define TEST_P2 __has_include("student_inorder_iterator.h")

#if !(__has_include("binary_tree.h")) && TEST_P2

int main() {
    std::cout << "binary_tree.h not found. Download all files from BB for proper testing.\n";
    return 0;
}

#else
#if TEST_P1
#include "student_unordered_map.h"
#include "student_unordered_map.h"
#endif
#if TEST_P2
#include "student_inorder_iterator.h"
#include "student_inorder_iterator.h"
#include "binary_tree.h"
#endif

#include <cstddef>
#include <iomanip>
#include <iterator>
#include <random>
#include <type_traits>

template <typename, typename = std::void_t<>>
struct size_type_is_size_t : std::false_type {};

template <typename T>
struct size_type_is_size_t<T, std::void_t<typename T::size_type>>
  : std::is_same<typename T::size_type, std::size_t> {};

template <typename T>
constexpr bool size_type_is_size_t_v = size_type_is_size_t<T>::value;

template <typename, typename = std::void_t<>>
struct difference_type_is_ptrdiff : std::false_type {};

template <typename T>
struct difference_type_is_ptrdiff<T, std::void_t<typename T::difference_type>>
  : std::is_same<typename T::difference_type, std::ptrdiff_t> {};

template <typename T>
constexpr bool difference_type_is_ptrdiff_v = difference_type_is_ptrdiff<T>::value;

template<typename T, typename U, class = void>
struct key_is_u : std::false_type {};

template<typename T, typename U>
struct key_is_u<T, U, std::void_t<typename T::key_type>>
  : std::is_same<typename T::key_type, U> {};

template<typename T, typename U>
inline constexpr bool key_is_u_v = key_is_u<T, U>::value;

template<typename T, typename U, class = void>
struct value_is_u : std::false_type {};

template<typename T, typename U>
struct value_is_u<T, U, std::void_t<typename T::value_type>>
  : std::is_same<typename T::value_type, U> {};

template<typename T, typename U>
inline constexpr bool value_is_u_v = value_is_u<T, U>::value;

template<typename T, typename U, class = void>
struct hash_is_u : std::false_type {};

template<typename T, typename U>
struct hash_is_u<T, U, std::void_t<typename T::hasher>>
  : std::is_same<typename T::hasher, U> {};

template<typename T, typename U>
inline constexpr bool hash_is_u_v = hash_is_u<T, U>::value;

template<typename T, typename U, class = void>
struct mapped_is_u : std::false_type {};

template<typename T, typename U>
struct mapped_is_u<T, U, std::void_t<typename T::mapped_type>>
  : std::is_same<typename T::mapped_type, U> {};

template<typename T, typename U>
inline constexpr bool mapped_is_u_v = mapped_is_u<T, U>::value;

template<class T, class = void>
struct size_returns_size_t : std::false_type {};

template<class T>
struct size_returns_size_t<T,
    std::void_t<decltype(std::declval<const T&>().size())>>
  : std::is_same<decltype(std::declval<const T&>().size()), std::size_t> {};

template<class T>
inline constexpr bool size_returns_size_t_v = size_returns_size_t<T>::value;

template<class T, class = void>
struct bucket_count_returns_size_t : std::false_type {};

template<class T>
struct bucket_count_returns_size_t<T,
    std::void_t<decltype(std::declval<const T&>().bucket_count())>>
  : std::is_same<decltype(std::declval<const T&>().bucket_count()), std::size_t> {};

template<class T>
inline constexpr bool bucket_count_returns_size_t_v = bucket_count_returns_size_t<T>::value;

template<class T, class = void>
struct empty_returns_bool : std::false_type {};

template<class T>
struct empty_returns_bool<T,
    std::void_t<decltype(std::declval<const T&>().empty())>>
  : std::is_same<decltype(std::declval<const T&>().empty()), bool> {};

template<class T>
inline constexpr bool empty_returns_bool_v = empty_returns_bool<T>::value;

template<class T, class = void>
struct erase_returns_size_t : std::false_type {};

template<class T>
struct erase_returns_size_t<T,
    std::void_t<decltype(std::declval<T&>().erase(std::declval<typename T::key_type const&>()))>>
  : std::is_same<decltype(std::declval<T&>().erase(std::declval<typename T::key_type const&>())), std::size_t> {};

template<class T>
inline constexpr bool erase_returns_size_t_v = erase_returns_size_t<T>::value;

template<class T, class = void>
struct contains_returns_bool : std::false_type {};

template<class T>
struct contains_returns_bool<T,
    std::void_t<decltype(std::declval<T&>().contains(std::declval<typename T::key_type const&>()))>>
  : std::is_same<decltype(std::declval<const T&>().contains(std::declval<typename T::key_type const&>())), bool> {};

template<class T>
inline constexpr bool contains_returns_bool_v = contains_returns_bool<T>::value;

template<class T, class = void>
struct clear_returns_void : std::false_type {};

template<class T>
struct clear_returns_void<T,
    std::void_t<decltype(std::declval<T&>().clear())>>
  : std::is_same<decltype(std::declval<T&>().clear()), void> {};

template<class T>
inline constexpr bool clear_returns_void_v = clear_returns_void<T>::value;

template<class T, class = void>
struct subscript_returns_tref : std::false_type {};

template<class T>
struct subscript_returns_tref<T,
    std::void_t<decltype(std::declval<T&>()[std::declval<typename T::key_type const&>()])>>
  : std::is_same<decltype(std::declval<T&>()[std::declval<typename T::key_type const&>()]), typename T::mapped_type&> {};

template<class T>
inline constexpr bool subscript_returns_tref_v = subscript_returns_tref<T>::value;

namespace {

struct test_key {
    int v = 0;
};
bool operator==(test_key const&, test_key const&) { return true; }
struct dummy_hash {
    std::size_t operator()(test_key const&) const { return 0; }
};

struct test_mapped {};

static int comparison_count = 0;

struct comparison_counting_key {
    int v = 0;
    bool operator==(comparison_counting_key const& o) const { ++comparison_count; return v == o.v; }
    bool operator!=(comparison_counting_key const& o) const { ++comparison_count; return v != o.v; }
};

class cck_hash {
public:
    std::size_t operator()(comparison_counting_key const& k) const {
        return m_hash(k.v);
    }
private:
    std::hash<int> m_hash = std::hash<int>{};
};

}

const char* check(bool b) {
    return b ? "SUCCESS" : "FAIL";
}

template <template<typename, typename, typename> typename T>
double map_test() {
    double score = 0.0;
    using int_double_map = T<int, double, std::hash<int>>;
    
    int_double_map map_default;
    int_double_map map_default_copy(map_default);
    int_double_map map_default_assigned = map_default;

    bool defaults_empty = true;

    std::cout << "Unordered map functionality test:\n";
    if(map_default.size() != 0 || !map_default.empty()) {
        std::cerr << "default constructed unordered_map is not empty.\n";
        defaults_empty = false;
    }
    if(map_default_copy.size() != 0 || !map_default_copy.empty()) {
        std::cerr << "copy of default constructed unordered_map is not empty.\n";
        defaults_empty = false;
    }
    if(map_default_assigned.size() != 0 || !map_default_assigned.empty()) {
        std::cerr << "copy assigned unordered_map of default constructed unordered_map is not empty.\n";
        defaults_empty = false;
    }
    if(defaults_empty)
        score += 0.5;
    std::cout << "default constructor, copy of empty, assigned from empty:\t" << score << " / 0.5\n";

    int_double_map five_entries;
    five_entries[0] = 1.0;
    five_entries[1] = 2.0;
    five_entries[2] = 3.0;
    five_entries[3] = 4.0;
    five_entries[4] = 5.0;
    int_double_map five_entries_copy(five_entries);
    int_double_map five_entries_assigned = five_entries;

    bool five_size_cap = true;
    if(five_entries.size() != 5 || five_entries.bucket_count() <= 2)
    {
        std::cerr << "After 5 insertions via subscript, size() != 5 or bucket_count() <= 2 (load factor > 2).\n";
        five_size_cap = false;
    }
    if(five_entries_assigned.size() != 5 || five_entries_assigned.bucket_count() <= 2)
    {
        std::cerr << "After 5 insertions via subscript and assigning, size() != 5 or bucket_count() <= 2 (load factor > 2).\n";
        five_size_cap = false;
    }
    if(five_entries_copy.size() != 5 || five_entries_copy.bucket_count() <= 2)
    {
        std::cerr << "After 5 insertions via subscript and copying, size() != 5 or bucket_count() <= 2 (load factor > 2).\n";
        five_size_cap = false;
    }
    if(five_entries.bucket_count() > 50) {
        std::cerr << "bucket_count after five insertions via subscript > 50 (unreasonable, do not try to get around dynamic realloc).\n";
        five_size_cap = false;
    }
    double five_entries_score = five_size_cap ? 0.5 : 0.;
    score += five_entries_score;
    std::cout << "Size, load factor after five insertions, copying, assigning:\t" << five_entries_score << " / 0.5\n";

    bool true_copy_address = true;
    if(&five_entries[0] == &five_entries_assigned[0] || &five_entries[0] == &five_entries_copy[0]) {
        std::cerr << "Addresses of entry and copy or entry and copy assigned equal, no true copy.\n";
        true_copy_address = false;
    }
    double true_copy_score = true_copy_address ? 0.5 : 0;
    score += true_copy_score;
    std::cout << "True copy:\t\t\t\t" << true_copy_score << " / 0.5\n";

    bool erase_milestones = true;
    five_entries.erase(0);
    five_entries.erase(2);
    five_entries.erase(4);
    if(five_entries.size() != 2 || five_entries.empty()) {
        std::cerr << "size() != 2 or empty() == true after 5 insertions and 3 erasures.\n";
        erase_milestones = false;
    }
    five_entries_copy.clear();
    if(five_entries_copy.size() != 0 || !five_entries_copy.empty())
    {
        std::cerr << "size() != 0 or empty() != true after clear().\n";
        erase_milestones = false;
    }
    double erase_score = erase_milestones ? 0.5 : 0.0;
    score += erase_score;
    std::cout << "Expected sizes after erase()/clear:\t\t\t\t" << erase_score << " / 0.5\n";

    bool expected_values = true;
    if(five_entries[1] != 2.0 || five_entries[3] != 4.0) {
        std::cerr << "map[1] or map[3] returned the wrong value.\n";
        expected_values = false;
    }
    if(five_entries[2] == 3.0 || five_entries[4] == 5.0 || five_entries[0] == 1.0) {
        std::cerr << "map[0], map[2], or map[4] recovered deleted values.\n";
        expected_values = false;
    }
    T<comparison_counting_key, int, cck_hash> counting_map;
    std::vector<int> keys;
    std::default_random_engine g{1};
    for(int i = 0; i < 100; ++i) {
        int v = g() % 2147483647;
        keys.push_back(v);
        counting_map[comparison_counting_key{v}] = v;
    }
    int old_count = comparison_count;
    for(auto& k : keys) {
        if(counting_map[comparison_counting_key{k}] != k) {
            std::cerr << "Wrong value returned for key.\n";
            expected_values = false;
        }
    }
    if (comparison_count - old_count > 3000) {
        std::cerr << "Unreasonable comparison number for given load factor and 100 lookups.\n";
        expected_values = false;
    }
    double expected_values_score = expected_values ? 0.5 : 0.0;
    std::cout << "Expected values, expected number of comparisons:\t\t" << expected_values_score << " / 0.5\n\n";
    score += expected_values_score;

    return score;
}

template<typename T, class = void>
struct iterator_cat_is_forward : std::false_type {};

template<typename T>
struct iterator_cat_is_forward<T, std::void_t<typename T::iterator_category>>
  : std::is_same<typename T::iterator_category, std::forward_iterator_tag> {};

template<typename T>
inline constexpr bool iterator_cat_is_forward_v = iterator_cat_is_forward<T>::value;

template<typename T, class = void>
struct reference_is_valcref : std::false_type {};

template<typename T>
struct reference_is_valcref<T, std::void_t<typename T::reference, typename T::value_type>>
  : std::is_same<typename T::value_type const&, typename T::reference> {};

template<typename T>
inline constexpr bool reference_is_valcref_v = reference_is_valcref<T>::value;

template<typename T, class = void>
struct pointer_is_valcptr : std::false_type {};

template<typename T>
struct pointer_is_valcptr<T, std::void_t<typename T::pointer, typename T::value_type>>
  : std::is_same<typename T::value_type const*, typename T::pointer> {};

template<typename T>
inline constexpr bool pointer_is_valcptr_v = pointer_is_valcptr<T>::value;


template<typename T, class = void>
struct iterator_preincrement_returns_ref : std::false_type {};

template<typename T>
struct iterator_preincrement_returns_ref<T, std::void_t<decltype(++std::declval<T&>())>>
  : std::is_same<decltype(++std::declval<T&>()), T&> {};

template<typename T>
inline constexpr bool iterator_preincrement_returns_ref_v = iterator_preincrement_returns_ref<T>::value;

template<typename T, class = void>
struct iterator_postincrement_returns_it : std::false_type {};

template<typename T>
struct iterator_postincrement_returns_it<T, std::void_t<decltype(std::declval<T&>()++)>>
  : std::is_same<decltype(std::declval<T&>()++), T> {};

template<typename T>
inline constexpr bool iterator_postincrement_returns_it_v = iterator_postincrement_returns_it<T>::value;

template<typename T, class = void>
struct iterator_deref_returns_ref : std::false_type {};

template<typename T>
struct iterator_deref_returns_ref<T, std::void_t<typename T::reference, decltype(*std::declval<const T&>())>>
  : std::is_same<decltype(*std::declval<const T&>()), typename T::reference> {};

template<typename T>
inline constexpr bool iterator_deref_returns_ref_v = iterator_deref_returns_ref<T>::value;

template<typename T, class = void>
struct iterator_memptr_returns_ptr : std::false_type {};

template<typename T>
struct iterator_memptr_returns_ptr<T, std::void_t<typename T::pointer, decltype(std::declval<const T&>().operator->())>>
  : std::is_same<decltype(std::declval<const T&>().operator->()), typename T::pointer> {};

template<typename T>
inline constexpr bool iterator_memptr_returns_ptr_v = iterator_memptr_returns_ptr<T>::value;

template<typename T, class = void>
struct iterator_eq_returns_bool : std::false_type {};

template<typename T>
struct iterator_eq_returns_bool<T, std::void_t<decltype(std::declval<T>() == std::declval<T>())>>
  : std::is_same<decltype(std::declval<T>() == std::declval<T>()), bool> {};

template<typename T>
inline constexpr bool iterator_eq_returns_bool_v = iterator_eq_returns_bool<T>::value;

template<typename T, class = void>
struct iterator_ineq_returns_bool : std::false_type {};

template<typename T>
struct iterator_ineq_returns_bool<T, std::void_t<decltype(std::declval<T>() != std::declval<T>())>>
  : std::is_same<decltype(std::declval<T>() != std::declval<T>()), bool> {};

template<typename T>
inline constexpr bool iterator_ineq_returns_bool_v = iterator_ineq_returns_bool<T>::value;

template <typename IntIt>
double iterator_test() {
    std::cout << "Inorder iterator functionality test:\n";
    
    using int_bst = student_std::binary_tree<int>;
    using it_t = IntIt;

    it_t default_it;
    bool default_construct_correct = 
        (it_t(nullptr) == default_it && !(it_t(nullptr) != default_it));
    if(!default_construct_correct) {
        std::cout << "Default constructed inorder_iterator had unexpected value.\n";
    }
    double score = default_construct_correct ? 0.5 : 0.0;
    std::cout << "default construction:\t\t\t\t\t\t" << score << " / 0.5\n";

    int_bst tree(4);
    tree.insert(3);
    tree.insert(7);
    tree.insert(1);
    tree.insert(6);
    tree.insert(5);
    tree.insert(2);

    it_t begin = it_t(&tree);
    
    bool begin_correct = true;
    if(*begin != 1) {
        std::cerr << "*(inorder_iterator(BST)) returns unexpected values.\n";
        begin_correct = false;
    }
    double begin_correct_score = begin_correct ? 0.5 : 0.0;
    score += begin_correct_score;
    std::cout << "begin():\t\t\t\t\t\t\t" << begin_correct_score << " / 0.5\n";

    bool iteration_small_tree_value = true;
    int i = 1;
    for (auto it = begin; it != it_t(nullptr); ++it) {
        if (*it != i++) {
            std::cerr << "unexpected value (*it) pointed at by iterator in iteration over tree containing 1,...,7.\n";
            iteration_small_tree_value = false;
        }
    }
    if(i != 8){
        std::cerr << "Iteration terminated early or late.\n";
        iteration_small_tree_value = false;
    }
    double score_iteration_small_tree_value = iteration_small_tree_value ? 0.5 : 0.0;
    std::cout << "Iteration value:\t\t\t\t\t\t" << score_iteration_small_tree_value << " / 0.5\n";
    score += score_iteration_small_tree_value;

    bool iteration_small_tree_address = true;
    i = 1;
    for (auto it = begin; it != it_t(nullptr); ++it) {
        ++i;
        if (&(*it) != it.operator->()) {
            std::cerr << "unexpected address (it->) pointed at by iterator in iteration over tree containing 1,...,7.\n";
            iteration_small_tree_address = false;
        }
    }
    if(i != 8){
        std::cerr << "Iteration terminated early or late.\n";
        iteration_small_tree_address = false;
    }
    double score_iteration_small_tree_address = iteration_small_tree_address ? 0.5 : 0.0;
    std::cout << "Iteration address:\t\t\t\t\t\t" << score_iteration_small_tree_address << " / 0.5\n";
    score += score_iteration_small_tree_address;

    int_bst root_only(4);
    int_bst left_only(4);
    left_only.insert(3);
    int_bst right_only(4);
    right_only.insert(7);

    bool degen_correct = true;
    it_t root_only_it(&root_only);
    if(*root_only_it != 4) {
        std::cerr << "Incorrect value returned by iterator for single node tree.\n";
        degen_correct = false;
    }
    if(++root_only_it != it_t(nullptr)) {
        std::cerr << "Incorrect incrementation on single node tree.\n";
        degen_correct = false;
    }
    it_t left_only_it(&left_only);
    if(*left_only_it++ != 3 || *left_only_it != 4) {
        std::cerr << "Incorrect value returned by iterator for tree with only left children.\n";
        degen_correct = false;
    }
    if(++left_only_it != it_t(nullptr)) {
        std::cerr << "Incorrect incrementation on tree with only left children.\n";
        degen_correct = false;
    }
    it_t right_only_it(&right_only);
    if(*right_only_it++ != 4 || *right_only_it != 7) {
        std::cerr << "Incorrect value returned by iterator for tree with only right children.\n";
        degen_correct = false;
    }
    if(++right_only_it != it_t(nullptr)) {
        std::cerr << "Incorrect incrementation on tree with only right children.\n";
        degen_correct = false;
    }

    double score_degen = degen_correct ? 0.5 : 0.0;
    std::cout << "Iteration on degen trees:\t\t\t\t\t" << score_degen << " / 0.5\n";
    score += score_degen;

    return score;
}

int main() {
#if TEST_P1
    using test_map = student_std::unordered_map<test_key, test_mapped, dummy_hash>;
    double score = 0.0;

    constexpr bool interface_size_type = size_type_is_size_t_v<test_map>;
    constexpr bool interface_difference_type = difference_type_is_ptrdiff_v<test_map>;
    constexpr bool interface_key_type = key_is_u_v<test_map, test_key>;
    constexpr bool interface_mapped_type = mapped_is_u_v<test_map, test_mapped>;
    constexpr bool interface_value_type = value_is_u_v<test_map, std::pair<test_key, test_mapped>>;
    constexpr bool interface_hash_type = hash_is_u_v<test_map, dummy_hash>;
    constexpr bool interface_default_ctor = std::is_default_constructible_v<test_map>;
    constexpr bool interface_copy_ctor = std::is_copy_constructible_v<test_map>;
    constexpr bool interface_assignable = std::is_copy_assignable_v<test_map>;
    
    constexpr bool interface_size = size_returns_size_t_v<test_map>;
    constexpr bool interface_bucket_count = bucket_count_returns_size_t_v<test_map>;
    constexpr bool interface_empty = empty_returns_bool_v<test_map>;
    
    constexpr bool interface_part1 =
        interface_size_type && interface_difference_type && interface_value_type &&
        interface_key_type && interface_mapped_type && interface_hash_type &&
        interface_default_ctor && interface_copy_ctor && interface_assignable &&
        interface_size && interface_empty && interface_bucket_count;

    double score_interface_part1 = interface_part1 ? 0.5 : 0.0;
    score += score_interface_part1;
    std::cout << std::fixed << std::setprecision(1) << "Unordered map interface part 1:\n"
        << "::size_type is size_t: " << check(interface_size_type) << "\n"
        << "::difference_type is ptrdiff_t: " << check(interface_difference_type) << "\n"
        << "::key_type is Key: " << check(interface_key_type) << "\n"
        << "::mapped_type is T: " << check(interface_mapped_type) << "\n"
        << "::value_type is pair<Key, T>: " << check(interface_value_type) << "\n"
        << "::hasher is Hash: " << check(interface_hash_type) << "\n"
        << "default constructible: " << check(interface_default_ctor) << "\n"
        << "copy constructible: " << check(interface_copy_ctor) << "\n"
        << "assignable: " << check(interface_assignable) << "\n"
        << "size() returns size_t: " << check(interface_size) << "\n"
        << "bucket_count() returns size_t: " << check(interface_bucket_count) << "\n"
        << "empty() returns bool: " << check(interface_empty) << "\n"
        << "Interface part 1 score:\t\t\t\t\t\t" << score_interface_part1 << " / 0.5\n\n";
    
    constexpr bool interface_erase = erase_returns_size_t_v<test_map>;
    constexpr bool interface_clear = clear_returns_void_v<test_map>;
    constexpr bool interface_subscript = subscript_returns_tref_v<test_map>;
    constexpr bool interface_contains = contains_returns_bool_v<test_map>;

    constexpr bool interface_part2 =
        interface_erase && interface_clear && interface_subscript &&
        interface_contains;

    double score_interface_part2 = interface_part2 ? 0.5 : 0.0;
    score += score_interface_part2;
    std::cout << "Unordered map interface part 2:\n"
        << "erase() returns size_t: " << check(interface_erase) << "\n"
        << "clear() returns void: " << check(interface_clear) << "\n"
        << "operator[](Key const&) returns T&: " << check(interface_subscript) << "\n"
        << "contains(Key const&) returns bool: " << check(interface_contains) << "\n"
        << "Interface part 2 score:\t\t\t\t\t\t" << score_interface_part2 << " / 0.5\n\n";
    
    if constexpr(interface_part1 && interface_part2) {
        score += map_test<student_std::unordered_map>();
    }
    else {
        std::cout << "Unordered map functionality test not run due to interface failure: 0 / 2.5\n\n";
    }
    double prob1_subtotal = score;
    std::cout << "-------------------------------------------------------------------------\n";
    std::cout << "Problem 1 Subtotal:\t\t\t\t\t\t" << prob1_subtotal << " / 3.5\n";
    std::cout << "=========================================================================\n\n";
#else
    double score = 0;
    double prob1_subtotal = 0;
    std::cout << "-------------------------------------------------------------------------\n";
    std::cout << "Problem 1 due to missing header:\t\t\t\t" << prob1_subtotal << " / 3.5\n";
    std::cout << "=========================================================================\n\n";
#endif
#if TEST_P2
    using int_bst = student_std::binary_tree<int>;
    using int_it = student_std::inorder_iterator<int_bst>;

    constexpr bool interface_it_value_type = value_is_u_v<int_it, int>;
    constexpr bool interface_it_difference_type = difference_type_is_ptrdiff_v<int_it>;
    constexpr bool interface_it_category = iterator_cat_is_forward_v<int_it>;
    constexpr bool interface_it_reference = reference_is_valcref_v<int_it>;
    constexpr bool interface_it_pointer = pointer_is_valcptr_v<int_it>;
    constexpr bool interface_it_default_ctor = std::is_default_constructible_v<int_it>;
    constexpr bool interface_it_copy_ctor = std::is_copy_constructible_v<int_it>;
    constexpr bool interface_it_ptr_ctor = std::is_constructible_v<int_it, int_bst const*>;
    constexpr bool interface_it_assignable = std::is_copy_assignable_v<int_it>;
    
    constexpr bool interface_it1 =
        interface_it_difference_type && interface_it_value_type &&
        interface_it_pointer && interface_it_reference && interface_it_category &&
        interface_it_default_ctor && interface_it_ptr_ctor && interface_it_copy_ctor &&
        interface_it_assignable;
    
    double score_interface_it1 = interface_it1 ? 0.5 : 0.0;
    score += score_interface_it1;
    std::cout << "inorder_iterator interface part 1:\n"
        << "inorder_iterator::value_type is BST::value_type: " << check(interface_it_value_type) << "\n"
        << "inorder_iterator::reference is value_type const&: " << check(interface_it_reference) << "\n"
        << "inorder_iterator::pointer is value_type const*: " << check(interface_it_pointer) << "\n"
        << "inorder_iterator::difference_type is ptrdiff_t: " << check(interface_it_difference_type) << "\n"
        << "default constructible: " << check(interface_it_default_ctor) << "\n"
        << "constructible from BST const*: " << check(interface_it_ptr_ctor) << "\n"
        << "copy constructible: " << check(interface_it_copy_ctor) << "\n"
        << "assignable: " << check(interface_it_assignable) << "\n"
        << "inorder_iterator interface part 1 score:\t\t\t" << score_interface_it1 << " / 0.5\n\n";
    
    
    constexpr bool interface_it_preinc = iterator_preincrement_returns_ref_v<int_it>;
    constexpr bool interface_it_postinc = iterator_postincrement_returns_it_v<int_it>;
    constexpr bool interface_it_deref = iterator_deref_returns_ref_v<int_it>;
    constexpr bool interface_it_memptr = iterator_memptr_returns_ptr_v<int_it>;
    constexpr bool interface_it_eq = iterator_eq_returns_bool_v<int_it>;
    constexpr bool interface_it_ineq = iterator_ineq_returns_bool_v<int_it>;
    
    constexpr bool interface_it2 =
        interface_it_preinc && interface_it_postinc && interface_it_deref && 
        interface_it_memptr && interface_it_eq && interface_it_ineq;
    double score_interface_it2 = interface_it2 ? 0.5 : 0.0;
    score += score_interface_it2;
    std::cout << "inorder_iterator interface part 2:\n"
        << "++it returns iterator&: " << check(interface_it_preinc) << "\n"
        << "it++ returns iterator: " << check(interface_it_postinc) << "\n"
        << "*it returns reference: " << check(interface_it_deref) << "\n"
        << "it-> returns pointer: " << check(interface_it_memptr) << "\n"
        << "it1 == it2 returns bool: " << check(interface_it_eq) << "\n"
        << "it1 != it2 returns bool: " << check(interface_it_ineq) << "\n"
        << "inorder_iterator interface part 2 score:\t\t\t" << score_interface_it2 << " / 0.5\n\n";
    
    
    if constexpr(interface_it1 && interface_it2) {
        score += iterator_test<int_it>();
    }
    else {
        std::cout << "Iterator functionality test not run due to interface failure: 0 / 2.5\n";
    }
    double prob2_subtotal = score - prob1_subtotal;
    std::cout << "-------------------------------------------------------------------------\n";
    std::cout << "Problem 2 Subtotal:\t\t\t\t\t\t" << prob2_subtotal << " / 3.5\n";
    std::cout << "=========================================================================\n\n";
#else
    double prob2_subtotal = 0;
    std::cout << "-------------------------------------------------------------------------\n";
    std::cout << "Problem 2 due to missing header:\t\t\t\t" << prob2_subtotal << " / 3.5\n";
    std::cout << "=========================================================================\n\n";
#endif
    std::cout << "\nTotal Score:\t\t\t\t\t\t\t" << score << " / 7.0\n";
    std::cout << "-------------------------------------------------------------------------\n";


    return 0;
}



#endif