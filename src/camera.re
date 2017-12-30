type camera = {
  dimensions: Vector.vector,
  focus: Vector.vector,
};

let initial = (windowDimensions: Vector.vector): camera => {
  dimensions: windowDimensions,
  focus: Vector.scale(0.5, windowDimensions)
};

let getViewBox = (camera: camera): Rectangle.rectangle => (
  Vector.add(camera.focus, Vector.scale(-0.5, camera.dimensions)),
  camera.dimensions
);

let update = (delta: float, camera: camera): camera => {
  ...camera,
  focus: Vector.add(camera.focus, (0.0, delta *. 0.1))
};
