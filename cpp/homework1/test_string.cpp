#include "student_string.h"

#include <algorithm>
#include <cassert>
#include <concepts>
#include <iostream>
#include <locale>
#include <random>
#include <string>
#include <string.h>


using student_string = student_std::string;
using std_string = std::string;

namespace {


template <typename T>
concept string_interface =
    std::default_initializable<T> &&
    std::copy_constructible<T> &&
    std::constructible_from<T, const char*> &&
    requires (T str, const T cstr) {
        { str[0] }      -> std::same_as<char&>;
        { cstr[0] }     -> std::same_as<const char&>;

        { (str = cstr) }    -> std::same_as<T&>;
        { (str += cstr) }   -> std::same_as<T&>;

        { str.to_upper() }                          -> std::same_as<void>;
        { str.to_lower() }                          -> std::same_as<void>;
        { str.strcopy(cstr) }                       -> std::same_as<void>;
        { cstr.equals(cstr) }                       -> std::same_as<bool>;
        { cstr.equals_ignore_case(cstr) }           -> std::same_as<bool>;
        { str.trim() }                              -> std::same_as<void>;
        { cstr.is_alphabetic() }                    -> std::same_as<bool>;
        { cstr.get_c_str() }                        -> std::same_as<const char*>;
        { str.strcat(cstr) }                        -> std::same_as<void>;
        { cstr.get_strlen() }                       -> std::same_as<int>;
    };

    std::string random_string(auto& rng) {
        std::uniform_int_distribution<std::size_t> length_dist(20, 40);
        std::uniform_int_distribution<int> char_dist(' ', '~');

        std::size_t length = length_dist(rng);
        std::string s;
        s.reserve(length);
        for (std::size_t i = 0; i < length; ++i)
            s.push_back(static_cast<char>(char_dist(rng)));
        return s;
    }

    char random_char(auto& rng) {
        std::uniform_int_distribution<int> char_dist(' ', '~');
        return static_cast<char>(char_dist(rng));
    }

    bool operator==(student_string const& a, std_string const& b) {
        return    a.get_strlen() == b.size()
               && strcmp(a.get_c_str(), b.c_str()) == 0;
    }

    
    std::string trim(const std::string& s) {
        auto not_space = [](unsigned char ch) { return ch != ' '; };

        auto start = std::find_if(s.begin(), s.end(), not_space);
        auto end   = std::find_if(s.rbegin(), s.rend(), not_space).base();

        if (start >= end) return {};
        return std::string(start, end);
    }

}

