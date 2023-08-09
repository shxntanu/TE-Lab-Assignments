# Assignment No 3 

(Based on Employee schema)  

- Employee( Emp_id, Dept_id, Emp_fname, Emp_lname, Emp_Position,    
                  Emp_salary,Emp_JoinDate)
- Dept ( Dept_id, Dept_name,location)
- Project( Proj_id,Dept_id ,Proj_Name,Proj_Location,Proj_cost,Proj_year)

Use the tables created in assignment no 2 and execute the following queries:  
1. Find Employee details and Department details using NATURAL JOIN.  
 2. Find the emp_fname,Emp_position,location,Emp_JoinDate who have same Dept id. 
 3. Find the Employee details ,Proj_id,Project cost who does not have Project       location as ‘Hyderabad’.
4. Find Department Name ,employee name, Emp_position for which project year  
     is 2020,
5. Display emp_position,D_name who have Project cost >30000
6.  Find the names of all the Projects that started in the year 2015.
7. List the Dept_name having no_of_emp=10  
8.Display the total number of employee who have joined  any project before 2009
  
9. Create a view showing the employee  and Department details.  
    10. Perform Manipulation on simple view-Insert, update, delete, drop view. 
