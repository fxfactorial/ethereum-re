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

/* verify that it starts with 0x and is length 42 */
let verifyHexlength = s => true;
