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
  let (px, py) = body.position;
  let ((minX, minY), (maxX, maxY)) = bounds;
  let fxFinal = if (px < minX) {
    fxInitial +. (0.1 *. (minX -. px))
  } else if (px > maxX) {
    fxInitial +. (0.1 *. (maxX -. px))
  } else {
    fxInitial
  };
  let fyFinal = if (py < minY) {
    fyInitial +. (0.1 *. (minY -. py))
  } else if (py > maxY) {
    fyInitial +. (0.1 *. (maxY -. py))
  } else {
    fyInitial
  };
  step(delta, (fxFinal, fyFinal), body)
}