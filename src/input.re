type key = (string, float);

type steer = Left | Right | Straight;
type thrust = Forward | Neutral | Reverse;

type state = {
  steer: steer,
  thrust: thrust,
  fire: bool
};

let initial = {
  steer: Straight,
  thrust: Neutral,
  fire: false
};

let stepKey = (delta: float, key: key) => {
  let (name, duration) = key;
  (name, duration +. delta)
};

let getKeyDuration = (keys: list(key), name: string) => {
  let (_, duration) = try (List.find(((n, _)) => n == name, keys)) {
    | Not_found => (name, -1.0)
  };
  duration
};

let stepSteer = (keys: list(key)) => {
  let leftArrow = getKeyDuration(keys, "ArrowLeft");
  let rightArrow = getKeyDuration(keys, "ArrowRight");
  if (rightArrow >= 0.0 && (leftArrow == -1.0 || rightArrow < leftArrow)) {
    Right
  } else if (leftArrow >= 0.0 && (rightArrow == -1.0 || leftArrow < rightArrow)) {
    Left
  } else {
    Straight
  }
};

let stepThrust = (keys: list(key)) => {
  let upArrow = getKeyDuration(keys, "ArrowUp");
  let downArrow = getKeyDuration(keys, "ArrowDown");
  if (upArrow >= 0.0 && (downArrow == -1.0 || upArrow < downArrow)) {
    Forward
  } else if (downArrow >= 0.0 && (upArrow == -1.0 || downArrow < upArrow)) {
    Reverse
  } else {
    Neutral
  }
};

let stepFire = (keys: list(key)) => {
  let space = getKeyDuration(keys, " ");
  space === 0.0
};

let step = (keys: list(key), state: state) => {
  steer: stepSteer(keys),
  thrust: stepThrust(keys),
  fire: stepFire(keys)
}
