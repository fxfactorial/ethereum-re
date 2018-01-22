open Types.JSONRPC;

let stringOfRpcVersion: Types.rpcVersion => string =
  fun
  | `two_zero => "2.0";

let stringOfBlockTag: Types.blockTag => string =
  fun
  | `latest => "latest"
  | `earliest => "earliest"
  | `pending => "pending"
  | `blockNumber(a) => string_of_int(a);

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

let transactionToString: Types.transaction => string =
  ({from, to_, gas, gasPrice, value, data}) =>
    Json.(
      Object([
        ("from", String(from)),
        ("to", String(to_)),
        ("gas", String(gas)),
        ("gasPrice", String(gasPrice)),
        ("value", String(value)),
        ("data", String(data))
      ])
      |> stringify
    );
