module permute

let rec perm l = 
    match l with
    | [] -> [ [] ]
    | x :: xs -> List.concat (List.map (interleave.inter x) (perm xs))

let test_list0 = []
let test_list1 = [ 1..1..1 ]
let test_list2 = [ 1..1..2 ]
let test_list3 = [ 1..1..3 ]

printf "%A\n" (perm test_list0)
printf "%A\n" (perm test_list1)
printf "%A\n" (perm test_list2)
printf "%A\n" (perm test_list3)