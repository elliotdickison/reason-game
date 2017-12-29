type body = {
  mass: float,
  drag: float,
  velocity: Vector.vector,
  position: Vector.vector,
};

/* f == m * a == m * ((vi - vt) / dt) */
let step = (delta: float, force: Vector.vector, body: body) => {
  let (pxInitial, pyInitial) = body.position;
  let (vxInitial, vyInitial) = body.velocity;
  let (fx, fy) = force;
  let vxFinal = vxInitial +. (delta *. (fx /. body.mass)) -. (vxInitial *. body.drag);
  let vyFinal = vyInitial +. (delta *. (fy /. body.mass)) -. (vyInitial *. body.drag);
  let pxFinal = pxInitial +. vxFinal;
  let pyFinal = pyInitial +. vyFinal;
  {
    ...body,
    velocity: (vxFinal, vyFinal),
    position: (pxFinal, pyFinal)
  }
};

let stepInBounds = (delta: float, force: Vector.vector, bounds: Rectangle.rectangle, body: body) => {
  let (fxInitial, fyInitial) = force;
  let (x, y) = body.position;
  let ((minX, minY), (maxX, maxY)) = bounds;
  let fxFinal = if (x < minX) {
    fxInitial +. (0.1 *. (minX -. x))
  } else if (x > maxX) {
    fxInitial +. (0.1 *. (maxX -. x))
  } else {
    fxInitial
  };
  let fyFinal = if (y < minY) {
    fyInitial +. (0.1 *. (minY -. y))
  } else if (y > maxY) {
    fyInitial +. (0.1 *. (maxY -. y))
  } else {
    fyInitial
  };
  step(delta, (fxFinal, fyFinal), body)
}