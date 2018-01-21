# Pure ReasonML Library to Ethereum

`ethereum-re` is a pure ReasonML library that implements the JSONRPC
protocol. You can compile this library to JavaScript or compile to
native code.

# Development

`yarn --production=false`

and then either `./node_modules/.bin/bsb -make-world -backend native
-w` or `./node_modules/.bin/bsb -make-world -backend js -w`
