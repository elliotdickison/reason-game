type ship = Physics.dynamicBody;

type state = {
  input: Input.state,
  viewport: (float, float),
  ship: ship,
};

let initial = {
  input: Input.initial,
  viewport: (600.0, 600.0),
  ship: {
    mass: 100.0,
    drag: 0.04,
    velocity: (0.0, 0.0),
    position: (300.0, 60.0)
  }
};

let stepShip = (delta: float, input: Input.state, ship: ship) => {
  let xForce = switch input.steer {
    | Left => -2.0
    | Right => 2.0
    | Straight => 0.0
  };
  let yForce = switch input.thrust {
    | Forward => 2.0
    | Reverse => -2.0
    | Neutral => 0.0
  };
  Physics.stepDynamicBodyInBounds(delta, (xForce, yForce), ((50.0, 50.0), (550.0, 550.0)), ship)
};

let step = (delta: float, keys: list(Input.key), state: state) => {
  let input = Input.step(keys, state.input);
  let ship = stepShip(delta, input, state.ship);
  {
    ...state,
    input,
    ship
  }
};
