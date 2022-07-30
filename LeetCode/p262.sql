# Write your MySQL query statement below
select
request_at as 'Day',
round(count(if(status!='completed',true,null)) / count(*), 2) as 'Cancellation Rate'
from Trips
left join Users as Clients on client_id = Clients.users_id
left join Users as Drivers on driver_id = Drivers.users_id
where Clients.banned = 'No' and Drivers.banned = 'No' and request_at between "2013-10-01" and "2013-10-03"
group by request_at
