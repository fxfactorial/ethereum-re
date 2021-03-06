open Lwt;

let () = {
  let connection = Types.{endpoint: "http://localhost:8545", rpcVersion: `two_zero};
  let web3 = (new LibNative.web3)(~connection);
  let net = (new LibNative.net)(~connection);
  Lwt_main.run(
    net#listening
    >>= (
      s =>
        Lwt_io.printlf("Got: %s", s)
        >>= (() => net#peerCount >>= (another => Lwt_io.printlf("Later: %s", another)))
    )
  );
};
