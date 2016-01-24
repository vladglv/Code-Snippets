module interleave

let inter e l = 
    let rec helper e il cl acc pos =
        match il with
        | [] -> (e :: cl) :: acc
        | x :: xs -> 
            let t_ = List.splitAt pos cl;
            helper e xs cl (((fst t_) @ (e :: (snd t_))) :: acc) (pos - 1)
    helper e l l [] (List.length l)
        
let test_list = [ 1 .. 1 .. 16 ]
let test_item = 0
let test_rslt = (inter test_item test_list)

printfn "Item to insert\t: %A" test_item
printfn "Original list\t: %A" test_list
printfn "Modified list\t: %A" test_rslt