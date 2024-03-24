#include "poly.h"
#include <stdexcept>  
#include <iostream>
#include <thread>

void multiplier(std::unordered_map<power, coeff>& p1, polynomial& p2, polynomial& temp_result)
{
    std::unordered_map<power, coeff>::iterator p1_start = p1.begin();
    std::unordered_map<power, coeff>::iterator p1_end = p1.end();

    std::unordered_map<power, coeff>::iterator p2_start = p2.poly.begin();
    std::unordered_map<power, coeff>::iterator p2_end = p2.poly.end();

    std::unordered_map<power, coeff>::iterator itr1;
    std::unordered_map<power, coeff>::iterator itr2;

    for (itr1 = p1_start; itr1 != p1_end; itr1++)
    {
        for (itr2 = p2_start; itr2 != p2_end; itr2++)
        {
            temp_result.poly[itr1->first + itr2->first] += itr1->second * itr2->second;
        }
    }
    
}

polynomial::polynomial()
{
    poly.clear();
    poly.insert({0,0});
}

polynomial::polynomial(const polynomial &other)
{
    poly = other.poly;
}

polynomial &polynomial::operator=(const polynomial &other)
{
    if(this == &other)
    {
        return *this;
    }

    poly = other.poly;

    return *this;
}

polynomial polynomial::operator+(const polynomial &other) const
{
    polynomial retval(*this); 

    for (const auto [power, coeff] : other.poly)
	{
	    retval.poly[power] += coeff;

        if(retval.poly[power] == 0)
        {
            retval.poly.erase(power);
        }
    }
    
    if(retval.poly.empty())
    {
        retval.poly.insert({0,0});
    }

    return retval;
}

polynomial polynomial::operator*(const polynomial &other) const
{

    std::vector<std::thread> all_threads; 
    std::vector<polynomial> temp_results;

    polynomial poly_used;
    polynomial poly_other;

    int size_used = 0;

    int num_threads = 8;

    if(poly.size() > other.poly.size())
    {
        poly_used = *this;
        poly_other = other;
        size_used = poly.size();
        
    }
    else
    {
        poly_used = other;   
        poly_other = *this;
        size_used = other.poly.size();
    }

    if(size_used < num_threads)
    {
        num_threads = size_used;
    }

    temp_results.resize(num_threads);

    std::vector<std::unordered_map<power, coeff>> chunckz;
    chunckz.resize(num_threads);

    int counter = 0;

    for (const auto [power, coeff]: poly_used.poly)
    {
        chunckz.at(counter % num_threads)[power] = coeff;
        counter++;
    }


    for(int i = 0; i < num_threads; i++)
    {
        all_threads.push_back(std::thread(multiplier, std::ref(chunckz.at(i)), std::ref(poly_other), std::ref(temp_results[i])));
    }

    for(int i = 0; i < num_threads; i++)
    {
        all_threads[i].join();
    }
    all_threads.clear();

    polynomial final_ans;

    for(int k = 0; k < num_threads; k++)
    {
        final_ans = final_ans + temp_results[k];
    }

    return final_ans;

}

bool polynomial::operator<(const polynomial &other) const
{
    std::map<power, coeff> sorted_poly(poly.begin(), poly.end());
    std::map<power, coeff> other_sorted_poly(other.poly.begin(), other.poly.end());

    std::map<power, coeff>::const_reverse_iterator val = sorted_poly.rbegin();
    std::map<power, coeff>::const_reverse_iterator val2 = other_sorted_poly.rbegin();
    
    int deg1 = val->first;
    int deg2 = val2->first;

    if(deg1 < deg2)
    {
        return true;
    }
    else if (deg1 > deg2)
    {
        return false;
    }

    for(; val != sorted_poly.rend(); val++)
    {
        try
        {
           if(val->second < other.poly.at(val->first))
           {
                return true;
           }
           else if(val->second > other.poly.at(val->first))
           {
                return false;
           }
        }
        catch(const std::out_of_range & oor)
        {
            return false;
        }
    }

    return false;

}

bool polynomial::operator>(const polynomial &other) const
{
    std::map<power, coeff> sorted_poly(poly.begin(), poly.end());
    std::map<power, coeff> other_sorted_poly(other.poly.begin(), other.poly.end());

    std::map<power, coeff>::const_reverse_iterator val = sorted_poly.rbegin();
    std::map<power, coeff>::const_reverse_iterator val2 = other_sorted_poly.rbegin();
    
    int deg1 = val->first;
    int deg2 = val2->first;

    if(deg1 > deg2)
    {
        return true;
    }
    else if (deg1 < deg2)
    {
        return false;
    }

    for(; val != sorted_poly.rend(); val++)
    {
        try
        {
           if(val->second > other.poly.at(val->first))
           {
                return true;
           }
           else if(val->second < other.poly.at(val->first))
           {
                return false;
           }
        }
        catch(const std::out_of_range & oor)
        {
            return true;
        }
    }

    return false;

}

bool polynomial::operator==(const polynomial &other) const
{
    std::map<power, coeff> sorted_poly(poly.begin(), poly.end());

    std::map<power, coeff>::const_reverse_iterator val;

    for(val = sorted_poly.rbegin(); val != sorted_poly.rend(); val++)
    {
        try
        {
           if(other.poly.at(val->first) != val->second)
           {
                return false;
           }
        }
        catch(const std::out_of_range & oor)
        {
            return false;
        }
    }

    return true;

}

size_t polynomial::find_degree_of() 
{
    std::map<power, coeff> sorted_poly(poly.begin(), poly.end());

    std::map<power, coeff>::const_reverse_iterator val = sorted_poly.rbegin();
    return ((val)->first);
}

std::vector<std::pair<power, coeff>> polynomial::canonical_form() const
{
    std::map<power, coeff> sorted_poly(poly.begin(), poly.end());

    std::vector<std::pair<power, coeff>> retval;

    std::map<power, coeff>::const_reverse_iterator itr;

    for(itr = sorted_poly.rbegin(); itr != sorted_poly.rend(); itr++)
    {
        retval.push_back(*itr);
    }

    return retval;
}

void polynomial::print() const
{
    if(poly.empty())
    {
        return;
    }

    std::map<power, coeff> sorted_poly(poly.begin(), poly.end());
    std::map<power, coeff>::const_reverse_iterator itr;

    for(itr = sorted_poly.rbegin(); itr != sorted_poly.rend(); itr++)
    {
        std::cout<<"Power: "<<itr->first<<" Coeff: "<<itr->second<<std::endl;
    }
}