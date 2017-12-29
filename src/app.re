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
    game: Game.initial
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
  render: (self) => {
    let (_, vy) = self.state.game.ship.velocity;
    <div>
      <View data={self.state.game} />
      (ReasonReact.stringToElement("Framerate: " ++ string_of_float(1000.0 /. self.state.delta)))
      (ReasonReact.stringToElement("Velocity: " ++ string_of_float(vy)))
      (ReasonReact.stringToElement("Missiles: " ++ string_of_int(List.length(self.state.game.missiles))))
      (ReasonReact.stringToElement("Keys: " ++ String.concat(" : ", List.map(((name, duration)) => name ++ " " ++ string_of_float(duration), self.state.keys))))
    </div>
  }
};
