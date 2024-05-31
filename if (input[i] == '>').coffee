if (input[i] == '>')
		{
			mini->flags->redirect->si_le += 1;
			if (input[i - 1] && input[i - 1] == '>')
			{
				mini->flags->redirect->do_le += 1;
				mini->flags->redirect->si_le -= 2;
			}
			if (input[i - 1] && input[i - 1] == '<')
			{
				mini->flags->redirect->red_error = 1;
				mini->flags->redirect->error[0] = input[i - 1];
				mini->flags->redirect->error[1] = input[i];
			}
			if (input[i - 2] && (input[i - 2] == '>' || input[i - 2] == '<'))
			{
				mini->flags->redirect->red_error = 3;
				mini->flags->redirect->error[0] = input[i];
				printf(BLUE"%c\n"RESET, input[i]);
			}
			if (input[i - 3] && (input[i - 3] == '>' || input[i - 3] == '<'))
			{
				mini->flags->redirect->red_error = 4;
				mini->flags->redirect->error[0] = input[i - 1];
				mini->flags->redirect->error[1] = input[i];
			}
		}
		if (input[i] == '<')
		{
			mini->flags->redirect->si_ri += 1;
			if (input[i - 1] && input[i - 1] == '<')
			{
				mini->flags->redirect->do_ri += 1;
				mini->flags->redirect->si_ri -= 2;
			}
			if (input[i - 1] && input[i - 1] == '>')
			{
				mini->flags->redirect->red_error = 9;
				mini->flags->redirect->error[0] = input[i];
				
				// if (input[i + 1] && (input[i + 1] == '>' || input[i + 1] == '<'))
				// {
				// 	mini->flags->redirect->error[0] = input[i];
				// 	mini->flags->redirect->error[1] = input[i + 1];
				// 	break ;
				// }
					
			}
			if (input[i - 2] && input[i - 2] == '>')
			{
				mini->flags->redirect->red_error = 3;
				mini->flags->redirect->error[0] = input[i];
				printf(CYAN"%c\n"RESET, input[i]);
			}
			if (input[i - 2] && input[i - 2] == '<')
				mini->flags->redirect->red_error = 9;
			if (input[i - 3] && (input[i - 3] == '<' || input[i - 3] == '>'))
			{
				mini->flags->redirect->red_error = 4;
				mini->flags->redirect->error[0] = input[i - 1];
				mini->flags->redirect->error[1] = input[i];
			}
			
		}