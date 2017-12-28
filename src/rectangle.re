type rectangle = ((float, float), (float, float));

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