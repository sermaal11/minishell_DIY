/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 11:35:48 by descamil          #+#    #+#             */
/*   Updated: 2024/06/22 15:00:49 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int main() {
    char *input;
    const char *history_file = ".minishell_history"; // Especifica la ruta del archivo de historial

    // Leer el historial desde el archivo
    read_history(history_file);

    // Bucle de entrada de comandos
    while ((input = readline(">> ")) != NULL) {
        // Añadir la entrada al historial si no está vacía
        if (*input) {
            add_history(input);
        }
        // Simulación de comando "exit"
        if (strcmp(input, "exit") == 0) {
            free(input);
            break;
        }
        free(input);
    }

    // Guardar el historial en el archivo
    write_history(history_file);

    return 0;
}