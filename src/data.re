type state = {
  input: Input.state,
  camera: Camera.camera,
  ship: Ship.ship,
  missiles: list(Missile.missile),
  terrain: list(Terrain.terrain)
};

let initial = (windowDimensions: Vector.vector) => {
  let camera = Camera.initial(windowDimensions);
  let viewBox = Camera.getViewBox(camera);
  {
    input: Input.initial,
    camera,
    ship: Ship.initial(viewBox),
    missiles: Missile.initial,
    terrain: Terrain.initial(viewBox)
  }
};

let update = (delta: float, keys: list(Input.key), state: state) => {
  let input = Input.update(keys, state.input);
  let camera = Camera.update(delta, state.camera);
  let viewBox = Camera.getViewBox(state.camera);
  let ship = Ship.update(delta, input, viewBox, state.ship);
  let missiles = Missile.updateList(delta, input, state.ship.position, viewBox, state.missiles);
  let terrain = Terrain.updateList(delta, viewBox, state.terrain);
  {
    input,
    ship,
    camera,
    missiles,
    terrain
  }
};
