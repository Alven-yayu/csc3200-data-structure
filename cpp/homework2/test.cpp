#if !(__has_include("student_vector.h"))
#include <iostream>

int main() {
    std::cout << "student_vector.h not found. Score: 0.0 / 7.0\n";
    return 0;
}

#else
#include "student_vector.h"
#include "student_vector.h"

#include <cstddef>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <type_traits>

template <typename T>
using student_vector = student_std::vector<T>;

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
struct value_is_u : std::false_type {};

template<typename T, typename U>
struct value_is_u<T, U, std::void_t<typename T::value_type>>
  : std::is_same<typename T::value_type, U> {};

template<typename T, typename U>
inline constexpr bool value_is_u_v = value_is_u<T, U>::value;

template<class T, class = void>
struct size_returns_size_t : std::false_type {};

template<class T>
struct size_returns_size_t<T,
    std::void_t<decltype(std::declval<const T&>().size())>>
  : std::is_same<decltype(std::declval<const T&>().size()), std::size_t> {};

template<class T>
inline constexpr bool size_returns_size_t_v = size_returns_size_t<T>::value;

template<class T, class = void>
struct capacity_returns_size_t : std::false_type {};

template<class T>
struct capacity_returns_size_t<T,
    std::void_t<decltype(std::declval<const T&>().capacity())>>
  : std::is_same<decltype(std::declval<const T&>().capacity()), std::size_t> {};

template<class T>
inline constexpr bool capacity_returns_size_t_v = capacity_returns_size_t<T>::value;

template<class T, class = void>
struct empty_returns_bool : std::false_type {};

template<class T>
struct empty_returns_bool<T,
    std::void_t<decltype(std::declval<const T&>().empty())>>
  : std::is_same<decltype(std::declval<const T&>().empty()), bool> {};

template<class T>
inline constexpr bool empty_returns_bool_v = empty_returns_bool<T>::value;

template<class T, class = void>
struct push_back_returns_void : std::false_type {};

template<class T>
struct push_back_returns_void<T,
    std::void_t<decltype(std::declval<T&>().push_back(std::declval<const typename T::value_type&>()))>>
  : std::is_same<decltype(std::declval<T&>().push_back(std::declval<const typename T::value_type&>())), void> {};

template<class T>
inline constexpr bool push_back_returns_void_v = push_back_returns_void<T>::value;

template<class T, class = void>
struct pop_back_returns_void : std::false_type {};

template<class T>
struct pop_back_returns_void<T,
    std::void_t<decltype(std::declval<T&>().pop_back())>>
  : std::is_same<decltype(std::declval<T&>().pop_back()), void> {};

template<class T>
inline constexpr bool pop_back_returns_void_v = pop_back_returns_void<T>::value;

template<class T, class = void>
struct resize1_returns_void : std::false_type {};

template<class T>
struct resize1_returns_void<T,
    std::void_t<decltype(std::declval<T&>().resize(std::declval<std::size_t>()))>>
  : std::is_same<decltype(std::declval<T&>().resize(std::declval<std::size_t>())), void> {};

template<class T, class = void>
struct resize2_returns_void : std::false_type {};

template<class T>
struct resize2_returns_void<T,
    std::void_t<decltype(std::declval<T&>().resize(std::declval<std::size_t>(), std::declval<const typename T::value_type&>()))>>
  : std::is_same<decltype(std::declval<T&>().resize(std::declval<std::size_t>(), std::declval<const typename T::value_type&>())), void> {};

template<class T>
inline constexpr bool resize_returns_void_v = resize1_returns_void<T>::value && resize2_returns_void<T>::value;

template<class T, class = void>
struct reserve_returns_void : std::false_type {};

template<class T>
struct reserve_returns_void<T,
    std::void_t<decltype(std::declval<T&>().reserve(std::declval<std::size_t>()))>>
  : std::is_same<decltype(std::declval<T&>().reserve(std::declval<std::size_t>())), void> {};

template<class T>
inline constexpr bool reserve_returns_void_v = reserve_returns_void<T>::value;

template<class T, class = void>
struct swap_returns_void : std::false_type {};

template<class T>
struct swap_returns_void<T,
    std::void_t<decltype(std::declval<T&>().swap(std::declval<T&>()))>>
  : std::is_same<decltype(std::declval<T&>().swap(std::declval<T&>())),void> {};

template<class T>
inline constexpr bool swap_returns_void_v = swap_returns_void<T>::value;

template<class T, class = void>
struct clear_returns_void : std::false_type {};

template<class T>
struct clear_returns_void<T,
    std::void_t<decltype(std::declval<T&>().clear())>>
  : std::is_same<decltype(std::declval<T&>().clear()), void> {};

template<class T>
inline constexpr bool clear_returns_void_v = clear_returns_void<T>::value;

template<class T, class = void>
struct data_returns_tptr : std::false_type {};

template<class T>
struct data_returns_tptr<T,
    std::void_t<decltype(std::declval<const T&>().data())>>
  : std::integral_constant<bool, 
           std::is_same<decltype(std::declval<T&>().data()), typename T::value_type*>::value
        && std::is_same<decltype(std::declval<const T&>().data()), const typename T::value_type*>::value> {};

template<class T>
inline constexpr bool data_returns_tptr_v = data_returns_tptr<T>::value;

template<class T, class = void>
struct at_returns_tref : std::false_type {};

template<class T>
struct at_returns_tref<T,
    std::void_t<decltype(std::declval<const T&>().at(std::declval<std::size_t>()))>>
  : std::integral_constant<bool, 
           std::is_same<decltype(std::declval<T&>().at(std::declval<std::size_t>())), typename T::value_type&>::value
        && std::is_same<decltype(std::declval<const T&>().at(std::declval<std::size_t>())), const typename T::value_type&>::value> {};

