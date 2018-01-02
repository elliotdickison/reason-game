type feature =
  | Crater(Vector.vector, float);

type terrain = {
  bounds: Rectangle.rectangle,
  features: list(feature)
};

let generateCrater = (bounds: Rectangle.rectangle): feature => {
  let center = Rectangle.randomVector(bounds);
  let radius = 20.0 +. (Random.float(60.0));
  Crater(center, radius)
};

let rec generateCraters = (bounds: Rectangle.rectangle, count: int, features: list(feature)): list(feature) => {
  if (count > 0) {
    generateCraters(bounds, count - 1, [ generateCrater(bounds), ...features ])
  } else {
    features
  }
};

let generate = (bounds: Rectangle.rectangle): terrain => {
  bounds,
  features: generateCraters(bounds, 3, [])
};

let initial (viewBox: Rectangle.rectangle): list(terrain) = {
  let ((viewBoxX, viewBoxY), viewBoxDimensions) = viewBox;
  let (_, viewBoxHeight) = viewBoxDimensions;
  [
    generate(((viewBoxX, viewBoxY +. viewBoxHeight), viewBoxDimensions)),
    generate(viewBox)
  ]
};

let getWorldsEnd = (terrain: list(terrain)): float =>
  switch terrain {
    | [] => -1.0
    | [farthestTerrain, ..._] => {
      let ((_, y), (_, height)) = farthestTerrain.bounds;
      y +. height
    }
  };

let updateList = (_delta: float, viewBox: Rectangle.rectangle, terrain: list(terrain)): list(terrain) => {
  let ((viewBoxX, viewBoxY), (viewBoxWidth, viewBoxHeight)) = viewBox;
  let worldsEnd = getWorldsEnd(terrain);
  let updatedTerrain = if (worldsEnd < viewBoxY +. (viewBoxHeight *. 2.0)) {
    [
      generate(((viewBoxX, worldsEnd), (viewBoxWidth, viewBoxHeight))),
      ...terrain
    ]
  } else {
    terrain
  };
  List.filter((terrain: terrain) => {
   let ((_, terrainY), (_, terrainHeight)) = terrain.bounds;
   terrainHeight +. terrainY > viewBoxY
  }, updatedTerrain)
};
