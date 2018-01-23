open Lwt;

let send = (~conn: Types.connection, ~uri, ~params: Json.t, ~method, ~id, ()) =>
  /* print_endline(msg); */
  Cohttp_lwt_unix.Client.post(~body=`String(Util.makeMsg(conn, method, id, params)), uri)
  >>= (((resp, body)) => Cohttp_lwt_body.to_string(body));

class common (~connection: Types.connection) = {
  val idCounter = ref(-1);
  val sendPrep = send(~conn=connection, ~uri=Uri.of_string(connection.endpoint));
};

class web3 (~connection: Types.connection) = {
  inherit (class common)(~connection);
  pub clientVersion = {
    incr(idCounter);
    sendPrep(~params=Json.Array([]), ~method="web3_clientVersion", ~id=idCounter^, ());
  };
  pub sha3 = param => {
    incr(idCounter);
    sendPrep(~params=Json.Array([Json.String(param)]), ~method="web3_sha3", ~id=idCounter^, ());
  };
};

class net (~connection: Types.connection) = {
  inherit (class common)(~connection);
  pub version = {
    incr(idCounter);
    sendPrep(~params=Json.Array([]), ~method="net_version", ~id=idCounter^, ());
  };
  pub listening = {
    incr(idCounter);
    sendPrep(~params=Json.Array([]), ~method="net_listening", ~id=idCounter^, ());
  };
  pub peerCount = {
    incr(idCounter);
    sendPrep(~params=Json.Array([]), ~method="net_peerCount", ~id=idCounter^, ());
  };
};

class eth (~connection: Types.connection) = {
  inherit (class common)(~connection);
  pub protocolVersion = {
    incr(idCounter);
    sendPrep(~params=Json.Array([]), ~method="eth_protocolVersion", ~id=idCounter^, ());
  };
  pub syncing = {
    incr(idCounter);
    sendPrep(~params=Json.Array([]), ~method="eth_syncing", ~id=idCounter^, ());
  };
  pub coinbase = {
    incr(idCounter);
    sendPrep(~params=Json.Array([]), ~method="eth_coinbase", ~id=idCounter^, ());
  };
  pub mining = {
    incr(idCounter);
    sendPrep(~params=Json.Array([]), ~method="eth_mining", ~id=idCounter^, ());
  };
  pub hashrate = {
    incr(idCounter);
    sendPrep(~params=Json.Array([]), ~method="eth_hashrate", ~id=idCounter^, ());
  };
  pub gasPrice = {
    incr(idCounter);
    sendPrep(~params=Json.Array([]), ~method="eth_gasPrice", ~id=idCounter^, ());
  };
  pub accounts = {
    incr(idCounter);
    sendPrep(~params=Json.Array([]), ~method="eth_accounts", ~id=idCounter^, ());
  };
  pub blockNumber = {
    incr(idCounter);
    sendPrep(~params=Json.Array([]), ~method="eth_blockNumber", ~id=idCounter^, ());
  };
  pub getBalance = (~address, ~quantity: Types.blockTag) => {
    incr(idCounter);
    sendPrep(
      ~params=Json.Array([Json.String(address), Util.stringOfBlockTag(quantity)]),
      ~method="eth_getBalance",
      ~id=idCounter^,
      ()
    );
  };
  pub getStorageAt = (~address, ~position: int, ~quantity: Types.blockTag) => {
    incr(idCounter);
    let params =
      Json.(
        Array([String(address), Number(float_of_int(position)), Util.stringOfBlockTag(quantity)])
      );
    sendPrep(~params, ~method="eth_getStorageAt", ~id=idCounter^, ());
  };
  pub getTransactionCount = (~address, ~quantity: Types.blockTag) => {
    incr(idCounter);
    let params = Json.(Array([String(address), Util.stringOfBlockTag(quantity)]));
    sendPrep(~params, ~method="eth_getTransactionCount", ~id=idCounter^, ());
  };
  pub getBlockTransactionCountByHash = block => {
    incr(idCounter);
    let params = Json.Array([Json.String(block)]);
    sendPrep(~params, ~method="eth_getBlockTransactionCountByHash", ~id=idCounter^, ());
  };
  pub getBlockTransactionCountByNumber = quantity => {
    incr(idCounter);
    let params = Json.Array([Util.stringOfBlockTag(quantity)]);
    sendPrep(~params, ~method="eth_getBlockTransactionCountByNumber", ~id=idCounter^, ());
  };
  pub getUncleCountByBlockHash = (~blockHash) => {
    incr(idCounter);
    let params = Json.Array([Json.String(blockHash)]);
    sendPrep(~params, ~method="eth_getUncleCountByBlockHash", ~id=idCounter^, ());
  };
  pub getUncleCountByBlockNumber = (~tag) => {
    incr(idCounter);
    let params = Json.Array([Util.stringOfBlockTag(tag)]);
    sendPrep(~params, ~method="eth_getUncleCountByBlockNumber", ~id=idCounter^, ());
  };
  pub getCode = (~address, ~tag) => {
    incr(idCounter);
    let params = Json.Array([Json.String(address), Util.stringOfBlockTag(tag)]);
    sendPrep(~params, ~method="eth_sendTransaction", ~id=idCounter^, ());
  };
  pub sign = (~address, ~data) => {
    incr(idCounter);
    let params = Json.Array([Json.String(address), Json.String(data)]);
    sendPrep(~params, ~method="eth_sendTransaction", ~id=idCounter^, ());
  };
  pub sendTransaction = transaction => {
    incr(idCounter);
    let params = Json.Array([Util.transactionToString(transaction)]);
    sendPrep(~params, ~method="eth_sendTransaction", ~id=idCounter^, ());
  };
  pub eth_sendRawTransaction = (~signedTransaction) => {
    incr(idCounter);
    let params = Json.Array([Util.transactionToString(signedTransaction)]);
    sendPrep(~params, ~method="eth_sendRawTransaction", ~id=idCounter^, ());
  };
  pub call = (~transaction, ~tag) => {
    incr(idCounter);
    let params = Json.Array([Util.transactionToString(transaction), Util.stringOfBlockTag(tag)]);
    sendPrep(~params, ~method="eth_call", ~id=idCounter^, ());
  };
  pub estimateGas = (~transaction, ~tag) => {
    incr(idCounter);
    let params = Json.Array([Util.transactionToString(transaction), Util.stringOfBlockTag(tag)]);
    sendPrep(~params, ~method="eth_estimateGas", ~id=idCounter^, ());
  };
  pub getBlockByHash = (~data, ~fullTransaction) => {
    incr(idCounter);
    let params = Json.Array([Json.String(data), fullTransaction ? Json.True : Json.False]);
    sendPrep(~params, ~method="eth_getBlockByHash", ~id=idCounter^, ());
  };
  pub getBlockByNumber = (~tag, ~fullTransaction) => {
    incr(idCounter);
    let params =
      Json.Array([Util.stringOfBlockTag(tag), fullTransaction ? Json.True : Json.False]);
    sendPrep(~params, ~method="eth_getBlockByNumber", ~id=idCounter^, ());
  };
  pub getTransactionByHash = (~data) => {
    incr(idCounter);
    let params = Json.Array([Json.String(data)]);
    /* Lwt.( */
    sendPrep(~params, ~method="eth_getTransactionByHash", ~id=idCounter^, ());
    /*   >|= Util.parseTransaction */
    /* ); */
  };
  pub getTransactionByBlockHashAndIndex = (~blockHash, ~position) => {
    incr(idCounter);
    let params = Json.(Array([String(blockHash), String(position)]));
    sendPrep(~params, ~method="eth_getTransactionByBlockHashAndIndex", ~id=idCounter^, ());
  };
  pub getTransactionByBlockNumberAndIndex = (~tag, ~position) => {
    incr(idCounter);
    let params = Json.(Array([Util.stringOfBlockTag(tag), String(position)]));
    sendPrep(~params, ~method="eth_getTransactionByBlockNumberAndIndex", ~id=idCounter^, ());
  };
  pub getTransactionReceipt = data => {
    incr(idCounter);
    let params = Json.(Array([String(data)]));
    sendPrep(~params, ~method="eth_getTransactionReceipt", ~id=idCounter^, ());
  };
  pub getUncleByBlockHashAndIndex = (~data, ~position) => {
    incr(idCounter);
    let params = Json.(Array([String(data), String(position)]));
    sendPrep(~params, ~method="eth_getUncleByBlockHashAndIndex", ~id=idCounter^, ());
  };
  pub getUncleByBlockNumberAndIndex = (~tag, ~position) => {
    incr(idCounter);
    let params = Json.(Array([Util.stringOfBlockTag(tag), String(position)]));
    sendPrep(~params, ~method="eth_getUncleByBlockNumberAndIndex", ~id=idCounter^, ());
  };
  pub getCompilers = () => {
    incr(idCounter);
    let params = Json.(Array([]));
    sendPrep(~params, ~method="eth_getCompilers", ~id=idCounter^, ());
  };
  pub compileSolidity = (~sourceCode) => {
    incr(idCounter);
    let params = Json.(Array([String(sourceCode)]));
    sendPrep(~params, ~method="eth_compileSolidity", ~id=idCounter^, ());
  };
  /* compileLLL && compileSerpent missing */
  /* pub compileSolidity = (~sourceCode) => { */
  /*   incr(idCounter); */
  /*   let params = Json.(Array([String(sourceCode)])); */
  /*   sendPrep(~params, ~method="eth_compileSolidity", ~id=idCounter^, ()); */
  /* }; */
};