template<class T>
inline constexpr bool at_returns_tref_v = at_returns_tref<T>::value;

template<class T, class = void>
struct subscript_returns_tref : std::false_type {};

template<class T>
struct subscript_returns_tref<T,
    std::void_t<decltype(std::declval<const T&>()[std::declval<std::size_t>()])>>
  : std::integral_constant<bool, 
           std::is_same<decltype(std::declval<T&>()[std::declval<std::size_t>()]), typename T::value_type&>::value
        && std::is_same<decltype(std::declval<const T&>()[std::declval<std::size_t>()]), const typename T::value_type&>::value> {};

template<class T>
inline constexpr bool subscript_returns_tref_v = subscript_returns_tref<T>::value;

template<class T, class = void>
struct front_returns_tref : std::false_type {};

template<class T>
struct front_returns_tref<T,
    std::void_t<decltype(std::declval<const T&>().front())>>
  : std::integral_constant<bool, 
           std::is_same<decltype(std::declval<T&>().front()), typename T::value_type&>::value
        && std::is_same<decltype(std::declval<const T&>().front()), const typename T::value_type&>::value> {};

template<class T>
inline constexpr bool front_returns_tref_v = front_returns_tref<T>::value;

template<class T, class = void>
struct back_returns_tref : std::false_type {};

template<class T>
struct back_returns_tref<T,
    std::void_t<decltype(std::declval<const T&>().back())>>
  : std::integral_constant<bool, 
           std::is_same<decltype(std::declval<T&>().back()), typename T::value_type&>::value
        && std::is_same<decltype(std::declval<const T&>().back()), const typename T::value_type&>::value> {};

template<class T>
inline constexpr bool back_returns_tref_v = back_returns_tref<T>::value;

namespace {

struct test_type {
    int v = 0;
};

}

const char* check(bool b) {
    return b ? "SUCCESS" : "FAIL";
}

template <template<typename> typename T>
double vector_test() {
    double score = 0.0;
    using int_vec = T<int>;
    
    int_vec vec_default;
    int_vec vec_default_copy(vec_default);
    int_vec vec_default_assigned = vec_default;

    bool defaults_empty = true;

    std::cout << "Vector functionality test:\n";
    if(vec_default.size() != 0 || !vec_default.empty()) {
        std::cerr << "default constructed vector is not empty.\n";
        defaults_empty = false;
    }
    if(vec_default_copy.size() != 0 || !vec_default_copy.empty()) {
        std::cerr << "copy of default constructed vector is not empty.\n";
        defaults_empty = false;
    }
    if(vec_default_assigned.size() != 0 || !vec_default_assigned.empty()) {
        std::cerr << "copy assigned vector of default constructed vector is not empty.\n";
        defaults_empty = false;
    }
    if(defaults_empty)
        score += 0.5;
    std::cout << "default constructor, copy of empty, assigned from empty:\t" << score << " / 0.5\n";

    int_vec five_entries;
    five_entries.push_back(0);
    five_entries.push_back(1);
    five_entries.push_back(2);
    five_entries.push_back(3);
    five_entries.push_back(4);
    int_vec five_entries_copy(five_entries);
    int_vec five_entries_assigned = five_entries;

    bool five_size_cap = true;
    if(five_entries.size() != 5 || five_entries.capacity() < 5)
    {
        std::cerr << "After 5 push_backs size() != 5 or capacity() < 5.\n";
        five_size_cap = false;
    }
    if(five_entries_assigned.size() != 5 || five_entries_assigned.capacity() < 5)
    {
        std::cerr << "After 5 push_backs and assigning, size() != 5 or capacity() < 5.\n";
        five_size_cap = false;
    }
    if(five_entries.capacity() > 100) {
        std::cerr << "Capacity after five push_backs > 100 (unreasonable, do not try to get around dynamic realloc).\n";
        five_size_cap = false;
    }
    double five_entries_score = five_size_cap ? 0.5 : 0.;
    score += five_entries_score;
    std::cout << "Size and capacity after five push_backs, copying, and assigning:" << five_entries_score << " / 0.5\n";

    bool true_copy_reserve = true;
    if(five_entries.data() == five_entries_copy.data() || five_entries.data() == five_entries_assigned.data()) {
        std::cerr << "Memory of vector and copy or vector and copy assigned equal, no true copy.\n";
        true_copy_reserve = false;
    }
    int_vec vec_reserve;
    int_vec vec_no_reserve;
    vec_reserve.reserve(101);
    if(vec_reserve.capacity() < 101) {
        std::cerr << "After reserve(n) on empty vector, capacity < n.\n";
        true_copy_reserve = false;
    }
    vec_reserve.reserve(50);
    if(vec_reserve.capacity() < 101) {
        std::cerr << "After reserve(n), reserve(m) with m < n on empty vector, capacity < n (smaller reserves should not reduce capacity).\n";
        true_copy_reserve = false;
    }
    if(vec_reserve.size() != 0) {
        std::cerr << "After reserve(n) on empty vector, size changed.\n";
        true_copy_reserve = false;
    }
    int* old_loc = vec_reserve.data();
    for(int i = 0; i < 101; ++i) {
        vec_reserve.push_back(i);
        vec_no_reserve.push_back(i);
    }
    int* new_loc = vec_reserve.data();
    if(old_loc != new_loc) {
        std::cerr << "After reserve(n) and n times push_back, the location changed, even though enough should have been reserved.\n";
        true_copy_reserve = false;
    }
    if(vec_reserve.size() != 101 || vec_no_reserve.size() != 101) {
        std::cerr << "Incorrect size after reserve/no reserve and 101 push_backs.\n";
        true_copy_reserve = false;
    }
    double true_copy_score = true_copy_reserve ? 0.5 : 0;
    score += true_copy_score;
    std::cout << "True copy, correct reserve handling:\t\t\t\t" << true_copy_score << " / 0.5\n";

    bool pop_back_milestones = true;
    five_entries.pop_back();
    five_entries.pop_back();
    five_entries.pop_back();
    if(five_entries.size() != 2 || five_entries.empty()) {
        std::cerr << "size() != 2 or empty() == true after 5 push_backs and 3 pop_backs.\n";
        pop_back_milestones = false;
    }
    five_entries_copy.clear();
    if(five_entries_copy.size() != 0 || !five_entries_copy.empty())
    {
        std::cerr << "size() != 0 or empty() != true after clear().\n";
        pop_back_milestones = false;
    }
    double pop_back_score = pop_back_milestones ? 0.5 : 0.0;
    score += pop_back_score;
    std::cout << "Expected sizes after pop_back()/clear:\t\t\t\t" << pop_back_score << " / 0.5\n";

    bool expected_values = true;
    if(five_entries.front() != 0 || five_entries.back() != 1) {
        std::cerr << "front or back returned the wrong value.\n";
        expected_values = false;
    }
    try{
        five_entries.at(2);
        std::cerr << "No exception thrown for out of range at.\n";
        expected_values = false;
    }
    catch(std::out_of_range& e) {}
    catch(...) {
        std::cerr << "Wrong exception type thrown for out of range at.\n";
        expected_values = false;
    }
    if(five_entries_assigned[0] != 0 || five_entries_assigned[4] != 4
       || vec_reserve[0] != 0 || vec_reserve[100] != 100
       || vec_reserve.data()[0] != 0 || vec_reserve.data()[100] != 100) {
        std::cerr << "at() or operator[] or data()[] returned unexpected value.\n";
        expected_values = false;
    }
    five_entries[0] = 100;
    five_entries.at(1) = 101;
    if(five_entries.front() != 100 || five_entries.back() != 101) {
        std::cerr << "front() or back() produces unexpected value after assign.\n";
        expected_values = false;
    }
    double expected_values_score = expected_values ? 0.5 : 0.0;
    std::cout << "Expected values after push_backs, pop_backs and assignments:\t" << expected_values_score << " / 0.5\n\n";
    score += expected_values_score;

    return score;
}

