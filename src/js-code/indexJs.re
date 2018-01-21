Js.log("This is running on Js code" ++ Common.a);

module Handle =
  Types.Make(
    {
      type promise('a) = Js.Promise.t('a);
      let web3_clientVersion = () => assert false;
    }
  );

let () = {
  let a = 10;
  Js.log("Hello");
};
