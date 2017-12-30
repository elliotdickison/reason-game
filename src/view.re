let component = ReasonReact.statelessComponent("View");

let make = (~data: Data.state, _children) => {
  ...component,
  render: (_self) => {
    let ((viewBoxX, viewBoxY), (viewBoxWidth, viewBoxHeight)) = Camera.getViewBox(data.camera);
    let viewBox = Printf.sprintf(
      "%f %f %f %f",
      viewBoxX,
      -1.0 *. viewBoxY,
      viewBoxWidth,
      viewBoxHeight
    );
    let globalTransform = Printf.sprintf("translate(0, %f) scale(1, -1)", viewBoxHeight);
    let terrain = List.map((terrain: Terrain.terrain) => {
      let ((x, y), (width, height)) = terrain.bounds;
      <rect fill="url(#bg)" width=Printf.sprintf("%f", width) height=Printf.sprintf("%f", height) x=Printf.sprintf("%f", x) y=Printf.sprintf("%f", y) stroke="none" />
    }, data.terrain);
    let missiles = List.map((missile: Missile.missile) => {
      let ( positionX, positionY ) = missile.body.position;
      <circle
        cx=Printf.sprintf("%f", positionX)
        cy=Printf.sprintf("%f", positionY)
        r="3"
        fill="blue"
      />
    }, data.missiles);
    let (positionX, positionY) = data.ship.position;
    <svg width=Printf.sprintf("%f", viewBoxWidth) height=Printf.sprintf("%f", viewBoxHeight) viewBox=viewBox>
      <g transform=globalTransform>
        <pattern id="bg" patternUnits="userSpaceOnUse" width="414" height="414">
          <image xlinkHref="https://i.pinimg.com/originals/14/9d/60/149d605137f5e8462bb8de252afc4254.jpg" x="0" y="0" width="414" height="414" />
        </pattern>
        (ReasonReact.arrayToElement(Array.of_list(terrain)))
        <circle
          cx=Printf.sprintf("%f", positionX)
          cy=Printf.sprintf("%f", positionY)
          r="10"
          fill="red"
        />
        (ReasonReact.arrayToElement(Array.of_list(missiles)))
      </g>
    </svg>
  }
};
