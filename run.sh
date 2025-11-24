#!/bin/bash

cc -Wall -Wextra -Werror *.c validation/*.c tokenization/*.c ast/*.c -lreadline -o minishell
