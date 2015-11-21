#!/usr/bin/python
import sys

try:
    f = open(sys.argv[1], "r")
except:
    sys.exit("ERROR. Can't read supplied input filename.")

# find how many clauses and variables
line = f.readline()
while(line[0] != 'p'):
	line = f.readline()

content = line.split()
variables = int(content[2])
clauses = int(content[3])


print "content: ", content
print "param N: ", variables
print "param M: ", clauses


# read each clause
clauses_list = []

for c in xrange(clauses):
	line = f.readline()
	if(line):
		var_list = line.split()
		var_list = [int(i) for i in var_list]
		clauses_list.append(var_list)		
f.close()

# fill variable present and not variable
variable_present = []
not_variable = []


for c in clauses_list:
	present_var = []
	not_var = []
	for var in xrange(1, variables+1):
		# set 1 if var variable is present in c clause to present_var
		# set 1 if !var to not_var
		if(var in c):
			present_var.append(1)
			not_var.append(0)
		elif ((var*-1) in c):
				not_var.append(1)
				present_var.append(1)
		else:
			present_var.append(0)
			not_var.append(0)

	variable_present.append(present_var)
	not_variable.append(not_var)


# write a compatible glpk data file
try:
    out = open(sys.argv[2], "w")
except:
    sys.exit("ERROR. Can't read supplied output filename.")
out.write("data;\n")
out.write("param C := " + str(clauses) + ";\n")
out.write("param V := " + str(variables) + ";\n")

vars_str = ' '.join(str(e) for e in range(1,76))
out.write("param variable_present (tr) : " + vars_str + " := \n")

for c in range(len(clauses_list)):
	out.write('\t' + str(c+1) + '\t' + ' '.join(str(e) for e in variable_present[c]) + '\n')
out.write(";\n\n")

out.write("param not_variable (tr) : " + vars_str + " := \n")
for c in range(len(clauses_list)):
	out.write('\t' + str(c+1) + '\t' + ' '.join(str(e) for e in not_variable[c]) + '\n')
out.write(";\n")
out.write("end;\n\n")
out.close()

print "done! :)"


