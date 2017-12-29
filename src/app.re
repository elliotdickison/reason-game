type state = {
  frame: int,
  timestamp: float,
  delta: float,
  keys: list(Input.key),
  game: Game.state,
};

type action =
 | Step(float)
 | InputKeyDown(string)
 | InputKeyUp(string)
 | NoOp;

let component = ReasonReact.reducerComponent("App");

let make = (_children) => {
  ...component,
  initialState: () => {
    frame: 0,
    timestamp: 0.0,
    delta: 0.0,
    keys: [],
    game: Game.initial((
      Document.Element.getWidth(Document.window),
      Document.Element.getHeight(Document.window)
    ))
  },
  reducer: (action, state) => {
    switch action {
      | Step(timestamp) => {
          let delta = timestamp -. state.timestamp;
          ReasonReact.Update({
            frame: state.frame + 1,
            timestamp: timestamp,
            delta,
            keys: List.map(Input.stepKey(delta), state.keys),
            game: Game.step(delta, state.keys, state.game)
          })
        }
      | InputKeyDown(keyName) => ReasonReact.Update({
          ...state,
          keys: [ (keyName, 0.0), ...state.keys ]
        })
      | InputKeyUp(keyName) => ReasonReact.Update({
          ...state,
          keys: List.filter(((name, _)) => name != keyName, state.keys)
        })
      | NoOp => ReasonReact.NoUpdate
    }
  },
  didMount: (self) => {
    Document.requestAnimationFrame(self.reduce((timestamp) => Step(timestamp)));
    Document.Event.addListener(
      Document.root,
      "keydown",
      self.reduce((event) => Document.Event.getRepeat(event) ? NoOp : InputKeyDown(Document.Event.getKey(event)))
    );
    Document.Event.addListener(
      Document.root,
      "keyup",
      self.reduce((event) => Document.Event.getRepeat(event) ? NoOp : InputKeyUp(Document.Event.getKey(event)))
    );
    ReasonReact.NoUpdate
  },
  didUpdate: ({ newSelf }) => Document.requestAnimationFrame(newSelf.reduce((timestamp) => Step(timestamp))),
  shouldUpdate: ({ oldSelf, newSelf }) => oldSelf.state.frame != newSelf.state.frame,
  render: (self) =>
    <div style=(ReactDOMRe.Style.make(~position="fixed", ~top="0", ~left="0", ~width="100vw", ~height="100vh", ()))>
      <View data={self.state.game} />
    </div>
};
