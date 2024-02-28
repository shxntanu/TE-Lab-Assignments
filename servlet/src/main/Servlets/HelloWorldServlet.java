import java.io.IOException;
import java.io.PrintWriter;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/hello")
public class HelloWorldServlet extends HttpServlet {

    private static final long serialVersionUID = 1L;

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        // Replace with your actual database connection details
        String url = "jdbc:mysql://localhost:3306/your_database_name";
        String user = "your_username";
        String password = "your_password";

        Connection conn = null;
        Statement stmt = null;
        ResultSet rs = null;

        try {
            Class.forName("com.mysql.cj.jdbc.Driver"); // Replace with your database driver
            conn = DriverManager.getConnection(url, user, password);

            stmt = conn.createStatement();
            String sql = "SELECT * FROM ebookshop"; // Modify SQL query according to your table
            rs = stmt.executeQuery(sql);

            response.setContentType("text/html");
            PrintWriter out = response.getWriter();
            out.println("<h1>E-Bookshop Inventory</h1>");
            out.println("<table border=\"1\">");
            out.println("<tr>");
            out.println("<th>Book ID</th>");
            out.println("<th>Book Title</th>");
            out.println("<th>Book Author</th>");
            out.println("<th>Book Price</th>");
            out.println("<th>Quantity</th>");
            out.println("</tr>");

            while (rs.next()) {
                int id = rs.getInt("book_id");
                String title = rs.getString("book_title");
                String author = rs.getString("book_author");
                double price = rs.getDouble("book_price");
                int quantity = rs.getInt("quantity");

                out.println("<tr>");
                out.println("<td>" + id + "</td>");
                out.println("<td>" + title + "</td>");
                out.println("<td>" + author + "</td>");
                out.println("<td>" + price + "</td>");
                out.println("<td>" + quantity + "</td>");
                out.println("</tr>");
            }

            out.println("</table>");

        } catch (ClassNotFoundException | SQLException e) {
            e.printStackTrace();
        } finally {
            if (rs != null) {
                try {
                    rs.close();
                } catch (SQLException e) {
                    e.printStackTrace();
                }
            }
            if (stmt != null) {
                try {
                    stmt.close();
                } catch (SQLException e) {
                    e.printStackTrace();
                }
            }
            if (conn != null) {
                try {
                    conn.close();
                } catch (SQLException e) {
                    e.printStackTrace();
                }
            }
        }
    }
}
