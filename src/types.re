type blockTag = [ | `latest | `earliest | `pending | `blockNumber(int)];

type rpcVersion = [ | `two_zero];

type connection = {
  endpoint: string,
  rpcVersion
};

module JSONRPC = {
  type error('a) = {
    code: int,
    message: string,
    data: option('a)
  };
  type response('a, 'b) = {
    jsonrpc: string,
    result: option('a),
    error: option(error('b)),
    id: string
  };
};

type networkId =
  | EthereumMainnet
  | MordenTestnetDeprecated
  | RopstenTestnet
  | RinkebyTestnet
  | KovanTestnet;

type transaction = {
  from: string,
  to_: string,
  gas: string,
  gasPrice: string,
  value: string,
  data: string
};
