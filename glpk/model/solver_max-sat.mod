/* clauses */
param C integer;

/* variables */
param V integer;


/* sets */
set Clauses := 1..C;
set Variables := 1..V;


/* input */

param variable_present{i in Variables, j in Clauses} >= 0 binary default 0;
param not_variable{i in Variables, j in Clauses} >= 0 binary default 0;

/* other */
var clause_value{i in Clauses} >= 0 binary;
var variable_value{i in Variables} >= 0 binary;

/* the formula */
maximize valid_clauses: sum{i in Clauses} clause_value[i];

s.t. clause_value_restriction{j in Clauses}:
	sum{i in Variables} (
		/* set to 1 if the variable is PRESENT and TRUE */
		(variable_present[i, j] * variable_value[i]) - 
		/* then, we test if there is a logical NOT op */
		/* if true (1), we must subtract 1 in order to set this to false (0) */
		/* if false (0), we must add 1 so we can have it true (1) */
		(variable_present[i, j] * not_variable[i, j] * (variable_value[i] - 1) )
	) >= clause_value[j];

end;
