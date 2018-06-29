open Item;
open Util;

let component = ReasonReact.statelessComponent("TodoItem");
let make = (~item, ~onToggle, children) => {
  ...component,
  render: (_) => {
    let checkbox = "checkbox-" ++ string_of_int(item.id);
    <div className="item mdc-form-field">
      <div className="mdc-checkbox">
        <input 
          _type="checkbox" 
          className="mdc-checkbox__native-control" 
          onClick=((evt) => onToggle())
          id=checkbox 
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
      <label htmlFor=checkbox>(str(item.title))</label>
    </div>
  }
};
