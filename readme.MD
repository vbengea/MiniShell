
* To implement:

	- Gestionar secuencia entrecomillada.

	- Los wildcards * deben funcionar para el directorio actual.

	- Gestionar $?, que deberá expandirse al estado de salida del comando más reciente ejecutado en la pipeline.

	- Review how builtins work with/without options. Commands first parse options, then arguments. If there are options, we compare the options we need to support (e.g. echo -n) and the rest should be outputed even tokens that looks like options with a leading "dash" (e.g echo -colores).


* Problems:

	- Naive handling of CTRL-C when running a long standing command. When e.g. a "sleep <seconds>" command is executed and interrupted with a CTRL-C, further CTRL-D (in interactive mode), exits adding an additional new line. Signals implementation will be revised.

	- Actual tokenizer doesn't support multiple redirections.

		+ Proposed solution:
			-Build a re-tokenizer on top of the actual one and update the AST structure.

			- A command like: cat < input.txt | grep "error" >> output.txt && echo "done" would have a structure like:

				![alt text](https://github.com/juandfloresm/minishare/blob/d280cd03d52180b5d4134df3951b1f946d357e49/resources/red.png)

			- A command node now will have a redirect linked list


* Inconsistency issues:

	- El comando "cat -e | ls -l && (cd / && ls -l)" tiene un comportamiento no convencionar cuando cat -e espera entrada del standard input. Si se ejecuta "cat | ls -l && (cd / && ls -l)" sin la opcion de cat "-e" funciona de manera standard.


* Solved issues:

	- El comando "cat main.c" muestra el archivo pero da error tambien como si tratara de ejecutar "cat" sin argumento. Este bug es inconsistente pues al probar en Ubuntu no hay errores.

	- Redirections are breaking long pipelines:

		< t1 cat -e | cat -e | cat -e					[OK]
		<t1 cat -e | cat -e | cat -e > t2				[OK]
		ls -l | cat -e | cat -e | cat -e > t2

	- El comando export sin argumentos lista las variables de entorno alfabéticamente y con un formato específico.

	- El comando "minishell" debe estar en el PATH, para que si uno ejecuta "minishell" desde dentro de minishell, haga en una subshell como hace bash. El comando exit saldría a la minishell anterior.

	- Una vez el proceso llega a pipex, no hay comunicación con el proceso original "selector" lo que hace que si uno de los elementos del pipe es una subshell, se pierda la salida de esta subshell y el proximo elemento del pipeline original se queda esperando la entrada indefinidamente e.g.:

		(ls -l | cat -e) | cat -e						[OK]
		ls -l | (cat -e && cat -e)						[OK]
		(ls -l | cat -e) | cat -e | cat -e				[OK]

	- Cuando ejectumos "ls -l | cat -e | cat -e | cat -e" el resultado es el correcto pero se imprimen unos caracteres extra en la línea del prompt.

	- El comando "(cd / && ls -l) && ls -l" realiza el cambio del directorio pero el cambio se ve desde fuera del paréntesis, lo que significa que o no se está ejecutando en una subshell o ambos se ejecutan en el mismo nivel de proceso.
