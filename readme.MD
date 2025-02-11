
* To implement:

	- The tree should convert format like "name=value" and also "export name=value" to "export name value".ex

	- Review how builtins work with/without options. Commands first parse options, then arguments. If there are options, we compare the options we need to support (e.g. echo -n) and the rest should be outputed even tokens that looks like options with a leading "dash" (e.g echo -colores).

	- Crear una super estructura para disminuir cantidad de parámetros.

	- Control de errores.

	- Guardar el historial en archivo y cargarlos a la hora de ejecturar la minishell.


* Environment differences:

	- When executing a list of commands the output differs from bash: bash creates all of the files and then execute the command, therefore, all "ls" will see the three files:
		(((ls > t3) && ls) > t2 && ls) > t1

	- Los .sh no se ejecutan sino le ponemos shelbang. Esto correcto? Porque en bash se ejecutan sin esta configuracion.


* Solved issues

	- Al parsear los argumentos muchas veces se hace trim y salen los argumentos sin debida separación.

	- Gestionar que el AST no incluya un argumento vacio al final de los argumentos con comandos como cat o rm;

	- Cuando se ejecuta cat en una pipeline sin entrada, con solo pulsar ENTER se cierra el stream de entrada. El comando "cat -e | ls -l" tiene un comportamiento no convencionar cuando cat -e espera entrada del standard input. Si se ejecuta "cat | ls -l && (cd / && ls -l)" sin la opcion de cat "-e" funciona de manera standard.

		bash-3.2$ ((ls) >t2 | cat -e)
		bash-3.2$ ((ls) >t2 >t1 >t3 | cat -e)

	- No expandir variables de entorno cuando el preparseo de ejecucion detecta comillas simples.
		echo "ba$PWD '$PWD'  3" 4 5  6 '$PWD'

	- echo no imprime bien: echo "ec$PWD ho"
		echo "blah $HOME 'no $HOME se' $HOMEblash"

	- Acutualizar la varable SHLVL. Debe incrementar al ejecutar "minishell" dentro.

	- Al inicar la minishell corremos el comando "cp minishell /home/.local

	- Actual tokenizer doesn't support multiple redirections.

		+ Proposed solution:
			-Build a re-tokenizer on top of the actual one and update the AST structure.

			- A command like: cat < input.txt | grep "error" >> output.txt && echo "done" would have a structure like:

				![alt text](https://github.com/juandfloresm/minishare/blob/d280cd03d52180b5d4134df3951b1f946d357e49/resources/red.png)

			- A command node now will have a redirect linked list

	- Signal. Esta variable global no puede proporcionar ninguna otra información o datos que el número de una señal recibida.

		+ Naive handling of CTRL-C when running a long standing command. When e.g. a "sleep <seconds>" command is executed and interrupted with a CTRL-C, further CTRL-D (in interactive mode), exits adding an additional new line. Signals implementation will be revised.
		+ With the updated signals we need to handle them at execution level; this means that a child process should execute:
			- `signal(SIGINT, SIG_DFL)`
			- `signal(SIGQUIT, SIG_DFL)`
		in order to restore the behavior of the signals. 
		
		The parent process must ignore them:
			- `signal(SIGINT, SIG_IGN)`
			- `signal(SIGQUIT, SIG_IGN)`
		When running in a subshell, the child becomes the parent so it must replicate the signal handling. 

	- HEREDOC ha dejado de funcionar en el pipeline.
		<<T1 cat -e | cat -e | cat -e
		<<T1 cat -e | cat -e | cat -e > t1
		<<T1 cat -e | cat -e | cat -e > t1 >> t2

	- Bad tree
		ls | cat -e && ls | cat -e | cat -e

	- Implement subshell redirections (execution time)
		(((ls) && ls) && ls) > t0
		(((ls > t3) && ls) > t2 && ls) > t1
		(((ls > t3) && ls) && ls) > t1

	- Resolver leaks de memoria con valgrind y santizer.

	- Los wildcards * deben funcionar para el directorio actual.

	- El comando cat hace segfault a veces. Si es el primer comando en ejecutarse despues de compilar, hace segfault.
		Si se ejecuta otro comando antes, no hace segfault pero lo hace el siguiente comando al ejecutarse.
		./minishell
		cat Makefile >>> segfault

		./minishell
		clear
		cat Makefile
		clear >>> segfault

	- Gestionar $?, que deberá expandirse al estado de salida del comando más reciente ejecutado en la pipeline.

	- Mini parser || no soportado
		false || echo 2
		true || echo 2
		make: *** [Makefile:105: runner] Segmentation fault (core dumped)

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
		((ls -l) | cat -e) | (cat -e | cat -e)			[OK]
		(((ls -l) | (cat -e))) | ((cat -e) | (cat -e))	[OK]	

	- Cuando ejectumos "ls -l | cat -e | cat -e | cat -e" el resultado es el correcto pero se imprimen unos caracteres extra en la línea del prompt.

	- El comando "(cd / && ls -l) && ls -l" realiza el cambio del directorio pero el cambio se ve desde fuera del paréntesis, lo que significa que o no se está ejecutando en una subshell o ambos se ejecutan en el mismo nivel de proceso.