int main() {

    if constexpr (!string_interface<student_string>) {
        std::cout << "student_std::string does not satisfy specified interface.\n"
                  << "test_string score: 0 / 2.5\n";
    }
    else
    {
        double score = 0.5;
        std::cout << "Interface correctness:\t\t\t\t0.5 / 0.5\n";

        std::default_random_engine rng{0};
        bool constructor_correctness = true;
        student_string zero;
        if (zero.get_strlen() != 0 || zero.get_c_str()[0] != '\0')
            constructor_correctness = false;
        if (!constructor_correctness)
        {
            std::cout << "Default constructor failure, expected \"\" (0), got \""
                      << zero.get_c_str() << "\" (" << zero.get_strlen() << ").\n";
        }
        for(int i = 0; i < 10; ++i)
        {
            bool case_correct = true;
            auto std_str = random_string(rng);
            student_string str1(std_str.c_str());
            student_string str2(str1);
            student_string str3 = str2;
            if (str1 != std_str)
                case_correct = false;
            if (str2 != std_str)
                case_correct = false;
            if (str3 != std_str)
                case_correct = false;
            if ( !case_correct )
            {
                std::cout << "Constructor failure for \""<< std_str << "\" (" << std_str.size() << ").\n";
                std::cout << "Constructed \""<< str1.get_c_str() << "\"  (" << str1.get_strlen() << ") from char*.\n";
                std::cout << "Copy constructed \""<< str2.get_c_str() << " (" << str2.get_strlen() << ") \".\n";
                std::cout << "Constructed \""<< str3.get_c_str() << "\"  (" << str3.get_strlen() << ") from assignment.\n";
            }
            constructor_correctness = constructor_correctness && case_correct;
        }
        std::cout << "Constructor, operator=, get_strlen, get_c_str:\t"
                  << (constructor_correctness ? 0.5 : 0) << " / 0.5\n";
        if (constructor_correctness)
            score += 0.5;

        bool operator_correctness = true;
        for(int i = 0; i < 10; ++i)
        {
            bool case_correct = true;
            const auto std_str1 = random_string(rng);
            const auto std_str2 = random_string(rng);
            auto std_cat = std_str1 + std_str2;
            const student_string str1(std_str1.c_str());
            const student_string str2(std_str2.c_str());
            student_string cat1;
            cat1 += str1;
            cat1 += str2;
            student_string cat2(str1);
            cat2.strcat(str2);

            char rc = random_char(rng);
            std_cat[2] = rc;
            cat1[2] = rc;
            cat2[2] = rc;

            const student_string cat1_const = cat1;
            const student_string cat2_const = cat2;

            for (int i = 0; i < cat1_const.get_strlen(); ++i)
            {
                case_correct = case_correct && (cat1_const[i] == std_cat[i]);
                case_correct = case_correct && (cat2_const[i] == std_cat[i]);
            }
            case_correct = case_correct && (cat1_const == std_cat);
            case_correct = case_correct && (cat2_const == std_cat);
            if ( !case_correct )
            {
                std::cout << "strcat, operator+= or operator[] failure for \"" 
                          << std_str1 << "\" (" << std_str1.size() << ") + \""
                          << std_str2 << "\" (" << std_str2.size() << ").\n";
                std::cout << "Got \"" << cat1_const.get_c_str() << "\" (" << cat1_const.get_strlen() << ").\n";
                std::cout << "Got \"" << cat2_const.get_c_str() << "\" (" << cat2_const.get_strlen() << ").\n";
            }
            operator_correctness = operator_correctness && case_correct;
        }
        std::cout << "strcat, operator+=, operator[]:\t\t\t"
                  << (operator_correctness ? 0.5 : 0) << " / 0.5\n";
        if (operator_correctness)
            score += 0.5;

        bool alphabetic_correctness = true;
        std::locale loc("C");
        const auto isalpha = [&loc](char c) { return std::isalpha<char>(c, loc); };
        for (int i = 0; i < 10; ++i)
        {
            bool case_correct = true;
            const auto std_str = random_string(rng);
            std_string std_str_alpha;
            std::copy_if(std_str.begin(), std_str.end(),
                         std::back_inserter(std_str_alpha), isalpha);
            std_string std_str_upper = std_str;
            for (char& c : std_str_upper)
                c = std::toupper(c, loc);
            std_string std_str_lower = std_str;
            for (char& c : std_str_lower)
                c = std::tolower(c, loc);
            const student_string str(std_str.c_str());
            const student_string str_alpha(std_str_alpha.c_str());
            student_string str_upper(str);
            str_upper.to_upper();
            student_string str_lower(str);
            str_lower.to_lower();

            case_correct = case_correct && (str_upper == std_str_upper);
            case_correct = case_correct && (str_lower == std_str_lower);
            case_correct = case_correct && (str_alpha == std_str_alpha);
            case_correct = case_correct && str_alpha.is_alphabetic();
            case_correct = case_correct &&
                (str.is_alphabetic() == std::all_of(std_str.begin(), std_str.end(), isalpha));
            case_correct = case_correct && str_upper.equals_ignore_case(str_lower);
            case_correct = case_correct &&
                (str_upper.equals(str_lower) == (std_str_upper == std_str_lower));

            if ( !case_correct )
            {
                std::cout << "to_upper, to_lower or is_alphabetic failure for \"" 
                          << std_str << "\" (" << std_str.size() << ")\n";
                std::cout << "Got to_lower: \"" << str_lower.get_c_str() << "\" (" << str_lower.get_strlen() << ", should be " << std_str_lower.size() << ")\n"
                          << "Got to_upper: \"" << str_upper.get_c_str() << "\" (" << str_upper.get_strlen() << ", should be " << std_str_upper.size() << ")\n"
                          << "Got is_alphabetic: " << (str.is_alphabetic() ? "true" : "false") << "\n"
                          << "Got is_alphabetic of \"" << str_alpha.get_c_str() << " (" << str_alpha.get_strlen() << ", should be " << std_str_alpha.size() << ")\": " 
                          << (str_alpha.is_alphabetic() ? "true" : "false") << "\n";
            }
            alphabetic_correctness = alphabetic_correctness && case_correct;
        }
        std::cout << "to_upper, to_lower, is_alphabetic:\t\t"
                  << (alphabetic_correctness ? 0.5 : 0) << " / 0.5\n";
        if (alphabetic_correctness)
            score += 0.5;
        
        bool trim_correctness = true;
        for (int i = 0; i < 10; ++i)
        {
            bool case_correct = true;
            std::uniform_int_distribution<> int_dist(0,5);
            const auto std_str = std_string(int_dist(rng), ' ')
                + random_string(rng) + std_string(int_dist(rng), ' ');
            student_string str(std_str.c_str());
            const auto std_str_trimmed = trim(std_str);
            str.trim();

            case_correct = case_correct && (str == std_str_trimmed);

            if ( !case_correct )
            {
                std::cout << "trim failure for \"" << std_str << "\"\n";
                std::cout << "Got: \"" << str.get_c_str() << "\"\n";
            }
            trim_correctness = trim_correctness && case_correct;
        }
        std::cout << "trim:\t\t\t\t\t\t"
                  << (trim_correctness ? 0.5 : 0) << " / 0.5\n";
        if (trim_correctness)
            score += 0.5;
        std::cout << "test_string subtotal:\t\t\t\t" << score << " / 2.5\n";
    }
    return 0;
}
