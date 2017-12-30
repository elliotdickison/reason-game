type terrain = {
  bounds: Rectangle.rectangle
};

let initial (viewBox: Rectangle.rectangle): list(terrain) = {
  let ((viewBoxX, viewBoxY), viewBoxDimensions) = viewBox;
  let (_, viewBoxHeight) = viewBoxDimensions;
  [
    {
      bounds: ((viewBoxX, viewBoxY +. viewBoxHeight), viewBoxDimensions)
    },
    {
      bounds: ((viewBoxX, viewBoxY), viewBoxDimensions)
    }
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
      {
        bounds: ((viewBoxX, worldsEnd), (viewBoxWidth, viewBoxHeight))
      },
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
