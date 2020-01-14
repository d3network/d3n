module Styles = {
  open Css;
  let fullWidth = style([width(`percent(100.0)), display(`flex)]);
};

[@react.component]
let make = (~txs: list(TxHook.Tx.t)=[]) => {
  <>
    <THead>
      <Row>
        <Col> <div className=TElement.Styles.msgIcon /> </Col>
        <Col size=1.0>
          <div className=TElement.Styles.hashContainer>
            <Text block=true value="TX HASH" size=Text.Sm weight=Text.Bold color=Colors.grayText />
          </div>
        </Col>
        <Col size=0.5>
          <Text block=true value="TYPE" size=Text.Sm weight=Text.Bold color=Colors.grayText />
        </Col>
        <Col size=0.2>
          <Text block=true value="BLOCK" size=Text.Sm weight=Text.Bold color=Colors.grayText />
        </Col>
        <Col size=1.1>
          <Text block=true value="SENDER" size=Text.Sm weight=Text.Bold color=Colors.grayText />
        </Col>
        <Col size=0.6>
          <div className=TElement.Styles.feeContainer>
            <Text block=true value="FEE" size=Text.Sm weight=Text.Bold color=Colors.grayText />
          </div>
        </Col>
      </Row>
    </THead>
    {txs
     ->Belt.List.mapWithIndex((idx, {blockHeight, hash, timestamp, gasUsed, messages, sender}) => {
         <TBody key={idx |> string_of_int}>
           <div
             className=Styles.fullWidth
             onClick={_ => Route.TxIndexPage(hash |> Hash.toHex(~with0x=true)) |> Route.redirect}>
             <Row>
               <Col>
                 <TElement elementType={messages->Belt.List.getExn(0)->TElement.Icon} />
               </Col>
               <Col size=1.0> <TElement elementType={TElement.TxHash(hash, timestamp)} /> </Col>
               <Col size=0.5>
                 <TElement
                   elementType={messages->Belt.List.getExn(0)->TElement.TxTypeWithDetail}
                 />
               </Col>
               <Col size=0.2> <TElement elementType={TElement.Height(blockHeight)} /> </Col>
               <Col size=1.1> <TElement elementType={sender->TElement.Address} /> </Col>
               <Col size=0.6> <TElement elementType={0.->TElement.Fee} /> </Col>
             </Row>
           </div>
         </TBody>
       })
     ->Array.of_list
     ->React.array}
  </>;
};
