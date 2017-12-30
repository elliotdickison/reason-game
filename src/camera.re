type camera = {
  resolution : Vector.vector,
  focus : Vector.vector,
};

let initial = (cameraResolution : Vector.vector) : camera => {
  resolution: cameraResolution,
  focus: Vector.scale(0.5, cameraResolution)
};

let getBounds = (camera : camera) : Rectangle.rectangle => (
  Vector.add(camera.focus, Vector.scale(-0.5, camera.resolution)),
  Vector.add(camera.focus, Vector.scale(0.5, camera.resolution))
);

let update = (delta : float, camera : camera) : camera => {
  ...camera,
  focus: Vector.add(camera.focus, (0.0, delta *. 0.1))
};
