/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initialize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarin-a <smarin-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:21:54 by smarin-a          #+#    #+#             */
/*   Updated: 2024/03/15 17:29:30 by smarin-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_set_env(t_env *env, char **enviroment)
{
	char	**matrix;
	int		i;

	i = 0;
	// Contamos el numero de variables de entorno presentes y guardamos la
	// cantidad en la variable env_amount dentro de la estruct env.
	while (enviroment[i])
		i++;
	env->env_amount = i;
	// Inicializamos una matriz auxiliar donde guardaremos las variables de 
	// entorno asegurandonos mediante calloc que tenemos suficiente memoria 
	// para ellas.
	matrix = ft_calloc(i, sizeof(char *));
	// Comprobamos si la asignacion de memoria fue exitosa
	if (!matrix)
		ft_exit_error("Malloc error", 1);
	while (--i >= 0)
	{
		// Hacemos una copia de cada variable de entorno dentro de la aux_matrix
		// usando ft_strdup()
		matrix[i] = ft_strdup(enviroment[i]);
		// Si la variable de entorno comienza con "PATH=", extrae la parte
		// después del signo '=' y la asigna al campo path de la estructura env
		// usando ft_substr.
		if (ft_strncmp(matrix[i], "PATH=", 5) == 0)
			env->path = ft_substr(matrix[i], 5, ft_strlen(matrix[i]) - 5);
		// Si la variable de entorno comienza con "SHLVL=", liberamos esa linea
		// de la matrix e incrementamos el SHLVL en 1 almacenandolo en matrix[i]
		if (ft_strncmp(matrix[i], "SHLVL=", 6) == 0)
		{
			free(matrix[i]);
			
			// 1:
			// ft_strchr(ev[i], '='): ft_strchr busca la primera aparición del
			// carácter '=' en la cadena enviroment[i], que representa una 
			// variable de entorno específica. Devuelve un puntero al primer 
			// carácter '=' encontrado en enviroment[i]. Esto es útil para
			// localizar donde termina el nombre de la variable y comienza su 
			// valor.
			
			// 2:
			// ft_strchr(eviroment[i], '=') + 1: Una vez que ft_strchr encuentra
			// el carácter '=', se desplaza un carácter más adelante para
			// apuntar al inicio del valor de la variable de entorno.
			
			// 3:
			// ft_atoi(ft_strchr(enviroment[i], '=') + 1): ft_atoi convierte la
			// cadena de caracteres que comienza en el puntero obtenido en el
			// paso anterior en un número entero. Esto significa que se está
			// convirtiendo el valor de la variable de entorno (que se encuentra
			// después del '=') en un número entero.
			
			// 4:
			// ft_atoi(...) + 1: Se incrementa el valor entero obtenido en el
			// paso anterior en 1. Esto se hace presumiblemente porque la
			// variable de entorno "SHLVL" generalmente indica el nivel de
			// profundidad de la shell actual, y se está aumentando en 1 para
			// reflejar que se está ejecutando una nueva instancia de la shell.			
			
			// 5:
			// ft_itoa(...): ft_itoa convierte el número entero obtenido en el
			// paso anterior de nuevo en una cadena de caracteres. Ahora, esta
			// cadena representa el valor "SHLVL" incrementado en 1.
			
			
			// 6:
			// ft_strjoin("SHLVL=", ...): ft_strjoin concatena dos cadenas de
			// caracteres. En este caso, une la cadena "SHLVL=" (el nombre de la
			// variable de entorno) con la cadena que contiene el valor "SHLVL"
			// incrementado en 1.
			
			// Resultado:
			// matrix[i] = ...: Finalmente, el resultado de la concatenación se
			// asigna al elemento i del array matrix. Esto significa que la
			// variable de entorno "SHLVL" se actualiza en matrix con su nuevo
			// valor incrementado en 1.
			matrix[i] = ft_strjoin("SHLVL=", ft_itoa(ft_atoi(ft_strchr(enviroment[i], '=') + 1) + 1));
		}
		// Si después de iterar no se encuentra ninguna variable de entorno
		// "PATH", establece env->path en "./" (el directorio actual).
		if (!env->path)
			env->path = ft_strdup("./");
		// Finalmente, asigna el array matrix, que contiene las variables de
		// entorno modificadas o copiadas, al campo env de la estructura env.
		env->env = matrix;
	}
	
}

// Inicializar estructura general;
t_mini	*ft_initialize(char **env)
{
	t_mini	*mini;
	
	// Asignamos memoria a la estructura t_mini y lo inicializamos con 0
	mini = ft_calloc(sizeof(mini), 1);
	// Comprobamos si la asignacion de memoria fue exitosa
	if (!mini)
		ft_exit_error("Malloc error", 1);
	// Establecemos el nivel de shell en shell_level = 2. Esto es porque estamos
	// iniciando la minishell dentro de la shell ya.
	mini->shell_level = 2;
	// Asignamos memoria a la estructuta t_env y lo inicializamos a 0.
	mini->env = ft_calloc(sizeof(t_env), 1);
	// Comrobamos si la asignacion de memoria fue exitosa.
	if (!mini->env)
		ft_exit_error("Malloc error", 2);
	// Seteamos el env con la informacion deseada.
	ft_set_env(mini->env, env);
	// ! Asignamos memoria a la estructuta t_flags y lo inicializamos a 0.
	mini->flags = ft_calloc(sizeof(t_flags), 1);
	// ! Comrobamos si la asignacion de memoria fue exitosa.
	if (!mini->flags)
		ft_exit_error("Malloc error", 4);
	return (mini);
	
}