template <typename, typename = std::void_t<>>
struct has_iterator_type : std::false_type {};

template <typename T>
struct has_iterator_type<T, std::void_t<typename T::iterator>> : std::true_type {};

template <typename T>
constexpr bool has_iterator_type_v = has_iterator_type<T>::value;

template <typename, typename = std::void_t<>>
struct iterator_difference_type_is_ptrdiff : std::false_type {};

template <typename T>
struct iterator_difference_type_is_ptrdiff<T, std::void_t<typename T::iterator::difference_type>>
  : std::is_same<typename T::iterator::difference_type, std::ptrdiff_t> {};

template <typename T>
constexpr bool iterator_difference_type_is_ptrdiff_v = iterator_difference_type_is_ptrdiff<T>::value;

template<typename T, typename U, class = void>
struct iterator_value_is_u : std::false_type {};

template<typename T, typename U>
struct iterator_value_is_u<T, U, std::void_t<typename T::iterator::value_type>>
  : std::is_same<typename T::iterator::value_type, U> {};

template<typename T, typename U>
inline constexpr bool iterator_value_is_u_v = iterator_value_is_u<T, U>::value;

template<typename T, typename U, class = void>
struct iterator_pointer_is_uptr : std::false_type {};

template<typename T, typename U>
struct iterator_pointer_is_uptr<T, U, std::void_t<typename T::iterator::pointer>>
  : std::is_same<typename T::iterator::pointer, U*> {};

template<typename T, typename U>
inline constexpr bool iterator_pointer_is_uptr_v = iterator_pointer_is_uptr<T, U>::value;

template<typename T, typename U, class = void>
struct iterator_reference_is_uref : std::false_type {};

template<typename T, typename U>
struct iterator_reference_is_uref<T, U, std::void_t<typename T::iterator::reference>>
  : std::is_same<typename T::iterator::reference, U&> {};

template<typename T, typename U>
inline constexpr bool iterator_reference_is_uref_v = iterator_reference_is_uref<T, U>::value;

template<typename T, class = void>
struct iterator_cat_is_random_access : std::false_type {};

template<typename T>
struct iterator_cat_is_random_access<T, std::void_t<typename T::iterator::iterator_category>>
  : std::is_same<typename T::iterator::iterator_category, std::random_access_iterator_tag> {};

template<typename T>
inline constexpr bool iterator_cat_is_random_access_v = iterator_cat_is_random_access<T>::value;

template<typename T, class = void>
struct iterator_is_default_constructible : std::false_type {};

template<typename T>
struct iterator_is_default_constructible<T, std::void_t<typename T::iterator>>
  : std::is_default_constructible<typename T::iterator> {};

template<typename T>
inline constexpr bool iterator_is_default_constructible_v = iterator_is_default_constructible<T>::value;

template<typename T, typename U, class = void>
struct iterator_is_constructible_from_uptr : std::false_type {};

template<typename T, typename U>
struct iterator_is_constructible_from_uptr<T, U, std::void_t<typename T::iterator>>
  : std::is_constructible<typename T::iterator, U*> {};

