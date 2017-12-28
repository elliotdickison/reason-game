type ship = Physics.dynamicBody;

type camera = {
  resolution: Physics.vector,
  focus: Physics.vector,
};

type state = {
  input: Input.state,
  camera: camera,
  ship: ship,
};

let initial = {
  input: Input.initial,
  camera: {
    resolution: (600.0, 600.0),
    focus: (300.0, 60.0)
  },
  ship: {
    mass: 100.0,
    drag: 0.04,
    velocity: (0.0, 0.0),
    position: (300.0, 60.0)
  }
};

let getCameraRectangle = (camera: camera) =>
  (
    Physics.addVectors(camera.focus, Physics.scaleVector(-0.5, camera.resolution)),
    Physics.addVectors(camera.focus, Physics.scaleVector(0.5, camera.resolution))
  );

let stepShip = (delta: float, input: Input.state, bounds: Physics.rectangle, ship: ship) => {
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
  Physics.stepDynamicBodyInBounds(delta, (xForce, yForce), bounds, ship)
};

let stepCamera = (delta: float, camera: camera) => {
  let (x, y) = camera.focus;
  {
    ...camera,
    focus: (x, y +. (delta *. 0.1))
  }
};

let step = (delta: float, keys: list(Input.key), state: state) => {
  let input = Input.step(keys, state.input);
  let cameraBounds = Physics.shrinkRectangle(50.0, getCameraRectangle(state.camera));
  let ship = stepShip(delta, input, cameraBounds, state.ship);
  let camera = stepCamera(delta, state.camera);
  {
    input,
    ship,
    camera
  }
};
