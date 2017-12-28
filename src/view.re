let component = ReasonReact.statelessComponent("View");

let make = (~data: Game.state, _children) => {
  ...component,
  render: (_self) => {
    let cameraRectangle = Game.getCameraRectangle(data.camera);
    let ((viewportX, viewportY), _) = cameraRectangle;
    let (viewportWidth, viewportHeight) = Physics.getRectangleDimensions(cameraRectangle);
    let viewBox = Printf.sprintf(
      "%f %f %f %f",
      viewportX,
      -1.0 *. viewportY,
      viewportWidth,
      viewportHeight
    );
    let (positionX, positionY) = data.ship.position;
    <svg width=Printf.sprintf("%f", viewportWidth) height=Printf.sprintf("%f", viewportHeight) viewBox=viewBox>
      <g transform=("translate(0, 600) scale(1, -1)")>
        <pattern id="bg" patternUnits="userSpaceOnUse" width="414" height="414">
          <image xlinkHref="https://i.pinimg.com/originals/14/9d/60/149d605137f5e8462bb8de252afc4254.jpg" x="0" y="0" width="414" height="414" />
        </pattern>
        <rect fill="url(#bg)" width=Printf.sprintf("%f", viewportWidth) height=Printf.sprintf("%f", viewportHeight *. 100.0) y="0" stroke="none" />
        <circle
          cx=Printf.sprintf("%f", positionX)
          cy=Printf.sprintf("%f", positionY)
          r="10"
          fill="red"
        />
      </g>
    </svg>
  }
};
