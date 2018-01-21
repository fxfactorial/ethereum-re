module JSONRPC = {
  type request = {
    jsonrpc: string,
    method: string,
    params: [ | `positional(array(string))],
    id: option(string)
  };
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

module type EthereumRPC = {
  type promise(+'a);
  let web3_clientVersion: unit => promise(JSONRPC.response(string, Json.t));
  let web3_sha3: string => promise(JSONRPC.response(string, 'b));
  let net_version: unit => promise(JSONRPC.response(networkId, 'b));
  /* let net_peerCount */
  /* let net_listening */
  /* let eth_protocolVersion */
  /* let eth_syncing */
  /* let eth_coinbase */
  /* let eth_mining */
  /* let eth_hashrate */
  /* let eth_gasPrice */
  /* let eth_accounts */
  /* let eth_blockNumber */
  /* let eth_getBalance */
  /* let eth_getStorageAt */
  /* let eth_getTransactionCount */
  /* let eth_getBlockTransactionCountByHash */
  /* let eth_getBlockTransactionCountByNumber */
  /* let eth_getUncleCountByBlockHash */
  /* let eth_getUncleCountByBlockNumber */
  /* let eth_getCode */
  /* let eth_sign */
  /* let eth_sendTransaction */
  /* let eth_sendRawTransaction */
  /* let eth_call */
  /* let eth_estimateGas */
  /* let eth_getBlockByHash */
  /* let eth_getBlockByNumber */
  /* let eth_getTransactionByHash */
  /* let eth_getTransactionByBlockHashAndIndex */
  /* let eth_getTransactionByBlockNumberAndIndex */
  /* let eth_getTransactionReceipt */
  /* let eth_getUncleByBlockHashAndIndex */
  /* let eth_getUncleByBlockNumberAndIndex */
  /* let eth_getCompilers */
  /* let eth_compileLLL */
  /* let eth_compileSolidity */
  /* let eth_compileSerpent */
  /* let eth_newFilter */
  /* let eth_newBlockFilter */
  /* let eth_newPendingTransactionFilter */
  /* let eth_uninstallFilter */
  /* let eth_getFilterChanges */
  /* let eth_getFilterLogs */
  /* let eth_getLogs */
  /* let eth_getWork */
  /* let eth_submitWork */
  /* let eth_submitHashrate */
  /* let db_putString */
  /* let db_getString */
  /* let db_putHex */
  /* let db_getHex */
  /* let shh_post */
  /* let shh_version */
  /* let shh_newIdentity */
  /* let shh_hasIdentity */
  /* let shh_newGroup */
  /* let shh_addToGroup */
  /* let shh_newFilter */
  /* let shh_uninstallFilter */
  /* let shh_getFilterChanges */
  /* let shh_getMessages */
};

module Make = (RpcImpl: EthereumRPC) => {
  let web3_clientVersion = RpcImpl.web3_clientVersion;
  /* type promiseWrapper('t) = */
  /*   | Native('t): promiseWrapper(RpcImpl.promise(string)) */
  /* | JSBased('t): promiseWrapper(Js.Promise.t(string)); */
};
