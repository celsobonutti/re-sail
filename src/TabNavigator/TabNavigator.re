open ReactNative;

[@react.component]
let make = (~tabs: list(React.element)) => {
  let dimensions = Dimensions.useWindowDimensions();
  let scrollViewRef = React.useRef(Js.Nullable.null);

  let styles =
    Style.(
      StyleSheet.create({
        "container": viewStyle(~flex=1., ~flexDirection=`row, ()),
        "page": style(~width=dimensions.width->dp, ()),
      })
    );

  <View style=Style.(style(~height=100.->pct, ~width=100.->pct, ()))>
    <ScrollView
      horizontal=true
      pagingEnabled=true
      showsHorizontalScrollIndicator=false
      ref=scrollViewRef>
      <View style=styles##container>
        {tabs
         ->Belt_List.map(element =>
             <View
               key={"tab_" ++ Random.bits()->string_of_int} style=styles##page>
               element
             </View>
           )
         ->Array.of_list
         ->React.array}
      </View>
    </ScrollView>
    <TabButtons numberOfTabs={tabs->List.length} scrollViewRef />
  </View>;
};