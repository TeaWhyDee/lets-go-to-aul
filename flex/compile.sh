#!/usr/bin/bash

flex lex.l
gcc lex.yy.c
