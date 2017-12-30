type state = {
  input : Input.state,
  camera : Camera.camera,
  ship : Ship.ship,
  missiles : list(Missile.missile)
};

let initial = (cameraResolution: Vector.vector) => {
  input: Input.initial,
  camera: Camera.initial(cameraResolution),
  ship: Ship.initial(cameraResolution),
  missiles: Missile.initial
};

let update = (delta: float, keys: list(Input.key), state: state) => {
  let input = Input.update(keys, state.input);
  let camera = Camera.update(delta, state.camera);
  let cameraBounds = Camera.getBounds(state.camera);
  let ship = Ship.update(delta, input, cameraBounds, state.ship);
  let missiles = Missile.updateList(delta, input, state.ship.position, cameraBounds, state.missiles);
  {
    input,
    ship,
    camera,
    missiles
  }
};
