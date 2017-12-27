type vector = (float, float);
type rectangle = (vector, vector);

type dynamicBody = {
  mass: float,
  drag: float,
  velocity: vector,
  position: vector,
};

let addVectors = (a: vector, b: vector) => {
  let (aX, aY) = a;
  let (bX, bY) = b;
  (aX +. bX, aY +. bY)
};

let scaleVector = (s: float, v: vector) => {
  let (x, y) = v;
  (x *. s, y *. s)
};

/* f == m * a == m * ((vi - vt) / dt) */
let stepDynamicBody = (delta: float, force: vector, body: dynamicBody) => {
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

let stepDynamicBodyInBounds = (delta: float, force: vector, bounds: rectangle, body: dynamicBody) => {
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
  stepDynamicBody(delta, (fxFinal, fyFinal), body)
}