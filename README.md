## GOAL
Design and implement a polynomial library to support various operations such as addition, multiplication
and comparison
Create a fast polynomial multiplication algorithm using Multithreading

## CODE EXPLAINATION

This code creates a polynomial class that impliments addition, multiplication and comparision operators for polynomials. The member function `canonical_form()` returns a vector that contains the polynomial is canonical form.\
This means that the power at index 0 is the largest power in the polynomial, the power at index 1 is the second largest power, etc.\
ie. x^2 + 7x^4 + 1 would be returned as [(4,7),(2,1),(0,1)] \
any terms that have a coefficient of zero aren't returned in the canonical form, with one exception. The only exception to this is the polynomial 0. If your polynomial is just the constant 0 then you would return a single entry of [(0,0)]\
ie. y = 0 would be returned as [(0,0)]   
