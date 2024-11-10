El programa se corre con ```./experiment.o [exp] [mult]```

* `exp` es un int que especifica que experimento correr, entre 0 y 4, donde 0 es correr todos y [1-4]
    corre solo ese experimento.

* `mult` es el multiplicador que usar para correr los experimentos, por enunciado en [0.1, 1]

Tambien se provee un `makefile`, utilizando clang++ por defecto, que ejecuta todos los experimentos utilizando multiplicadores en incrementos de 0.1, desde 0.1 hasta 10