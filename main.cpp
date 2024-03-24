#include <iostream>
#include <chrono>
#include <optional>
#include <vector>

#include "poly.h"

std::optional<double> poly_test(polynomial& p1,
                                polynomial& p2,
                                std::vector<std::pair<power, coeff>> solution)

{
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    polynomial p3 = p1 * p2;

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    p3.print();

    if (p3.canonical_form() != solution)
    {
        return std::nullopt;
    }

    return std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
}

int main()
{
    /** We're doing (x+1)^2, so solution is x^2 + 2x + 1*/
    std::vector<std::pair<power, coeff>> solution = {{2,1}, {1,2}, {0,1}};

    /** This holds (x+1), which we'll pass to each polynomial */
    std::vector<std::pair<power, coeff>> poly_input1 = {{1,1}, {0,1}};
    std::vector<std::pair<power, coeff>> poly_input2 = {{10,1}, {4,27}};
    std::vector<std::pair<power, coeff>> poly_input3 = {{2,-1}, {1,-2}, {0,-1}};
    std::vector<std::pair<power, coeff>> poly_input4 = {{3,1}, {1,2}, {0,1}};
    std::vector<std::pair<power, coeff>> poly_input5 = {{4,1}, {0,2}};

    polynomial p1(poly_input1.begin(), poly_input1.end());
    polynomial p2(poly_input2.begin(), poly_input2.end());
    polynomial p3(poly_input3.begin(), poly_input3.end());
    polynomial p4(poly_input4.begin(), poly_input4.end());
    polynomial p5(poly_input5.begin(), poly_input5.end());
    polynomial p6;
    polynomial result;

    // ADDITION CHECK
    std::cout<<"ADDITION CHECK:\n";
    result = p4 + p1;
    result.print();

    // MULTIPLICATION CHECK
    std::cout<<"\nMULTIPLICATION CHECK:\n";
    result = p1 * p6;
    result.print();

    // COMPARISON CHECK
    int comp = p4 == p5;
    std::cout<< "\nComparison check: " << comp << std::endl;

    // DEGREE CHECK
    std::cout<<"\nDEGREE CHECK:\n";
    std::cout << "Degree: " << result.find_degree_of() << std::endl;
    std::cout << "Degree: " << p1.find_degree_of() << std::endl;
    std::cout << "Degree: " << p4.find_degree_of() << std::endl;

    // CANONICAL CHECK
    std::cout<<"\nCANONICAL CHECK:\n";
    std::vector<std::pair<power, coeff>> canonical = result.canonical_form();

    for (auto i: canonical)
        std::cout << i.first << ' '<< i.second <<"\n";

    // std::optional<double> result = poly_test(p1, p2, solution);

    // if (result.has_value())
    // {
    //     std::cout << "Passed test, took " << result.value()/1000 << " seconds" << std::endl;
    // } 
    // else 
    // {
    //     std::cout << "Failed test" << std::endl;
    // }
}