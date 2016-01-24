module interleave

let rec inter e l = 
    match l with
    | [] -> [ [ e ] ]
    | x :: xs -> (e :: x :: xs) :: List.map (fun u -> x :: u) (inter e xs)
        
let test_list = [ 1 .. 1 .. 16 ]
let test_item = 0
let test_rslt = (inter test_item test_list)

printfn "Item to insert\t: %A" test_item
printfn "Original list\t: %A" test_list
printfn "Modified list\t: %A" test_rslt