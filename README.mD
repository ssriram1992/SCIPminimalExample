# SCIP Minimal example
Implements the following problem and solves it using SCIP C API. 
```
Minimize
  - x - y - z
Subject To
 R0: x + y <= 1
 R1: y + z <= 1
 R2: x + z <= 1
Bounds
Binaries
 x y z
End

```

## Install instructions
Do
```
mkdir build && cd build && cmake .. & make & ./clique
```
