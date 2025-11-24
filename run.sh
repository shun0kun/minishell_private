#!/bin/bash

cc -Wall -Wextra -Werror *.c validation/*.c tokenization/*.c ast/*.c env/*.c ft/*.c -lreadline -o minishell
