#!/bin/sh
python3 -m minishell_test builtin/cd | grep builtin/cd | tail -1 > out.log
python3 -m minishell_test builtin/echo | grep builtin/echo | tail -1 >> out.log
python3 -m minishell_test builtin/env | grep builtin/env | tail -1 >> out.log
python3 -m minishell_test builtin/exit | grep builtin/exit | tail -1 >> out.log
python3 -m minishell_test builtin/export | grep builtin/export | tail -1 >> out.log
python3 -m minishell_test builtin/pwd | grep builtin/pwd | tail -1 >> out.log
python3 -m minishell_test builtin/unset | grep builtin/unset | tail -1 >> out.log
python3 -m minishell_test cmd/cmd | grep cmd/cmd | tail -1 >> out.log
python3 -m minishell_test cmd/cmd_path | grep cmd/cmd_path | tail -1 >> out.log
python3 -m minishell_test cmd/redirection | grep cmd/redirection | tail -1 >> out.log
python3 -m minishell_test cmd/status | grep cmd/status | tail -1 >> out.log
python3 -m minishell_test flow/end | grep flow/end | tail -1 >> out.log
python3 -m minishell_test flow/pipe | grep flow/pipe | tail -1 >> out.log
python3 -m minishell_test flow/syntax_error | grep flow/syntax_error | tail -1 >> out.log
python3 -m minishell_test misc/lastcmd | grep misc/lastcmd | tail -1 >> out.log
python3 -m minishell_test misc/shlvl | grep misc/shlvl | tail -1 >> out.log
python3 -m minishell_test path/path | grep path/path | tail -1 >> out.log
python3 -m minishell_test path/path_variable | grep path/path_variable | tail -1 >> out.log
python3 -m minishell_test preprocess/escape | grep preprocess/escape | tail -1 >> out.log
python3 -m minishell_test preprocess/interpolation | grep preprocess/interpolation | tail -1 >> out.log
python3 -m minishell_test preprocess/quote | grep preprocess/quote | tail -1 >> out.log
python3 -m minishell_test preprocess/spaces | grep preprocess/spaces | tail -1 >> out.log
cut -d " " -f5 out.log | awk '{sum+=$1 ; print $0} END{print "sum=",sum}'
