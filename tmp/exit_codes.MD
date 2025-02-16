

* SIGNALS & EXIT CODES:

	- `kill -l` en bash nos devuelve esta lista:

		```
		 1) SIGHUP		2) SIGINT	 	3) SIGQUIT	 	4) SIGILL	 	5) SIGTRAP
		 6) SIGABRT	 	7) SIGBUS	 	8) SIGFPE	 	9) SIGKILL		10) SIGUSR1
		11) SIGSEGV		12) SIGUSR2		13) SIGPIPE		14) SIGALRM		15) SIGTERM
		16) SIGSTKFLT	17) SIGCHLD		18) SIGCONT		19) SIGSTOP		20) SIGTSTP
		21) SIGTTIN		22) SIGTTOU		23) SIGURG		24) SIGXCPU		25) SIGXFSZ
		26) SIGVTALRM	27) SIGPROF		28) SIGWINCH	29) SIGIO		30) SIGPWR
		31) SIGSYS		34) SIGRTMIN	35) SIGRTMIN+1	36) SIGRTMIN+2	37) SIGRTMIN+3
		38) SIGRTMIN+4	39) SIGRTMIN+5	40) SIGRTMIN+6	41) SIGRTMIN+7	42) SIGRTMIN+8
		43) SIGRTMIN+9	44) SIGRTMIN+10	45) SIGRTMIN+11	46) SIGRTMIN+12	47) SIGRTMIN+13
		48) SIGRTMIN+14	49) SIGRTMIN+15	50) SIGRTMAX-14	51) SIGRTMAX-13	52) SIGRTMAX-12
		53) SIGRTMAX-11	54) SIGRTMAX-10	55) SIGRTMAX-9	56) SIGRTMAX-8	57) SIGRTMAX-7
		58) SIGRTMAX-6	59) SIGRTMAX-5	60) SIGRTMAX-4	61) SIGRTMAX-3	62) SIGRTMAX-2
		63) SIGRTMAX-1	64) SIGRTMAX
		```
	- Cuando un proceso es terminado con una señal, su codigo de salida se convierte en 128 + N.
		N corresponde a la señal recibida. 
		Ejemplo: `sleep 10` y lo paramos con `CTRL + C` (SIGINT). Si hacemos `echo $?` nos saldra 130.
		128 + 2 que corresponde a SIGINT. 

	- Rango de codigos de salida `0 - 255`

	- Algunos comunes:
		
		+ `0` Success
		+ `1` General error
		+ `2` Incorrect usage of builtins `cd /noexist`
		+ `126` Command found but not executable
		+ `127` Command not found
		+ `128 + N` Process killed by signal.
		+ `255` Exit status out of range


* BUILTINS EXIT CODES (`man 1 command`)

	- exit

		+ The  exit  status shall be n, if specified, except that the behavior is unspecified if n is not an unsigned decimal
	   integer or is greater than 255. Otherwise, the value shall be the exit value of the last command executed, or  zero
	   if  no  command was executed. When exit is executed in a trap action, the last command is considered to be the com‐
	   mand that executed immediately preceding the trap action.


	- cd 

		+    The following exit values shall be returned:

			0    The directory was successfully changed.

			\>0    An error occurred.

	- export

		+

			0    All name operands were successfully exported.

			\> 0    At least one name could not be exported, or the -p option was specified and an error occurred.

	- unset

		+

			0    All name operands were successfully unset.

			\> 0    At least one name could not be unset.
