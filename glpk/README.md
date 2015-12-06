### Para chamar o script de testes
*	`./auto.sh [tempo limite de execução de cada arquivo pelo solver]`


### Para converter um arquivo para .dat compativel com o solver
*	`python ./data/convert-data.py ./data/raw/uf175-053.cnf ./data/compatible/uf175-053.dat` 

### Para chamar o solver independentemente:
* *-m [codigo do solver]*
* *-d [dados]*
* *--output [arquivo de saida]*

#### Ex:
*	`glpsol --math -m ./model/solver_max-sat.mod -d ./data/compatible/uf75-034.dat --output ./solution/uf75-034.out`

