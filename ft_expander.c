/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 13:20:46 by descamil          #+#    #+#             */
/*   Updated: 2024/06/09 18:54:54 by descamil         ###   ########.fr       */
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

int	ft_final_var(/*t_mini *mini,*/int *k, char *input, int i)
{
	printf("Aquí\n");
	(*k)++;
	while (input[i] != '\0' && input[i] != ' ')
	{
		i++;
		(*k)++;
		/*mini->flags->expander++;*/
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
	names = malloc(sizeof(char **) * j);
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

int	ft_size_var(char **env, char *input)
{
	int		i;
	char	*str;
	char	*join;

	i = -1;
	join = ft_strjoin(input, "=");
	printf("%s\n", join);
	while (env[++i] != NULL)
	{
		if (ft_strnstr_mini(env[i], join, ft_strlen(join)) == 1)
		{
			printf("%s\n", env[i]);
			ft_strlcpy(str, env[i] + ft_strlen(join), ft_strlen(env[i] - ft_strlen(join)));
			// ft_remove_var(str, str, ft_strlen(join), 0);
			printf("\n----------------\n%s\n----------------\n\n", str);
		}
		
	}
	return (0);
}

// Cadena entera sin '$' y con los nuevos valores.
char	*ft_expander(/*t_mini *mini, */char *input, char **env)
{
	int		i;
	int		k1;
	int		k2;
	int		len;
	int		index;
	int		start;
	char	**names;

	i = 0;
	k1 = 0;
	index = 0;
	names = ft_var(input);
	while (input[i] != '\0')
	{
		if (input[i] == '$')
		{
			start = i;
			i = ft_final_var(/*mini,*/&k1, input, i + 1);
			len = i - start;
			names[index++] = ft_substr(input, start + 1, len - 1);
			// printf("%dq\n", len);
		}
		i++;
	}
	names[index] = NULL;
	i = 0;
	index = -1;
	k2 = 0;
	while (names[++index] != NULL)
	{
		k2 += ft_size_var(env, names[index]);
	}
	// i = 0;
	// while (index-- != 0)
	// 	printf("\t%sq\n", names[i++]);
	// printf("\n%s\n", env[0]);
	// printf(" 🚀 %d 🚀 \n", /*mini->flags->expander*/k1);
	return (NULL);
}
// Valor para sumar al int de sizes variables


// Char ** con todos los valores de las variables, en orden
// char	**ft_var_values(t_mini *mini)
// {
	
// }

//
int main(int argc, char **argv, char **env)
{
	t_mini *mini;
	char *str = "ls $a $GJS_DEBUG_TOPICS $ss aaf";

	ft_expander(/*mini,*/ str, env);

	printf("Llega! 🚀\n");

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