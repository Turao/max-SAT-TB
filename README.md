### Para converter um arquivo para .dat compativel com o solver
*	`python ./data/convert-data.py ./data/raw/uf175-053.cnf ./data/compatible/uf175-053.dat` 

### Para chamar o solver:
* *-m [codigo do solver]*
* *-d [dados]*
* *--output [arquivo de saida]*

#### Ex:
*	`glpsol --math -m ./model/solver_max-sat.mod -d ./data/compatible/uf75-034.dat --output ./solution/uf75-034.out`