template<typename T, typename U>
inline constexpr bool iterator_is_constructible_from_uptr_v = iterator_is_constructible_from_uptr<T, U>::value;

template<typename T, typename = void>
struct iterator_is_copy_constructible : std::false_type {};

template<typename T>
struct iterator_is_copy_constructible<T, std::void_t<typename T::iterator>>
  : std::is_copy_constructible<typename T::iterator> {};

template<typename T>
inline constexpr bool iterator_is_copy_constructible_v = iterator_is_copy_constructible<T>::value;

template<typename T, class = void>
struct iterator_is_copy_assignable : std::false_type {};

template<typename T>
struct iterator_is_copy_assignable<T, std::void_t<typename T::iterator>>
  : std::is_copy_assignable<typename T::iterator> {};

template<typename T>
inline constexpr bool iterator_is_copy_assignable_v = iterator_is_copy_assignable<T>::value;

template<typename T, class = void>
struct iterator_preincrement_returns_ref : std::false_type {};

template<typename T>
struct iterator_preincrement_returns_ref<T, std::void_t<decltype(++std::declval<typename T::iterator&>())>>
  : std::is_same<decltype(++std::declval<typename T::iterator&>()), typename T::iterator&> {};

template<typename T>
inline constexpr bool iterator_preincrement_returns_ref_v = iterator_preincrement_returns_ref<T>::value;

template<typename T, class = void>
struct iterator_predecrement_returns_ref : std::false_type {};

template<typename T>
struct iterator_predecrement_returns_ref<T, std::void_t<decltype(--std::declval<typename T::iterator&>())>>
  : std::is_same<decltype(--std::declval<typename T::iterator&>()), typename T::iterator&> {};

template<typename T>
inline constexpr bool iterator_predecrement_returns_ref_v = iterator_predecrement_returns_ref<T>::value;

template<typename T, class = void>
struct iterator_postincrement_returns_it : std::false_type {};

template<typename T>
struct iterator_postincrement_returns_it<T, std::void_t<decltype(std::declval<typename T::iterator&>()++)>>
  : std::is_same<decltype(std::declval<typename T::iterator&>()++), typename T::iterator> {};

template<typename T>
inline constexpr bool iterator_postincrement_returns_it_v = iterator_postincrement_returns_it<T>::value;

template<typename T, class = void>
struct iterator_postdecrement_returns_it : std::false_type {};

template<typename T>
struct iterator_postdecrement_returns_it<T, std::void_t<decltype(std::declval<typename T::iterator&>()--)>>
  : std::is_same<decltype(std::declval<typename T::iterator&>()--), typename T::iterator> {};

template<typename T>
inline constexpr bool iterator_postdecrement_returns_it_v = iterator_postdecrement_returns_it<T>::value;

template<typename T, typename U, class = void>
struct iterator_deref_returns_u : std::false_type {};

template<typename T, typename U>
struct iterator_deref_returns_u<T, U, std::void_t<decltype(*std::declval<const typename T::iterator&>())>>
  : std::is_same<decltype(*std::declval<const typename T::iterator&>()), U&> {};

template<typename T, typename U>
inline constexpr bool iterator_deref_returns_u_v = iterator_deref_returns_u<T, U>::value;

template<typename T, typename U, class = void>
struct iterator_memptr_returns_uptr : std::false_type {};

template<typename T, typename U>
struct iterator_memptr_returns_uptr<T, U, std::void_t<decltype(std::declval<const typename T::iterator&>().operator->())>>
  : std::is_same<decltype(std::declval<const typename T::iterator&>().operator->()), U*> {};

template<typename T, typename U>
inline constexpr bool iterator_memptr_returns_uptr_v = iterator_memptr_returns_uptr<T, U>::value;

template<typename T, class = void>
struct iterator_less_than_returns_bool : std::false_type {};

template<typename T>
struct iterator_less_than_returns_bool<T, std::void_t<decltype(std::declval<typename T::iterator>() < std::declval<typename T::iterator>())>>
  : std::is_same<decltype(std::declval<typename T::iterator>() < std::declval<typename T::iterator>()), bool> {};

template<typename T>
inline constexpr bool iterator_less_than_returns_bool_v = iterator_less_than_returns_bool<T>::value;

template<typename T, class = void>
struct iterator_lesseq_than_returns_bool : std::false_type {};

template<typename T>
struct iterator_lesseq_than_returns_bool<T, std::void_t<decltype(std::declval<typename T::iterator>() <= std::declval<typename T::iterator>())>>
  : std::is_same<decltype(std::declval<typename T::iterator>() <= std::declval<typename T::iterator>()), bool> {};

template<typename T>
inline constexpr bool iterator_lesseq_than_returns_bool_v = iterator_lesseq_than_returns_bool<T>::value;

template<typename T, class = void>
struct iterator_eq_returns_bool : std::false_type {};

template<typename T>
struct iterator_eq_returns_bool<T, std::void_t<decltype(std::declval<typename T::iterator>() == std::declval<typename T::iterator>())>>
  : std::is_same<decltype(std::declval<typename T::iterator>() == std::declval<typename T::iterator>()), bool> {};

template<typename T>
inline constexpr bool iterator_eq_returns_bool_v = iterator_eq_returns_bool<T>::value;

template<typename t, class = void>
struct iterator_ineq_returns_bool : std::false_type {};

template<typename t>
struct iterator_ineq_returns_bool<t, std::void_t<decltype(std::declval<typename t::iterator>() != std::declval<typename t::iterator>())>>
  : std::is_same<decltype(std::declval<typename t::iterator>() != std::declval<typename t::iterator>()), bool> {};

