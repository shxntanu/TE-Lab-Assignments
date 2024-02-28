<%@ page import="java.sql.*" %>
<%@ page contentType="text/html; charset=UTF-8" language="java" %>
<!DOCTYPE html>
<html>
<head>
    <title>Display Students</title>
</head>
<body>
    <h1>Students Information</h1>
    <table border="1">
        <tr>
            <th>Student ID</th>
            <th>Name</th>
            <th>Class</th>
            <th>Division</th>
            <th>City</th>
        </tr>
        <% 
            try {
                Class.forName("com.mysql.jdbc.Driver");
                Connection con = DriverManager.getConnection("jdbc:mysql://localhost:3306/school", "username", "password");
                Statement stmt = con.createStatement();
                ResultSet rs = stmt.executeQuery("SELECT * FROM students_info");
                while (rs.next()) {
        %>
        <tr>
            <td><%= rs.getInt("stud_id") %></td>
            <td><%= rs.getString("stud_name") %></td>
            <td><%= rs.getString("class") %></td>
            <td><%= rs.getString("division") %></td>
            <td><%= rs.getString("city") %></td>
        </tr>
        <% 
                }
                con.close();
            } catch (Exception e) {
                out.println(e);
            }
        %>
    </table>
</body>
</html>
