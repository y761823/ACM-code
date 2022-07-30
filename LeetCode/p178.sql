# Write your MySQL query statement below
select O.score, dense_rank() over(order by score desc) as 'rank'
from Scores as O
order by `rank`
