module inter

let list_insert (e, n, list) = 
    let len = List.length list
    
    let rec helper (e, n, l, acc) = 
        match l with
        | [] -> 
            if n = len then [ e ]
            else []
        | x :: xs -> 
            if n = acc then e :: x :: helper (e, n, xs, acc + 1)
            else x :: helper (e, n, xs, acc + 1)
    helper (e, n, list, 0)

let inter item list = 
    let rec helper (item, ilist, clist, pos) = 
        match ilist with
        | [] -> [ list_insert (item, pos, clist) ]
        | x :: xs -> 
            list_insert (item, pos, clist) :: helper (item, xs, clist, pos + 1)
    helper (item, list, list, 0)

[<EntryPoint>]
let main args = 
    let test_list = [ 1; 2; 3 ]
    let test_item = 0
    printfn "Item to insert\t: %A" test_item
    printfn "Original list\t: %A" test_list
    printfn "Modified list\t: %A" (inter test_item test_list)
    // Return 0. This indicates success.
    0