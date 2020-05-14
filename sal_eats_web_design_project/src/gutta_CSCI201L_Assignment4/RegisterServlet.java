package gutta_CSCI201L_Assignment4;

import java.io.IOException;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/RegisterServlet")
public class RegisterServlet extends HttpServlet{
	public static final long serialVersionUID = 1L;
	protected void service(HttpServletRequest request, HttpServletResponse response)
		throws ServletException, IOException{
		String username = request.getParameter("username");
		String email = request.getParameter("email");
		String password = request.getParameter("password");
		String confirm_password = request.getParameter("confirm-password");
		String next = "/login.jsp";
		if(!Database.verifyUserNotExists(username)) {
			//user already exists
			request.setAttribute("error", "ERROR: A user with that username already exists.");
		}else if(!password.contentEquals(confirm_password)) {
			request.setAttribute("error", "ERROR: Password and confirmed password must be equal.");
		}else{
			String hashed_password = Database.generateHash(password);
			Database.insertUser(username, email, hashed_password);
			int user_id = Database.getUserID(username,  password);
			request.getSession().setAttribute("user_id", user_id);
			next = "/index.jsp";
		}
		RequestDispatcher dispatch = getServletContext().getRequestDispatcher(next);
		dispatch.forward(request, response);
	}
}