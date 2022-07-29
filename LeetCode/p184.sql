# Write your MySQL query statement below

# select Department.name as 'Department', A.name as 'Employee', salary
# from Employee as A
# left join Department
# on A.departmentId = Department.id
# where A.salary = (select max(B.salary) from Employee as B where B.departmentId = A.departmentId)

select Department.name as 'Department', Employee.name as 'Employee', salary
from Employee
left join Department
on departmentId = Department.id
where (departmentId, salary) in (select departmentId, max(salary) from Employee group by departmentId)
