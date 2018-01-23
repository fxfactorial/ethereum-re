# Pure ReasonML Library to Ethereum

`ethereum-re` is a pure ReasonML library that implements the JSONRPC
protocol. You can compile this library to JavaScript or compile to
native code.

# Development

you need to be on the bucklescript switch

```
$ opam switch 4.02.3+buckle-master
```

And make sure to do: 

```
$ eval `opam config env`
```

Then: 

```
opam install lwt cotthp result ppx_deriving -y
```

And then: 

```
$ yarn --production=false
```

and then either `./node_modules/.bin/bsb -make-world -backend native
-w` or `./node_modules/.bin/bsb -make-world -backend js -w`
