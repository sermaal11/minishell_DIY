/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarin-a <smarin-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:25:39 by smarin-a          #+#    #+#             */
/*   Updated: 2024/03/14 16:59:56 by smarin-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include	<stdio.h>
# include	<unistd.h>
# include	<stdlib.h>
# include 	<string.h>

int main(int argc, char **argv)
{
	char	*token;
	
	token = strtok(argv[1], ",");
	while (token)
	{
		printf("%s\n", token);
		token = strtok(NULL, ",");
	}
	return (0);
}