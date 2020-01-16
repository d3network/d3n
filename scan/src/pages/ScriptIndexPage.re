module Styles = {
  open Css;

  let pageContainer = style([paddingTop(`px(50))]);

  let vFlex = style([display(`flex), flexDirection(`row), alignItems(`center)]);

  let logo = style([width(`px(27)), marginRight(`px(10))]);

  let sourceContainer = style([marginTop(`px(15))]);

  let seperatedLine =
    style([
      width(`px(13)),
      height(`px(1)),
      marginLeft(`px(10)),
      marginRight(`px(10)),
      backgroundColor(Colors.grayHeader),
    ]);

  let codeVerifiedBadge =
    style([
      backgroundColor(`hex("D7FFEC")),
      borderRadius(`px(6)),
      display(`inlineFlex),
      justifyContent(`center),
      alignItems(`center),
      padding4(~top=`px(10), ~bottom=`px(10), ~left=`px(13), ~right=`px(13)),
    ]);

  let checkLogo = style([marginRight(`px(10))]);

  let tableContainer = style([border(`px(1), `solid, Colors.lightGray)]);

  let tableHeader = style([backgroundColor(Colors.white), padding(`px(20))]);

  let tableLowerContainer =
    style([
      padding(`px(20)),
      backgroundImage(
        `linearGradient((
          deg(0.0),
          [(`percent(0.0), Colors.white), (`percent(100.0), Colors.lighterGray)],
        )),
      ),
    ]);

  let codeTabHeader =
    style([
      lineHeight(`px(20)),
      borderBottom(`px(1), `solid, Colors.lightGray),
      margin2(`px(0), `px(5)),
    ]);

  let mediumText = style([fontSize(`px(14)), lineHeight(`px(20))]);

  let maxHeight20 = style([maxHeight(`px(20))]);
};

