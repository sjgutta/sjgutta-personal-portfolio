package gutta_CSCI201L_Assignment4;

import java.io.IOException;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/LoginServlet")
public class LoginServlet extends HttpServlet{
	public static final long serialVersionUID = 1L;
	protected void service(HttpServletRequest request, HttpServletResponse response)
		throws ServletException, IOException{
		String username = request.getParameter("username");
		String password = request.getParameter("password");
		String next = "/login.jsp";
		if(Database.authenticateUser(username, password)) {
			next = "/index.jsp";
			int id = Database.getUserID(username, password);
			System.out.println(Integer.toString(id));
			request.getSession().setAttribute("user_id", id);
		}
		RequestDispatcher dispatch = getServletContext().getRequestDispatcher(next);
		dispatch.forward(request, response);
	}
}