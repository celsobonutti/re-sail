open ReactNative;

module Styles = {
  open Style;

  let container =
    viewStyle(~width=100.->pct, ~position=`absolute, ~height=100.->pct, ());
  let hidden = viewStyle(~display=`none, ());
};

[@react.component]
let make = (~children, ~index, ~length) => {
  let dimension = Dimensions.useWindowDimensions();
  let position = React.useRef(Animated.Value.create(dimension.height));

  React.useEffect0(() => {
    Animated.(
      timing(
        position->React.Ref.current,
        Value.Timing.config(
          ~useNativeDriver=true,
          ~toValue=0.->Value.create->Value.Timing.fromAnimatedValue,
          ~duration=200.,
          (),
        ),
      )
      ->Animation.start()
    );
    None;
  });

  <Animated.View
    style={Style.listOption([
      Some(Styles.container),
      index === length - 1 || index === length - 2
        ? None : Some(Styles.hidden),
      Some(
        Style.(
          style(
            ~transform=[|
              translateX(
                ~translateX=
                  position->React.Ref.current->Animated.StyleProp.float,
              ),
            |],
            (),
          )
        ),
      ),
    ])}>
    children
  </Animated.View>;
};