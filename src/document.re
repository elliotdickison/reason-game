/* Element */

type element;

module Element {
  [@bs.get] external getWidth : element => int = "innerWidth";
  [@bs.get] external getHeight : element => int = "innerHeight";

  [@bs.set] external setWidth : element => int => unit = "width";
  [@bs.set] external setHeight : element => int => unit = "height";
};

/* Event */

type event;

module Event {
  [@bs.get] external getKey : event => string = "key";

  [@bs.get] external getRepeat : event => bool = "repeat";

  [@bs.send] external addListener :
    element =>
    string =>
    (event => unit) =>
    unit = "addEventListener";
};

/* Values */

[@bs.val] external requestAnimationFrame : (float => unit) => unit = "requestAnimationFrame";

[@bs.val] external root : element = "document";