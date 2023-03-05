
-- =============== DO NOT MODIFY ===================

{-# LANGUAGE ExistentialQuantification #-}
{-# LANGUAGE FlexibleInstances #-}

-- ==================================================

module Tasks where

import Dataset
import Data.List
import Text.Printf
import Data.Array

import Common

type CSV = String
type Value = String
type Row = [Value]
type Table = [Row]
type ColumnName = String

-- Prerequisities
split_by :: Char -> String -> [String]
split_by x = foldr op [""]
  where op char acc
            | char == x = "":acc
            | otherwise = (char:head(acc)):tail(acc)

read_csv :: CSV -> Table
read_csv = (map (split_by ',')) . (split_by '\n')

write_csv :: Table -> CSV
write_csv = (foldr (++) []).
            (intersperse "\n").
            (map (foldr (++) [])).
            (map (intersperse ","))


{-
    TASK SET 1
-}

-- Functii auxiliare task1
transposeTable :: [[String]] -> [[String]]
transposeTable ([]:_) = []
transposeTable mat = map (\x -> head x) mat : transposeTable( map (tail) mat )

f = read "12"::Int

my_sum::[Int]->Int
my_sum [] = 0
my_sum (x:xs) = x + sum xs

my_sum2::[String]->Int
my_sum2 [] = 0
my_sum2 (x:xs) = (read x :: Int) + my_sum2 xs

my_sum3 :: [String]->[String]
my_sum3 eight_hours =  map tail eight_hours

l = transposeTable eight_hours
l2 = drop 1 l
l3 = transposeTable l2

f2 :: [[ String]]->[Int]
f2 = map my_sum2

a = f2 l3
totalSteps2 = drop 1 a

my_div::Int->Float
my_div x = fromIntegral x / fromIntegral 8

totalSteps = map my_div totalSteps2

idk ::[Float]-> [String]
idk = map (\x->(printf("%.2f")) x::String)

var = idk totalSteps



names =  map head eight_hours

first_line = ["Name","Average Number of Steps"]

all_names = drop 1 names

g::[String]->[[String]]
g [] = []
g (x:xs) = [[x]]++(g xs)

names_column = g all_names
stringTotalSteps = map show totalSteps

other_lines = zipWith (++) names_column (g var )

final_answer = first_line : other_lines





-- Task 1

compute_average_steps :: Table -> Table
compute_average_steps m = final_answer

--End Task 1




-- Task 2
--Functii auxiliare Task 2
count_people ::[Int]->Int
count_people [] = 0
count_people (x:xs)
    | x >= 1000 = 1 + count_people xs
    | otherwise = count_people xs
nr = count_people totalSteps2

how_many_people::[Int]->Int
how_many_people [] = 0
how_many_people (x:xs) = 1 + (how_many_people xs)

nrTotal = how_many_people totalSteps2


-- Number of people who have achieved their goal:
get_passed_people_num :: Table -> Int
get_passed_people_num m = nr




-- Percentage of people who have achieved their:
get_passed_people_percentage :: Table -> Float
get_passed_people_percentage m = fromIntegral nr / fromIntegral nrTotal


-- Average number of daily steps
get_steps_avg :: Table -> Float
get_steps_avg m = fromIntegral (my_sum totalSteps2) / fromIntegral nrTotal


--functii ajutatoare pentru Task 3
transposeInt ([]:_) = []
transposeInt m = (map head m):(transposeInt ( map (tail) m ))

my_table = drop 1 l3

parseString::[String]->[Int]
parseString [] = []
parseString (x:xs) = [(read x :: Int)]++ (parseString xs)

my_table2 = map parseString my_table
my_table2Tr= transposeInt my_table2

suma_pe_coloane = map my_sum my_table2Tr
avg_pe_coloane = map (\x -> fromIntegral x / fromIntegral nrTotal) suma_pe_coloane

first_line2 = [["H10", "H11", "H12", "H13", "H14", "H15", "H16", "H17"]] 
avg_pe_coloane_string = idk avg_pe_coloane
final_answerTask3 = first_line2 ++ [avg_pe_coloane_string]

-- Task 3

get_avg_steps_per_h :: Table -> Table
get_avg_steps_per_h m = final_answerTask3

-- Functii ajutatoare Task 4
list = drop 1 physical_activity -- tabelul ramane fara prima linie
my_list = map tail (map tail (map tail list)) 
-- ne-au ramas in tabel doar VeryActiveMinutes, FairlyActiveMinutes si LightlyActiveMinutes columns
task4_table = map parseString my_list

range1::[Int]->Int
range1 [] = 0
range1 (x:xs)
    | ((0<=x) && (x<50)) = 1 + (range1 xs)
    | otherwise = (range1 xs)

range2::[Int]->Int
range2 [] = 0
range2 (x:xs)
    | ((50<=x) && (x<100)) = 1 + (range2 xs)
    | otherwise = (range2 xs)

range3::[Int]->Int
range3 [] = 0
range3 (x:xs)
    | ((100<=x) && (x<500)) = 1 + (range3 xs)
    | otherwise = (range3 xs)     

my_VeryActiveMinutesR1 = range1 (map head task4_table )
my_VeryActiveMinutesR2 = range2 (map head task4_table )
my_VeryActiveMinutesR3 = range3 (map head task4_table )

--aici elimin coloana VeryActiveMinutes, astfel incat prima coloana devine FairlyActiveMinutes
task4_table2 = map tail task4_table
my_FairlyActiveMinutesR1 = range1 (map head task4_table2 )
my_FairlyActiveMinutesR2 = range2 (map head task4_table2 )
my_FairlyActiveMinutesR3 = range3 (map head task4_table2 )

--aici elimin coloana VeryActiveMinutes, astfel incat prima coloana devine LightlyActiveMinutes
task4_table3 = map tail task4_table2
my_LightlyActiveMinutesR1 = range1 (map head task4_table3 )
my_LightlyActiveMinutesR2 = range2 (map head task4_table3 )
my_LightlyActiveMinutesR3 = range3 (map head task4_table3 )

denumire_tabel = ["column", "range1", "range2", "range3"]
line1 = ["VeryActiveMinutes"] ++ 
        [show my_VeryActiveMinutesR1] ++ 
        [show my_VeryActiveMinutesR2] ++ 
        [show my_VeryActiveMinutesR3]


line2 = ["FairlyActiveMinutes"] ++ 
        [show my_FairlyActiveMinutesR1] ++ 
        [show my_FairlyActiveMinutesR2] ++ 
        [show my_FairlyActiveMinutesR3]


line3 = ["LightlyActiveMinutes"] ++ 
        [show my_LightlyActiveMinutesR1] ++ 
        [show my_LightlyActiveMinutesR2] ++  
        [show my_LightlyActiveMinutesR3]

answerT4 = [denumire_tabel]  ++ [line1] ++ [line2] ++ [line3]
-- Task 4

get_activ_summary :: Table -> Table
get_activ_summary m = answerT4


-- Task 5
--Functii auxiliare pentru Task 5
list_tr = transposeTable list -- unde list este acelasi tabel de la task4, putem folosi aceasi var
my_listT5 = take 2 list_tr

-- tabel ce contine doar primele 2 coloane, nume si total number of steps
lista_mea = transposeTable my_listT5


-- tip de element comparat exemplu: ["Olivia Noah","13162"]
-- sortare dupa intul din dreapta si in caz de egalitate, lexicografic dupa numele de pe 
--                                                                  prima pozitie din lista [String]
myCompare::[String]->[String]->Ordering
myCompare a b 
        | (  ( (read (head (tail a))::Int) ) < ( (read (head (tail b)) ::Int) ) )  = LT
        | (  ( (read (head (tail a))::Int) ) > ( (read (head (tail b)) ::Int) ) )  = GT
        | ((head a) > (head b)) = GT -- daca ajunge aici se compara numele, 
        | ((head a) < (head b)) = LT --                         daca int-urile sunt egale
        | otherwise = EQ

my_insertBy :: ([String]->[String]->Ordering) -> [String] -> [[String]] ->[[String]]
my_insertBy nume_functie y [] = [y]
my_insertBy nume_functie y (x:xs) 
    | ((nume_functie x y) == LT ) = [x] ++ (my_insertBy nume_functie y xs)
    | otherwise = [y]++(x:xs)

insertSortBy :: ([String]->[String]->Ordering) -> [[String]] -> [[String]]
insertSortBy nume_functie [] = []
insertSortBy nume_functie (x:xs) = my_insertBy nume_functie x (insertSortBy nume_functie xs)

lista_mea_sortata = insertSortBy myCompare lista_mea
prima_linie = [["Name","Total Steps"]]

result_t5 = prima_linie ++ lista_mea_sortata

get_ranking :: Table -> Table
get_ranking m = result_t5


-- Functii auxiliare Task6
l6 = drop 1 eight_hours
hours = drop 1 l3

first4hList = map (take 4) hours
last4hList = map (drop 4) hours


-- suma in primele 4 ore, respectiv ultimele 4 ore
total_first4h = map my_sum2 first4hList
total_last4h = map my_sum2 last4hList


my_div2::Int->Float
my_div2 x = fromIntegral x / fromIntegral 4
-- media aritmetica in primele 4h, respectiv ultimele 4h
avg_first4h = map my_div2 total_first4h
avg_last4h = map my_div2 total_last4h

-- functia anonima intoarce diferenta modulelor, pentru a calcula diferenta 
--                                                          intre average 4h mare - average 4h mic
diff = zipWith (\x y -> if x>y then x-y else y-x) avg_first4h avg_last4h


coloana_avg_first4h = idk avg_first4h
coloana_avg_last4h = idk avg_last4h
coloana_diff = idk diff

linie_cap_table=[["Name", "Average first 4h", "Average last 4h", "Difference"]]

tabel_netranspus_nesortat = [(drop 1 names)] ++ 
                            [coloana_avg_first4h] ++ 
                            [coloana_avg_last4h] ++ 
                            [coloana_diff]

tabel_nesortat = transposeTable tabel_netranspus_nesortat


-- exemplu read:                     f = read "12"::Int
-- exemplu extragere camp diff de pe linia curenta
-- a2 = (read (head (drop 3 my_elem))::(Float))

myCompare2::[String]->[String]->Ordering
myCompare2 a b 
        | ( (read (head (drop 3 a))::(Float)) < ( read (head (drop 3 b))::(Float) ) ) = LT
        | ( (read (head (drop 3 a))::(Float)) > ( read (head (drop 3 b))::(Float) ) ) = GT
        | ((head a) > (head b)) = GT -- daca ajunge aici se compara numele,
        | ((head a) < (head b)) = LT --                          daca int-urile sunt egale
        | otherwise = EQ
--Testing myCompare2
--my_elem = ["Olivia Noah","171.00","0.00","171.00"] -- exemplu visual pentru Ordering de Stringuri
--my_elem2 = ["Olivia 2Noah","171.00","0.00","2171.00"]

tabel_sortat = insertSortBy myCompare2 tabel_nesortat
result_t6 = linie_cap_table ++ tabel_sortat

-- Task 6

get_steps_diff_table :: Table -> Table
get_steps_diff_table m = result_t6


-- Task 7

-- Applies the given function to all the values
vmap :: (Value -> Value) -> Table -> Table
vmap f m = map (map f) m


-- Task 8
--Task-uri auxiliare task 8


-- Convertim un int la un float
intToF::Int->Float
intToF x = fromIntegral x / fromIntegral 1


-- Applies the given function to all the entries
rmap :: (Row -> Row) -> [String] -> Table -> Table
rmap f s m = map f m


get_sleep_total :: Row -> Row
get_sleep_total r = (take 1 r) ++ [   printf "%.2f"  ((intToF (my_sum2 (drop 1 r)) )::Float)  ]




{-
    TASK SET 2
-}

-- Functii auxiliare Task 1 

determina_coloana :: String -> [String] -> Int ->Int
determina_coloana nume_col [] contor = -1
determina_coloana nume_col (x:xs) contor
    | ( nume_col == x ) = contor 
    | otherwise = determina_coloana nume_col xs ( contor + 1 )

det_column :: String -> [String]  -> Int
det_column nume_col lista = determina_coloana nume_col lista 0

-- sortez dupa valoare in coloana, adica in cadrul liniei de la indicele determinat cu functia det_column

myCompare3::String->[[String]]->[String]->[String]->Ordering
myCompare3 column table a b
    | (( read ( a !! det_column column (head table) ) :: (Float)) < 
                                            ( read ( b !! det_column column (head table) ) :: (Float))) = LT
    | (( read ( a !! det_column column (head table) ) :: (Float)) > 
                                            ( read ( b !! det_column column (head table) ) :: (Float))) = GT
    | (( head a ) < ( head b )) = LT    -- comparam lexicografic dupa prima coloana daca ajunge aici
    | (( head a ) > ( head b )) = GT    -- se compara lexicografic 
    | otherwise = EQ

-- Task 1

tsort :: ColumnName -> Table -> Table
tsort column table = [(head table )] ++ insertSortBy (myCompare3 column table) (drop 1 table)
    
-- Task 2
{-
Implement a function which takes Tables t1 and t2 and adds all rows from t2 at the end of t1, if column names coincide.
If columns names are not the same, t1 remains unchanged. 
-}

--aux3 verifica daca coincid coloanele celor 2 tabele
aux3 :: [[String]] -> [[String]] -> Int
aux3 t1 t2 
    | (head t1) == (head t2) = 1
    | otherwise = 0


vunion :: Table -> Table -> Table
vunion t1 t2 
    | (aux3 t1 t2 == 1 ) = t1 ++ (drop 1 t2)
    | otherwise = t1 

-- Task 3
-- Functii auxiliare Task3

nr_linii :: [[String]] -> Int
nr_linii [] = 0
nr_linii (x:xs) = 1 + (nr_linii xs)

nr_coloane :: [ String ] -> Int
nr_coloane [] = 0
nr_coloane (x:xs) = 1 + (nr_coloane xs)

compara_nr_linii :: [[String]]->[[String]]->Int
compara_nr_linii t1 t2
    | (nr_linii t1) > (nr_linii t2) = 1
    | (nr_linii t1) < (nr_linii t2) = -1
    | otherwise = 0

dif_nr_linii :: [[String]] -> [[String]] -> Int 
dif_nr_linii t1 t2 = ( nr_linii t1 ) - ( nr_linii t2 ) 

dif_nr_coloane:: [[String]] -> [[String]] -> Int
dif_nr_coloane t1 t2 = abs (nr_coloane (head t1) - nr_coloane (head t2))
    
fill_rows :: Int -> [String]
fill_rows 0 = []
fill_rows x = [""] ++ fill_rows (x - 1)

-- adaug la tabelul care are numarul minim de linii
hunion :: [[String]] -> [[String]] -> [[String]]
hunion t1 t2 
    | (dif_nr_linii t1 t2 == 0) = zipWith (++) t1 t2 
    | (dif_nr_linii t1 t2 > 0) = zipWith (++) t1 ( t2 ++ 
                        (replicate (dif_nr_linii t1 t2) (replicate ( nr_coloane (head t2)) "")) )
    | otherwise = zipWith (++) (t1 ++ 
                        (replicate (dif_nr_linii t2 t1) (replicate (nr_coloane (head t1)) ""))) t2



-- Functii auxiliara Task 4

find_index_aux :: String -> [[String]] -> Int -> Int
find_index_aux nume_linie [] contor = -1
find_index_aux nume_linie (x:xs) contor
    | (head x) == nume_linie = contor
    | otherwise = find_index_aux nume_linie xs (contor + 1 )

find_index :: String -> [[String]]-> Int
find_index nume_linie t = find_index_aux nume_linie t 0

get_index :: Int-> [[String]] -> [String]
get_index n t =  head (drop n t)

remove_index :: Int -> [[String]] -> [[String]]
remove_index _ [] = []
remove_index n (x:xs)
    | (n == 0) = xs
    |  otherwise = [x] ++ ( remove_index ( n - 1 ) xs ) 

functie:: [[String]] -> [[String]]
functie [] = []
functie (x:xs)
    | ( (find_index (head x) xs) == -1) = [x] ++ (functie xs)
    | ( ((get_index (find_index (head x) xs) xs ) !! 1) /= "") = 
                                [ (get_index (find_index (head x) xs) xs )] 
                                    ++ functie ( remove_index (find_index (head x) xs) xs ) 
    | otherwise = [x] ++ functie ( remove_index (find_index (head x) xs) xs )

functie_aux :: [String]->[String]->[String]->[String]->[[String]]
functie_aux cap_tabel1 linie1 cap_tabel2 linie2 =
                transposeTable( hunion ([cap_tabel1] ++ [linie1] ) ([cap_tabel2] ++ [linie2] ) )
                
prelucrare_tabele2_aux::String->Int->[[String]]->Int->[[String]]->[[String]]
prelucrare_tabele2_aux col _ [] _ _ = []
prelucrare_tabele2_aux col index_t1 (x:xs) index_t2 (y:ys)
    | ((x !! index_t1 ) == (y !! index_t2 )) = [x] ++ (prelucrare_tabele2_aux col index_t1 xs index_t2 ys)
    | otherwise = prelucrare_tabele2_aux col index_t1 xs index_t2 (y:ys)

prelucrare_tabele2 :: String ->[[String]] -> [[String]]->[[String]]
prelucrare_tabele2 col t1 t2 = prelucrare_tabele2_aux col (det_column col (head t1)) t1 (det_column col (head t2)) t2

definetly_merging_aux ::[[String]]-> [String]->[[String]] -> [String] ->[[String]]
definetly_merging_aux [] _ _ _= []
definetly_merging_aux (x:xs) cap_tabel1 (y:ys) cap_tabel2 =
    tail (transposeTable(functie (functie_aux cap_tabel1 x cap_tabel2 y)))
             ++ (definetly_merging_aux xs cap_tabel1 ys cap_tabel2)
 
definetly_merging :: [[String]]->[[String]]->[[String]]
definetly_merging t1 t2 = definetly_merging_aux t1 (head t1) t2 (head t2) 


-- Task 4

tjoin :: ColumnName -> Table -> Table -> Table
tjoin key_column t1 t2 = definetly_merging ( prelucrare_tabele2 key_column t1 t2 ) t2

concateneaza_table:: [Table] -> Table
concateneaza_table [] = []
concateneaza_table (x:xs) = x ++ (concateneaza_table xs)

-- Task 5
--Task auxiliare task 5
auxiliara :: ([String]->[String]->[String])->[String]->[[String]] -> [[String]]
auxiliara functie linie t = map(\x-> functie linie x) t

concateneazaTable :: [[[String]]] -> [[String]]
concateneazaTable [] = []
concateneazaTable (x:xs) = x ++ (concateneazaTable xs)

cartesian :: (Row -> Row -> Row) -> [ColumnName] -> Table -> Table -> Table
cartesian new_row_function new_column_names t1 t2 = [new_column_names]++ 
                concateneazaTable ( map (\linie -> auxiliara new_row_function linie (drop 1 t2) ) (drop 1 t1) )

-- Functii auxiliare task 6
-- Extract from a table those columns specified by name in the first argument. 

f_auxiliara :: [String] -> [String] -> [String]
f_auxiliara my_row lista_cuvinte_de_extras = 
    if ( (head my_row) `elem` lista_cuvinte_de_extras ) then my_row else [] 



projection_help :: [String] -> [[String]] -> [[String]]
projection_help _ [] = []
projection_help lista_cuvinte_de_extras (x:xs) = [ f_auxiliara x lista_cuvinte_de_extras ] ++ 
                                                                projection_help lista_cuvinte_de_extras xs 


my_projection :: [[String]] ->[[String]]
my_projection [] = []
my_projection (x:xs)
    | (x == [] ) = my_projection xs
    | otherwise = [x] ++ my_projection xs

-- Task 6

projection :: [ColumnName] -> Table -> Table
projection columns_to_extract t = transposeTable ( my_projection
                                                    (projection_help columns_to_extract (transposeTable t))) 

-- Task 7

-- Functii auxiliare task 7



filterTable :: (Value -> Bool) -> ColumnName -> Table -> Table
filterTable condition key_column t = [(head t )] ++ filter (\x -> condition 
                                                ( x !! (det_column key_column (head t) ) ) )  (drop 1 t) 


{-
    TASK SET 3
-}


-- 3.1

data Query =
    FromTable Table
    | AsList String Query
    | Sort String Query
    | ValueMap (Value -> Value) Query
    | RowMap (Row -> Row) [String] Query
    | VUnion Query Query
    | HUnion Query Query
    | TableJoin String Query Query
    | Cartesian (Row -> Row -> Row) [String] Query Query
    | Projection [String] Query
    | forall a. FEval a => Filter (FilterCondition a) Query -- 3.4
    | Graph EdgeOp Query -- 3.5


class Eval a where
    eval :: a ->QResult

instance Eval Query where
    eval (FromTable t) = Table t
    eval (AsList nume_string q) = List[""]
    eval (Sort colname query) = Table []
    eval (ValueMap op query) = Table []
    eval (RowMap op colnames query) = Table []
    eval (VUnion query1 query2) = Table []
    eval (HUnion query1 query2) = Table []
    eval (TableJoin colname query1 query2) = Table []
    eval (Cartesian op colnames query1 query2) = Table []
    eval (Projection colnames query) = Table []
    eval (Filter filter_conditie query1) = Table []
    eval (Graph edgeOp query) = Table []



instance Show QResult where
    show (List l) = show l
    show (Table t) = show t

-- 3.2 & 3.3

type FilterOp = Row -> Bool

data FilterCondition a =
    Eq String a |
    Lt String a |
    Gt String a |
    In String [a] |
    FNot (FilterCondition a) |
    FieldEq String String


class FEval a where
    feval :: [String] -> (FilterCondition a) -> FilterOp

instance FEval Float where
    feval lista (Eq nume_string parametru) =  \x->True
    feval lista (Lt nume_string parametru) = \x->True
    feval lista (Gt nume_string parametru) = \x->True
    feval lista (In nume_string lista_de_tip_a) = \x->True
    feval lista (FNot filter_condition ) = \x->True
    feval lista (FieldEq nume_string nume_string2) = \x->True

instance FEval String where
    feval lista (Eq nume_string parametru) =  \x->True
    feval lista (Lt nume_string parametru) = \x->True
    feval lista (Gt nume_string parametru) = \x->True
    feval lista (In nume_string lista_de_tip_a) = \x->True
    feval lista (FNot filter_condition ) = \x->True
    feval lista (FieldEq nume_string nume_string2) = \x->True

-- 3.4

-- where EdgeOp is defined:
type EdgeOp = Row -> Row -> Maybe Value

-- 3.5
similarities_query :: Query
similarities_query = FromTable []

-- 3.6 (Typos)
correct_table :: String -> Table -> Table -> Table
correct_table col csv1 csv2 = csv1
