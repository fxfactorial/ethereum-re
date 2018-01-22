open Lwt;

let () = {
  let conn = Types.{endpoint: "http://localhost:8545", rpcVersion: `two_zero};
  let web3 = (new Native.web3)(~connection=conn, ());
  let net = (new Native.net)(~connection=conn, ());
  Lwt_main.run(
    net#listening
    >>= (
      s =>
        Lwt_io.printlf("Got: %s", s)
        >>= (() => net#peerCount >>= (another => Lwt_io.printlf("Later: %s", another)))
    )
  );
};
