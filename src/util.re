open Types.JSONRPC;

let stringOfRpcVersion: Types.rpcVersion => string =
  fun
  | `two_zero => "2.0";

let stringOfBlockTag: Types.blockTag => Json.t = {
  let helper =
    fun
    | `latest => "latest"
    | `earliest => "earliest"
    | `pending => "pending"
    | `blockNumber(a) => a;
  s => Json.String(helper(s));
};

/* |> fun s => Json.String(s) */
let extractError = e =>
  Json.(
    switch (get("code", e), get("message", e), get("data", e)) {
    | (Some(code), Some(message), data) => {
        code: stringify(code) |> int_of_string,
        message: stringify(message),
        data
      }
    /* Later do a better exception */
    | _ => assert false
    }
  );

let makeMsg = (conn, method, id, params) =>
  Json.Object([
    ("jsonrpc", Json.String(conn.Types.rpcVersion |> stringOfRpcVersion)),
    ("method", Json.String(method)),
    ("params", params),
    ("id", Json.Number(float_of_int(id)))
  ])
  |> Json.stringify;

let withField = fieldName =>
  fun
  | None => []
  | Some(s) => [(fieldName, Json.String(s))];

let transactionToString: Types.transaction => Json.t =
  ({from, to_, gas, gasPrice, value, data}) =>
    Json.(
      Object(
        List.flatten([
          withField("from", from),
          withField("to", to_),
          withField("gas", gas),
          withField("gasPrice", gasPrice),
          withField("value", value),
          withField("data", data)
        ])
      )
    );

let safeGet = (key, json) =>
  switch (Json.get(key, json)) {
  | None => None
  | Some(s) => Some(Json.stringify(s))
  };

let unsafeGet = (key, json) =>
  switch (Json.get(key, json)) {
  | None => raise(Not_found)
  | Some(s) => Json.stringify(s)
  };

let parseTransaction = t =>
  switch (Json.parse(t)) {
  | Json.Null => None
  | s =>
    Some(
      Types.{
        hash: unsafeGet("hash", s),
        nonce: unsafeGet("nonce", s),
        blockHash: safeGet("blockHash", s),
        blockNumber: safeGet("blockNumber", s),
        transactionIndex: safeGet("transactionIndex", s),
        from: unsafeGet("from", s),
        to_: safeGet("to", s),
        value: unsafeGet("value", s),
        gasPrice: unsafeGet("gasPrice", s),
        gas: unsafeGet("gas", s),
        input: unsafeGet("input", s)
      }
    )
  };

let topicToJson: Types.topic => Json.t =
  Json.(
    fun
    | Anything => Array([])
    | AInFirst(a) => Array([String(a)])
    | AnyInFirstBInSecond(b) => Array([Null, String(b)])
    | AInFirstAndBInSecond(a, b) => Array([String(a), String(b)])
    | AOrBInFirstAndAOrBInSecond(a, b) =>
      Array([Array([String(a), String(b)]), Array([String(a), String(b)])])
  );

let filterToJson: Types.filter => Json.t = Json.(({fromBlock, toBlock, address, topics}) => Null);

/* verify that it starts with 0x and is length 42 */
let verifyHexlength = s => true;
