open Util;

type state = string;
let component = ReasonReact.reducerComponent("Input");
let make = (~onSubmit, _) => {
  ...component,
  initialState: () => "",
  reducer: (newText, _text) => ReasonReact.Update(newText),
  render: ({state: text, reduce}) =>
    <div className="mdc-text-field">
      <input
        value=text
        _type="text"
        className="mdc-text-field__input"
        placeholder="Write something to do"
        onChange=(reduce((evt) => valueFromEvent(evt)))
        onKeyDown=((evt) =>
          if (ReactEventRe.Keyboard.key(evt) == "Enter") {
            onSubmit(text);
            (reduce(() => ""))()
          }
        )/>
      <div className="mdc-line-ripple"/>
    </div>
};