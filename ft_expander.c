/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 13:20:46 by descamil          #+#    #+#             */
/*   Updated: 2024/06/10 16:11:34 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strnstr_mini(const char *s1, const char *s2, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	if (*s2 == '\0')
		return (0);
	while (s1[i] != '\0' && i < len)
	{
		if (s1[i] == s2[j])
		{
			k = i;
			while (s1[k] == s2[j] && s2[j] != '\0' && (k < len))
			{
				k++;
				j++;
				if (s2[j] == '\0')
					return (1);
			}
			j = 0;
		}
		i++;
	}
	return (0);
}

int	ft_final_var(int *k, char *input, int i)
{
	(*k)++;
	while (input[i] != '\0' && input[i] != ' ')
	{
		i++;
		(*k)++;
		if (input[i] == '$')
			return (i);
		
	}
	return (i);
}

char	**ft_var(char *input)
{
	char	**names;
	int		i;
	int		j;
	
	i = 0;
	j = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '$')
			j++;
		i++;
	}
	if (j == 0)
		return (NULL);
	names = malloc(sizeof(char **) * (j + 1));
	if (names == NULL)
		return (NULL);
	return (names);
}


char	*ft_remove_var(char *dst, const char *src, int num, int i)
{
	while (src[num] != '\0')
		dst[i++] = src[num++];
	while (dst[i] != '\0')
		dst[i++] = '\0';
	return (dst);
}

char	*ft_size_var(char **env, int *k2, char *input)
{
	int		i;
	char	*str;

	i = -1;
	while (env[++i] != NULL)
	{
		// printf("%s\n", env[i]);
		if (ft_strnstr_mini(env[i], input, ft_strlen(input)) == 1)
		{
			str = ft_strdup(env[i] + ft_strlen(input));
			printf("%s\n", str);
			(*k2) += ft_strlen(str);
			free(input);
			return (str);
		}
	}
	free(input);
	return (NULL);
}

int	ft_var_mod(char **env, char **names)
{
	int 	i;
	int		j;
	int		size;
	
	i = 0;
	size = 0;
	while (names[i] != NULL)
	{
		j = 0;
		while (env[j] != NULL)
		{
			if (ft_strnstr_mini(env[j], names[i], ft_strlen(names[i])) == 1)
				size++;
			j++;
		}
		i++;
	}
	return (size);
}

char	**ft_names_var(char *input, int *k1)
{
	int		i;
	int		len;
	int		start;
	int		index;
	char	**names;

	i = 0;
	index = 0;
	names = ft_var(input);
	if (names == NULL)
		return (NULL);
	while (input[i] != '\0')
	{
		if (input[i] == '$')
		{
			start = i;
			i = ft_final_var(*(&k1), input, i + 1);
			len = i - start;
			names[index] = ft_substr(input, start + 1, len - 1);
			index++;
		}
		if (input[i] == '$')
			i--;
		i++;
	}
	names[index] = NULL;
	return (names);
}

char	**ft_value_var(char **env, char **names, int *k2)
{
	char	**str;
	char	*join;
	int		index;
	int		i;
	
	i = 0;
	index = -1;
	str = malloc(sizeof(char **) * ft_var_mod(env, names) + 1);
	if (str == NULL)
		return (NULL);
	
	while (names[++index] != NULL)
	{
		join = ft_strjoin(names[index], "=");
		printf("%s\n", join);
		str[i++] = ft_size_var(env, *(&k2), join);
		if (str[i - 1] == NULL)
			free(str[--i]);
	}
	return (str);
}

// Cadena entera sin '$' y con los nuevos valores.
char	*ft_expander(char *input, char **env)
{
	char	**names;
	char	**str;
	int		k0;
	int		k1;
	int		k2;
	int		i;

	i = 0;
	k2 = 0;
	k1 = 0;
	names = ft_names_var(input, &k1);
	
	str = ft_value_var(env, names, &k2);
	

	k0 = ft_strlen(input) + (k1 - k2);
	printf("Size_old = %zu\n", ft_strlen(input));
	printf("K0 = %d\n", k0);
	printf("K1 = %d\n", k1);
	printf("K2 = %d\n", k2);
	if (names)
		free(names);
	if (str)
	{
		if (str[i])
		{
			while (str[i])
				free(str[i++]);
		}
		free(str);
	}
	return (NULL);
}

// int main(int argc, char **argv, char **env)
// {
// 	t_mini	*mini;
// 	char	*str = "ls $$AAA$LANGUAGE $LANG aaf";
// 	char	*ptr;
	
// 	ptr = ft_expander(str, env);
	
// 	// free(ptr);
// 	// printf("PTR = %s\n", ptr);
// 	// printf("Llega! 🚀\n");

// 	return (0);
// }

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