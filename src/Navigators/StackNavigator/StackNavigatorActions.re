type stackNavigationActions('a) =
  | PushRoute('a)
  | PopRoute
  | PushAndReplaceRoute('a);

type navigationState('a) = {navigationStack: list('a)};

type navigationActions('a) = stackNavigationActions('a) => unit;

