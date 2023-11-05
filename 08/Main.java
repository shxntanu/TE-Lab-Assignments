package assignment8;

import java.util.*;
import java.sql.*;

public class Main
{
//	void select() {}
//	void insert() {}
//	void update() {}
//	void delete() {}
	
    public static void main(String[] args)
    {
        String url = "jdbc:mysql://10.10.15.233/te31301db";
        String username = "te31301";
        String password = "te31301";
        
        Connection con = null;
        Statement st;
        PreparedStatement ps;
        ResultSet rs;
        
        try
        {
        	// establish connection with database
            Class.forName("com.mysql.cj.jdbc.Driver");
            con = DriverManager.getConnection(url, username, password);
            st = con.createStatement();
            
            if (con != null && !con.isClosed())
            {
                System.out.println("Database connected!");
            }   
            else
            {
                System.out.println("Not connected.");
            }
            
            Scanner sc = new Scanner(System.in);
            int ch, id;
            double salary;
            String ans, name, position, output;
            
            do
            {
            	// operations menu
            	System.out.println("\n1. Select\n2. Insert\n3. Update\n4. Delete\n5. Drop");
                System.out.print("Enter choice: ");
                ch = sc.nextInt();
                
                if (ch == 5)
                {
                	sc.close();
                	break;
                }
                
                switch(ch)
                {
                case 1:  // select              	
              	
                	String query = "SELECT * FROM emp_table";
                	
                	st = con.createStatement();
                	rs = st.executeQuery(query);
                	
                	// display result
                	System.out.println("| ID |      Name      |  Position  |  Salary  |");
                	System.out.println("---------------------------------");
                	while (rs.next())
                	{
                		// indexing starts from 1
                		id = rs.getInt(1);
                		name = rs.getString(2);
                		position = rs.getString(3);
                		salary = rs.getDouble(4);
                		output = " %d  %s    %s    %f";
                		System.out.println(String.format(output, id, name, position, salary));
                	}
                	break;
                	
                case 2:  // insert
                	query = "INSERT INTO emp_table VALUES (?, ?, ?, ?)";
                	ps = con.prepareStatement(query);
                	
                	System.out.print("Enter ID: ");
                	id = sc.nextInt();
                	sc.nextLine();
                	
                	System.out.print("Enter Name: ");
                	name = sc.next();
                	sc.nextLine();
                	
                	System.out.print("Enter Position: ");
                	position = sc.nextLine();
                	
                	System.out.print("Enter Salary: ");
                	salary = sc.nextDouble();
                	
                	ps.setInt(1, id);
                	ps.setString(2, name);
                	ps.setString(3, position);
                	ps.setDouble(4, salary);
                	
                	int rowsInserted = ps.executeUpdate();
                	if (rowsInserted > 0)
                	{
                		System.out.println("Record inserted successfully!");
                	}
                	break;
                	
                case 3:  // update
                	query = "UPDATE emp_table SET emp_name = ?, emp_position = ?, emp_salary = ? WHERE emp_id = ?";
                	ps = con.prepareStatement(query);
                	
                	System.out.print("Enter ID: ");
                	id = sc.nextInt();
                	sc.nextLine();
                	
                	System.out.print("Enter Name: ");
                	name = sc.next();
                	sc.nextLine();
                	
                	System.out.print("Enter Position: ");
                	position = sc.nextLine();
                	
                	System.out.print("Enter Salary: ");
                	salary = sc.nextDouble();
                	
                	ps.setString(1, name);
                	ps.setString(2, position);
                	ps.setDouble(3, salary);
                	ps.setInt(4, id);
                	
                	int rowsUpdated = ps.executeUpdate();
                	if (rowsUpdated > 0)
                	{
                		System.out.println(rowsUpdated + " record(s) updated successfully!");
                	}
                	break;
                	
                case 4:  // delete
                	query = "DELETE FROM emp_table WHERE emp_id = ?";
                	ps = con.prepareStatement(query);
                	
                	System.out.print("Enter ID: ");
                	id = sc.nextInt();
                	
                	ps.setInt(1, id);
                	
                	int rowsDeleted = ps.executeUpdate();
                    if(rowsDeleted > 0){
                        System.out.println("Record deleted successfully!");
                    }
                }
                
                
                System.out.print("\nContinue? (y/n): ");
                ans = sc.next();
                
            } while (ans.equals("y") || ans.equals("Y"));
        }
        catch(SQLException e)
        {
        	System.out.println("An error occurred.");
            e.printStackTrace();
        }
        catch(ClassNotFoundException ce)
        {
        	System.out.println("An error occurred.");
            ce.printStackTrace();
        }
        
        // close connection
        try
        {
            con.close();
        }
        catch (SQLException e)
        {
            e.printStackTrace();
        }
        
    }
}
