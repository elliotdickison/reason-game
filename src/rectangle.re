type rectangle = (Vector.vector, Vector.vector);

let shrink = (amount: float, r: rectangle) => {
  let (anchor, dimensions) = r;
  let shrinkVector = (amount, amount);
  (
    Vector.add(anchor, shrinkVector),
    Vector.add(dimensions, Vector.scale(-2.0, shrinkVector))
  )
};

let getBoundingPoints = (r: rectangle): (Vector.vector, Vector.vector) => {
  let ((x, y), (width, height)) = r;
  ((x, y), (x +. width, y +. height))
};

let getCenter = (r: rectangle): Vector.vector => {
  let (bottomLeft, topRight) = getBoundingPoints(r);
  Vector.scale(0.5, Vector.add(bottomLeft, topRight))
};

let containsPoint = (p: Vector.vector, r: rectangle) => {
  let (x, y) = p;
  let ((minX, minY), (maxX, maxY)) = getBoundingPoints(r);
  x >= minX && x <= maxX && y >= minY && y <= maxY
};

let randomVector = (r: rectangle): Vector.vector => {
  let ((x, y), (width, height)) = r;
  (x +. Random.float(width), y +. Random.float(height))
};