let query = s => {
  open Lwt;
  let uri = Uri.of_string(s);
  Cohttp_lwt_unix.Client.post(
    ~body=
      `String(
        {|{"jsonrpc":"2.0","method":"web3_clientVersion","params":[],"id":67}|}
      ),
    uri
  )
  >>= (((resp, body)) => Cohttp_lwt_body.to_string(body));
};

let (|>>) = (value, fn) =>
  switch value {
  | None => None
  | Some(v) => fn(v)
  };

module Handle =
  Types.Make(
    {
      type promise('a) = Lwt.t('a);
      open Lwt;
      let web3_clientVersion = () =>
        query("http://localhost:8545")
        >>= (
          response => {
            open Json;
            open Types.JSONRPC;
            let parsed = parse(response);
            let result =
              switch (
                get("jsonrpc", parsed),
                get("result", parsed),
                get("error", parsed),
                get("id", parsed)
              ) {
              | (_, None, Some(oops), _) => {
                  jsonrpc: "10",
                  result: None,
                  error: None,
                  id: "1"
                }
              | (None, Some(result), None, None) => {
                  jsonrpc: "10",
                  result: None,
                  error: None,
                  id: "1"
                }
              | _ => assert false
              };
            Lwt.return(result);
          }
        );
      let web3_sha3 = s => assert false;
      let net_version = s => assert false;
    }
  );

let () = {
  open Lwt;
  let a = Handle.web3_clientVersion() >>= (s => Lwt.return_unit);
  let program = query("http://localhost:8545");
  Lwt_main.run(program) |> ignore;
};
/* let () = Lwt_main.run(Lwt_io.printlf("Hello %s", "World")); */
/* print_endline("And now this is native code" ++ Common.a); */
