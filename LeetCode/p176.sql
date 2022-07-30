# Write your MySQL query statement below
select ifnull((select salary
from Employee
group by salary
order by salary desc
limit 1,1), null) as 'SecondHighestSalary'
