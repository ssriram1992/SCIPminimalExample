# SCIP Minimal example
Implements the following problem and solves it using SCIP C API. 
```
Minimize
  - x - y - z
Subject To
 xy: x + y <= 1
 yz: y + z <= 1
 xz: x + z <= 1
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
