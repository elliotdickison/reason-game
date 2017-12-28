type vector = (float, float);

let add = (a: vector, b: vector) => {
  let (aX, aY) = a;
  let (bX, bY) = b;
  (aX +. bX, aY +. bY)
};

let scale = (s: float, v: vector) => {
  let (x, y) = v;
  (x *. s, y *. s)
};