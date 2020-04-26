open ReactNative;

[@react.component]
let make = (~tabs : list(Route.t), ~scrollViewRef) => {
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
       tabs->Belt.List.mapWithIndex((index, element) =>
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
             {element.title->React.string}
           </Text>
         </TouchableOpacity>
       );
     }
     ->Array.of_list
     ->React.array}
  </View>;
};