template<typename t>
inline constexpr bool iterator_ineq_returns_bool_v = iterator_ineq_returns_bool<t>::value;

template<typename T, class = void>
struct iterator_addassign_returns_itref : std::false_type {};

template<typename T>
struct iterator_addassign_returns_itref<T, std::void_t<decltype(std::declval<typename T::iterator>() += std::declval<typename T::iterator::difference_type>())>>
  : std::is_same<decltype(std::declval<typename T::iterator>() += std::declval<typename T::iterator::difference_type>()), typename T::iterator&> {};

template<typename T>
inline constexpr bool iterator_addassign_returns_itref_v = iterator_addassign_returns_itref<T>::value;

template<typename T, class = void>
struct iterator_subassign_returns_itref : std::false_type {};

template<typename T>
struct iterator_subassign_returns_itref<T, std::void_t<decltype(std::declval<typename T::iterator>() -= std::declval<typename T::iterator::difference_type>())>>
  : std::is_same<decltype(std::declval<typename T::iterator>() -= std::declval<typename T::iterator::difference_type>()), typename T::iterator&> {};

template<typename T>
inline constexpr bool iterator_subassign_returns_itref_v = iterator_subassign_returns_itref<T>::value;

template<typename T, class = void>
struct iterator_add_returns_it : std::false_type {};

template<typename T>
struct iterator_add_returns_it<T, std::void_t<decltype(std::declval<typename T::iterator>() + std::declval<typename T::iterator::difference_type>())>>
  : std::is_same<decltype(std::declval<typename T::iterator>() + std::declval<typename T::iterator::difference_type>()), typename T::iterator> {};

template<typename T>
inline constexpr bool iterator_add_returns_it_v = iterator_add_returns_it<T>::value;

template<typename T, class = void>
struct iterator_sub_returns_it : std::false_type {};

template<typename T>
struct iterator_sub_returns_it<T, std::void_t<decltype(std::declval<typename T::iterator>() - std::declval<typename T::iterator::difference_type>())>>
  : std::is_same<decltype(std::declval<typename T::iterator>() - std::declval<typename T::iterator::difference_type>()), typename T::iterator> {};

template<typename T>
inline constexpr bool iterator_sub_returns_it_v = iterator_sub_returns_it<T>::value;

template<typename T, class = void>
struct iterator_subit_returns_diff : std::false_type {};

template<typename T>
struct iterator_subit_returns_diff<T, std::void_t<decltype(std::declval<typename T::iterator>() - std::declval<typename T::iterator>())>>
  : std::is_same<decltype(std::declval<typename T::iterator>() - std::declval<typename T::iterator>()), typename T::iterator::difference_type> {};

template<typename T>
inline constexpr bool iterator_subit_returns_diff_v = iterator_subit_returns_diff<T>::value;

template<typename T, class = void>
struct begin_returns_it : std::false_type {};

template<typename T>
struct begin_returns_it<T, std::void_t<decltype(std::declval<T&>().begin()), typename T::iterator>>
  : std::is_same<decltype(std::declval<T&>().begin()), typename T::iterator> {};

template<typename T>
inline constexpr bool begin_returns_it_v = begin_returns_it<T>::value;

template<typename T, class = void>
struct end_returns_it : std::false_type {};

template<typename T>
struct end_returns_it<T, std::void_t<decltype(std::declval<T&>().end()), typename T::iterator>>
  : std::is_same<decltype(std::declval<T&>().end()), typename T::iterator> {};

template<typename T>
inline constexpr bool end_returns_it_v = end_returns_it<T>::value;

template<typename T, class = void>
struct erase1_returns_it : std::false_type {};

template<typename T>
struct erase1_returns_it<T, std::void_t<decltype(std::declval<T&>().erase(std::declval<typename T::iterator>()))>>
  : std::is_same<decltype(std::declval<T&>().erase(std::declval<typename T::iterator>())), typename T::iterator> {};

template<typename T, class = void>
struct erase2_returns_it : std::false_type {};

template<typename T>
struct erase2_returns_it<T, std::void_t<decltype(std::declval<T&>().erase(std::declval<typename T::iterator>(), std::declval<typename T::iterator>()))>>
  : std::is_same<decltype(std::declval<T&>().erase(std::declval<typename T::iterator>(), std::declval<typename T::iterator>())), typename T::iterator> {};

template<typename T>
inline constexpr bool erase_returns_it_v = erase1_returns_it<T>::value && erase2_returns_it<T>::value;

template<typename T, class = void>
struct insert_returns_it : std::false_type {};

template<typename T>
struct insert_returns_it<T, std::void_t<decltype(std::declval<T&>().insert(std::declval<typename T::iterator>(), std::declval<const typename T::value_type&>()))>>
  : std::is_same<decltype(std::declval<T&>().insert(std::declval<typename T::iterator>(), std::declval<const typename T::value_type&>())), typename T::iterator> {};

template<typename T>
inline constexpr bool insert_returns_it_v = insert_returns_it<T>::value;

namespace {
    struct foo {
        bool test() { return v == 1; }
        int v = 0;
    };
}

