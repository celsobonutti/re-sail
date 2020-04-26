open ReactNative;

[@react.component]
let make = (~numberOfTabs, ~scrollViewRef) => {
  let width = Dimensions.get(`screen).width;

  let styles =
    Style.(
      StyleSheet.create({
        "button": style(~flex=1., ~alignItems=`center, ()),
        "text": style(~color="blue", ~fontSize=16., ()),
      })
    );

  <View style=Style.(style(~width=100.->pct, ~flexDirection=`row, ()))>
    {{
       numberOfTabs->Belt_Array.makeBy(index =>
         <TouchableOpacity
           style=styles##button
           onPress={_ => {
             let targetWidth = width ** index->float_of_int;
             switch (scrollViewRef->React.Ref.current->Js.Nullable.toOption) {
             | Some(scrollView) =>
               scrollView->ScrollView.scrollTo(
                 ScrollView.scrollToParams(
                   ~x=targetWidth,
                   ~y=0.,
                   ~animated=true,
                   (),
                 ),
               )
             | _ => ()
             };
           }}>
           <Text style=styles##text>
             {index->string_of_int->React.string}
           </Text>
         </TouchableOpacity>
       );
     }
     ->React.array}
  </View>;
};