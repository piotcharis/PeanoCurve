# PeanoCurve
This program creates an svg file of the Peano Curve with the given parameters. If no parameters are given the program uses the default values.

Usage:
```
make
```

```
./peano [options]
```

Possible options:
```
-V <int>:    Version of the algorithm to use, if not set the main implementation is used

-B <int>:    If set the runtime is measured and the optional argument specifies the number of iterations. 
             No output is generated.

-n <int>:    Degree of the peano curve

-o <string>: Name of the output file

-h:          Print this help message

--help:      Print this help message
```

```-V0```: iterative and optimized algorithm

```-V1```: iterative algorithm

```-V2```: recursive algorithm

Usage examples:
Generate curve of degree 5 with version 1 and output file 'out.svg': ```./peano -V1 -n5 -o out.svg```

Benchmark version 0 with degree 3 and 10 iterations: ```./peano -B10 -V0 -n3```

Default Values:
| Parameter             | Value          |
| -----------           | -----------    |
| version               | 0              |
| number of iterations  | 3              |
| degree                | 3              |
| name                  | peano.svg      |

If you want to learn more about the project, you can read [this](./Ausarbeitung.pdf) file (German).
