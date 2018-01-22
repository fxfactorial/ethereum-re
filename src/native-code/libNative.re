open Lwt;

let send = (~conn: Types.connection, ~uri, ~params: Json.t, ~method, ~id, ()) =>
  /* print_endline(msg); */
  Cohttp_lwt_unix.Client.post(~body=`String(Util.makeMsg(conn, method, id, params)), uri)
  >>= (((resp, body)) => Cohttp_lwt_body.to_string(body));

class common (~connection: Types.connection) = {
  val idCounter = ref(-1);
  val sendPrep = send(~conn=connection, ~uri=Uri.of_string(connection.endpoint));
};

class web3 (~connection: Types.connection, ()) = {
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

class net (~connection: Types.connection, ()) = {
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

class eth (~connection: Types.connection, ()) = {
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
};
