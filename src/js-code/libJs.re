let send = (~conn: Types.connection, ~params: Json.t, ~method, ~id, ()) =>
  Js.Promise.(
    Fetch.fetchWithInit(
      conn.Types.endpoint,
      Fetch.RequestInit.make(
        ~method_=Post,
        ~body=Fetch.BodyInit.make(Util.makeMsg(conn, method, id, params)),
        ()
      )
    )
    |> then_(Fetch.Response.json)
    |> then_(reply => Js.Result.Ok(reply) |> resolve)
    |> catch(oops => Js.Result.Error(oops) |> resolve)
  );

class common (~connection: Types.connection) = {
  val idCounter = ref(-1);
  val sendPrep = send(~conn=connection);
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
