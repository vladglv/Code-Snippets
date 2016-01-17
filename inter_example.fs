module inter

let list_insert (e, n, list) = 
    let rec list_insert_helper (e, n, list, acc_i, acc) = 
        match list with
        | [] -> List.rev acc
        | x :: xs -> 
            if n = 0 then 
                    list_insert_helper (e, n, [], 1, List.rev (e :: list))
            else if n = acc_i then 
                    list_insert_helper (e, n, xs, acc_i + 1, e :: (x :: acc))
            else    list_insert_helper (e, n, xs, acc_i + 1, x :: acc)
    list_insert_helper (e, n, list, 1, [])

let inter item list = 
    let rec inter_helper (item, ilist, clist, pos, acc) = 
        match ilist with
        | [] -> List.rev (list_insert (item, pos, clist) :: acc)
        | x :: xs -> 
            inter_helper (item, xs, clist, pos + 1,
                         list_insert (item, pos, clist) :: acc)
    inter_helper (item, list, list, 0, [])

[<EntryPoint>]
let main args = 
    let test_list = [ 1; 2; 3 ]
    let test_item = 0
    printfn "Item to insert\t: %A" test_item
    printfn "Original list\t: %A" test_list
    printfn "Modified list\t: %A" (inter test_item test_list)
    // Return 0. This indicates success.
    0
