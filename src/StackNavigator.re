open ReactNative;

type stackNavigationActions('a) =
  | PushRoute('a)
  | PopRoute;

type navigationState('a) = {navigationStack: list('a)};

type navigationActions('a) = stackNavigationActions('a) => unit;

let reducer = (state, action) => {
  switch (action) {
  | PushRoute(route) => {navigationStack: [route, ...state.navigationStack]}
  | PopRoute =>
    switch (state.navigationStack) {
    | [] => {navigationStack: []}
    | [route] => {navigationStack: [route]}
    | [_head, ...tail] => {navigationStack: tail}
    }
  };
};

[@react.component]
let make =
    (
      ~initialRoute: 'a,
      ~renderFunction: ('a, navigationActions('a)) => React.element,
    ) => {
  let initialState = {navigationStack: [initialRoute]};

  let (state, dispatch) = React.useReducer(reducer, initialState);

  <View style=StyleSheet.absoluteFill>
    <SafeAreaView>
      {state.navigationStack
       ->Belt_List.mapWithIndex((index, element) => {
           let display = index == 0 ? `flex : `none;
           <View style=Style.(style(~display, ()))>
             {renderFunction(element, dispatch)}
           </View>;
         })
       ->Array.of_list
       ->React.array}
    </SafeAreaView>
  </View>;
};