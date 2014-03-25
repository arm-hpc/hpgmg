#!/bin/sh

test_description='Test Poisson solve using FMG'

. ./fefas-sharness.sh

# Error norm is converging at second order
test_expect_stdout 'FE Poisson FMG solve fedegree=1 serial' 1 'fefas fmg -op_type poisson1 -M 8,16,24' '
F(2,2)  0: |e|_2/|u|_2 2.26e-02  |r|_2/|f|_2 3.37e-02
V(2,2)  1: |e|_2/|u|_2 2.58e-02  |r|_2/|f|_2 2.05e-03
V(2,2)  2: |e|_2/|u|_2 2.60e-02  |r|_2/|f|_2 1.25e-04
'

test_expect_stdout 'FE Poisson MG V-cycle solve fedegree=1 parallel' 4 'fefas fmg -op_type poisson1 -M 8,16,24 -p 1,2,2' '
F(2,2)  0: |e|_2/|u|_2 2.26e-02  |r|_2/|f|_2 3.37e-02
V(2,2)  1: |e|_2/|u|_2 2.58e-02  |r|_2/|f|_2 2.05e-03
V(2,2)  2: |e|_2/|u|_2 2.60e-02  |r|_2/|f|_2 1.25e-04
'

test_done
