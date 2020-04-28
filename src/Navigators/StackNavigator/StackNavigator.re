open ReactNative;
include StackNavigatorActions;

type navigator('a) = {
  useNavigator: unit => (list('a), stackNavigationActions('a) => unit),
  buildNavigator: (~renderFunction: 'a => Route.t) => React.element,
};

module Navigator = {
  [@react.component]
  let make = (~initialRoute: 'a, ~renderFunction: 'a => Route.t, ~context) => {
    let initialState = {navigationStack: [initialRoute]};

    let reducer = (state, action) => {
      switch (action) {
      | PushRoute(route) => {
          navigationStack: [route, ...state.navigationStack],
        }
      | PopRoute =>
        switch (state.navigationStack) {
        | [] => {navigationStack: []}
        | [route] => {navigationStack: [route]}
        | [_currentRoute, ...pastRoutes] => {navigationStack: pastRoutes}
        }
      | PushAndReplaceRoute(route) =>
        switch (state.navigationStack) {
        | [] => {navigationStack: []}
        | [_currentRoute] => {navigationStack: [route]}
        | [_currentRoute, ...pastRoutes] => {
            navigationStack: [route, ...pastRoutes],
          }
        }
      };
    };

    let provider = React.Context.provider(context);

    let providerProps = (~value, ~children, ()) => {
      "value": value,
      "children": children,
    };

    let (state, dispatch) = React.useReducer(reducer, initialState);

    let children =
      <View style=Style.(viewStyle(~flex=1., ~width=100.->pct, ()))>
        {state.navigationStack
         ->Belt_List.reverse
         ->Belt_List.mapWithIndex((index, routeVariant) => {
             let route = renderFunction(routeVariant);
             let length = state.navigationStack->List.length;
             <StackContainer index length> {route.component} </StackContainer>;
           })
         ->Array.of_list
         ->React.array}
      </View>;

    React.createElement(
      provider,
      providerProps(~value=([initialRoute], dispatch), ~children, ()),
    );
  };
};

let createNavigator = (~initialRoute) => {
  let context = React.createContext(([initialRoute], ignore));

  let useNavigator = () => React.useContext(context);

  let buildNavigator = (~renderFunction) =>
    React.createElement(
      Navigator.make,
      Navigator.makeProps(~initialRoute, ~renderFunction, ~context, ()),
    );

  {useNavigator, buildNavigator};
};