# Write your MySQL query statement below
select A.Name as Employee from Employee as A
left join Employee as B
on A.managerId = B.id
where A.managerId is not null and A.salary > B.salary
