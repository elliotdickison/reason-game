type rectangle = (Vector.vector, Vector.vector);

let getDimensions = (r: rectangle) => {
  let (bottomLeft, topRight) = r;
  Vector.add(topRight, Vector.scale(-1.0, bottomLeft))
};

let shrink = (s: float, r: rectangle) => {
  let (bottomLeft, topRight) = r;
  let shrinkVector = (s, s);
  (
    Vector.add(bottomLeft, shrinkVector),
    Vector.add(topRight, Vector.scale(-1.0, shrinkVector))
  )
};

let containsPoint = (p: Vector.vector, r: rectangle) => {
  let (x, y) = p;
  let ((minX, minY), (maxX, maxY)) = r;
  x >= minX && x <= maxX && y >= minY && y <= maxY
};