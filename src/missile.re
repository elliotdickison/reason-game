type missile = {
  age : float,
  rate : float,
  body : Body.body
};

type state = {
  input : Input.state,
  camera : Camera.camera,
  ship : Ship.ship,
  missiles : list(missile)
};

let initial : list(missile) = [];

let canFire = (missiles : list(missile)) : bool =>
  switch missiles {
  | [] => true
  | [missile, ..._] => missile.age >= missile.rate
  };

let update = (delta : float, missile : missile) : missile => {
  ...missile,
  age: missile.age +. delta,
  body: Body.update(delta, (0.0, 0.00), missile.body)
};

let make = (position : Vector.vector) : missile => {
  let missileBody : Body.body = {
    mass: 1.0,
    drag: 0.0,
    velocity: (0.0, 10.0),
    position
  };
  {
    age: 0.0,
    rate: 100.0,
    body: missileBody
  }
};

let updateList = (delta : float, input : Input.state, spawnPosition : Vector.vector, bounds : Rectangle.rectangle, missiles : list(missile)) : list(missile) => {
  /* Add a new missile if input.fire is true and no missiles have been fired for
  `rate` ms */
  let missiles = if (input.fire && canFire(missiles)) {
    [make(spawnPosition), ...missiles]
  } else {
    missiles
  };
  /* update each missile (update age and position) */
  let updatedMissiles = List.map(update(delta), missiles);
  /* Filter out missiles that have moved offscreen */
  List.filter((missile : missile) =>
    Rectangle.containsPoint(missile.body.position, bounds), updatedMissiles)
};