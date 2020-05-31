AutomataProject
The function that creates an automat by a reggex expression does not wor whit nested brakets and
also your expression must be surrounded by brakets.
To create an automat whit a more complex regex expresion you need to create the automats of the more
simple expresions and then use the functions for concatenation, union, positive wrap and I have also added the function for
Kleene's star
Examplses:
(a+b) // will work
(a+b)* // will work
(a.c+b)* // will work
(a*+b) // will work
((a+s)+b)// will not work
(a+s)+(s+b)// will not work