template <template<typename> typename T>
double iterator_test() {
    using int_vec = T<int>;
    std::cout << "Vector/Iterator Functionality Test:\n";
    
    int_vec vec_10;
    for(int i = 0; i < 10; ++i)
        vec_10.push_back(i);
    double score = 0.;

    bool begin_end = true;
    if(*vec_10.begin() != 0 || *(vec_10.end() - 1) != 9) {
        std::cerr << "*begin() and *(end-1) return unexpected values.\n";
        begin_end = false;
    }
    score = begin_end ? 0.5 : 0.0;
    std::cout << "begin(), end():\t\t\t\t\t\t\t" << score << " / 0.5\n";

    bool ranged_for = true;
    int i = 0;
    for (const auto& entry : vec_10) {
        if (i++ != entry) {
            std::cerr << "unexpected value pointed at by iterator in ranged for loop (uses begin(), end(), iterator != end(), *iterator, and iterator++).\n";
            ranged_for = false;
        }
    }
    if(i != 10){
        std::cerr << "Ranged for loop (uses begin(), end(), iterator++) terminated early or late.\n";
        ranged_for = false;
    }
    i = 0;
    for (auto& entry : vec_10)
        entry *= 2;
    for (const auto& entry : vec_10) {
        if ((i++) * 2 != entry) {
            std::cerr << "unexpected value pointed at by iterator in ranged for loop (uses begin(), end(), iterator != end(), *iterator, and iterator++) after manipulation.\n";
            ranged_for = false;
        }
    }
    double score_ranged_for = ranged_for ? 0.5 : 0.0;
    std::cout << "ranged-for:\t\t\t\t\t\t\t" << score_ranged_for << " / 0.5\n";
    score += score_ranged_for;


    T<foo> vec_foo;
    vec_foo.push_back(foo{1});
    vec_foo.push_back(foo{});
    vec_foo.push_back(foo{});

    bool deref = true;
    if( !vec_foo.begin()->test() ) {
        std::cerr << "iterator-> returned unexpected result.\n";
        deref = false;
    }
    double score_deref = deref ? 0.5 : 0.0;
    std::cout << "iterator->:\t\t\t\t\t\t\t" << score_deref << " / 0.5\n";
    score += score_deref;


    bool comparison = true;
    if(    !(vec_10.begin() < vec_10.begin() + 1) || !(vec_10.begin() < vec_10.end())
        || !( vec_10.begin() <= vec_10.begin()) || !(vec_10.begin() <= vec_10.begin() + 1)
        || !( vec_10.begin() <= vec_10.end())) {
        std::cerr << "operator< or operator<= produced unexpected results.\n";
        comparison = false;
    }
    if(    !(vec_10.begin() + 10 == vec_10.end()) || !(vec_10.begin() != vec_10.end())
        || !(vec_10.begin() == vec_10.begin()) || (vec_10.end() != vec_10.end()) ) {
        std::cerr << "operator== or operator!= produced unexpected results.\n";
        comparison = false;
    }
    auto it1 = vec_10.begin() + 2;
    auto it2 = vec_10.begin() + 4;
    auto it3 = it2;
    auto it4 = it1;
    it3 -= 2;
    it4 += 2;
    if( it2 - it1 != 2 || it1 - it2 != -2 || it2 - 2 != it1 || it3 != it1 || it4 != it2) {
        std::cerr << "operator-, operator+, operator-=, or operator+= produced unexpected results.\n";
        comparison = false;
    }
    double comparison_score = comparison ? 0.5 : 0.0;
    score += comparison_score;
    std::cout << "Comparisons:\t\t\t\t\t\t\t" << comparison_score << " / 0.5\n";

    bool insert_erase = true;
    auto it10 = vec_10.insert(vec_10.end(), 10);
    if(*it10 != 10) {
        std::cerr << "Incorrect iterator returned by insert.\n";
        insert_erase = false;
    }
    auto itm1 = vec_10.insert(vec_10.begin(), -1);
    if(*itm1 != -1) {
        std::cerr << "Incorrect iterator returned by insert.\n";
        insert_erase = false;
    }
    auto it1_ = vec_10.erase(vec_10.begin() + 1);
    if(*it1_ != 2) {
        std::cerr << "Incorrect iterator returned by erase, should point to 2.\n";
        insert_erase = false;
    }
    auto it10_ = vec_10.erase(vec_10.begin() + 1, vec_10.end() - 1);
    if(*it10_ != 10) {
        std::cerr << "Incorrect iterator returned by erase, should point to 10.\n";
        insert_erase = false;
    }
    if(vec_10.front() != -1 || vec_10.back() != 10 || vec_10.size() != 2) {
        std::cerr << "State incorrect after insert and erase.\n";
        insert_erase = false;
    }
    auto end_ = vec_10.erase(vec_10.begin(), vec_10.end());
    if( !vec_10.empty() || end_ != vec_10.end() ) {
        std::cerr << "State incorrect after erase(begin(), end()), or incorrect iterator returned (should return end()).\n";
        insert_erase = false;
    }
    auto it17 = vec_10.insert(vec_10.begin(), 17);
    if(vec_10.size() != 1 || vec_10.front() != 17 || vec_10.back() != 17 || *it17 != 17) {
        std::cerr << "State incorrect after insert(begin()) in empty vector.\n";
        insert_erase = false;
    }
    double insert_erase_score = insert_erase ? 0.5 : 0.0;
    std::cout << "Insert/Erase:\t\t\t\t\t\t\t" << insert_erase_score << " / 0.5\n\n";
    score += insert_erase_score;

    return score;
}

