* To implement:

	- El arbol tiene los flags de espacios para el siguiente comando pero en `5` y `6` estan juntos en el output.
		echo "ba$PWD '$PWD'  3" 4 5  6 '$PWD'

	- En el siguiente comando hay un error de sintaxis pero deberia parsearse:
		((ls) >t2 | cat -e)
		Syntax error: UNCLOSED PARENTHSES

	- En un momento me dio memory leaks:
		ls -l > file1 > file2 > file3 > file4 | << EOF << END


* Solved issues:

	- Este comando no esta haciendo output:
		ls -l > file1 > file2 > file3 > file4 > file5 | << EOF cat -e << END

	- What happens if we specify an environment variable name starting with a number? Or any other name not allowed?

	- Control de errores

	- Context errors

	- File descriptor leaks

	- Pasar la norma

	- << EOF cat -e | cat -e << END > T1

	- pipeline without redirections: no leaks on file descriptors, memory.

	- `ls -l && (cd .. && ls -l) > file`

	- `ls -l | echo "hola" > a.txt && cat -e a.txt >> hola.txt` No esta funcionando correctamente. Esta creando los archivos pero estan vacios.
	Parece que `echo` no esta funcionando en una pipe

	- Probar
		VAR="test" && echo "$VAR" | grep "test" > output.txt && cat < output.txt | wc -l >> output.txt && echo "Success" || echo "Failure"

	- We have discovered an environment variable context which is not env OR export. We call it local to differentiate from global OR command. Are the variables in the local container visible to the command: e.g. if we have script.sh which echoes the variable $VAR and we first do:

		$ VAR=9
		$ ./script.sh

		does the `script.sh` script sees `VAR`?

	- Memory Leaks
		Cuando introducimos comandos invalidos, sin importar el comando en si, se generan still reachable leaks. El comando que probe fue `ls-l|cat-e` (sin espacios)

	- Verificar que se puede cambiar el timezone antes de llamar el comando `date`

		$ date
		Wed Feb 19 09:29:07 CET 2025

		$ TZ=UTC date
		Wed Feb 19 08:28:53 UTC 2025

	- Enviar un comando al binario de la minishell:
		minishell -c "ls -l | cat -e"

	- export VER="ls -l"
		$VER

	- Support command level environemnt variable
		GO=5 env
		GA=1 GE=2 GI=3 GO=4 GU=5 env
	
	- Variable de entorno
		Gestionar declaracion del tipo `export ARG="a b c d e"` igual que haciamos para probar push_swap.
		Al igual que en push_swap, expandir la variable con un split cuando es pasada como parametro. 

		export AA=1 AB=2 AC=3 AD AE
		BA=1 BB=2 BC
		export BA

	- HEREDOC en pipe `cat << EOF | ls` Esta ejecutando antes el comando `ls`

	- Actualmente la shell esta interpretando comandos en comillas `"ls -l"` no deberia ejecutarse

	- No esta dando fallo en caso de no tener permisos una redireccion de salida.
		`ls -l > output` habiendole quitado el permiso de escritura a output no hace nada pero tampoco da el fallo.

	- Gestionar codigos de error como lo hace bash. Command not fount: 127.

	- Verificar comportamiendo de señales. Si CTRL + C se usa despues de la ejecucion de un comando o al principio del programa, imprime ^C y el cursor baja a una
		nueva linea vacia. Hay que pulsar de nuevo CTRL + C para que vuelva a aparecer el prompt. 
		CTRL + D dependiendo de cuando se use no lo detecta a la primera, hay que pulsar una segunda vez para salir.
		(Es probable que se deba al entorno)

	- `ls -l && echo hello || mkdir test` Este comando esta ejecutando tambien despues del `||`. 
		el output deberia serl unicamente el de `ls -l` y el de `echo hello`

	- Tal vez gestionar como lo hace bash el builtin `exit`. Ejemplo `exit 150` actualiza la variable `?` de la shell original con ese codigo. 
		Seria simplemente verificar el argumento despues de exit y pasarselo a `exit()`.

	- `<< EOF << END | ls -l > file1 > file2 > file3` No esta ejecutando despues del pipe.

	- Mismo comando pero al reves `ls -l > file1 > file2 > file3 | << EOF << END` no esta borrando los archivos temporales de heredoc.

	- VERIFICAR (por el momento ha dejado de pasar)
		- A parte de still reachable leaks he observado que al ejecutar el comando
			`ls -l | cat -e | echo hola > output && echo $PATH` funciona perfectamente pero si 
			ejecutamos otro comando usando el mismo archivo como output, por ejemplo, `ls -l > output`
			el archivo se actualiza con el nuevo contenido y al volver a ejecutar el comando original ya no se ecribe correctamente el output. 
			El alrchivo deberia haberse actualizado y contener `hola` pero se queda vacio. 

	- Verificar redireccion `ls -l && (cd .. && ls -l) > output`

	- Double free detected `ls -l && (cd .. && ls -l)`

	- La variable `?` no se esta actualizando con el ultimo codigo de error. 
		al hacer `echo $?` muestra solo `?`,

	- Guardar el historial en archivo y cargarlos a la hora de ejecturar la minishell.

	- El primer argumento de echo tiene un espacio cuando se interpolan variables.

	- execve can execute binaries in the same directory if the first argument is just the name of the binary.

	- Gestionar declaracion de variables en dos niveles: global y local.
		GO=5
		export G=5

		en principio podemos tener tres listas:
			(1) Global: shells y subshells
			(2) Local: shell
			(3) Comando: comando

		export G1=1 G=2 hola que tal
		GB=B 

	- Verificar CTRL-C mientras se ejecuta HEREDOC.

	- Cuando el environment viene vacio, leer el /etc/environment.

	- Con un comando incompleto como "<< EOF" la ejecucion da segmentation fault.

	- Crear una super estructura para disminuir cantidad de parámetros.

	- Expandir variables de entorno en el heredoc cuando el delimitador no viene en comillas dobles. La linea que lea el get_next_line tiene que ser interpolada.
		a. Flag en redireccion cuando el heredoc viene entre comillas dobles.

	- Some limits.h like PATH_MAX are presenting squiggly in VS.

	- Gestionar cuando hay doble HEREDOC sin comando. LLega un nodo NODE_CMND sin argumentos y hace segfault

	- Verificar comportamiendo cuando se borra una carpeta anterior a la actual.
		Ejemplo: > working directory /home/user/folder1/folder2/folder3
		Si en ese directorio ejecutamos `rm -f ../../../folder1` y despues tratamos de hacer pwd o cd .., verificar la integridad del programa.

	- Hay que cambiar la ruta $HOME/bin donde ponemos el binario minishell. Cuando la minishell se ejecuta sin environment esta variable de entorno no esta presente y entonces significa que no ponemos el binario en el PATH.

	- Gestionar la ejecucucion sin environment (env -i) o sin PATH. Como sin PATH no podemos hacer nada. He copiado las rutas que normalmente son utilizadas por sudo. No se si hay una mejor manera de hacerlo. Tambien he puesto controles para que cuando getenv trata de buscar HOME o SHLVL no haga segmentation fault.

	- EXPORT > declarar todos los args que contenga el comando `export` incluido el propio export como variables de entorno vacias, sin valor. 
		En caso de que algun argumento en medio contenga alguna declaracion tipo `NAME=value` 
		declarar la variable con su valor correspondiente.
		Ejemplo: `export hola que tal esto es una prueba` Cada palabra debe ser una varibale vacia. En caso de ser `export hola que tal TEST=hola probando`, `TEST=hola` debe ser declarado como `NAME=value`. En este caso, tal como se estan seteando las flags actualmente, ese input crearia un comando como este 
		```
		minishell$ export hola que tal TEST=hola probando
		[TYPE:0] [NID:11] [SIDE:0] [ARGS]: _export_(1, 1),_hola_(1, 1),_que_(1, 1),_tal_(1, 1),_export_(1, 0),_TEST_(0, 0),_hola_(0, 0),_probando_(1, 0),[REDIRS]:
		```
		Al encontrar un `export` con el flag (1, 0) en este caso, se debe ignorar el string literal y declarar los siguientes dos args como `NAME=value`

		En el caso de tener un export en medio de los argumentos pero sin declarar nada, el output seria el siguiente:
		```
		minishell$ export hola que tal esto es una export prueba
		[TYPE:0] [NID:12] [SIDE:0] [ARGS]: _export_(1, 1),_hola_(1, 1),_que_(1, 1),_tal_(1, 1),_esto_(1, 1),_	es_(1, 1),_una_(1, 1),_export_(1, 1),_prueba_(1, 0),[REDIRS]: 
		```
		En caso de encontrar `export` con los flags (1, 1) este debe ser declarado como variable sin valor igual que el resto de argumentos. 

	- HREDOC dejo de funcionar cuando se ejecutan varios a la vez.
		Eejemplo: `<< EOF cat -e << END`
		Tambien pasa lo mismo con un comando mas largo como:
			`ls -l > file1 > file2 > file3 > file4 | << EOF << END` 
			ls -l > file1 > file2 > file3 > file4 > file5 | << EOF cat -e << END

	- Review how builtins work with/without options. Commands first parse options, then arguments. If there are options, we compare the options we need to support (e.g. echo -n) and the rest should be outputed even tokens that looks like options with a leading "dash" (e.g echo -colores).
	
	- Bash doesn't execute commands with double NODE_GROUP in a row, e.g. (ls) gives an output but ((ls)) doesn't. 

	- Changing the minishell binary route from ~/.local/bin to ~/bin. The previous one doesn't exist in 42 campus.

	- When executing a list of commands the output differs from bash: bash creates all of the files and then execute the command, therefore, all "ls" will see the three files:
		(((ls > t3) && ls) > t2 && ls) > t1

	- The tree should convert format like "name=value" and also "export name=value" to "export name value".ex
		Now works with simple declaration (TEST=helo) or with export (export TEST=hello)
		Only works without spaces around '=', like bash. 
		TEST =hello, TEST= hello or TEST = hello will be separated into different tokens;

	- Al parsear los argumentos muchas veces se hace trim y salen los argumentos sin debida separación.

	- Gestionar que el AST no incluya un argumento vacio al final de los argumentos con comandos como cat o rm;

	- Cuando se ejecuta cat en una pipeline sin entrada, con solo pulsar ENTER se cierra el stream de entrada. El comando "cat -e | ls -l" tiene un comportamiento no convencionar cuando cat -e espera entrada del standard input. Si se ejecuta "cat | ls -l && (cd / && ls -l)" sin la opcion de cat "-e" funciona de manera standard.

		bash-3.2$ ((ls) >t2 | cat -e)
		bash-3.2$ ((ls) >t2 >t1 >t3 | cat -e)

	- No expandir variables de entorno cuando el preparseo de ejecucion detecta comillas simples.
		echo "ba$PWD '$PWD'  3" 4 5  6 '$PWD'
		echo '$USER':"$USER"

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


