## GOAL
Design and implement a polynomial library to support various operations such as addition, multiplication
and comparison
Create a fast polynomial multiplication algorithm using Multithreading

## CODE EXPLAINATION

This code creates a polynomial class that impliments addition, multiplication and comparision operators for polynomials. \\

The member function `canonical_form()` returns a vector that contains the polynomial is canonical form. This means that the power at index 0 is the largest power in the polynomial, the power at index 1 is the second largest power, etc.   ie. x^2 + 7x^4 + 1 would be returned as [(4,7),(2,1),(0,1)] \\

Any terms that have a coefficient of zero aren't returned in the canonical form, with one exception. The only exception to this is the polynomial 0. If your polynomial is just the constant 0 then you would return a single entry of [(0,0)] ie. y = 0 would be returned as [(0,0)]\\

I store the entire polynomial in a unordered map. This is because search, insertion, and removal of elements have average constant-time complexity in an unordered map. This speeds up the multiplication for large polynomials. \\

## MULTI THREADING

To speed up the multiplication process for very large polynomials I use multithreading. I first choose the larger of the 2 polynomials and and break it up into smaller chuncks. Each chunck is then multiplied with the other polynomial in its own thread. All the outputs from the threads are then collected and added up to give the final result.


