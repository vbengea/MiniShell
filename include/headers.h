/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   headers.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 11:20:05 by vbengea           #+#    #+#             */
/*   Updated: 2025/03/04 19:16:52 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADERS_H
# define HEADERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <limits.h>

# include <sys/types.h>
# include <sys/wait.h>
# include <dirent.h>
# include <signal.h>

# include "libft/libft.h"
# include "data_structure.h"
# include "history.h"
# include "executor.h"
# include "token.h"
# include "colors.h"
# include "builtins.h"
# include "ast_build.h"
# include "prompt.h"

# include "tokenizer_functions.h"
# include "terminal.h"
# include "wildcard.h"
# include "environment.h"

#endif