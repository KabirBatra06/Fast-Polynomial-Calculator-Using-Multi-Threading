#ifndef POLY_H
#define POLY_H

#include <map>
#include <vector>
#include <cstddef>
#include <unordered_map>

using power = size_t;
using coeff = int;

class polynomial
{

public:
    std::unordered_map<power, coeff> poly;
    /**
     * @brief Construct a new polynomial object that is the number 0 (ie. 0x^0)
     * 
     */
    polynomial();

    /**
     * @brief Construct a new polynomial object from an iterator to pairs of <power,coeff>
     *
     * @tparam Iter 
     *  An iterator that points to a std::pair<power, coeff>
     * @param begin
     *  The start of the container to copy elements from
     * @param end
     *  The end of the container to copy elements from
     */
    template <typename Iter>
    polynomial(Iter begin, Iter end);

    /**
     * @brief Construct a new polynomial object from an existing polynomial object
     * 
     * @param other
     *  The polynomial to copy
     */
    polynomial(const polynomial &other);

    /**
     * @brief Prints the polynomial. 
     * 
     * Only used for debugging, isn't graded.
     *
     */
    void print() const;

    /**
     * Each of these has the standard math definition
     */
    polynomial &operator=(const polynomial &other);
    polynomial operator+(const polynomial &other) const;
    polynomial operator*(const polynomial &other) const;
    bool operator<(const polynomial &other) const;
    bool operator>(const polynomial &other) const;
    bool operator==(const polynomial &other) const;

    /**
     * @brief Returns the degree of the polynomial
     *
     * @return size_t
     *  The degree of the polynomial
     */
    size_t find_degree_of();

    /**
     * @brief Returns a vector that contains the polynomial is canonical form. This
     *        means that the power at index 0 is the largest power in the polynomial,
     *        the power at index 1 is the second largest power, etc.
     *
     *        ie. x^2 + 7x^4 + 1 would be returned as [(4,7),(2,1),(0,1)]
     * 
     *        Note: any terms that have a coefficient of zero aren't returned in 
     *        in the canonical form, with one exception. 
     *        See the above example (there's no x^3 term, so
     *        there's no entry in the vector for x^3)
     * 
     *        The only exception to this is the polynomial 0. If your polynomial is 
     *        just the constant 0 then you would return a single entry of [(0,0)]
     * 
     *        ie. y = 0 would be returned as [(0,0)]    
     *
     * @return std::vector<std::pair<power, coeff>>
     *  A vector of pairs representing the canonical form of the polynomial
     */
    std::vector<std::pair<power, coeff>> canonical_form() const;
};

template <typename Iter>
polynomial::polynomial(Iter begin, Iter end)
{
    poly.clear();
    while(begin != end)
    {
        if(begin->first >= 0 && begin->second != 0)
        {
            poly.insert(*begin);
        }
        begin++;
    }
}


#endif
