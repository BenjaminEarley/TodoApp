open Item;
open JustgageReasonCookie;

let valueFromEvent = (evt) : string => (
  evt
  |> ReactEventRe.Form.target
  |> ReactDOMRe.domElementToObj
)##value;

let str = ReasonReact.stringToElement;

let serialize = (~items: list(item)): string => {
  let helper = (~item) => {
    "(" ++ string_of_int(item.id) ++ " " ++ item.title ++ " " ++ string_of_bool(item.completed) ++ ")"
  };
  switch items {
    | [] => "()"
    | list => List.fold_left((acc, x) => acc ++ helper(x), "(", list) ++ ")"
  };
};

let deserialize = (~x: string): option(list(item)) => {
  let deserializeBool = (~index) => {
    let endIndex = String.index_from(x, index, ')');
    let completed = String.sub(x, index, endIndex - index) |> bool_of_string;
    (completed, endIndex + 1)
  };
  let deserializeString = (~index) => {
    let spaceIndex = String.index_from(x, index, ' ');
    let label = String.sub(x, index, spaceIndex - index);
    (label, spaceIndex + 1)
  };
  let deserializeInt = (~index) => {
    let spaceIndex = String.index_from(x, index, ' ');
    let number = String.sub(x, index, spaceIndex - index) |> int_of_string;
    (number, spaceIndex + 1)
  };
  let deserializeItem = (~index) => {
    switch (String.get(x, index)) {
      | '(' => {
          let (id, index) = deserializeInt(index + 1);
          let (label, index) = deserializeString(index);
          let (completed, index) = deserializeBool(index);
          Some(({id: id, title: label, completed: completed} , index))
        }
      | _ => None
    }
  };
  let deserializeHelper = (~index) => {
    let rec helper = (~i) => {
      switch (deserializeItem(i)) {
        | Some((item, ii)) => {
          let (xs, iii) = helper(ii);
          ([item, ...xs], iii)
        }
        | None => ([], i)   
      }
    };
    switch (String.get(x, index)) {
      | '(' => {
          let (items, i) = helper(index + 1);
          if (String.get(x, i) == ')') Some(items)
          else None
        }
      | _ => None
    }
  };
  deserializeHelper(0)
};

let getSavedItems = () => Cookie.getAsString("todo");

let saveItems = (~items) => Cookie.setString("todo", serialize(items));
