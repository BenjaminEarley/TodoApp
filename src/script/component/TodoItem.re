open Item;
open Util;

let component = ReasonReact.statelessComponent("TodoItem");
let make = (~item, ~onToggle, ~onDelete, children) => {
  ...component,
  render: (_) => {
    let checkboxId = "checkbox-" ++ string_of_int(item.id);
    <div className="item mdc-form-field">
      <div className="mdc-checkbox">
        <input 
          _type="checkbox" 
          className="mdc-checkbox__native-control" 
          onClick=((evt) => onToggle())
          id=checkboxId 
          checked=(Js.Boolean.to_js_boolean(item.completed))/>
        <div className="mdc-checkbox__background">
          <svg className="mdc-checkbox__checkmark" 
               viewBox="0 0 24 24">
            <path className="mdc-checkbox__checkmark-path" 
                  fill="none" 
                  d="M1.73,12.91 8.1,19.28 22.79,4.59"/>
          </svg>
          <div className="mdc-checkbox__mixedmark"/>
        </div>
      </div>
      <label htmlFor=checkboxId>(str(item.title))</label>
      <i onClick=((evt) => onDelete()) className="material-icons md-18 light">(str("clear"))</i>
    </div>
  }
};