* To be tested (bash vs. minishell) 😅:

	- We should set and use $TMPDIR as the variable holding the directory where temporary files. Like those we use to gather input / output from different redirections. The reason this might be important is that if the binary is placed in another directory and executed, it won't find the "./tmp" file we are currently using.

	- Do we need to support having several arguments to the `unset` command?

	- When the user uses `cd` we correctly set the $PWD, but we don't set the $OLDPWD to the previous working directory.

	- We should support `~` as an environment variable. Our project doesn't do it. I wonder if there are other conversions we need to support e.g.:

		$ echo ~
		/Users/juandanielflores

	- We are currently printing SHLVL but I didn't know there is also a BASH_SUBSHELL environment variable that indicates the level of sub shell bash is currently in. e.g

		$ echo $SHLVL $BASH_SUBSHELL
		1 0
		$ bash
		$ echo $SHLVL $BASH_SUBSHELL
		2 0
		$ echo ($SHLVL $BASH_SUBSHELL)
		2 1
		$ echo (($SHLVL $BASH_SUBSHELL))
		2 2

	- Deberiamos soportar $(CMD) y ${VAR_NAME}?
		$ ls $(pwd)/executor
		ls ${PWD}/executor
		${PWD} y $(pwd) son diferentes

	- Should we detect non-word characters that we don't support at the tokenize level:
		$ }
		$ {
		Syntax error: INVALID TOKEN

	- When the shell starts, the environment variables are loaded from a file called `.bashrc`. Do we have to support something similar?

	- There are variables like $SHELL and $BASH that output the location of the bash binary. Should we do the same with $MINISHELL?


* Food for thought:

	- The variables we thought were hidden "local environment" are visible if we use the `declare` command. This one lists all. Well, this was tested in Mac so... The only thing `export` does different is that it still shows variables without values. Also `set` without arguments lists all environment variables in order. Don't know if there is another difference.

	- We need to watch out from the $IGNOREEOF variable which can be used to customize how the shell behaves in interactive mode when pressing CTRL+D. By default it exits the terminal. So we are good.

	- There is a $CDPATH variable that `cd` uses to resolve things in the order specified. I don't think it applies to use because we are using chdir() c function in the background.

	- If we would like to version our minishell, there are variables that are used to indicate this $BASH_VERSION and $BASH_VERSINFO[n]. The `n` indicating (mayor, minor, patch, build, release, etc..).

	- The $BASH_ENV and $ENV variables contains a location of a script that be used for debugging and doing things before the command is executed. I wonder if we could have used this to store commands in a history file.

	- We should make sure that all errors are sent to the standard error. I assume that `perror` does that but we need to scan code for printf's and write's that don't.

	- 🤦 Apparently there is a GLOBIGNORE environemnt variable that describes colon separated patterns that should be ignored by the "wildcard" file expansions. It's like a git .gitignore. I think this could be difficult to implement and not sure it is part of the assignment. There is also a way to ignore executables even if their containing folder is listed by $PATH. We can do this with $EXECIGNORE. And yet also, there is a variable called $FIGIGNORE with file extension patterns to ignore when fetching the wildcards pattterns.

	- A la hora de probar la minishell, debemos procurar que no se pruebe con un perfil diferente del de uno de nosotros dos. En teoria no deberia pasar nada pero las configuraciones de cada perfil pueden ser unicas.
