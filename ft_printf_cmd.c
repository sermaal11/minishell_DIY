/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 15:23:41 by descamil          #+#    #+#             */
/*   Updated: 2024/07/20 15:21:03 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_cmd(t_cmd *cmd) {
    if (cmd == NULL) {
        printf(B_WH_0"------------------------\n\n"B_RD_0"No command structure.\n" RESET);
        return;
    }
    t_cmd *current = cmd;
    int cmd_index = 0;
    while (current != NULL) {
        printf(B_WH_0"------------------------\n\n"B_CY_0"Command structure {-%d-}\n" RESET, cmd_index);
        if (current->cmd)
            printf(B_OR_0 "\n  Cmd: {%s}\n" RESET, current->cmd);
        else
            printf(B_RD_0 "\n  Cmd: (null).\n" RESET);
        
        if (current->args) {
            printf(B_PR_0 "\n  Args:\n" RESET);
            for (int i = 0; current->args[i] != NULL; i++)
                printf(B_GR_0 "   - Args[%d]: {%s}\n" RESET, i, current->args[i]);
        } else {
            printf(B_RD_0 "\n  Args: (null).\n" RESET);
        }

        // Verificación de files
        if (current->files) {
            int has_f_order = current->files->f_order && current->files->f_order[0] != NULL;
            int has_order = current->files->order && current->files->order[0] != NULL;
            
            if (has_f_order || has_order) {
                printf(B_PR_0 "\n  Files:\n" RESET);

                if (has_f_order) {
                    for (int i = 0; current->files->f_order[i] != NULL; i++)
                        printf(B_GR_0 "   - Files[%d]: {%s}\n" RESET, i, current->files->f_order[i]);
                } else {
                    printf(B_RD_0 "\n    Files: (null).\n" RESET);
                }

                if (has_order) {
                    printf(B_PR_0 "\n  Order:\n" RESET);
                    for (int i = 0; current->files->order[i] != NULL; i++)
                        printf(B_GR_0 "   - Order[%d]: {%s}\n" RESET, i, current->files->order[i]);
                } else {
                    printf(B_RD_0 "\n    Order: (null).\n" RESET);
                }
            } else {
                printf(B_RD_0 "\n  Files: (null).\n" RESET);
            }

            printf(B_PR_0 "\n  Error:\n" RESET);
            printf(B_GR_0 "    Error: %d\n"B_WH_0"\n------------------------\n"RESET, current->files->error);
        }
        current = current->next;
        cmd_index++;
    }
}
