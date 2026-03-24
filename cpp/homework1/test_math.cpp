#include "student_math.h"

#include <cassert>
#include <cmath>
#include <concepts>
#include <iostream>
#include <numbers>
#include <random>

template <typename T>
concept double_to_double = std::same_as<T, double(double)>;

bool matches(double angle, double student_output, double std_output, const char* label) {
    bool out =
        (std::abs(student_output) >=  1e10 && std::abs(std_output) >=  1e10) ||
        std::abs(student_output - std_output) <= 1e-3 ||
        std::abs( (student_output - std_output) / std_output) <= 0.001;
    if (!out)
        std::cout << "Mismatch for function " << label << " with x = " << angle 
                  << ", student output = " << student_output
                  << ", standard output = " << std_output << std::endl;
    return out;
}

int main() {
    constexpr bool required_interface =
           double_to_double<decltype(student_std::sin)>
        && double_to_double<decltype(student_std::sin_deg)>
        && double_to_double<decltype(student_std::cos)>
        && double_to_double<decltype(student_std::cos_deg)>
        && double_to_double<decltype(student_std::tan)>
        && double_to_double<decltype(student_std::tan_deg)>
        && double_to_double<decltype(student_std::cot)>
        && double_to_double<decltype(student_std::cot_deg)>;

    if constexpr (!required_interface) {
        std::cout << "Functions must take and return one double by value and "
                  << "follow the specified naming and namespace.\n"
                  << "Problem 1 score: 0 / 2.5\n";
    }
    else
    {
        double score = 0.5;
        std::cout << "Interface correctness:\t\t0.5 / 0.5\n";

        const double pi = std::numbers::pi;
        auto rad = [pi](double deg) { return deg * pi / 180.; };

        bool all_match = true;
        for (double x : {-4 * pi, -3 * pi, -2 * pi, -pi, 0., pi, 2 * pi, 3 * pi}) {
            all_match = all_match && matches(x, student_std::sin(x), std::sin(x), "sin");
            all_match = all_match && matches(x, student_std::cos(x), std::cos(x), "cos");
            all_match = all_match && matches(x, student_std::tan(x), std::tan(x), "tan");
            all_match = all_match && matches(x, student_std::cot(x), 1 / std::tan(x), "cot");
        }
        if (all_match) {
            score += 0.5;
        }
        std::cout << "Special case correctness (rad):\t"
                  << (all_match ? 0.5 : 0.) << " / 0.5\n";
        all_match = true;
        for (double x : {-3 * 180., -2 * 180., -180., 0., 180., 2 * 180., 3 * 180.}) {
            all_match = all_match && matches(x, student_std::sin_deg(x), std::sin(rad(x)), "sin_deg");
            all_match = all_match && matches(x, student_std::cos_deg(x), std::cos(rad(x)), "cos_deg");
            all_match = all_match && matches(x, student_std::tan_deg(x), std::tan(rad(x)), "tan_deg");
            all_match = all_match && matches(x, student_std::cot_deg(x), 1 / std::tan(rad(x)), "cot_deg");
        }
        if (all_match) score += 0.5;
        std::cout << "Special case correctness (deg):\t"
                  << (all_match ? 0.5 : 0.) << " / 0.5\n";
        all_match = true;
        std::default_random_engine rng (0);
        std::uniform_real_distribution<> rad_dist(-10., 10.);
        for(int i = 0; i < 20; ++i)
        {
            double x = rad_dist(rng);
            all_match = all_match && matches(x, student_std::sin(x), std::sin(x), "sin");
            all_match = all_match && matches(x, student_std::cos(x), std::cos(x), "cos");
            all_match = all_match && matches(x, student_std::tan(x), std::tan(x), "tan");
            all_match = all_match && matches(x, student_std::cot(x), 1 / std::tan(x), "cot");
        }
        if (all_match) {
            score += 0.5;
        }
        std::cout << "Random case correctness (rad):\t"
                  << (all_match ? 0.5 : 0.) << " / 0.5\n";
        all_match = true;
        std::uniform_real_distribution<> deg_dist(-1800., 1800.);
        for(int i = 0; i < 20; ++i)
        {
            double x = deg_dist(rng);
            all_match = all_match && matches(x, student_std::sin_deg(x), std::sin(rad(x)), "sin_deg");
            all_match = all_match && matches(x, student_std::cos_deg(x), std::cos(rad(x)), "cos_deg");
            all_match = all_match && matches(x, student_std::tan_deg(x), std::tan(rad(x)), "tan_deg");
            all_match = all_match && matches(x, student_std::cot_deg(x), 1 / std::tan(rad(x)), "cot_deg");
        }
        if (all_match) {
            score += 0.5;
        }
        std::cout << "Random case correctness (deg):\t"
                  << (all_match ? 0.5 : 0.) << " / 0.5\n";
        std::cout << "test_math.cpp subtotal:\t\t" << score << " / 2.5\n";
    }
    return 0;
}
