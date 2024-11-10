El programa se corre con ```./experiment.o [exp] [mult]```

* `exp` es un int que especifica que experimento correr, entre 0 y 4, donde 0 es correr todos y [1-4]
    corre solo ese experimento.

* `mult` es el multiplicador que usar para correr los experimentos, por enunciado en [0.1, 1]

Tambien se provee un `makefile`, utilizando clang++ por defecto.
El Makefile por defecto ejecuta todos los experimentos diez veces, partiendo con un multiplicador de 0.1 e incrementando por cada ejecución hasta `mult=1`.

Se puede ejecutar `make x EXP=y` para correr el experimento `y` con multiplicador $\frac{x}{10}$, o se puede omitir el argumento x para correr el experimento especificado con los 10 incrementos de multiplicador.