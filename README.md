## GOAL
Design and implement a polynomial library to support various operations such as addition, multiplication and comparison. Create a fast polynomial multiplication algorithm using Multithreading

## CODE EXPLAINATION

This code creates a polynomial class that implements addition, multiplication and comparison operators for polynomials. I also implement a copy constructor and assignment operator. 

The member function `canonical_form()` returns a vector that contains the polynomial in canonical form. This means that the power at index 0 is the largest power in the polynomial, the power at index 1 is the second largest power, etc.   ie. x^2 + 7x^4 + 1 would be returned as [(4,7),(2,1),(0,1)]

Any terms that have a coefficient of zero aren't returned in the canonical form, with one exception. The only exception to this is the polynomial 0. If your polynomial is just the constant 0 then you would return a single entry of [(0,0)] ie. y = 0 would be returned as [(0,0)]

I store the entire polynomial in an unordered map. This is because the search, insertion, and removal of elements have average constant-time complexity in an unordered map. This speeds up the multiplication of large polynomials.

## MULTI THREADING

To speed up the multiplication process for very large polynomials I use multithreading. I first choose the larger of the 2 polynomials and break it into smaller chunks. Each chunk is then multiplied with the other polynomial in its own thread. All the outputs from the threads are then collected and added up to give the final result.