int main() {
    using test_vec = student_vector<test_type>;
    double score = 0.0;

    constexpr bool interface_size_type = size_type_is_size_t_v<test_vec>;
    constexpr bool interface_difference_type = difference_type_is_ptrdiff_v<test_vec>;
    constexpr bool interface_value_type = value_is_u_v<test_vec, test_type>;
    constexpr bool interface_default_ctor = std::is_default_constructible_v<test_vec>;
    constexpr bool interface_copy_ctor = std::is_copy_constructible_v<test_vec>;
    constexpr bool interface_assignable = std::is_copy_assignable_v<test_vec>;
    
    constexpr bool interface_size = size_returns_size_t_v<test_vec>;
    constexpr bool interface_capacity = capacity_returns_size_t_v<test_vec>;
    constexpr bool interface_empty = empty_returns_bool_v<test_vec>;
    
    constexpr bool interface_part1 =
        interface_size_type && interface_difference_type && interface_value_type &&
        interface_default_ctor && interface_copy_ctor && interface_assignable &&
        interface_size && interface_capacity && interface_empty;

    double score_interface_part1 = interface_part1 ? 0.5 : 0.0;
    score += score_interface_part1;
    std::cout << std::fixed << std::setprecision(1) << "Vector Interface Part 1:\n"
        << "::size_type is size_t: " << check(interface_size_type) << "\n"
        << "::difference_type is ptrdiff_t: " << check(interface_difference_type) << "\n"
        << "::value_type is T: " << check(interface_value_type) << "\n"
        << "default constructible: " << check(interface_default_ctor) << "\n"
        << "copy constructible: " << check(interface_copy_ctor) << "\n"
        << "assignable: " << check(interface_assignable) << "\n"
        << "size() returns size_t: " << check(interface_size) << "\n"
        << "capacity() returns size_t: " << check(interface_capacity) << "\n"
        << "empty() returns bool: " << check(interface_empty) << "\n"
        << "Interface Part 1 Score:\t\t\t\t\t\t" << score_interface_part1 << " / 0.5\n\n";
    
    constexpr bool interface_push_back = push_back_returns_void_v<test_vec>;
    constexpr bool interface_pop_back = pop_back_returns_void_v<test_vec>;
    constexpr bool interface_resize = resize_returns_void_v<test_vec>;
    constexpr bool interface_reserve = reserve_returns_void_v<test_vec>;

    constexpr bool interface_swap = swap_returns_void_v<test_vec>;
    constexpr bool interface_clear = clear_returns_void_v<test_vec>;
    constexpr bool interface_data = data_returns_tptr_v<test_vec>;
    constexpr bool interface_at = at_returns_tref_v<test_vec>;
    constexpr bool interface_subscript = subscript_returns_tref_v<test_vec>;
    constexpr bool interface_front = front_returns_tref_v<test_vec>;
    constexpr bool interface_back = back_returns_tref_v<test_vec>;

    constexpr bool interface_part2 =
        interface_push_back && interface_pop_back && interface_resize &&
        interface_reserve && interface_swap && interface_clear &&
        interface_data && interface_at && interface_subscript &&
        interface_front && interface_back;

    double score_interface_part2 = interface_part2 ? 0.5 : 0.0;
    score += score_interface_part2;
    std::cout << "Vector Interface Part 2:\n"
        << "push_back() returns void: " << check(interface_push_back) << "\n"
        << "pop_back() returns void: " << check(interface_pop_back) << "\n"
        << "resize() returns void: " << check(interface_resize) << "\n"
        << "reserve() returns void: " << check(interface_reserve) << "\n"
        << "swap() returns void: " << check(interface_swap) << "\n"
        << "clear() returns void: " << check(interface_clear) << "\n"
        << "data() returns T*: " << check(interface_data) << "\n"
        << "at() returns T&: " << check(interface_at) << "\n"
        << "operator[] returns T&: " << check(interface_subscript) << "\n"
        << "front() returns T&: " << check(interface_front) << "\n"
        << "back() returns T&: " << check(interface_back) << "\n"
        << "Interface Part 2 Score:\t\t\t\t\t\t" << score_interface_part2 << " / 0.5\n\n";
    
    if constexpr(interface_part1 && interface_part2) {
        score += vector_test<student_vector>();
    }
    else {
        std::cout << "Vector functionality test not run due to interface failure: 0 / 2.5\n\n";
    }
    double prob1_subtotal = score;
    std::cout << "-------------------------------------------------------------------------\n";
    std::cout << "Problem 1 Subtotal:\t\t\t\t\t\t" << prob1_subtotal << " / 3.5\n";
    std::cout << "=========================================================================\n\n";
    
    constexpr bool interface_iterator = has_iterator_type_v<test_vec>;
    constexpr bool interface_it_difference_type = iterator_difference_type_is_ptrdiff_v<test_vec>;
    constexpr bool interface_it_value_type = iterator_value_is_u_v<test_vec, test_type>;
    constexpr bool interface_it_pointer_type = iterator_pointer_is_uptr_v<test_vec, test_type>;
    constexpr bool interface_it_reference_type = iterator_reference_is_uref_v<test_vec, test_type>;
    constexpr bool interface_it_category_type = iterator_cat_is_random_access_v<test_vec>;
    constexpr bool interface_it_default_ctor = iterator_is_default_constructible_v<test_vec>;
    constexpr bool interface_it_ptr_ctor = iterator_is_constructible_from_uptr_v<test_vec, test_type>;
    constexpr bool interface_it_copy_ctor = iterator_is_copy_constructible_v<test_vec>;
    constexpr bool interface_it_assignable = iterator_is_copy_assignable_v<test_vec>;
    constexpr bool interface_it_preinc = iterator_preincrement_returns_ref_v<test_vec>;
    constexpr bool interface_it_postinc = iterator_postincrement_returns_it_v<test_vec>;
    constexpr bool interface_it_predec = iterator_predecrement_returns_ref_v<test_vec>;
    constexpr bool interface_it_postdec = iterator_postdecrement_returns_it_v<test_vec>;
    constexpr bool interface_it_deref = iterator_deref_returns_u_v<test_vec, test_type>;
    constexpr bool interface_it_memptr = iterator_memptr_returns_uptr_v<test_vec, test_type>;
    constexpr bool interface_it_lt = iterator_less_than_returns_bool_v<test_vec>;
    constexpr bool interface_it_lteq = iterator_lesseq_than_returns_bool_v<test_vec>;
    constexpr bool interface_it_eq = iterator_eq_returns_bool_v<test_vec>;
    constexpr bool interface_it_ineq = iterator_ineq_returns_bool_v<test_vec>;
    constexpr bool interface_it_addassign = iterator_addassign_returns_itref_v<test_vec>;
    constexpr bool interface_it_subassign = iterator_subassign_returns_itref_v<test_vec>;
    constexpr bool interface_it_add = iterator_add_returns_it_v<test_vec>;
    constexpr bool interface_it_sub = iterator_sub_returns_it_v<test_vec>;
    constexpr bool interface_it_subit = iterator_subit_returns_diff_v<test_vec>;

    constexpr bool interface_it =
        interface_iterator && interface_it_difference_type && interface_it_value_type &&
        interface_it_pointer_type && interface_it_reference_type && interface_it_category_type &&
        interface_it_default_ctor && interface_it_ptr_ctor && interface_it_copy_ctor &&
        interface_it_assignable && interface_it_preinc && interface_it_postinc &&
        interface_it_predec && interface_it_postdec && interface_it_deref &&
        interface_it_memptr && interface_it_lt && interface_it_lteq &&
        interface_it_eq && interface_it_ineq && interface_it_addassign &&
        interface_it_subassign && interface_it_add && interface_it_sub &&
        interface_it_subit;

    double score_interface_it = interface_it ? 0.5 : 0.0;
    score += score_interface_it;
    std::cout << "vector::iterator Interface:\n"
        << "::iterator exists: " << check(interface_iterator) << "\n"
        << "::iterator::pointer_type is T*: " << check(interface_it_pointer_type) << "\n"
        << "::iterator::reference_type is T&: " << check(interface_it_reference_type) << "\n"
        << "::iterator::difference_type is ptrdiff_t: " << check(interface_it_difference_type) << "\n"
        << "::iterator::value_type is T: " << check(interface_it_value_type) << "\n"
        << "default constructible: " << check(interface_it_default_ctor) << "\n"
        << "constructible from T*: " << check(interface_it_ptr_ctor) << "\n"
        << "copy constructible: " << check(interface_it_copy_ctor) << "\n"
        << "assignable: " << check(interface_it_assignable) << "\n"
        << "++it returns iterator&: " << check(interface_it_preinc) << "\n"
        << "it++ returns iterator: " << check(interface_it_postinc) << "\n"
        << "--it returns iterator&: " << check(interface_it_predec) << "\n"
        << "it-- returns iterator: " << check(interface_it_postdec) << "\n"
        << "*it returns T&: " << check(interface_it_deref) << "\n"
        << "it-> returns T*: " << check(interface_it_memptr) << "\n"
        << "it1 < it2 returns bool: " << check(interface_it_lt) << "\n"
        << "it1 <= it2 returns bool: " << check(interface_it_lteq) << "\n"
        << "it1 == it2 returns bool: " << check(interface_it_eq) << "\n"
        << "it1 != it2 returns bool: " << check(interface_it_ineq) << "\n"
        << "it += size_t{} returns iterator&: " << check(interface_it_addassign) << "\n"
        << "it -= size_t{} returns iterator&: " << check(interface_it_subassign) << "\n"
        << "it + size_t{} returns iterator: " << check(interface_it_add) << "\n"
        << "it - size_t{} returns iterator: " << check(interface_it_sub) << "\n"
        << "it1 - it2 returns ptrdiff_t: " << check(interface_it_subit) << "\n"
        << "vector::iterator Interface Score:\t\t\t\t" << score_interface_it << " / 0.5\n\n";
    
    constexpr bool interface_begin = begin_returns_it_v<test_vec>;
    constexpr bool interface_end = end_returns_it_v<test_vec>;
    constexpr bool interface_erase = erase_returns_it_v<test_vec>;
    constexpr bool interface_insert = insert_returns_it_v<test_vec>;

    constexpr bool interface_vec_it =
        interface_begin && interface_end && interface_erase && interface_insert;
    double score_interface_vec_it = interface_vec_it ? 0.5 : 0.0;
    score += score_interface_vec_it;
    std::cout << "Vector Iterator Function Interface:\n"
        << "begin() returns iterator: " << check(interface_begin) << "\n"
        << "end() returns iterator: " << check(interface_end) << "\n"
        << "erase(iterator), erase(iterator, iterator) return iterator: " << check(interface_erase) << "\n"
        << "insert(T{}, iterator) returns iterator: " << check(interface_insert) << "\n"
        << "Vector Iterator Function Interface Score:\t\t\t" << score_interface_vec_it << " / 0.5\n\n";
    
    if constexpr(interface_it && interface_vec_it) {
        score += iterator_test<student_vector>();
    }
    else {
        std::cout << "Vector/Iterator functionality test not run due to interface failure: 0 / 2.5\n";
    }
    double prob2_subtotal = score - prob1_subtotal;
    std::cout << "-------------------------------------------------------------------------\n";
    std::cout << "Problem 2 Subtotal:\t\t\t\t\t\t" << prob2_subtotal << " / 3.5\n";
    std::cout << "=========================================================================\n\n";

    std::cout << "\nTotal Score:\t\t\t\t\t\t\t" << score << " / 7.0\n";
    std::cout << "-------------------------------------------------------------------------\n";


    return 0;
}



#endif