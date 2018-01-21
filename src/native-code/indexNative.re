open Lwt;

let query = s => {
  let uri = Uri.of_string(s);
  Cohttp_lwt_unix.Client.post(
    ~body=
      `String(
        {|{"jsonrpc":"2.0","method":"web3_clientVersion","params":[],"id":67}|}
      ),
    uri
  )
  >>= (
    ((resp, body)) =>
      Cohttp_lwt_body.to_string(body)
      >>= (
        as_string => {
          let a = 10;
          Lwt_io.printlf("Got: %s", as_string);
        }
      )
  );
};

module Handle =
  Types.Make(
    {
      type promise('a) = Lwt.t('a);
      let web3_clientVersion = () => assert false;
    }
  );

let () = {
  let program = query("http://localhost:8545");
  Lwt_main.run(program);
};
/* let () = Lwt_main.run(Lwt_io.printlf("Hello %s", "World")); */
/* print_endline("And now this is native code" ++ Common.a); */
