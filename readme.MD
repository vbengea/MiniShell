* Known issues:

    - Una vez el proceso llega a pipex, no hay comunicación con el proceso original "selector" lo que hace que si uno de los elementos del pipe es una subshell (e.g (ls -l && echo 1) | ls -l | cat -e), se pierda en el pipeline.

    - El comando "cat main.c" muestra el archivo pero da error tambien como si tratara de ejecutar "cat" sin argumento. Este bug es inconsistente pues al probar en Ubuntu no hay errores.

    - El comando "cat -e | ls -l && (cd / && ls -l)" tiene un comportamiento no convencionar cuando cat -e espera entrada del standard input. Si se ejecuta "cat | ls -l && (cd / && ls -l)" sin la opcion de cat "-e" funciona de manera standard.


* Solved issues:

    - Implementamos el nodo NODE_REDIRECT.

    - Cuando ejectumos "ls -l | cat -e | cat -e | cat -e" el resultado es el correcto pero se imprimen unos caracteres extra en la línea del prompt.

    - El comando "(cd / && ls -l) && ls -l" realiza el cambio del directorio pero el cambio se ve desde fuera del paréntesis, lo que significa que o no se está ejecutando en una subshell o ambos se ejecutan en el mismo nivel de proceso.


* Probelms:

    - Actual tokenizer doesn't support multiple redirections.
    - Proposed solution:
        -Build a re-tokenizer on top of the actual one and update the AST structure.

        - A command like: cat < input.txt | grep "error" >> output.txt && echo "done" would have a structure like:

        NODE_AND
       /        \
   NODE_PIPE   NODE_CMND ("echo")
   /       \          ├── args: ["echo", "done"]
NODE_CMND  NODE_CMND  └── redirs: NULL
 ("cat")   ("grep")
    │          ├── args: ["grep", "error"]
    │          └── redirs:
    │              └── REDIRECT_APPEND -> "output.txt"
    ├── args: ["cat"]
    └── redirs:
        └── REDIRECT_IN -> "input.txt"

        - A command node now will have a redirect linked list