[@react.component]
let make = (~codeHash, ~hashtag: Route.script_tab_t) => {
  let scriptOpt = ScriptHook.getInfo(codeHash);
  // let txHash = {
  //   switch (scriptOpt) {
  //   | Some(script) => script.txHash
  //   | None => "" |> Hash.fromHex
  //   };
  // };
  // let txOpt = TxHook.atHash(txHash);
  // Js.Console.log(txOpt);
  <div className=Styles.pageContainer>
    <Row justify=Row.Between>
      <Col>
        <div className=Styles.vFlex>
          <img src=Images.newScript className=Styles.logo />
          <Text
            value="DATA REQUEST SCRIPT"
            weight=Text.Semibold
            size=Text.Lg
            nowrap=true
            color=Colors.grayHeader
            block=true
          />
          <HSpacing size=Spacing.sm />
          <div className=Styles.seperatedLine />
          {switch (scriptOpt) {
           | Some(script) =>
             <TimeAgos time={script.createdAtTime} size=Text.Lg weight=Text.Regular />
           | None => React.null
           }}
        </div>
      </Col>
      <Col>
        {switch (scriptOpt) {
         | Some(_) =>
           <div className=Styles.codeVerifiedBadge>
             <img src=Images.checkIcon className=Styles.checkLogo />
             <Text
               value="Code Verified"
               size=Text.Lg
               weight=Text.Semibold
               color=Colors.darkGreen
             />
           </div>
         | None => React.null
         }}
      </Col>
    </Row>
    <div className=Styles.sourceContainer>
      <Text
        value={
          switch (scriptOpt) {
          | Some(script) => script.name
          | None => "?"
          }
        }
        size=Text.Xxl
        weight=Text.Bold
        nowrap=true
      />
    </div>
    <VSpacing size=Spacing.xl />
    <InfoHL
      info={
        InfoHL.DataSources(
          scriptOpt->Belt_Option.mapWithDefault([], script =>
            script.dataSources->Belt_List.map(source => source.name)
          ),
        )
      }
      header="DATA SOURCES"
    />
    <VSpacing size=Spacing.xl />
    <Row>
      <Col>
        <InfoHL info={InfoHL.Hash(codeHash, Colors.brightPurple)} header="SCRIPT HASH" />
      </Col>
      <HSpacing size=Spacing.xl />
      <HSpacing size=Spacing.xl />
      <Col>
        {switch (scriptOpt) {
         | Some(script) =>
           <InfoHL info={InfoHL.Address(script.creator, Colors.brightPurple)} header="CREATOR" />
         | None => React.null
         }}
      </Col>
    </Row>
    <VSpacing size=Spacing.xl />
    <div className=Styles.tableContainer>
      <div className=Styles.tableHeader>
        <Row>
          <TabButton
            active={hashtag == ScriptTransactions}
            text="Transactions"
            route={Route.ScriptIndexPage(codeHash, ScriptTransactions)}
          />
          <HSpacing size=Spacing.lg />
          <TabButton
            active={hashtag == ScriptCode}
            text="Code"
            route={Route.ScriptIndexPage(codeHash, ScriptCode)}
          />
          <HSpacing size=Spacing.lg />
          <TabButton
            active={hashtag == ScriptIntegration}
            text="Integration"
            route={Route.ScriptIndexPage(codeHash, ScriptIntegration)}
          />
        </Row>
      </div>
      {switch (hashtag) {
       | ScriptTransactions =>
         <div className=Styles.tableLowerContainer>
           <Text value="196 Request Transactions" color=Colors.grayHeader size=Text.Lg />
           <VSpacing size=Spacing.lg />
           <TxsTable txs=[] />
           <VSpacing size=Spacing.lg />
           <LoadMore />
         </div>
       | ScriptCode =>
         <div className=Styles.tableLowerContainer>
           <div className=Styles.codeTabHeader>
             <Row>
               <Col size=1.0>
                 <Row>
                   <Col size=1.0>
                     <Text value="Platform" color=Colors.darkGrayText size=Text.Lg />
                   </Col>
                   <Col size=1.0> <Text value="OWASM v0.1" size=Text.Lg /> </Col>
                 </Row>
               </Col>
               <Col size=1.0>
                 <Row>
                   <Col size=1.0>
                     <Text value="Parameters" color=Colors.darkGrayText size=Text.Lg />
                   </Col>
                   <Col size=1.0> <Text value="2" size=Text.Lg /> </Col>
                 </Row>
               </Col>
             </Row>
             <VSpacing size=Spacing.lg />
             <Row>
               <Col size=1.0>
                 <Row>
                   <Col size=1.0>
                     <Text value="Language" color=Colors.darkGrayText size=Text.Lg />
                   </Col>
                   <Col size=1.0> <Text value="Rust 1.39.0" size=Text.Lg /> </Col>
                 </Row>
               </Col>
               <Col size=1.0> <div /> </Col>
             </Row>
             <VSpacing size=Spacing.lg />
           </div>
           <VSpacing size=Spacing.xl />
           <Row>
             <img src=Images.textDocument className=Styles.maxHeight20 />
             <HSpacing size=Spacing.md />
             <Text value="Cargo.toml" size=Text.Lg color=Colors.grayHeader />
           </Row>
           <VSpacing size=Spacing.md />
           <div className=Styles.mediumText>
             <ReactHighlight> {CodeExample.toml |> React.string} </ReactHighlight>
           </div>
           <VSpacing size=Spacing.xl />
           <Row>
             <img src=Images.textDocument className=Styles.maxHeight20 />
             <HSpacing size=Spacing.md />
             <Text value="src/logic.rs" size=Text.Lg color=Colors.grayHeader />
           </Row>
           <VSpacing size=Spacing.md />
           <div className=Styles.mediumText>
             <ReactHighlight> {CodeExample.logic |> React.string} </ReactHighlight>
           </div>
         </div>
       | ScriptIntegration => <div> {"TODO2" |> React.string} </div>
       }}
    </div>
    <VSpacing size=Spacing.xxl />
  </div>;
};
