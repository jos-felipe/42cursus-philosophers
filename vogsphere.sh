#!/bin/bash

find . -maxdepth 1 -not -name . -not -name .git -not -name philo -exec rm -rf {} \;

find ./philo -maxdepth 1 -not -name philo -not -name .git -not -name main.c -not -name 01_args_utils.c -not -name 01_args.c -not -name 02_buffet_utils.c -not -name 02_buffet.c -not -name 03_diners.c -not -name 03_diners_utils.c -not -name 04_the_reaper.c -not -name Makefile -not -name philo.h -exec rm -rf {} \;

