/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 13:20:46 by descamil          #+#    #+#             */
/*   Updated: 2024/06/13 15:40:50 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_size_var(char **env, int *k2, char *input)
{
	int		i;
	char	*str;

	i = -1;
	while (env[++i] != NULL)
	{
		if (ft_strnstr_mini(env[i], input, ft_strlen(input)) == 1)
		{
			str = ft_strdup(env[i] + ft_strlen(input));
			(*k2) += ft_strlen(str);
			free(input);
			return (str);
		}
	}
	free(input);
	return (NULL);
}

char	**ft_names_var(char *input, int *k1, int **position)
{
	int		i;
	int		len;
	int		start;
	int		index;
	char	**names;

	i = 0;
	index = 0;
	names = malloc(sizeof(char *) * (ft_var(input) + 1));
	if (names == NULL)
		return (NULL);
	while (input[i] != '\0')
	{
		if (input[i] == '$' && input[i + 1] == '$')
			i++;
		else if (input[i] == '$' && input[i + 1] != '$')
		{
			(*position)[index] = i;
			start = i;
			i = ft_final_var(*(&k1), input, i + 1);
			len = i - start;
			names[index] = ft_substr(input, start + 1, len - 1);
			index++;
			if (input[i] == '$')
				i--;
		}
		i++;
	}
	names[index] = NULL;
	return (names);
}

char	**ft_value_var(char **env, char **names, int *k2, int  **wrong_var)
{
	char	**str;
	char	*join;
	int		index;
	int		i;
	int		j;
	
	i = 0;
	j = 0;
	index = -1;
	str = malloc(sizeof(char **) * (ft_var_mod(env, names) + 1));
	if (str == NULL)
		return (NULL);
	while (names[++index] != NULL)
	{
		join = ft_strjoin(names[index], "=");
		str[i++] = ft_size_var(env, *(&k2), join);
		if (str[i - 1] == NULL)
		{
			(*wrong_var)[j++] = index + 1;
			free(str[--i]);
		}
	}
	str[i] = NULL;
	return (str);
}

int	ft_fin_var(char *input, int i)
{
	while (input[i] != '\0' && input[i] != ' ')
	{
		i++;
		if (input[i] == '$')
			return (i);
	}
	return (i);
}

int	ft_size_int(int *test)
{
	int	i = 0;
	
	while (test[i])
		i++;
	return (i);
}

int	*ft_remove_dolar_pos(char **names, int *locate, int *wrong_var, int **wrong_value)
{
	int	*final;
	int	i = 0;
	int	j = 0;
	int	k = 0;
	int	final_i = 0;
	int	wrong = ft_size_int(wrong_var);
	int	total;

	*wrong_value = (int *)malloc(sizeof(int *) * wrong);
	total = (ft_size_int(locate) - wrong);
	final = malloc(sizeof(int *) * total);
	i = 0;
	while (j != ft_size_int(locate))
	{
		if (i < wrong && (wrong_var[i] - 1) == j)
		{
			(*wrong_value)[k++] = ft_strlen(names[j++]) + 1;
			i++;
		}
		else
			final[final_i++] = locate[j++];
	}
	return (final);
}

// Cadena entera sin '$' y con los nuevos valores.
char	*ft_expander(char *input, char **env)
{
	char	**names;
	char	**str;
	int		k0;
	int		k2;
	int		i;
	int	*wrong_value = NULL;
	int	*locate_2;
	char	*final;
	int	pos = 0;
	int	final_i = 0;
	int	str_i;
	char *final_1;


	i = 0;
	k2 = 0;

// --------------------------------->
	int		*wrong_var;
	int		*locate;
	char	*str_1;
	char	*join;
	int		number;
	int		wrong;
	int		k1;

	k1 = 0;
	wrong = 0;
	number = ft_var(input);
	locate = malloc(sizeof(int *) * ft_var(input));
	if (locate == NULL)
		return (NULL);
	names = ft_names_var(input, &k1, &locate);
	while (i < number)
	{														// Necesita input, env, 
		join = ft_strjoin(names[i++], "=");					// Devuelve los valores k1, k2, wrong, locate
		str_1 = ft_size_var(env, &k2, join);
		if (str_1 == NULL)
			wrong++;
		free(str_1);
	}
	wrong_var = malloc(sizeof(int *) * wrong);
	if (wrong_var == NULL)
		return (NULL);
	
// --------------------------------->

	str = ft_value_var(env, names, &k2, &wrong_var);
	if (k1 > k2)
		k0 = ft_strlen(input) + (k1 - k2);
	else
		k0 = ft_strlen(input) + (k2 - k1);

// --------------------------------->

	final = malloc(sizeof(char) * (k0 + 1));
	locate_2 = ft_remove_dolar_pos(names, locate, wrong_var, &wrong_value);
	i = 0;
	while (input[i] != '\0')
	{
		str_i = 0;
		while (i < locate_2[pos])
			final[final_i++] = input[i++];
		while (str[pos][str_i] != '\0')
			final[final_i++] = str[pos][str_i++];
		i = ft_fin_var(input, i + 1);
		pos++;
	}
	final[final_i] = '\0';
	final_1 = ft_remove_wrong_var(final, wrong_value);

// --------------------------------->

	free(final);
	free(locate);
	free(locate_2);
	free(wrong_var);
	if (names)
		free(names);
	i = 0;
	if (str)
	{
		while (str[i])
			free(str[i++]);
		free(str);
	}

// --------------------------------->

	return (final_1);
}

int main(int argc, char **argv, char **env)
{
	char	*str = "ls $USR$LANG $U $AGE $LANG";	// SOLUCIONAR "$$VAR" SEG_FAULT
	char	*ptr;
	
	if (argc != 1)
		printf("%s\n", argv[2]);

	ptr = ft_expander(str, env);
	free(ptr);
	
	// free(ptr);
	// printf("PTR = %s\n", ptr);
	// printf("Llega! 🚀\n");

	return (0);
}

/*

Leer la linea que nos dan sin | ni >.
Guardar en un int* las posiciones de los dolares y en otro int* los tamaños de las variables, con dolar incluido.
Calcular longitudes de todas las variables e ir sumandolas.
Calcular longitudes de todas los valores e ir sumando.
En el caso de encontar una variable que no existe, el tamaño es 0 y se salta a la siguiente sin error.
Despues cuando ya se tenga todo, ir copiando caracter por caracter, cuando te encuentres un dolar, acceder a los ints*, para ver la longitud y en vez de copiar los caracteres de la cadena principal.
Char **, para guardar todos los valores de las variabbles 

	  MALLOC		  COPIAR		  MALLOC
_________________________________________________________________
|		S_T		|		POS		|		S_V		|	CHAR_VAR	|
|				|				|				|				|
|	size +=		|	2			|	size +=		|	[0] = asd	|
|				|	7			|				|	[1] = das	|
|				|	12			|				|	[2] = sad	|
|				|				|				|	[3] = NULL	|
|				|				|				|				|
|				|				|				|				|
|				|				|				|				|
|				|				|				|				|
|				|				|				|				|
|				|				|				|				|
|				|				|				|				|
|				|				|				|				|
¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
*/