open Types.JSONRPC;

let extractError = e =>
  Json.(
    switch (get("code", e), get("message", e), get("data", e)) {
    | (Some(code), Some(message), data) => {
        code: stringify(code) |> int_of_string,
        message: stringify(message),
        data
      }
    | _ => assert false
    }
  );
