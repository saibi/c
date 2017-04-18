#!/bin/bash

make T=ns
make T=nsf
make T=nsfn
make T=nhf
make T=ahf

make T=ns O=1
make T=nsf O=1
make T=nsfn O=1
make T=nhf O=1
make T=ahf O=1

make T=ns O=2
make T=nsf O=2
make T=nsfn O=2
make T=nhf O=2
make T=ahf O=2

make T=ns O=3
make T=nsf O=3
make T=nsfn O=3
make T=nhf O=3
make T=ahf O=3

make T=ns O=s
make T=nsf O=s
make T=nsfn O=s
make T=nhf O=s
make T=ahf O=s

make T=ahf O=fast
make T=ahf O=g
