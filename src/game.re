type ship = Body.body;
type missile = Body.body;

type camera = {
  resolution: (float, float),
  focus: Vector.vector,
};

type state = {
  input: Input.state,
  camera: camera,
  ship: ship,
  missiles: list(missile)
};

let initial = {
  input: Input.initial,
  camera: {
    resolution: (600.0, 600.0),
    focus: (300.0, 60.0)
  },
  ship: {
    mass: 110.0,
    drag: 0.04,
    velocity: (0.0, 0.0),
    position: (300.0, 60.0)
  },
  missiles: []
};

let getCameraRectangle = (camera: camera) =>
  (
    Vector.add(camera.focus, Vector.scale(-0.5, camera.resolution)),
    Vector.add(camera.focus, Vector.scale(0.5, camera.resolution))
  );

let stepShip = (delta: float, input: Input.state, bounds: Rectangle.rectangle, ship: ship) => {
  let xForce = switch input.steer {
    | Left => -1.8
    | Right => 1.8
    | Straight => 0.0
  };
  let yForce = switch input.thrust {
    | Forward => 1.8
    | Reverse => -1.8
    | Neutral => 0.0
  };
  Body.stepInBounds(delta, (xForce, yForce), bounds, ship)
};

let stepCamera = (delta: float, camera: camera) => {
  let (x, y) = camera.focus;
  {
    ...camera,
    focus: (x, y +. (delta *. 0.1))
  }
};

let stepMissiles = (delta: float, input: Input.state, state: state): list(missile) => {
  let missiles = if (input.fire) {
    let (_, velocityY) = state.ship.velocity;
    let missile: missile = {
      mass: 1.0,
      drag: 0.0,
      velocity: (0.0, 12.0),
      position: state.ship.position
    };
    [missile, ...state.missiles]
  } else {
    state.missiles
  };
  let steppedMissiles = List.map(Body.step(delta, (0.0, 0.00)), missiles);
  List.filter((missile: missile) => {
    let (_, missilePositionY) = missile.position;
    let (_, (_, cameraMaxY)) = getCameraRectangle(state.camera);
    missilePositionY <= cameraMaxY
  }, steppedMissiles)
};

let step = (delta: float, keys: list(Input.key), state: state) => {
  let input = Input.step(keys, state.input);
  let cameraBounds = Rectangle.shrink(50.0, getCameraRectangle(state.camera));
  let ship = stepShip(delta, input, cameraBounds, state.ship);
  let camera = stepCamera(delta, state.camera);
  let missiles = stepMissiles(delta, input, state);
  {
    input,
    ship,
    camera,
    missiles
  }
};
