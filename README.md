eight-queens
============

A brute-force program on the [eight-queens problem](http://en.wikipedia.org/wiki/Eight_queens_puzzle).

```Shell
> make
> ./eight-queens
```

The following options are available :
 * [-s]: Make the program stop when it gets 92 possibilities (which is the maximum)
 * [-c]: Activate color display
 * [-b]: Activate brute-force
 * [-h, --help]: Display all the previous options

##Example :

```Shell
> ./eight_queens -h
> ./eight_queens --help
> ./eight_queens -c -s
> ./eight_queens -cs
```

Since it is a brute-force, it can take some time to end its execution (even if it already have find all solutions). Use the -s option if you want to go faster.
