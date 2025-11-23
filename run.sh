#!/bin/bash

cc -Wall -Wextra -Werror *.c validate_tokens/*.c -lreadline -o minishell
