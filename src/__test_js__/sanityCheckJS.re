[%raw "require('isomorphic-fetch')"];

let () = {
  let conn = Types.{endpoint: "http://localhost:8545", rpcVersion: `two_zero};
  let web3 = (new LibJs.web3)(~connection=conn, ());
  web3#sha3("0x68656c6c6f20776f726c64")
  /* web3#clientVersion */
  |> Js.Promise.then_(s => {
       switch s {
       | Js.Result.Ok(s) => Js.log(s)
       | _ => ()
       };
       Js.Promise.resolve();
     });
  ();
};
