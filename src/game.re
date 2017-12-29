type ship = Body.body;
type missile = {
  age : float,
  rate: float,
  body : Body.body
};

type camera = {
  resolution: Vector.vector,
  focus: Vector.vector,
};

type state = {
  input: Input.state,
  camera: camera,
  ship: ship,
  missiles: list(missile)
};

let initial = (cameraResolution: Vector.vector) => {
  input: Input.initial,
  camera: {
    resolution: cameraResolution,
    focus: Vector.scale(0.5, cameraResolution)
  },
  ship: {
    mass: 110.0,
    drag: 0.04,
    velocity: (0.0, 0.0),
    position: Vector.scale(0.5, cameraResolution)
  },
  missiles: []
};

let canFireMissile = (missiles: list(missile)) =>
  switch missiles {
  | [] => true
  | [missile, ..._] => missile.age >= missile.rate
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

let stepMissile = (delta : float, missile : missile) : missile => {
  ...missile,
  age: missile.age +. delta,
  body: Body.step(delta, (0.0, 0.00), missile.body)
};

let stepMissiles = (delta: float, input: Input.state, state: state): list(missile) => {
  /* Add a new missile if input.fire is true and no missiles have been fired for
  `rate` ms */
  let missiles = if (input.fire && canFireMissile(state.missiles)) {
    let missileBody: Body.body = {
      mass: 1.0,
      drag: 0.0,
      velocity: (0.0, 10.0),
      position: state.ship.position
    };
    let missile: missile = {
      age: 0.0,
      rate: 100.0,
      body: missileBody
    };
    [missile, ...state.missiles]
  } else {
    state.missiles
  };
  /* Step each missile (update age and position) */
  let steppedMissiles = List.map(stepMissile(delta), missiles);
  /* Filter out missiles that have moved offscreen */
  List.filter((missile: missile) => {
    let (_, missilePositionY) = missile.body.position;
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
