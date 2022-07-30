# Write your MySQL query statement below
select Department.name as 'Department', S.name as 'Employee', salary as 'Salary'
from(
select departmentId, name, salary, dense_rank() over(partition by departmentId order by salary desc) as `rank`
from Employee
) as S
left join Department on departmentId = id
where `rank` <= 3
