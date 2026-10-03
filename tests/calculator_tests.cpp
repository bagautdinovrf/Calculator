#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>

#include "calculator.h"
#include "mymath.h"

namespace {
int checks = 0;
int failures = 0;

void checkValue(Calculator& calculator, const char* expression, double expected)
{
    ++checks;
    try {
        const double actual = calculator.calc(expression);
        if (!std::isfinite(actual) ||
            std::abs(actual - expected) > 1e-12 * std::max(1.0, std::abs(expected))) {
            ++failures;
            std::cerr << expression << ": expected " << expected << ", got " << actual << '\n';
        }
    } catch (const std::exception& error) {
        ++failures;
        std::cerr << expression << ": unexpected exception: " << error.what() << '\n';
    }
}

template<typename Action>
void checkError(const char* description, Action action)
{
    ++checks;
    try {
        action();
        ++failures;
        std::cerr << description << ": expected std::runtime_error\n";
    } catch (const std::runtime_error&) {
        // The public API promises this exception type for invalid expressions.
    } catch (...) {
        ++failures;
        std::cerr << description << ": wrong exception type\n";
    }
}
}

int main()
{
    Calculator calculator;
    const struct {
        const char* expression;
        double expected;
    } values[] = {
        {"0", 0}, {"123", 123}, {".10", 0.1}, {"(1.)", 1},
        {"2.0 ^ 2. ^ 3.0", 256}, {"13. / 2.0", 6.5},
        {"((4. - 1.0) / ((2.) - 1.0))", 3},
        {"1+(2+3)", 6}, {"10-(2+3)", 5}, {"2^(1+2)", 8},
        {"1+(2*(3+4))", 15}, {"1+(2-(3-4))", 4},
        {"1+(8/(2+2))", 3}, {"2+3*4", 14}, {"15*15/5*5", 225},
        {"8/4/2", 1}, {"10-3-2", 5},
        {"2^3^2", 512}, {"(2^3)^2", 64}, {"2^(3^2)", 512},
        {"(2^3)^(2)", 64}, {"2^(3)^2", 512}, {"2^3*2", 16},
        {"2*3^2", 18}, {"(2^2)^(1+2)", 64}, {"2^0", 1},
        {"2^-3", 0.125}, {"2^--3", 8},
        {"-2", -2}, {"--2", 2}, {"---2", -2}, {"----2", 2},
        {"2*-3", -6}, {"1+--2", 3}, {"1+-2", -1},
        {"2---3", -1}, {"2*--3", 6}, {"2*(-(3+4))", -14},
        {"-(1+2)", -3}, {"--(1+2)", 3}, {"1+-(2+3)", -4},
        {"~2", -2}, {"~~2", 2}, {"2*~3", -6},
        // Keep the existing precedence: unary minus binds tighter than '^'.
        {"-2^2", 4}, {"-(2^2)", -4}, {"3*-2^2", 12},
        {"2+3 ", 5}, {"   2+3   ", 5}, {"2+3\t\r\n", 5},
        {"\t( 2 + 3 )\n", 5}, {"2 +\n 3", 5},
        {"0.12345678901234567890", 0.12345678901234567890},
        {"1.12345678901234567890", 1.12345678901234567890},
        {"0.000000000001", 1e-12},
        {"2.5 * (-22 + 2 ^ 2 ^ 3) * (3 - 1)", 1170},
        {"3 + 40 * 2 / (1 - 5)^2^3", 3.001220703125}
    };
    for (const auto& value : values)
        checkValue(calculator, value.expression, value.expected);

    const char* errors[] = {
        "", " ", "\t\n", "1+", "+1", "()", "-", "1/",
        "*2", "/2", "^2", "2**3", "2+*3", "2^", "2^^3", "2-",
        "1 2", "1.2.3", ".", "..", "1..", ".1.2", "(1 2)",
        "2(3)", "(2)3", "(2)(3)", "(2", "2)", ")(2(", "(1+)",
        "2~3", "abc", "2e3", "2,3", "1/0", "0/0", "2/(1-1)",
        "(-2)^.5", "0^-1", "10^1000"
    };
    for (const auto* expression : errors) {
        checkError(expression, [&] { calculator.calc(expression); });
        // A failed call must not leave state affecting later evaluations.
        checkValue(calculator, "1+(2+3)", 6);
        checkValue(calculator, "--2", 2);
    }
    checkError("null expression", [&] { calculator.calc(nullptr); });
    const std::string oversized_number(400, '9');
    checkError("number overflow", [&] { calculator.calc(oversized_number.c_str()); });
    const std::string large_number(200, '9');
    const std::string product = large_number + "*" + large_number;
    checkError("arithmetic overflow", [&] { calculator.calc(product.c_str()); });

    const char* invalid_numbers[] = {"", ".", "1.2.3", "1a", "2e3"};
    for (const auto* number : invalid_numbers)
        checkError(number, [&] { MyMath::my_atod(number); });
    checkError("null number", [] { MyMath::my_atod(nullptr); });

    // Metamorphic checks exercise nested stack depths and grouping invariance.
    for (int a = 1; a <= 6; ++a) {
        for (int b = 1; b <= 6; ++b) {
            for (int c = 1; c <= 6; ++c) {
                const std::string sa = std::to_string(a);
                const std::string sb = std::to_string(b);
                const std::string sc = std::to_string(c);
                checkValue(calculator, (sa + "+(" + sb + "+" + sc + ")").c_str(), a + b + c);
                checkValue(calculator, (sa + "*(" + sb + "-" + sc + ")").c_str(), a * (b - c));
                checkValue(calculator, (sa + "/(" + sb + "+" + sc + ")").c_str(),
                           static_cast<double>(a) / (b + c));
                checkValue(calculator, (sa + "*--(" + sb + "+" + sc + ")").c_str(), a * (b + c));
            }
        }
    }
    const std::string nested = std::string(1000, '(') + "1+2" + std::string(1000, ')');
    checkValue(calculator, nested.c_str(), 3);
    const std::string many_minuses = std::string(1001, '-') + "2";
    checkValue(calculator, many_minuses.c_str(), -2);
    Calculator another;
    checkValue(another, "2^3^2", 512);

    std::cout << checks << " checks, " << failures << " failures\n";
    return failures == 0 ? 0 : 1;
}
