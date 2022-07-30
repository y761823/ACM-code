# Write your MySQL query statement below
select A.id
from Weather as A
left join Weather as B
on date_sub(A.recordDate, interval 1 day) = B.recordDate
where A.temperature > B.temperature
