module Crescent {
  type radius =
    | Inside(float)
    | Outside(float);

  let component = ReasonReact.statelessComponent("Crescent");

  let make = (
    ~center: Vector.vector,
    ~radius: radius,
    ~thickness: float,
    ~angle: float,
    ~color: string,
    ~backgroundColor: string,
    _children
  ) => {
    ...component,
    render: (_self) => {
      let (x, y) = center;
      let (r, ryInner, ryOuter) = switch radius {
        | Inside(r) => (r, r, r +. thickness)
        | Outside(r) => (r, r -. thickness, r)
      };
      <g transform=Printf.sprintf("rotate(%f, %f, %f)", angle, x, y)>
        <defs>
          <clipPath id=Printf.sprintf("ellipse-clip-%f-%f", x, y)>
            <rect
              x=Printf.sprintf("%f", x -. r)
              y=Printf.sprintf("%f", y)
              width=Printf.sprintf("%f", r *. 2.0)
              height=Printf.sprintf("%f", r +. thickness)
            />
          </clipPath>
        </defs>
        <ellipse
          className="ellipse-outer"
          cx=Printf.sprintf("%f", x)
          cy=Printf.sprintf("%f", y)
          rx=Printf.sprintf("%f", r)
          ry=Printf.sprintf("%f", ryOuter)
          fill=color
          clipPath=Printf.sprintf("url(#ellipse-clip-%f-%f", x, y)
        />
        <ellipse
          className="ellipse-inner"
          cx=Printf.sprintf("%f", x)
          cy=Printf.sprintf("%f", y)
          rx=Printf.sprintf("%f", r)
          ry=Printf.sprintf("%f", ryInner)
          fill=backgroundColor
          clipPath=Printf.sprintf("url(#ellipse-clip-%f-%f", x, y)
        />
      </g>
    }
  }
};

module Crater {
  let component = ReasonReact.statelessComponent("Crater");

  let make = (~position: Vector.vector, ~radius: float, _children) => {
    ...component,
    render: (_self) => {
      let (x, y) = position;
      <g>
        <Crescent
          center=position
          radius=Crescent.Inside(radius)
          thickness=(0.24 *. radius)
          angle=45.0
          color="#e5ebdf"
          backgroundColor="#c4ccbf"
        />
        <Crescent
          center=position
          radius=Crescent.Inside(radius)
          thickness=(0.24 *. radius)
          angle=(225.0)
          color="#a2ae98"
          backgroundColor="#c4ccbf"
        />
        <circle
          className="crater"
          cx=Printf.sprintf("%f", x)
          cy=Printf.sprintf("%f", y)
          r=Printf.sprintf("%f", radius)
          fill="#c4ccbf"
        />
        <Crescent
          center=position
          radius=Crescent.Outside(0.84 *. radius)
          thickness=(0.14 *. radius)
          angle=45.0
          color="#a2ae98"
          backgroundColor="#c4ccbf"
        />
        <Crescent
          center=position
          radius=Crescent.Outside(0.84 *. radius)
          thickness=(0.14 *. radius)
          angle=(225.0)
          color="#e5ebdf"
          backgroundColor="#c4ccbf"
        />
      </g>
    }
  }
};

module Ship {
  let component = ReasonReact.statelessComponent("Ship");

  let make = (~position: Vector.vector, _children) => {
    ...component,
    render: (_self) => {
      let (x, y) = position;
      <g>
        <circle
          cx=Printf.sprintf("%f", x)
          cy=Printf.sprintf("%f", y)
          r="20"
          fill="#db4d3f"
        />
        <Crescent
          center=position
          radius=Crescent.Outside(20.0)
          thickness=(6.0)
          angle=225.0
          color="#bb5144"
          backgroundColor="#db4d3f"
        />
        <circle
          cx=Printf.sprintf("%f", x)
          cy=Printf.sprintf("%f", y)
          r="10"
          fill="#aadbfe"
        />
      </g>
    }
  }
};

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
      <rect fill="#d7ddd1" width=Printf.sprintf("%f", width) height=Printf.sprintf("%f", height) x=Printf.sprintf("%f", x) y=Printf.sprintf("%f", y) stroke="none" />
    }, data.terrain);
    let features = data.terrain
      |> List.fold_left((features, terrain: Terrain.terrain) => List.append(terrain.features, features), [])
      |> List.map((feature: Terrain.feature) => switch feature {
          | Crater(position, radius) => <Crater position=position radius=radius />
        });
    let missiles = List.map((missile: Missile.missile) => {
      let ( positionX, positionY ) = missile.body.position;
      <circle
        cx=Printf.sprintf("%f", positionX)
        cy=Printf.sprintf("%f", positionY)
        r="3"
        fill="#1ca362"
      />
    }, data.missiles);
    <svg width=Printf.sprintf("%f", viewBoxWidth) height=Printf.sprintf("%f", viewBoxHeight) viewBox=viewBox>
      <g transform=globalTransform>
        (ReasonReact.arrayToElement(Array.of_list(terrain)))
        (ReasonReact.arrayToElement(Array.of_list(features)))
        (ReasonReact.arrayToElement(Array.of_list(missiles)))
        <Ship position=data.ship.position />
      </g>
    </svg>
  }
};
