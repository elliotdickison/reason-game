let component = ReasonReact.statelessComponent("View");

let make = (~data: Game.state, _children) => {
  ...component,
  render: (_self) => {
    let (viewportWidth, viewportHeight) = data.viewport;
    let (positionX, positionY) = data.ship.position;
    <svg width=string_of_float(viewportWidth) height=string_of_float(viewportHeight)>
      <g transform=("translate(0, 600) scale(1, -1)")>
        <pattern id="bg" patternUnits="userSpaceOnUse" width="414" height="414">
          <image xlinkHref="https://i.pinimg.com/originals/14/9d/60/149d605137f5e8462bb8de252afc4254.jpg" x="0" y="0" width="414" height="414" />
        </pattern>
        <rect fill="url(#bg)" width=string_of_float(viewportWidth) height=string_of_float(viewportHeight *. 100.0) y=string_of_float(viewportHeight *. -99.0) stroke="none" />
        <circle
          cx=string_of_float(positionX)
          cy=string_of_float(positionY)
          r="10"
          fill="red"
        />
      </g>
    </svg>
  }
};
