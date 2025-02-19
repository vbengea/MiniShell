* To implement:

	- Pasar la norma
	
	- Control de errores

	- Memory Leaks

	- Context errors
	
	- File descriptor leaks


* To be tested (bash vs. minishell):

	- What happens if we specify an environment variable name starting with a number? Or any other name not allowed.

	- We have discovered an environment variable context which is not env OR export. We call it local to differentiate from global OR command. Are the variables in the local container visible to the command: e.g. if we have script.sh which echoes the variable $VAR and we frist do:

		$ VAR=9
		$ ./script.sh

		does script.sh sees `VAR`?

	- Verificar que se puede cambiar el timezone antes de llamar el comando `date`

		$ date
		Wed Feb 19 09:29:07 CET 2025

		$ TZ=UTC date
		Wed Feb 19 08:28:53 UTC 2025
	
	- When the shell starts, the environment variables are loaded from a file called `.bashrc`. Do we have support something similar?

	- The variables we thought were hidden "local environment" are visible if we use the `declare` command. This one lists all. Well, this was tested in Mac so... The only thing `export` does different is that it still shows variables without values. Also `set` without areguments lists all environment variables in order. Don't know if there is another difference.

	- Do we support having several arguments to the `unset` command?

	- We should support `~` as an environment variable. Our project doesn't do it. I wonder if there are other conversions we need to support e.g.:

		$ echo ~
		/Users/juandanielflores

	- 

	- 

	- 

	- 

	- 

	- 

	- 

	- 

	- 

	- 

	- 

	- 

	- A la hora de probar la minishell, debemos procurar que no se pruebe con un perfil diferente del de uno de nosotros dos. En teoria no deberia pasar nada pero las configuraciones de cada perfil pueden ser unicas.

* Solved issues:

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
