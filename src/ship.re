type ship = Body.body;

let initial = (cameraResolution: Vector.vector): ship => {
  mass: 110.0,
  drag: 0.04,
  velocity: (0.0, 0.0),
  position: Vector.scale(0.5, cameraResolution)
};

let update = (delta: float, input: Input.state, bounds: Rectangle.rectangle, ship: ship): ship => {
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
  Body.updateInBounds(delta, (xForce, yForce), Rectangle.shrink(50.0, bounds), ship)
};
