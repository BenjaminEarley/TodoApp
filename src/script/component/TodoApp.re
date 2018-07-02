open Util;
open Item;

type state = {
  items: list(item)
};
type action =
  | AddItem(string)
  | ToggleItem(int)
  | DeleteItem(int);

let component = ReasonReact.reducerComponent("TodoApp");

let lastId = ref(0);
let newItem = (text) => {
  lastId := lastId^ + 1;
  {id: lastId^, title: text, completed: false}
};
let make = (children) => {
  ...component,
  initialState: () => {
    items: []
  },
  reducer: (action, {items}) =>
    switch action {
    | AddItem(text) => ReasonReact.Update({items: [newItem(text), ...items]})
    | ToggleItem(id) =>
      let items =
        List.map(
          (item) =>
            item.id === id ?
              {...item, completed: ! item.completed} : item,
          items
        );
      ReasonReact.Update({items: items})
    | DeleteItem(id) =>
      let items =
        List.filter(
          (item) => item.id === id ? false : true,
          items
        );
      ReasonReact.Update({items: items})
    },
  render: ({state: {items}, reduce}) => {
    let numItems = List.length(items);
    <div className="mdc-card todo-card">
      <div className="mdc-typography--headline5 title">
        (str("What to do"))
        <Input onSubmit=(reduce((text) => AddItem(text))) />
      </div>
      <div className="items">
        (
          ReasonReact.arrayToElement(Array.of_list(List.map(
            (item) =>
              <TodoItem
                key=(string_of_int(item.id))
                onToggle=(reduce(() => ToggleItem(item.id)))
                onDelete=(reduce(() => DeleteItem(item.id)))
                item
              />,
            items
          )))
        )
      </div>
      <div className="mdc-typography--overline footer">
        (str(string_of_int(numItems) ++ " items"))
      </div>
    </div>
  }
};