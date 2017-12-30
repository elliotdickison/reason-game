/* Element */

type element;

module Element {
  [@bs.get] external getWidth: element => float = "innerWidth";
  [@bs.get] external getHeight: element => float = "innerHeight";
};

/* Event */

type event;

module Event {
  [@bs.get] external getKey: event => string = "key";

  [@bs.get] external getRepeat: event => bool = "repeat";

  [@bs.send] external addListener :
    element =>
    string =>
    (event => unit) =>
    unit = "addEventListener";
};

/* Values */

[@bs.val] external requestAnimationFrame: (float => unit) => unit = "requestAnimationFrame";

[@bs.val] external root: element = "document";
[@bs.val] external window: element = "window";